#include "src/block/submodel.hpp"
#include "src/solver/euler.hpp"
#include "src/solver/simulator.hpp"
#include "src/tires.hpp"
#include <gtest/gtest.h>

class TestTires : public testing::Test {
public:
  TestTires() { model_.add_block(lateral_slip_, {s_v_x_, s_v_y_}, {}); }

  void SetUp() override {}

protected:
  pooya::Submodel model_;
  LateralSlip lateral_slip_;

  pooya::ScalarSignal s_v_x_;
  pooya::ScalarSignal s_v_y_;
};

TEST_F(TestTires, assertPT1Behavior) {

  constexpr double tire_vlon{1.0};
  constexpr double t_start{5.0};
  constexpr double t_step_size{0.01};
  constexpr double tau = 0.5 / 1.0;

  pooya::Euler stepper;
  pooya::Simulator sim(
      model_,
      [&](pooya::Block &, double t) -> void {
        pooya_trace0;
        s_v_x_ = 1.0;
        (t > t_start) ? s_v_y_ = 1.0 : s_v_y_ = 0.0;
      },
      &stepper);

  double t{0.0};
  uint k{0};
  while (t < t_start + tau) {
    t += t_step_size;
    sim.run(t);
    k++;
  }

  constexpr double tire_vlat_final{1.0};
  constexpr double tire_vlat_start{0.0};
  constexpr double lateral_slip_expected =
      ((tire_vlat_final - tire_vlat_start) * (1 - std::exp(-1))) / tire_vlon;

  EXPECT_NEAR(lateral_slip_._s_alpha, lateral_slip_expected, 4e-3);
}
