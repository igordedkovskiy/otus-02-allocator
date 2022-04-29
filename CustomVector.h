#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR

#include <cstdint>
#include <memory>

//template<typename T> struct TD;

namespace custom_vector
{
	
template<typename T, typename Allocator = std::allocator<T>> struct CustomVector
{
    struct Iterator
	{
		using value_type = T;
        using pointer = T*;
		using reference = T&;

        Iterator() noexcept = default;

        Iterator(pointer p) noexcept:
            ptr{p}
        {}

        Iterator(const Iterator& l) noexcept:
            ptr{l.ptr}
        {}

        ~Iterator() noexcept = default;

        Iterator& operator=(const Iterator& l) noexcept
        {
            ptr = l.ptr;
            return *this;
        }

        Iterator& operator++() noexcept
        {
            ++ptr;
            return *this;
        }

        Iterator& operator--() noexcept
        {
            --ptr;
            return *this;
        }

        reference operator*() const noexcept
        {
            return *ptr;
        }

        pointer operator->() const noexcept
        {
            return ptr;
        }

        friend bool operator==(const Iterator& l, const Iterator& r) noexcept
        {
            return l.ptr == r.ptr;
        }

        friend bool operator!=(const Iterator& l, const Iterator& r) noexcept
        {
            return l.ptr != r.ptr;
        }

    private:
        T* ptr = nullptr;
	};
	
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = Iterator;
    using const_iterator = const Iterator;

    CustomVector() = default;
    ~CustomVector()
    {
        if(m_start)
            allocator.deallocate(m_start, size());
        m_start = nullptr;
        m_end = nullptr;
    }

    iterator begin() noexcept
    {
        return {m_start};
    }

    const_iterator begin() const noexcept
    {
        return {m_start};
    }

    iterator end() noexcept
    {
        return {m_end};
    }

    const_iterator end() const noexcept
    {
        return {m_end};
    }

    iterator erase(const_iterator pos)
    {
        if(pos == end())
            return end();
        auto p = &(*pos);
        while(p < m_end-1)
        {
            allocator.destroy(p);
            allocator.construct(p, *(p + 1));
            ++p;
        }
        allocator.destroy(p);
        --m_end;
        return {&(*pos) + 1};
    }
	
	template<typename... Args> void emplace_back(Args&&... args)
	{
		// if allocator is stateless
		//if constexpr(std::is_same<Allocator, std::allocator>)
        //{
        //    std::allocator<T> allocator;
        //    auto p = allocator.allocate(1);
        //    allocator.construct(p, std::forward<Args>(args)...);
        //}
		// if allocator is not stateless
		//else if constexpr(!std::is_same<Allocator, std::allocator>)
        //{
        //    auto p = allocator.allocate(1);
        //    allocator.construct(p, std::forward<Args>(args)...);
        //}
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
	
    inline T& operator[](std::size_t index) noexcept
    {
        return *(m_start + index);
    }

    inline std::size_t size() const noexcept
	{
        return m_end - m_start;
	}
	
    inline bool empty() const noexcept
	{
        return !size();
	}
	
    Allocator allocator;
    T* m_start = nullptr;
    T* m_end = nullptr;
};

}

#endif //#define CUSTOM_VECTOR
