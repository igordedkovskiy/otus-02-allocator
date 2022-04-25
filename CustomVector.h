#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR

#include <cstdint>
#include <memory>

template<typename T> struct TD;

namespace custom_vector
{
	
template<typename T, typename Allocator = std::allocator<T>> struct CustomVector
{
	struct CustomIterator
	{
		using value_type = T;
		using reference = T&;
	};
	
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
	using iterator = CustomIterator;

    CustomVector() = default;
    ~CustomVector() = default;
	
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
		auto p = allocator.allocate(1);
		allocator.construct(p, std::forward<Args>(args)...);
	}
	
	
	
	T& operator[](std::size_t index) noexcept
	{
		return *(start + index);
	}
	
	T& at(std::size_t index)
	{
		if(index >= size)
			throw ...;
		return *(start + index);
	}
	
	std::size_t size() const noexcept
	{
		return size;
	}
	
	bool empty() const noexcept
	{
		return !size;
	}
	
	Allocator allocator;
	T* start = nullptr;
	std::size_t size = 0;
};

}

#endif //#define CUSTOM_VECTOR
