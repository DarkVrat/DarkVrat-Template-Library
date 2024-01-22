#ifndef DVTL_ALLOCATOR_H
#define DVTL_ALLOCATOR_H

#include "utility.h"

namespace DVTL 
{
    class Allocator 
    {
    public:
        template<typename T>
        static inline T* Allocate(const size_t& size = 1) 
        {
            T* ptr = static_cast<T*>(operator new(size * sizeof(T)));
            return ptr;
        }

        template<typename T> static inline void Construct(T* const ptr, const size_t& index, const T& obj) { new (ptr + index) T(obj); }
        template<typename T> static inline void Construct(T* const ptr, const size_t& index, T&& obj) { new (ptr + index) T(Move(obj)); }
        template<typename T> static inline void Construct(T* const ptr, const T& obj) { new (ptr) T(obj); }
        template<typename T> static inline void Construct(T* const ptr, T&& obj) { new (ptr) T(Move(obj)); }

        template<typename T, typename... Types>
        static inline void ConstructForward(T* const ptr, const size_t& index, Types&&... params) { new (ptr + index) T(Forward<Types>(params)...); }
        template<typename T, typename... Types>
        static inline void ConstructForward(T* const ptr, Types&&... params) { new (ptr) T(Forward<Types>(params)...); }

        template<typename T> static inline void Destroy(T* const ptr, const size_t& index) { ptr[index].~T(); }
        template<typename T> static inline void Destroy(T* const ptr) { ptr->~T(); }

        template<typename T> static inline void Deallocate(T* const ptr) noexcept { operator delete(ptr); }
    };

}

#endif // !DVTL_ALLOCATOR_H
