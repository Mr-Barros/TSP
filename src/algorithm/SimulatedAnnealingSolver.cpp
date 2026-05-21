#include "SimulatedAnnealingSolver.h"

#include "util/Random.h"

bool SimulatedAnnealingSolver::solve()
{
    Solution currentSolution = solution;

    currentSolution.evaluate();

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

    return true;
}

bool SimulatedAnnealingSolver::acceptWithProbability(double currentCost, double candidateCost, double temperature)
{
    double probability = exp(-(candidateCost - currentCost) / temperature);
    if (probability > 1)
        return true;

    return Random::randomDouble() < probability;
}