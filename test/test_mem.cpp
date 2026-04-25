#include "../include/memory.h"
#include "micro_test_framework.h"

class TestMemoryManagerSuite : public TestSuite {
public:
  void runTests() {
    executeTest("TestReset", [this] { this->testReset(); });
    executeTest("TestWriteRead", [this] { this->testWriteRead(); });
    executeTest("TestWriteReadBoundary",
                [this] { this->testWriteReadBoundary(); });
    executeTest("TestMultipleWrites", [this] { this->testMultipleWrites(); });
    executeTest("TestOverwriteValue", [this] { this->testOverwriteValue(); });
  }

  void onMount() { std::cout << "\n[SUITE] Test Memory Begin\n"; }
  void onDismount() { std::cout << "\n[SUITE] Test Memory End\n"; }

private:
  // Singleton member
  MemoryManager m_mem;

  void testReset() {
    m_mem.reset();
    test_assert(m_mem.read(0) == 0);
    test_assert(m_mem.read(ISA::MAX_MEM_ADDR) == 0);
    test_assert(m_mem.read(0x50) == 0);
  }

  void testWriteRead() {
    m_mem.reset();
    m_mem.write(0x10, 0xDEAD);
    test_assert(m_mem.read(0x10) == 0xDEAD);
  }

  void testWriteReadBoundary() {
    m_mem.reset();
    m_mem.write(0, 0x1234);
    m_mem.write(ISA::MAX_MEM_ADDR, 0x5678);
    test_assert(m_mem.read(0) == 0x1234);
    test_assert(m_mem.read(ISA::MAX_MEM_ADDR) == 0x5678);
  }

  void testMultipleWrites() {
    m_mem.reset();
    for (uint16_t i = 0; i < 10; i++) {
      m_mem.write(i, i * 0x111);
    }
    for (uint16_t i = 0; i < 10; i++) {
      test_assert(m_mem.read(i) == i * 0x111);
    }
  }

  void testOverwriteValue() {
    m_mem.reset();
    m_mem.write(0x20, 0xAAAA);
    test_assert(m_mem.read(0x20) == 0xAAAA);
    m_mem.write(0x20, 0x5555);
    test_assert(m_mem.read(0x20) == 0x5555);
  }
};
