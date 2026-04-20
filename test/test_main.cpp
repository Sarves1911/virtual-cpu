#include "micro_test_framework.h"
#include "test_alu.cpp"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Hello There, Starting Test\n");
  TestRunner testrunner;
  testrunner.addSuite(std::make_unique<TestALUSuite>());

  testrunner.runTests();

  return 0;
}
