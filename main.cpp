#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "CustomAllocator.h"

using namespace custom_allocator;

template<typename T> void print_vec(const T& arg)
{
    std::cout << "size = " << arg.size() << "\nvalue:\n";
    for(const auto it:arg)
        std::cout << it << " ";
    std::cout << "\n\n";
}

template<typename T> void print_map(const T& arg)
{
    std::cout << "size = " << arg.size() << "\nvalue:\n";
    for(const auto it:arg)
        std::cout << '[' << it.first << "," << it.second << "] ";
    std::cout << "\n\n";
}

int main()
{
    {
        std::cout << "std::vector:\n";
        std::vector<int, CustomAllocator<int, 4>> vec;
        vec.emplace_back(1);
        vec.emplace_back(2);
        vec.clear();
        vec.emplace_back(3);
        vec.emplace_back(4);
        vec.emplace_back(5);
        vec.emplace_back(6);
        vec.emplace_back(7);
        vec.emplace_back(8);
        vec.emplace_back(9);
        vec.emplace_back(10);
        vec.emplace_back(11);
        vec.emplace_back(12);
        print_vec(vec);

        vec.clear();
        print_vec(vec);

        vec.emplace_back(4);
        vec.emplace_back(5);
        vec.emplace_back(6);
        vec.emplace_back(7);
        vec.emplace_back(8);
        vec.emplace_back(9);
        vec.emplace_back(10);
        print_vec(vec);
    }


    {
        std::cout << "std::list:\n";
        std::list<int, CustomAllocator<int, 4>> vec;
        assert(vec.size() == 0);
        vec.emplace_back(1);
        assert(vec.size() == 1);
        vec.emplace_back(2);
        assert(vec.size() == 2);
        vec.emplace_back(3);
        assert(vec.size() == 3);
        vec.emplace_back(4);
        assert(vec.size() == 4);
        vec.emplace_back(5);
        assert(vec.size() == 5);
        vec.emplace_back(6);
        assert(vec.size() == 6);
        vec.emplace_back(7);
        assert(vec.size() == 7);
        vec.emplace_back(8);
        assert(vec.size() == 8);
        vec.emplace_back(9);
        assert(vec.size() == 9);
        vec.emplace_back(10);
        assert(vec.size() == 10);
        vec.emplace_back(11);
        assert(vec.size() == 11);
        vec.emplace_back(12);
        assert(vec.size() == 12);
        print_vec(vec);

        vec.clear();
        assert(vec.size() == 0);
        print_vec(vec);

        vec.emplace_back(4);
        assert(vec.size() == 1);
        vec.emplace_back(5);
        assert(vec.size() == 2);
        vec.emplace_back(6);
        assert(vec.size() == 3);
        auto it = std::begin(vec);
        ++it;
        ++it;
        vec.erase(it);
        assert(vec.size() == 2);
        vec.emplace_back(7);
        assert(vec.size() == 3);
        vec.emplace_back(8);
        assert(vec.size() == 4);
        vec.emplace_back(9);
        assert(vec.size() == 5);
        vec.emplace_back(10);
        assert(vec.size() == 6);
        print_vec(vec);
    }


    std::cout << "std::map:\n";
    std::map<int,int,std::less<int>, CustomAllocator<std::pair<const int,int>, 4>> mp;
    assert(mp.size() == 0);
    mp.insert(std::make_pair(1, 234));
    assert(mp.size() == 1);
    mp.insert(std::make_pair(2, 74));
    assert(mp.size() == 2);
    auto it = mp.insert(std::make_pair(3, 39));
    assert(mp.size() == 3);
    mp.erase(it.first);
    assert(mp.size() == 2);
    mp.insert(std::make_pair(4, 957));
    assert(mp.size() == 3);
    mp.insert(std::make_pair(5, 84));
    assert(mp.size() == 4);
    mp.insert(std::make_pair(6, 85));
    assert(mp.size() == 5);
    mp.insert(std::make_pair(7, 21));
    assert(mp.size() == 6);
    print_map(mp);

    return 0;
}
