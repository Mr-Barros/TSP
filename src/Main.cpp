#include <iostream>
#include <format>

#include "input/Loader.h"
#include "input/Data.h"

#include "algorithm/Solver.h"

#include "util/Timer.h"

using namespace std;

int main()
{
	Loader loader;
	if (!loader.load("data/eil101.tsp"))
		throw runtime_error("Failed to load data");

	const Data& data = Data::getInstance();
	cout << "Data loaded: " << data.name << " (" << data.type << "), bks: " << data.bks << endl;

	Timer timer;

	Solver solver;
	solver.solve();

	cout << format("Time: {:.6f}s", timer.stop()) << endl;

	return 0;
}
