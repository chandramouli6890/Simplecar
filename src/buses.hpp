#include "src/block/submodel.hpp"

class Buses : public pooya::Bus {
public:
  Buses(const std::string &name)
      : pooya::Bus( //
            name,   //
            {
                {"vel", pooya::Bus( //
                            "vel",  //
                            {
                                {"x", pooya::ScalarSignal("x")},
                                {"y", pooya::ScalarSignal("y")},
                            })},
                // {"slip", pooya::Bus( //
                //              "slip", //
                //              {
                //                  {"x", pooya::ScalarSignal("x")},
                //                  {"y", pooya::ScalarSignal("y")},
                //              })},
            }) {}
};
