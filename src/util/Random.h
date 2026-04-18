#pragma once

#include <random>
#include <algorithm>

class Random
{
public:
    static void seed(unsigned int seed);
    static unsigned int seed();

    // Generates a random integer on [0, std::numeric_limits<int>::max()] interval.
    static int randomInt();

    // Generates a random integer on [a, b] interval.
    static int randomInt(int a, int b);

    // Generates a random double on [0, 1) interval.
    static double randomDouble();

    // Generates a random double on [a, b) interval.
    static double randomDouble(double a, double b);

    // Shuffles vector.
    template<typename T>
    static void shuffle(std::vector<T>& vec)
    {
        std::shuffle(vec.begin(), vec.end(), engine);
    }

    // Shuffles vector.
    template<typename T>
    static void shuffle(const std::vector<T>::iterator& begin, const std::vector<T>::iterator& end)
    {
        std::shuffle(begin, end, engine);
    }

    // Returns a random element from the vector.
    template<typename T>
    static T& randomElem(std::vector<T>& vec)
    {
        return vec[randomInt(0, (int)vec.size() - 1)];
    }

    // Returns a random element from the vector.
    template<typename T>
    static const T& randomElem(const std::vector<T>& vec)
    {
        return vec[randomInt(0, (int)vec.size() - 1)];
    }

private:
    static unsigned int _seed;
    static std::mt19937 engine;
    static std::uniform_int_distribution<> uniformIntDistribution;
    static std::uniform_real_distribution<> uniformRealDistribution;
};
