#ifndef DVTL_ALLOCATOR_H
#define DVTL_ALLOCATOR_H

#include "utility.h"

namespace DVTL 
{
    class allocator 
    {
    public:
        template<typename T>
        static inline T* allocate(const size_t& size = 1) 
        {
            T* ptr = static_cast<T*>(operator new(size * sizeof(T)));
            return ptr;
        }

        template<typename T> static inline void construct(T* const ptr, const size_t& index, const T& obj) { new (ptr + index) T(obj); }
        template<typename T> static inline void construct(T* const ptr, const size_t& index, T&& obj) { new (ptr + index) T(move(obj)); }
        template<typename T> static inline void construct(T* const ptr, const T& obj) { new (ptr) T(obj); }
        template<typename T> static inline void construct(T* const ptr, T&& obj) { new (ptr) T(move(obj)); }

        template<typename T, typename... Types>
        static inline void constructForward(T* const ptr, const size_t& index, Types&&... params) { new (ptr + index) T(forward<Types>(params)...); }
        template<typename T, typename... Types>
        static inline void constructForward(T* const ptr, Types&&... params) { new (ptr) T(forward<Types>(params)...); }

        template<typename T> static inline void destroy(T* const ptr, const size_t& index) { ptr[index].~T(); }
        template<typename T> static inline void destroy(T* const ptr) { ptr->~T(); }

        template<typename T> static inline void deallocate(T* const ptr) noexcept { operator delete(ptr); }
    };

}

#endif // !DVTL_ALLOCATOR_H
