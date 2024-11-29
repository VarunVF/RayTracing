#pragma once

#include <chrono>


// Simple scope-based timer.
// Starts timing when constructed and ends timing when destructed (goes out of scope).
class Timer
{
public:
	Timer();				// Start the timer
	~Timer();				// End the timer

private:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
};

