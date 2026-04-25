#include "micro_test_framework.h"
#include "test_alu.cpp"
#include "test_clock.cpp"
#include "test_cpu.cpp"
#include "test_mem.cpp"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Hello There, Starting Test\n");
  TestRunner testrunner;
  testrunner.addSuite(std::make_unique<TestALUSuite>());
  testrunner.addSuite(std::make_unique<TestClockSuite>());
  testrunner.addSuite(std::make_unique<TestMemoryManagerSuite>());
  testrunner.addSuite(std::make_unique<TestCPUSuite>());

  testrunner.runTests();

  return 0;
}
