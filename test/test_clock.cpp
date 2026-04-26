#include "../include/clock.h"
#include "micro_test_framework.h"

class TestClockSuite : public TestSuite {

public:
  void runTests() {
    executeTest("clock ticking", [this] { this->testClockTick(); });
  }
  void onMount() { std::cout << "\n[SUITE] Test Clock Begin\n"; }
  void onDismount() { std::cout << "[SUITE] Test Clock End\n"; }

private:
  // Pretty trivial but test coverage is nice
  void testClockTick() {
    Clock clock;
    test_assert(clock.tick());
    test_assert(clock.getTime() == 1);
  }
};
