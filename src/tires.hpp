#include "src/block/leaf.hpp"
#include "src/block/submodel.hpp"
#include "src/helper/trace.hpp"
#include "src/misc/gp-ios.hpp"
#include "src/solver/euler.hpp"
#include "src/solver/history.hpp"
#include "src/solver/simulator.hpp"

class LateralSlip : public pooya::Leaf {
protected:
  double _sigma;
  double _alpha;

public:
  LateralSlip() : pooya::Leaf(2, 0), _sigma(0.5), _alpha(0.0) {}

  pooya::ScalarSignal _s_v_x{"vx"};
  pooya::ScalarSignal _s_v_y{"vy"};
  pooya::ScalarSignal _s_alpha{"alpha"};
  pooya::ScalarSignal _s_alpha_d{"alpha"};

  bool connect(const pooya::Bus &ibus, const pooya::Bus &) override {
    pooya_trace0;

    if (!pooya::Leaf::connect(ibus))
      return false;

    _s_v_x.reset(scalar_input_at(0));
    _s_v_y.reset(scalar_input_at(1));

    _s_alpha.set_deriv_signal(_s_alpha_d);

    link_signal(_s_alpha, SignalLinkType::Input);
    link_signal(_s_alpha_d, SignalLinkType::Internal);

    return true;
  }

  void activation_function(double /*t*/) override {
    pooya_trace0;

    _s_alpha_d = (-_s_alpha * _s_v_x + _s_v_y) / _sigma;
  }

  void pre_step(double /*t*/) override { _s_alpha = _alpha; }

  void post_step(double /*t*/) override { _alpha = _s_alpha; }
};
