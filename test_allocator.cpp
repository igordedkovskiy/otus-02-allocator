#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "CustomAllocator.h"
#include "gtest/gtest.h"

using namespace custom_allocator;

TEST(TEST_ADDR_SORT, test_addr_sort)
{
    ASSERT_TRUE(false);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
