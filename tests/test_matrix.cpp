#include <gtest/gtest.h>
#include <nbkit/matrix.h>
#include <vector>
#include <algorithm>
#include <numeric>

template<typename T>
using Matrix = nbkit::Matrix<T>;

class MatrixTest : public ::testing::Test
{
};

//-------------------------------------------------------- constructor

TEST_F(MatrixTest, DefaultConstructor)
{
    Matrix<int> matrix;
    EXPECT_EQ(matrix.GetSizeX(), 0);
    EXPECT_EQ(matrix.GetSizeY(), 0);
}

TEST_F(MatrixTest, ConstructorWithWidth)
{
    Matrix<int> matrix(5);
    EXPECT_EQ(matrix.GetSizeX(), 5);
    EXPECT_EQ(matrix.GetSizeY(), 1);
}

TEST_F(MatrixTest, ConstructorWithWidthAndVector)
{
    Matrix<int> matrix(3, std::vector<int>{0, 1, 2, 3, 4, 5});

    EXPECT_EQ(matrix.GetSizeX(), 3);
    EXPECT_EQ(matrix.GetSizeY(), 2);
    
    EXPECT_EQ(matrix.Get(0, 0), 0);
    EXPECT_EQ(matrix.Get(1, 0), 1);
    EXPECT_EQ(matrix.Get(2, 0), 2);
    EXPECT_EQ(matrix.Get(0, 1), 3);
    EXPECT_EQ(matrix.Get(1, 1), 4);
    EXPECT_EQ(matrix.Get(2, 1), 5);
}

//-------------------------------------------------------- resize

TEST_F(MatrixTest, IncreaseSizeY)
{
    Matrix<int> matrix(2);
    EXPECT_EQ(matrix.GetSizeY(), 1);
    
    matrix.IncreaseSizeY();
    EXPECT_EQ(matrix.GetSizeY(), 2);
    
    matrix.IncreaseSizeY();
    EXPECT_EQ(matrix.GetSizeY(), 3);
    
    // Verify old data is preserved
    matrix.Get(0, 0) = 10;
    matrix.Get(1, 0) = 20;
    matrix.IncreaseSizeY();
    
    EXPECT_EQ(matrix.Get(0, 0), 10);
    EXPECT_EQ(matrix.Get(1, 0), 20);
    EXPECT_EQ(matrix.GetSizeY(), 4);
}

TEST_F(MatrixTest, Resize)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    EXPECT_EQ(matrix.GetSizeX(), 2);
    EXPECT_EQ(matrix.GetSizeY(), 2);
    
    matrix.Resize(3, 4);
    EXPECT_EQ(matrix.GetSizeX(), 3);
    EXPECT_EQ(matrix.GetSizeY(), 4);
}

//-------------------------------------------------------- clear

TEST_F(MatrixTest, Clear)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    EXPECT_NE(matrix.GetSizeX(), 0);
    
    matrix.Clear();
    EXPECT_EQ(matrix.GetSizeX(), 0);
    EXPECT_EQ(matrix.GetSizeY(), 0);
}

//-------------------------------------------------------- iterator tests

TEST_F(MatrixTest, IteratorStart)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    
    auto it_begin = matrix.begin();
    EXPECT_EQ(*it_begin, 0);
}

TEST_F(MatrixTest, IteratorEnd)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});

    auto end_it = matrix.end();
    EXPECT_EQ(*(--end_it), 5);
}

TEST_F(MatrixTest, IteratorPreIncrement)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    Matrix<int> matrix(3, vec);

    auto it = matrix.begin();
    EXPECT_EQ(*(++it),1);
    EXPECT_EQ(*(++it),2);
}

TEST_F(MatrixTest, IteratorPostIncrement)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    Matrix<int> matrix(3, vec);

    auto it = matrix.begin();
    EXPECT_EQ(*(it++),0);
    EXPECT_EQ(*(it++),1);
}

TEST_F(MatrixTest, IteratorPreDecrement)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    Matrix<int> matrix(3, vec);

    auto it = matrix.end();
    --it;

    EXPECT_EQ(*(--it),4);
    EXPECT_EQ(*(--it),3);
}

TEST_F(MatrixTest, IteratorPostDecrement)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    Matrix<int> matrix(3, vec);

    auto it = matrix.end();
    --it;

    EXPECT_EQ(*(it--),5);
    EXPECT_EQ(*(it--),4);
}

TEST_F(MatrixTest, IteratorJumpForward)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    
    auto it = matrix.begin();
    EXPECT_EQ(*(it + 2), 2);
    EXPECT_EQ(*(it + 4), 4);
}

TEST_F(MatrixTest, IteratorJumpBack)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});

    auto it_end = matrix.end();
    --it_end;
    EXPECT_EQ(*(it_end - 2), 3);
    EXPECT_EQ(*(it_end - 4), 1);
}

TEST_F(MatrixTest, IteratorArithmetic)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    auto it = matrix.begin();
    auto it2 = it + 3;

    EXPECT_EQ(it2 - it, 3);
}

TEST_F(MatrixTest, IteratorPlusEquals)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    auto it = matrix.begin();

    it += 2;
    EXPECT_EQ(*it, 2);

    it += 2;
    EXPECT_EQ(*it, 4);
}

TEST_F(MatrixTest, IteratorMinusEquals)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    auto it = matrix.end();
    --it;

    it -= 2;
    EXPECT_EQ(*it, 3);

    it -= 2;
    EXPECT_EQ(*it, 1);
}

TEST_F(MatrixTest, IteratorComparisonLessThan)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it1 < it2);
    EXPECT_TRUE(it2 < it3);
}

TEST_F(MatrixTest, IteratorComparisonLessThanOrEqual)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it1 <= it2);
    EXPECT_TRUE(it2 <= it3);
    EXPECT_TRUE(it1 <= it1);
}

TEST_F(MatrixTest, IteratorComparisonGreaterThan)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it2 > it1);
    EXPECT_TRUE(it3 > it2);
}

TEST_F(MatrixTest, IteratorComparisonGreaterThanOrEqual)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it2 >= it1);
    EXPECT_TRUE(it3 >= it2);
    EXPECT_TRUE(it1 >= it1);
}

TEST_F(MatrixTest, IteratorComparisonEquality)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin();
    
    EXPECT_TRUE(it1 == it1);
    EXPECT_TRUE(it1 == it2);
}

TEST_F(MatrixTest, IteratorComparisonInequality)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it1 != it2);
    EXPECT_TRUE(it2 != it3);
    EXPECT_TRUE(it1 != it3);
}

TEST_F(MatrixTest, IteratorSubscript)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it = matrix.begin();
    EXPECT_EQ(it[0], 0);
    EXPECT_EQ(it[1], 1);
    EXPECT_EQ(it[2], 2);
    EXPECT_EQ(it[3], 3);
}

TEST_F(MatrixTest, IteratorRangeBasedFor)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    Matrix<int> matrix(3, vec);
    
    std::vector<int> result;
    for (auto& value : matrix)
        result.push_back(value);
    
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result, vec);
}

TEST_F(MatrixTest, IteratorModifyThroughIterator)
{
    Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    for (auto& value : matrix)
        value *= 2;
    
    EXPECT_EQ(matrix.Get(0, 0), 0);
    EXPECT_EQ(matrix.Get(1, 0), 2);
    EXPECT_EQ(matrix.Get(0, 1), 4);
    EXPECT_EQ(matrix.Get(1, 1), 6);
}

TEST_F(MatrixTest, IteratorSTLFind)
{
    Matrix<int> matrix(3, std::vector<int>{3, 1, 4, 1, 5, 9});
    
    auto it = std::find(matrix.begin(), matrix.end(), 4);
    EXPECT_NE(it, matrix.end());
    EXPECT_EQ(*it, 4);
}

TEST_F(MatrixTest, IteratorSTLCount)
{
    Matrix<int> matrix(3, std::vector<int>{3, 1, 4, 1, 5, 9});
    
    EXPECT_EQ(std::count(matrix.begin(), matrix.end(), 1), 2);
}

TEST_F(MatrixTest, IteratorSTLAccumulate)
{
    Matrix<int> matrix(3, std::vector<int>{3, 1, 4, 1, 5, 9});
    
    int sum = std::accumulate(matrix.begin(), matrix.end(), 0);
    EXPECT_EQ(sum, 23);
}

TEST_F(MatrixTest, IteratorSTLFill)
{
    Matrix<int> matrix(3, std::vector<int>{3, 1, 4, 1, 5, 9});
    
    std::fill(matrix.begin(), matrix.end(), 42);
    EXPECT_EQ(matrix.Get(0, 0), 42);
    EXPECT_EQ(matrix.Get(2, 1), 42);
}

//-------------------------------------------------------- Const Iterator Tests

TEST_F(MatrixTest, ConstIteratorStart)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    
    auto it_begin = matrix.begin();
    EXPECT_EQ(*it_begin, 0);
}

TEST_F(MatrixTest, ConstIteratorEnd)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});

    auto end_it = matrix.end();
    EXPECT_EQ(*(--end_it), 5);
}

TEST_F(MatrixTest, ConstIteratorPreIncrement)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    const Matrix<int> matrix(3, vec);

    auto it = matrix.begin();
    EXPECT_EQ(*(++it), 1);
    EXPECT_EQ(*(++it), 2);
}

TEST_F(MatrixTest, ConstIteratorPostIncrement)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    const Matrix<int> matrix(3, vec);

    auto it = matrix.begin();
    EXPECT_EQ(*(it++), 0);
    EXPECT_EQ(*(it++), 1);
}

TEST_F(MatrixTest, ConstIteratorPreDecrement)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    const Matrix<int> matrix(3, vec);

    auto it = matrix.end();
    --it;

    EXPECT_EQ(*(--it), 4);
    EXPECT_EQ(*(--it), 3);
}

TEST_F(MatrixTest, ConstIteratorPostDecrement)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    const Matrix<int> matrix(3, vec);

    auto it = matrix.end();
    --it;

    EXPECT_EQ(*(it--), 5);
    EXPECT_EQ(*(it--), 4);
}

TEST_F(MatrixTest, ConstIteratorJumpForward)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    
    auto it = matrix.begin();
    EXPECT_EQ(*(it + 2), 2);
    EXPECT_EQ(*(it + 4), 4);
}

TEST_F(MatrixTest, ConstIteratorJumpBack)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});

    auto it_end = matrix.end();
    --it_end;
    EXPECT_EQ(*(it_end - 2), 3);
    EXPECT_EQ(*(it_end - 4), 1);
}

TEST_F(MatrixTest, ConstIteratorArithmetic)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    auto it = matrix.begin();
    auto it2 = it + 3;

    EXPECT_EQ(it2 - it, 3);
}

TEST_F(MatrixTest, ConstIteratorPlusEquals)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    auto it = matrix.begin();

    it += 2;
    EXPECT_EQ(*it, 2);

    it += 2;
    EXPECT_EQ(*it, 4);
}

TEST_F(MatrixTest, ConstIteratorMinusEquals)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3, 4, 5});
    auto it = matrix.end();
    --it;

    it -= 2;
    EXPECT_EQ(*it, 3);

    it -= 2;
    EXPECT_EQ(*it, 1);
}

TEST_F(MatrixTest, ConstIteratorComparisonLessThan)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it1 < it2);
    EXPECT_TRUE(it2 < it3);
}

TEST_F(MatrixTest, ConstIteratorComparisonLessThanOrEqual)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it1 <= it2);
    EXPECT_TRUE(it2 <= it3);
    EXPECT_TRUE(it1 <= it1);
}

TEST_F(MatrixTest, ConstIteratorComparisonGreaterThan)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it2 > it1);
    EXPECT_TRUE(it3 > it2);
}

TEST_F(MatrixTest, ConstIteratorComparisonGreaterThanOrEqual)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it2 >= it1);
    EXPECT_TRUE(it3 >= it2);
    EXPECT_TRUE(it1 >= it1);
}

TEST_F(MatrixTest, ConstIteratorComparisonEquality)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin();
    
    EXPECT_TRUE(it1 == it1);
    EXPECT_TRUE(it1 == it2);
}

TEST_F(MatrixTest, ConstIteratorComparisonInequality)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it1 = matrix.begin();
    auto it2 = matrix.begin() + 2;
    auto it3 = matrix.end();
    
    EXPECT_TRUE(it1 != it2);
    EXPECT_TRUE(it2 != it3);
    EXPECT_TRUE(it1 != it3);
}

TEST_F(MatrixTest, ConstIteratorSubscript)
{
    const Matrix<int> matrix(2, std::vector<int>{0, 1, 2, 3});
    
    auto it = matrix.begin();
    EXPECT_EQ(it[0], 0);
    EXPECT_EQ(it[1], 1);
    EXPECT_EQ(it[2], 2);
    EXPECT_EQ(it[3], 3);
}

TEST_F(MatrixTest, ConstIteratorRangeBasedFor)
{
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    const Matrix<int> matrix(3, vec);
    
    std::vector<int> result;
    for (const auto& value : matrix)
        result.push_back(value);
    
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result, vec);
}

TEST_F(MatrixTest, ConstIteratorSTLFind)
{
    const Matrix<int> matrix(3, std::vector<int>{3, 1, 4, 1, 5, 9});
    
    auto it = std::find(matrix.begin(), matrix.end(), 4);
    EXPECT_NE(it, matrix.end());
    EXPECT_EQ(*it, 4);
}

TEST_F(MatrixTest, ConstIteratorSTLCount)
{
    const Matrix<int> matrix(3, std::vector<int>{3, 1, 4, 1, 5, 9});
    
    EXPECT_EQ(std::count(matrix.begin(), matrix.end(), 1), 2);
}

TEST_F(MatrixTest, ConstIteratorSTLAccumulate)
{
    const Matrix<int> matrix(3, std::vector<int>{3, 1, 4, 1, 5, 9});
    
    int sum = std::accumulate(matrix.begin(), matrix.end(), 0);
    EXPECT_EQ(sum, 23);
}

//-------------------------------------------------------- Edge Cases

TEST_F(MatrixTest, ZeroWidthMatrix)
{
    Matrix<int> matrix(0);
    EXPECT_EQ(matrix.GetSizeX(), 0);
    EXPECT_EQ(matrix.GetSizeY(), 0);
    EXPECT_EQ(matrix.begin(), matrix.end());
}

TEST_F(MatrixTest, LargeMatrix)
{
    Matrix<int> matrix(100);
    matrix.Resize(100, 200);
    EXPECT_EQ(matrix.GetSizeX(), 100);
    EXPECT_EQ(matrix.GetSizeY(), 200);
    EXPECT_EQ(std::distance(matrix.begin(), matrix.end()), 20000);
}

TEST_F(MatrixTest, StringMatrix)
{
    Matrix<std::string> matrix(2, std::vector<std::string>{"hello", "world", "test", "matrix"});
    EXPECT_EQ(matrix.GetSizeX(), 2);
    EXPECT_EQ(matrix.GetSizeY(), 2);
    EXPECT_EQ(matrix.Get(0, 0), "hello");
    EXPECT_EQ(matrix.Get(1, 1), "matrix");
}

TEST_F(MatrixTest, FloatMatrix)
{
    Matrix<float> matrix(2, std::vector<float>{1.5f, 2.5f, 3.5f, 4.5f});
    EXPECT_FLOAT_EQ(matrix.Get(0, 0), 1.5f);
    EXPECT_FLOAT_EQ(matrix.Get(1, 1), 4.5f);
}