#pragma once

#include <cassert>
#include <cmath>
#include <cstdlib>

namespace nbkit
{
    namespace random_utils
    {
        inline double GetRandomDouble(double min, double max)
        {
            assert(min <= max);

            double r = std::rand() / static_cast<double>(RAND_MAX);
            return ((max - min) * r + min);
        }

        inline int GetRandomInt(int min_inclusive, int max_inclusive)
        {
            assert(min_inclusive <= max_inclusive);

            return min_inclusive + std::rand() % (max_inclusive - min_inclusive + 1);
        }

        inline bool GetRandomBool() { return GetRandomInt(0, 1) == 0; }
    }
}