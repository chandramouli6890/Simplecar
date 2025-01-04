#include "src/block/gain.hpp"
#include "src/buses.hpp"
#include "src/solver/simulator.hpp"
#include <gtest/gtest.h>

class TestBuses : public testing::Test {
public:
  TestBuses(){};
  Buses buses_{"buses"};
};

TEST_F(TestBuses, assertBuses) {
  pooya::Gain gain(2.0);
  pooya::ScalarSignal s_x = buses_.scalar_at("vel.x");
  pooya::ScalarSignal s_y = buses_.scalar_at("vel.y");
  gain.connect(s_x, s_y);

  pooya::Simulator sim(
      gain, [&](pooya::Block &, double /*t*/) -> void { s_x = 10.0; });

  sim.init(0.0);

  std::cout << s_y << std::endl;

  EXPECT_DOUBLE_EQ(20.0, s_y);
}
