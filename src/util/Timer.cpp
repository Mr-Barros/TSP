#include "Timer.h"

using namespace std;
using namespace std::chrono;

Timer::Timer(bool started)
{
	running = false;
	if (started) start();
	else total = 0;
}

void Timer::start()
{
	if (running) return;
	start_point = system_clock::now();
	running = true;
}

double Timer::lap()
{
	if (!running) return numeric_limits<double>::infinity();
	auto x = system_clock::now();
	return (total = duration_cast<microseconds>(x - start_point).count() / 1'000'000.0);
}

double Timer::stop()
{
	double temp = lap();
	running = false;
	return temp;
}
