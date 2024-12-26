#include "Timer.hpp"

#include <iostream>


Timer::Timer()
{
	start = std::chrono::steady_clock::now();
	end = start;
}

Timer::~Timer()
{
	end = std::chrono::steady_clock::now();
	const std::chrono::duration<double> elapsed_seconds{ end - start };
	std::cout << "Time elapsed: " << elapsed_seconds.count() * 1000 << " milliseconds\n";
}
