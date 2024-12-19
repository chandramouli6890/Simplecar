#include "src/block/submodel.hpp"
#include "src/misc/gp-ios.hpp"
#include "src/solver/euler.hpp"
#include "src/solver/history.hpp"
#include "src/solver/simulator.hpp"
#include "src/tires.hpp"
#include <filesystem>
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

  pooya::History history;
  history.track(lateral_slip_._s_alpha);

  double t{0.0};
  uint k{0};
  while (t < t_start + tau) {
    t += t_step_size;
    sim.run(t);
    history.update(k, t);
    k++;
  }
  history.shrink_to_fit();

  constexpr double tire_vlat_final{1.0};
  constexpr double tire_vlat_start{0.0};
  constexpr double lateral_slip_expected =
      ((tire_vlat_final - tire_vlat_start) * (1 - std::exp(-1))) / tire_vlon;

  EXPECT_NEAR(lateral_slip_._s_alpha, lateral_slip_expected, 4e-3);

  std::string file_name = "test_plot.png";
  std::string file_path =
      std::filesystem::current_path().string() + "/" + file_name;

  std::string search_pattern = "__main__";
  size_t pos = file_path.find(search_pattern);
  if (pos != std::string::npos)
    std::cout << file_path.substr(pos + search_pattern.length(),
                                  file_path.length())
              << std::endl;

  Gnuplot gp;
  gp << "set terminal png\n"; // Use PNG terminal
  gp << "set output '" << file_name << "'\n";
  gp << "set xrange [0:" << history.nrows() - 1 << "]\n";
  gp << "set yrange [-0.1:1.0]\n";
  gp << "plot" << gp.file1d(history[lateral_slip_._s_alpha])
     << "with lines title 'x'\n";
}
