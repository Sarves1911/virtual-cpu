#include "../include/clock.h"

bool Clock::tick() {
    m_time++; // Increment the internal time
    return true;
}