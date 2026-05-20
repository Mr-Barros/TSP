cmake_minimum_required(VERSION 4.2)
project(tsp)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(tsp
        src/algorithm/AbstractSolver.cpp
        src/algorithm/AbstractSolver.h
        src/input/Data.h
        src/algorithm/GraspSolver.cpp
        src/algorithm/GraspSolver.h
        src/input/Loader.cpp
        src/input/Loader.h
        src/Main.cpp
        src/algorithm/NearestNeighborSolver.cpp
        src/algorithm/NearestNeighborSolver.h
        src/algorithm/neighborhoods/Neighborhood.cpp
        src/algorithm/neighborhoods/Neighborhood.h
        src/util/Point.h
        src/util/Random.cpp
        src/util/Random.h
        src/algorithm/RandomSolver.cpp
        src/algorithm/RandomSolver.h
        src/algorithm/neighborhoods/Shift.cpp
        src/algorithm/neighborhoods/Shift.h
        src/util/Singleton.h
        src/output/Solution.cpp
        src/output/Solution.h
        src/algorithm/Solver.cpp
        src/algorithm/Solver.h
        src/algorithm/neighborhoods/Swap.cpp
        src/algorithm/neighborhoods/Swap.h
        src/util/Timer.cpp
        src/util/Timer.h
        src/algorithm/VNDSolver.cpp
        src/algorithm/VNDSolver.h
        src/input/Parameters.cpp
        src/input/Parameters.h
        src/algorithm/SimulatedAnnealingSolver.cpp
        src/algorithm/SimulatedAnnealingSolver.h)
