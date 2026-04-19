
class TestSuite {
	public: 
		void runTests() {
		}
};


class TestRunner {
	public:
		void mount(TestSuite& testSuite);
		void unmount();
		void runTests();
	private:
		TestSuite* m_testSuite;
};
