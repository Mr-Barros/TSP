#pragma once

#include "AbstractSolver.h"

class SimulatedAnnealingSolver : public AbstractSolver {
public:

    bool solve() override;
};
