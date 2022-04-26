#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "CustomAllocator.h"
#include "CustomVector.h"

using namespace custom_allocator;
using namespace custom_vector;

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
        CustomVector<int> vec;
        for(std::size_t cntr = 0; cntr < 15; ++cntr)
            vec.emplace_back(cntr + 1);
        for(const auto it:vec)
            std::cout << it << ' ';
        std::cout << '\n';
        for(std::size_t cntr = 0; cntr < vec.size(); ++cntr)
            std::cout << vec[cntr] << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
    {
        CustomVector<int, CustomAllocator<int>> vec;
        for(std::size_t cntr = 0; cntr < 15; ++cntr)
            vec.emplace_back(cntr + 1);
        for(const auto it:vec)
            std::cout << it << ' ';
        std::cout << '\n';
        for(std::size_t cntr = 0; cntr < vec.size(); ++cntr)
            std::cout << vec[cntr] << ' ';
        std::cout << '\n';
    }
    return 0;
}
