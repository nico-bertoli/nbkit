#pragma once
#include <cstdlib>
#include <cmath>
#include <cassert>

namespace nbkit
{
    namespace random_utils
    {
        inline double GetRandomDouble(double min, double max)
        {
            assert(min<=max);

            double r = rand() / static_cast<double>(RAND_MAX);
            return ((max - min) * r + min);
        }

        inline int GetRandomInt(int minInclusive, int maxInclusive)
        {
            assert(minInclusive <= maxInclusive);
            
            return minInclusive + std::rand() % (maxInclusive - minInclusive + 1);
        }

        inline bool GetRandomBool()
        {
            return GetRandomInt(0, 1) == 0;
        }
    }
}