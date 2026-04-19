#pragma once

#include <sys/types.h>
class Clock {

	public: 
		Clock() {
			m_time = 0;
		}
		bool tick();
	private:
		uint m_time;
};
