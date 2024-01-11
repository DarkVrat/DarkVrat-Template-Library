#ifndef DVTL_UTILITY_H
#define DVTL_UTILITY_H

namespace DVTL {
	template<typename T>
	inline T&& move(T&& obj) noexcept
	{
		return static_cast<T&&>(obj);
	}
}

#ifndef __PLACEMENT_NEW_INLINE
#define __PLACEMENT_NEW_INLINE
inline void* operator new(size_t Size, void* Where) noexcept
{
	return Where;
}
#endif // !__PLACEMENT_NEW_INLINE

#endif // !DVTL_UTILITY_H