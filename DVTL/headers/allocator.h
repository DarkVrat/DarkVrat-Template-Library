#ifndef DVTL_ALLOCATOR_H
#define DVTL_ALLOCATOR_H

#include "utility.h"

namespace DVTL 
{
    template<typename T>
    class allocator 
    {
    public:
        static inline T* allocate(const size_t& size = 1) 
        {
            T* ptr = static_cast<T*>(operator new(size * sizeof(T)));
            return ptr;
        }

        static inline void construct(T* const ptr, const size_t& index, const T& obj) { new (ptr + index) T(obj); }
        static inline void construct(T* const ptr, const size_t& index, T&& obj) { new (ptr + index) T(move(obj)); }
        static inline void construct(T* const ptr, const T& obj) { new (ptr) T(obj); }
        static inline void construct(T* const ptr, T&& obj) { new (ptr) T(move(obj)); }

        static inline void destroy(T* const ptr, const size_t& index) { ptr[index].~T(); }
        static inline void destroy(T* const ptr) { ptr->~T(); }

        static inline void deallocate(T* const ptr) noexcept { operator delete(ptr); }
    };

}

#endif // !DVTL_ALLOCATOR_H
