#include <stdlib.h>
#include <stdio.h>
#include "test_alu.cpp"
#include "micro_test_framework.h"

int main() {
	printf("Hello There, Starting Test\n");
	TestRunner testrunner;		
	testrunner.addSuite(std::make_unique<TestALUSuite>());

	testrunner.runTests();

	return 0;
}
