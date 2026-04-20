#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Attempt to define structure on test suites
// The test runner will mount a test suite, execute tests, and unmount
// The runner then proceeds to the next set of suites

// The test assert should print an red error if wrong - vibed
#define test_assert(condition)                                                 \
  if (!(condition)) {                                                          \
    std::cout << "\n      \033[31m[FAIL]\033[0m " << #condition                \
              << " (Line: " << __LINE__ << ")";                                \
    m_suitePassed = false;                                                     \
    m_currentTestFailed = true;                                                \
  }

class TestSuite {
protected:
  bool m_suitePassed = true;
  bool m_currentTestFailed = false;

  // This abstracts the printing logic - vibed, so it's kinda ugly
  void executeTest(std::string testName, std::function<void()> testFunc) {
    m_currentTestFailed = false; // Reset for this specific test
    std::cout << "  -> " << testName << "... ";
    testFunc(); // Run the actual test code
    if (m_currentTestFailed) {
      std::cout << "\n";
    } else {
      std::cout << "\033[32mPASSED\033[0m\n"; // Green PASS
    }
  }

public:
  virtual ~TestSuite() = default;
  virtual void runTests() = 0;
  virtual void onMount() = 0;
  virtual void onDismount() = 0;
};

class TestRunner {
public:
  void addSuite(std::unique_ptr<TestSuite> suite);
  void mount(TestSuite &testSuite);
  void dismount();
  void runTests();

private:
  std::vector<std::unique_ptr<TestSuite>> m_suites;
};
