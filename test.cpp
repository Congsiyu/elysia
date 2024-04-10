#include <gtest/gtest.h>
#include "a.h"

TEST(MaxSum, Test1)
{
    int arr[] = {0, -31, -41, -59, -26, -53, -58, -97, -93, -23, -84};
    int cnt = 10;
    EXPECT_EQ(MaxSum(arr, cnt), 0);
}

TEST(MaxSum, Test2)
{
    int arr[] = {0, 31, 41, -59, 26, -53, 58, -97, -93, -23, -84};
    int cnt = 10;
    EXPECT_EQ(MaxSum(arr, cnt), 72);
}
TEST(MaxSum, Test3)
{
    int arr[] = {0, 31, 41, -59, 26, -53, 58, -97, -93, 23, 84};
    int cnt = 10;
    EXPECT_EQ(MaxSum(arr, cnt), 107);
}
TEST(MaxSum, Test4)
{
    int arr[] = {0, 31, 41, -59, 26, -53, 58, 97, -93, -23, -84};
    int cnt = 10;
    EXPECT_EQ(MaxSum(arr, cnt), 155);
}