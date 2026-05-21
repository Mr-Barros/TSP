#pragma once

#include <string>

#include "util/Singleton.h"

class Parameters : public Singleton<Parameters>
{
    friend class Singleton;
public:
    bool load(int argc, const char* argv[]);

    enum SolverType
    {
        Random,
        NearestNeighbor,
        GRASP,
        VariableNeighborhoodDecent,
        Christofides,
    };

    std::string inputFile = "data/eil101.tsp";
    SolverType solverType = Christofides;

private:
    static bool help(const std::string& msg = "");
};
