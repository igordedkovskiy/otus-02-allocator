#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "CustomAllocator.h"
#include "CustomVector.h"
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


//int main()
//{
//    {
//        std::cout << "std::vector:\n";
//        std::vector<int, CustomAllocator<int, 4>> vec;
//        vec.emplace_back(1);
//        vec.emplace_back(2);
//        vec.clear();
//        vec.emplace_back(3);
//        vec.emplace_back(4);
//        vec.emplace_back(5);
//        vec.emplace_back(6);
//        vec.emplace_back(7);
//        vec.emplace_back(8);
//        vec.emplace_back(9);
//        vec.emplace_back(10);
//        vec.emplace_back(11);
//        vec.emplace_back(12);
//        print_vec(vec);

//        vec.clear();
//        print_vec(vec);

//        vec.emplace_back(4);
//        vec.emplace_back(5);
//        vec.emplace_back(6);
//        vec.emplace_back(7);
//        vec.emplace_back(8);
//        vec.emplace_back(9);
//        vec.emplace_back(10);
//        print_vec(vec);
//    }


//    {
//        std::cout << "std::list:\n";
//        std::list<int, CustomAllocator<int, 4>> vec;
//        assert(vec.size() == 0);
//        vec.emplace_back(1);
//        assert(vec.size() == 1);
//        vec.emplace_back(2);
//        assert(vec.size() == 2);
//        vec.emplace_back(3);
//        assert(vec.size() == 3);
//        vec.emplace_back(4);
//        assert(vec.size() == 4);
//        vec.emplace_back(5);
//        assert(vec.size() == 5);
//        vec.emplace_back(6);
//        assert(vec.size() == 6);
//        vec.emplace_back(7);
//        assert(vec.size() == 7);
//        vec.emplace_back(8);
//        assert(vec.size() == 8);
//        vec.emplace_back(9);
//        assert(vec.size() == 9);
//        vec.emplace_back(10);
//        assert(vec.size() == 10);
//        vec.emplace_back(11);
//        assert(vec.size() == 11);
//        vec.emplace_back(12);
//        assert(vec.size() == 12);
//        print_vec(vec);

//        vec.clear();
//        assert(vec.size() == 0);
//        print_vec(vec);

//        vec.emplace_back(4);
//        assert(vec.size() == 1);
//        vec.emplace_back(5);
//        assert(vec.size() == 2);
//        vec.emplace_back(6);
//        assert(vec.size() == 3);
//        auto it = std::begin(vec);
//        ++it;
//        ++it;
//        vec.erase(it);
//        assert(vec.size() == 2);
//        vec.emplace_back(7);
//        assert(vec.size() == 3);
//        vec.emplace_back(8);
//        assert(vec.size() == 4);
//        vec.emplace_back(9);
//        assert(vec.size() == 5);
//        vec.emplace_back(10);
//        assert(vec.size() == 6);
//        print_vec(vec);
//    }


//    std::cout << "std::map:\n";
//    std::map<int,int,std::less<int>, CustomAllocator<std::pair<const int,int>, 4>> mp;
//    assert(mp.size() == 0);
//    mp.insert(std::make_pair(1, 234));
//    assert(mp.size() == 1);
//    mp.insert(std::make_pair(2, 74));
//    assert(mp.size() == 2);
//    auto it = mp.insert(std::make_pair(3, 39));
//    assert(mp.size() == 3);
//    mp.erase(it.first);
//    assert(mp.size() == 2);
//    mp.insert(std::make_pair(4, 957));
//    assert(mp.size() == 3);
//    mp.insert(std::make_pair(5, 84));
//    assert(mp.size() == 4);
//    mp.insert(std::make_pair(6, 85));
//    assert(mp.size() == 5);
//    mp.insert(std::make_pair(7, 21));
//    assert(mp.size() == 6);
//    print_map(mp);

//    return 0;
//}
