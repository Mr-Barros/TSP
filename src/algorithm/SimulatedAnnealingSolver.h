#pragma once

#include "AbstractSolver.h"
#include "neighborhoods/Neighborhood.h"
#include "neighborhoods/Shift.h"

class SimulatedAnnealingSolver : public AbstractSolver {
public:

    bool solve() override;

private:
    Neighborhood* neighborhood = new Shift();
    Neighborhood* perturbation = new Shift();

    bool acceptWithProbability(double currentCost, double candidateCost, double temperature);
};
