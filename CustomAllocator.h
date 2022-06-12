#ifndef CUSTOM_ALLOCATOR
#define CUSTOM_ALLOCATOR

#include <cstdint>
#include <cassert>
#include <bitset>
#include <new>

template<typename T> struct TD;

namespace custom_allocator
{
	
template<typename T, std::size_t SIZE = 8> struct CustomAllocator
{
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    CustomAllocator() = default;
    ~CustomAllocator()
    {
        if(start)
            delete[] reinterpret_cast<std::uint8_t*>(start);
        start = nullptr;
    }

    template<typename U> CustomAllocator(const CustomAllocator<U, SIZE>&){}

    template<typename U> struct rebind
    {
        using other = CustomAllocator<U, SIZE>;
    };

    inline T* allocate(std::size_t n)
    {
        auto alloc = [](std::size_t N)
        {
            auto p = reinterpret_cast<T*>(new std::uint8_t[N * sizeof(T)]);
            return p;
        };

        if(n < SIZE)
        {
            if(!start)
            {
                start = alloc(SIZE);
                return start;
            }
            else
            {
                // are there n free consencutive elements in a storage?
                // index - an index of first of n free consencutive elements
                const auto index = find_free_elements(n);
                if(index < SIZE)
                    return start + index;
            }
        }
        auto p = alloc(n);
        return p;
    }

    inline void deallocate(T* p, std::size_t)
    {
        if(!p)
            return;
        if(p == start && is_storage_empty())
            start = nullptr;
        if(!start || (p < start) || (p > start + SIZE - 1))
            delete[] reinterpret_cast<std::uint8_t*>(p);
    }

    template<typename U, typename ...Args> void construct(U* p, Args&& ...args)
    {
        if(!p)
            return;
        static_assert(sizeof(T) >= sizeof(U), "Wtf?!");
        auto cast = [](auto p){ return reinterpret_cast<std::uint8_t*>(p); };
        if(start && (cast(p) >= cast(start)) && (cast(p) < cast(start + SIZE)))
        {
            const std::size_t index = (cast(p) - cast(start)) / sizeof(T);
            storage_status.set(index);
        }
        new(p) U(std::forward<Args>(args)...);
    }

    inline void destroy(T* p)
    {
        if(!p)
            return;
        if(start && (p >= start) && (p < (start + SIZE)))
            storage_status.reset(p - start);
        p->~T();
    }
	
//private:
    inline bool is_storage_empty() const
    {
        return !storage_status.any();
    }

    std::size_t find_free_elements(std::size_t n) const noexcept
    {
        auto count = [this, n](std::size_t& start)
        {
            for(std::size_t cntr = start; cntr < start + n; ++cntr)
            {
                if(storage_status.test(cntr))
                {
                    start = cntr;
                    return false;
                }
            }
            return true;
        };

        if(n > SIZE)
            return SIZE;
        for(std::size_t cntr = 0; cntr < SIZE - n + 1; ++cntr)
        {
            if(count(cntr))
                return cntr;
        }
        return SIZE;
    }
    
    inline std::size_t elements_occupied() const noexcept
    {
        return storage_status.count();
    }

    T* start = nullptr; // first element of reserved space
    // if storage_status[i] = 0, then i-th element of storage is empty
    std::bitset<SIZE> storage_status;
};

}

#endif //#define CUSTOM_ALLOCATOR
