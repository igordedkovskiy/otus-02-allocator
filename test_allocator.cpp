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
        if(!pos)
            return nullptr;
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

TEST(TEST_ALLOCATOR, add_rem_elements)
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

TEST(TEST_ALLOCATOR, boundaries)
{
    kinda_vector<int> vec;

    ASSERT_TRUE(vec.allocator.elements_occupied() == 0);
    ASSERT_TRUE(vec.allocator.is_storage_empty());
    ASSERT_TRUE(vec.size() == 0);
    ASSERT_TRUE(vec.allocator.find_free_elements(1 + vec.size()) == 0);
    vec.emplace((int)1);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 1);
    ASSERT_TRUE(vec.allocator.storage_status.test(0));
    ASSERT_TRUE(!vec.allocator.storage_status.test(1));
    ASSERT_TRUE(!vec.allocator.storage_status.test(2));
    ASSERT_TRUE(!vec.allocator.storage_status.test(3));

    ASSERT_TRUE(!vec.allocator.is_storage_empty());
    ASSERT_TRUE(vec.size() == 1);
    ASSERT_TRUE(vec.allocator.find_free_elements(1 + vec.size()) == 1);
    vec.emplace((int)2);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 2);
    ASSERT_TRUE(vec.size() == 2);
    ASSERT_TRUE(!vec.allocator.storage_status.test(0));
    ASSERT_TRUE(vec.allocator.storage_status.test(1));
    ASSERT_TRUE(vec.allocator.storage_status.test(2));
    ASSERT_TRUE(!vec.allocator.storage_status.test(3));

    vec.erase(vec.m_start);
    ASSERT_TRUE(!vec.allocator.is_storage_empty());
    ASSERT_TRUE(vec.size() == 1);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 1);
    ASSERT_TRUE(!vec.allocator.storage_status.test(0));
    ASSERT_TRUE(vec.allocator.storage_status.test(1));
    ASSERT_TRUE(!vec.allocator.storage_status.test(2));
    ASSERT_TRUE(!vec.allocator.storage_status.test(3));
    ASSERT_TRUE(vec.allocator.find_free_elements(1 + vec.size()) == 2);
    vec.emplace((int)2);
    ASSERT_TRUE(vec.allocator.elements_occupied() == 2);
    ASSERT_TRUE(vec.size() == 2);
    ASSERT_TRUE(!vec.allocator.storage_status.test(0));
    ASSERT_TRUE(!vec.allocator.storage_status.test(1));
    ASSERT_TRUE(vec.allocator.storage_status.test(2));
    ASSERT_TRUE(vec.allocator.storage_status.test(3));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
