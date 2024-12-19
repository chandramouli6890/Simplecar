#include "src/tires.hpp"
#include "src/block/leaf.hpp"
#include "src/block/submodel.hpp"
#include "src/helper/trace.hpp"
#include "src/misc/gp-ios.hpp"
#include "src/solver/euler.hpp"
#include "src/solver/history.hpp"
#include "src/solver/simulator.hpp"
#include <iostream>

int main() {
  pooya_trace0;

  using milli = std::chrono::milliseconds;
  auto start = std::chrono::high_resolution_clock::now();

  // create pooya blocks
  LateralSlip model;

  // create pooya signals
  pooya::ScalarSignal vx("vx");
  pooya::ScalarSignal vy("vy");

  // setup the model
  model.connect({vx, vy}, {});

  pooya::Euler stepper;
  pooya::Simulator sim(
      model,
      [&](pooya::Block &, double t) -> void {
        pooya_trace0;
        vx = 1.0;
        (t > 5) ? vy = 1.0 : vy = 0.0;
      },
      &stepper);

  pooya::History history;
  history.track(model._s_alpha);

  uint k = 0;
  double t;
  while (pooya::arange(k, t, 0, 10, 0.01)) {
    sim.run(t);
    history.update(k, t);
    k++;
  }

  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "It took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " milliseconds\n";

  history.shrink_to_fit();

  Gnuplot gp;
  gp << "set xrange [0:" << history.nrows() - 1 << "]\n";
  gp << "set yrange [-0.1:1.0]\n";
  gp << "plot" << gp.file1d(history[model._s_alpha])
     << "with lines title 'x'\n";

  assert(pooya::helper::pooya_trace_info.size() == 1);

  return 0;
}
