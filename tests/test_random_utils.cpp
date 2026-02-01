#include <gtest/gtest.h>
#include <nbkit/random_utils.h>
#include <cstdlib>
#include <set>
#include <algorithm>

namespace random_utils = nbkit::random_utils;

class RandomUtilsTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Seed random number generator for reproducible tests
        std::srand(42);
    }
};

//-------------------------------------------------------- GetRandomDouble

TEST_F(RandomUtilsTest, GetRandomDouble_WithinRange)
{
    const double min = 0.0;
    const double max = 10.0;
    const int iterations = 1000;
    
    for (int i = 0; i < iterations; ++i)
    {
        double value = random_utils::GetRandomDouble(min, max);
        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}

TEST_F(RandomUtilsTest, GetRandomDouble_NegativeRange)
{
    const double min = -10.0;
    const double max = -5.0;
    const int iterations = 1000;
    
    for (int i = 0; i < iterations; ++i)
    {
        double value = random_utils::GetRandomDouble(min, max);
        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}

TEST_F(RandomUtilsTest, GetRandomDouble_MixedRange)
{
    const double min = -5.0;
    const double max = 5.0;
    const int iterations = 1000;
    
    for (int i = 0; i < iterations; ++i)
    {
        double value = random_utils::GetRandomDouble(min, max);
        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}

TEST_F(RandomUtilsTest, GetRandomDouble_SameMinMax)
{
    const double value = 42.5;
    const int iterations = 100;
    
    for (int i = 0; i < iterations; ++i)
    {
        double result = random_utils::GetRandomDouble(value, value);
        EXPECT_DOUBLE_EQ(result, value);
    }
}

TEST_F(RandomUtilsTest, GetRandomDouble_ProducesVariety)
{
    const double min = 0.0;
    const double max = 100.0;
    const int iterations = 1000;
    std::set<int> unique_values;
    
    for (int i = 0; i < iterations; ++i)
    {
        double value = random_utils::GetRandomDouble(min, max);
        // Convert to int for set comparison (with some precision loss)
        unique_values.insert(static_cast<int>(value));
    }
    
    // Should produce many different values
    EXPECT_GT(unique_values.size(), 50);
}

//-------------------------------------------------------- GetRandomInt

TEST_F(RandomUtilsTest, GetRandomInt_WithinRange)
{
    const int min = 0;
    const int max = 10;
    const int iterations = 1000;
    
    for (int i = 0; i < iterations; ++i)
    {
        int value = random_utils::GetRandomInt(min, max);
        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}

TEST_F(RandomUtilsTest, GetRandomInt_NegativeRange)
{
    const int min = -10;
    const int max = -5;
    const int iterations = 1000;
    
    for (int i = 0; i < iterations; ++i)
    {
        int value = random_utils::GetRandomInt(min, max);
        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}

TEST_F(RandomUtilsTest, GetRandomInt_MixedRange)
{
    const int min = -5;
    const int max = 5;
    const int iterations = 1000;
    
    for (int i = 0; i < iterations; ++i)
    {
        int value = random_utils::GetRandomInt(min, max);
        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}

TEST_F(RandomUtilsTest, GetRandomInt_SameMinMax)
{
    const int value = 42;
    const int iterations = 100;
    
    for (int i = 0; i < iterations; ++i)
    {
        int result = random_utils::GetRandomInt(value, value);
        EXPECT_EQ(result, value);
    }
}

TEST_F(RandomUtilsTest, GetRandomInt_SingleValueRange)
{
    const int min = 7;
    const int max = 7;
    const int iterations = 100;
    
    for (int i = 0; i < iterations; ++i)
    {
        int result = random_utils::GetRandomInt(min, max);
        EXPECT_EQ(result, 7);
    }
}

TEST_F(RandomUtilsTest, GetRandomInt_ProducesVariety)
{
    const int min = 0;
    const int max = 100;
    const int iterations = 1000;
    std::set<int> unique_values;
    
    for (int i = 0; i < iterations; ++i)
    {
        int value = random_utils::GetRandomInt(min, max);
        unique_values.insert(value);
    }
    
    // Should produce many different values
    EXPECT_GT(unique_values.size(), 50);
}

//-------------------------------------------------------- GetRandomBool

TEST_F(RandomUtilsTest, GetRandomBool_ProducesBothValues)
{
    const int iterations = 1000;
    bool found_true = false;
    bool found_false = false;
    
    for (int i = 0; i < iterations; ++i)
    {
        bool value = random_utils::GetRandomBool();
        if (value) found_true = true;
        else found_false = true;
        
        if (found_true && found_false) break;
    }
    
    EXPECT_TRUE(found_true);
    EXPECT_TRUE(found_false);
}

TEST_F(RandomUtilsTest, GetRandomBool_StatisticalDistribution)
{
    const int iterations = 10000;
    int true_count = 0;
    int false_count = 0;
    
    for (int i = 0; i < iterations; ++i)
    {
        if (random_utils::GetRandomBool())
            ++true_count;
        else
            ++false_count;
    }
    
    double true_ratio = static_cast<double>(true_count) / iterations;
    EXPECT_GT(true_ratio, 0.40);
    EXPECT_LT(true_ratio, 0.60);
}
