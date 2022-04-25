#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "CustomAllocator.h"
#include "gtest/gtest.h"

using namespace custom_allocator;

TEST(TEST_ALLOCATOR, test_allocator_for_vec)
{
    // parameterise vector
    //     invoke allocate 1 element
    //     invoke construct 1 element
    //     ASSERT_TRUE(check storage_status)
    
    //     invoke allocate 2 element
    //     invoke destroy 1 element
    //     invoke deallocate 1 element
    //     invoke construct 2 element
    //     ASSERT_TRUE(check storage_status)
    
    //     invoke allocate 4 element
    //     invoke destroy 2 element
    //     invoke deallocate 2 element
    //     invoke construct 3 element
    //     ASSERT_TRUE(check storage_status)
    
    //     invoke allocate 8 element
    //     invoke destroy 3 element
    //     invoke deallocate 3 element
    //     invoke construct 4 element
    //     ASSERT_TRUE(check storage_status)
    ASSERT_TRUE(false);
}

TEST(TEST_ALLOCATOR, test_allocator_for_list)
{
    ASSERT_TRUE(false);
}

TEST(TEST_ALLOCATOR, test_allocator_for_map)
{
    ASSERT_TRUE(false);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
