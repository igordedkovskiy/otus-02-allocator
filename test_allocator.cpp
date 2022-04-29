#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "CustomAllocator.h"
#include "CustomVector.h"
#include "gtest/gtest.h"

using namespace custom_allocator;

template<typename T> struct kinda_vector
{
    ~kinda_vector()
    {
        if(m_start)
            allocator.deallocate(m_start, size());
        m_start = nullptr;
        m_end = nullptr;
    }

    std::size_t size() const noexcept
    {
        return m_end - m_start;
    }

    template<typename... Args> void emplace(Args... args)
    {
        const auto p = allocator.allocate(1 + size());
        allocator.construct(p + size(), std::forward<Args>(args)...);
        if(m_start)
        {
            for(std::size_t cntr = 0; cntr < size(); ++cntr)
            {
                allocator.construct(p + cntr, *(m_start + cntr));
                allocator.destroy(m_start + cntr);
            }
            allocator.deallocate(m_start, size());
        }
        m_end = p + size() + 1;
        m_start = p;
    }

    T* erase(T* pos) noexcept
    {
        if(pos == m_end)
            return m_end;
        auto p = pos;
        while(p < m_end-1)
        {
            allocator.destroy(p);
            allocator.construct(p, *(p + 1));
            ++p;
        }
        allocator.destroy(p);
        --m_end;
        return pos + 1;
    }

    T* m_start = nullptr;
    T* m_end = nullptr;
    CustomAllocator<T, 4> allocator;
};

TEST(TEST_ALLOCATOR, test_allocator_for_vec)
{
    kinda_vector<int> vec;

    ASSERT_TRUE(vec.allocator.elements_occupied() == 0);
    ASSERT_TRUE(vec.allocator.is_storage_empty());
    ASSERT_TRUE(vec.size() == 0);
    ASSERT_TRUE(vec.allocator.find_free_elements(1 + vec.size()) == 0);
    vec.emplace((int)1);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 1);
    
    ASSERT_TRUE(!vec.allocator.is_storage_empty());
    ASSERT_TRUE(vec.size() == 1);
    ASSERT_TRUE(vec.allocator.find_free_elements(1 + vec.size()) == 1);
    vec.emplace((int)2);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 2);
    
    ASSERT_TRUE(!vec.allocator.is_storage_empty());
    ASSERT_TRUE(vec.size() == 2);
    ASSERT_TRUE(vec.allocator.find_free_elements(1 + vec.size()) == 4);
    vec.emplace((int)3);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 0);

    ASSERT_TRUE(vec.allocator.is_storage_empty());
    ASSERT_TRUE(vec.size() == 3);
    ASSERT_TRUE(vec.allocator.find_free_elements(1 + vec.size()) == 0);
    vec.emplace((int)4);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 0);

    ASSERT_TRUE(vec.allocator.is_storage_empty());
    ASSERT_TRUE(vec.size() == 4);
    ASSERT_TRUE(vec.allocator.find_free_elements(1 + vec.size()) == 4);
    vec.emplace((int)5);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 0);
    ASSERT_TRUE(vec.size() == 5);

    vec.erase(vec.m_end - 1);
    vec.erase(vec.m_end - 1);
    vec.erase(vec.m_end - 1);
    ASSERT_TRUE(vec.allocator.is_storage_empty());
    ASSERT_TRUE(vec.size() == 2);
    ASSERT_TRUE(vec.allocator.find_free_elements(1 + vec.size()) == 0);
    vec.emplace((int)6);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 3);
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
