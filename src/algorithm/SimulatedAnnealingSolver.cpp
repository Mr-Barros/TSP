#include "SimulatedAnnealingSolver.h"

#include <iostream>

#include "NearestNeighborSolver.h"
#include "util/Random.h"

using namespace std;

bool SimulatedAnnealingSolver::solve()
{
    constructiveSolver->solve();
    solution = constructiveSolver->solution;
    solution.evaluate();
    Solution currentSolution = solution;

    double temperature = 10000;
    double decayRate = 0.995;

    while (temperature > 1) {
        Solution candidateSolution = currentSolution;
        perturbation->randomMove(candidateSolution);
        candidateSolution.evaluate();

        if (acceptWithProbability(currentSolution.cost, candidateSolution.cost, temperature))
        {
            currentSolution = candidateSolution;
            neighborhood->localSearch(currentSolution);
            currentSolution.evaluate();

            if (currentSolution.cost < solution.cost)
                solution = currentSolution;
        }

        temperature *= decayRate;
    }

    cout << "SimulatedAnnealingSolver: " << solution << endl;
    return true;
}

bool SimulatedAnnealingSolver::acceptWithProbability(double currentCost, double candidateCost, double temperature)
{
    double probability = exp(-(candidateCost - currentCost) / temperature);
    if (probability > 1)
        return true;

    return Random::randomDouble() < probability;
}