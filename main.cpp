#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "CustomAllocator.h"
#include "CustomVector.h"

constexpr std::size_t factorial(std::size_t n) noexcept
{
    return n ? (n * factorial(n - 1)) : 1;
}

using namespace custom_allocator;
using namespace custom_vector;

template<typename F, typename S> std::ostream& operator<<(std::ostream& o, const std::pair<const F, S>& el)
{
    o << el.first << " " << el.second;
    return o;
}

template<typename T> void print(const T& arg)
{
    for(const auto it:arg)
        std::cout << it << "; ";
    std::cout << '\n';
}

template<typename T> void filL_vec(T& arg, std::size_t size)
{
    for(std::size_t cntr = 0; cntr < size; ++cntr)
        arg.emplace_back(cntr);
}

template<typename T> void filL_map(T& arg, std::size_t size)
{
    for(std::size_t cntr = 0; cntr < size; ++cntr)
        arg.insert({cntr, factorial(cntr)});
}

int main()
{
    {
        std::map<int,int> mp;
        filL_map(mp, 10);
        print(mp);
    }
    {
        std::map<int,int,std::less<int>, CustomAllocator<std::pair<const int,int>, 10>> mp;
        filL_map(mp, 10);
        print(mp);
    }
    {
        CustomVector<int> vec;
        filL_vec(vec, 10);
        print(vec);
    }
    {
        CustomVector<int, CustomAllocator<int,10>> vec;
        filL_vec(vec, 10);
        print(vec);
    }

    {
        std::map<int,int,std::less<int>, CustomAllocator<std::pair<const int,int>, 4>> mp;
        filL_map(mp, 10);
        // remove an element
        auto it = mp.find(4);
        mp.erase(it);
        print(mp);
    }
    {
        CustomVector<int, CustomAllocator<int,6>> vec;
        filL_vec(vec, 10);
        auto it = vec.begin();
        ++it;
        ++it;
        ++it;
        vec.erase(it);
        print(vec);
    }
    return 0;
}
