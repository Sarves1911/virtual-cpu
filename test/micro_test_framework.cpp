#include "micro_test_framework.h"
#include <memory>
#include <vector>

void TestRunner::addSuite(std::unique_ptr<TestSuite> suite) {
  m_suites.push_back(std::move(suite));
}

void TestRunner::runTests() {
  for (auto &suite : m_suites) {
    suite->onMount();
    suite->runTests();
    suite->onDismount();
  }
}
