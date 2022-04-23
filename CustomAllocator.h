#ifndef CUSTOM_ALLOCATOR
#define CUSTOM_ALLOCATOR

#include <vector>
#include <list>
#include <string>
#include <utility>

namespace custom_allocator
{

template<typename T, std::size_t SIZE = 4> class CustomAllocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    CustomAllocator() = default;
    ~CustomAllocator() = default;

    template<typename U> CustomAllocator(const CustomAllocator<U, SIZE>&)
    {
        ;
    }

    template<typename U> struct rebind
    {
        using other = CustomAllocator<U, SIZE>;
    };

    inline T* allocate(std::size_t n)
    {
        auto p = std::malloc(n * sizeof(T));
        if(!p)
            throw std::bad_alloc();
        return reinterpret_cast<T*>(p);
    }

    inline void deallocate(T* p, std::size_t)
    {
        std::free(p);
    }

    template<typename U, typename ...Args> void construct(U* p, Args&& ...args)
    {
        new(p) U(std::forward<Args>(args)...);
    };

    inline void destroy(T* p)
    {
        p->~T();
    }

private:

};

}

#endif //#define CUSTOM_ALLOCATOR
