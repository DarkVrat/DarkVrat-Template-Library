#ifndef DVTL_UTILITY_H
#define DVTL_UTILITY_H

namespace DVTL 
{
	template<typename T> struct remove_reference			{ typedef T type; };
	template<typename T> struct remove_reference<T&>		{ typedef T type; };
	template<typename T> struct remove_reference<T&&>		{ typedef T type; };

	template<typename T> using remove_reference_t = typename remove_reference<T>::type;

	template<typename T> constexpr bool is_lvalue_reference_v		= false;
	template<typename T> constexpr bool is_lvalue_reference_v<T&>	= true;

	template<typename T> constexpr remove_reference_t<T>&& move(T&& obj) noexcept { return static_cast<remove_reference_t<T>&&>(obj); }
	template<typename T> constexpr T&& forward(remove_reference_t<T>& obj) noexcept { return static_cast<T&&>(obj); }
	template<typename T> constexpr T&& forward(remove_reference_t<T>&& obj) noexcept 
	{
		static_assert(!is_lvalue_reference_v<T>, "bad forward call");
		return static_cast<T&&>(obj);
	}

	template<typename T> inline void swap(T& left, T& right) { left.swap(right); }

	template<typename T> inline T& max(T& left, T& right) { return left > right ? left, right; }
	template<typename T> inline T& min(T& left, T& right) { return left < right ? left, right; }
}

#ifndef __PLACEMENT_NEW_INLINE
#define __PLACEMENT_NEW_INLINE
inline void* operator new(size_t Size, void* Where) noexcept
{
	return Where;
}
#endif // !__PLACEMENT_NEW_INLINE

#endif // !DVTL_UTILITY_H
