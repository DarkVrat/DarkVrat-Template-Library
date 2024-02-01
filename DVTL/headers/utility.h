#ifndef DVTL_UTILITY_H
#define DVTL_UTILITY_H

namespace DVTL
{
	template<typename T> struct Remove_reference		{ typedef T type; };
	template<typename T> struct Remove_reference<T&>	{ typedef T type; };
	template<typename T> struct Remove_reference<T&&>	{ typedef T type; };

	template<typename T> using Remove_reference_t = typename Remove_reference<T>::type;

	template<typename T> constexpr bool Is_lvalue_reference_v = false;
	template<typename T> constexpr bool Is_lvalue_reference_v<T&> = true;

	template<typename T> constexpr Remove_reference_t<T>&& Move(T&& obj) noexcept	{ return static_cast<Remove_reference_t<T>&&>(obj); }
	template<typename T> constexpr T&& Forward(Remove_reference_t<T>& obj) noexcept { return static_cast<T&&>(obj); }
	template<typename T> constexpr T&& Forward(Remove_reference_t<T>&& obj) noexcept
	{
		static_assert(!Is_lvalue_reference_v<T>, "bad forward call");
		return static_cast<T&&>(obj);
	}

	template<typename T1, typename T2>
	struct Pair {
		T1 First;
		T2 Second;

		constexpr Pair() :First(T1()), Second(T2()) {};
		constexpr Pair(const T1& val1, const T2& val2) :First(val1), Second(val2) {};
		constexpr Pair(const T1& val1, T2&& val2) :First(val1), Second(Move(val2)) {};
		constexpr Pair(T1&& val1, const T2& val2) :First(Move(val1)), Second(val2) {};
		constexpr Pair(T1&& val1, T2&& val2) :First(Move(val1)), Second(Move(val2)) {};
		template<typename U1, typename U2> Pair(const Pair<U1, U2>& right) :First(right.First), Second(right.Second) {};
		template<typename U1, typename U2> Pair(const U1& val1, const U2 val2) :First(val1), Second(val2) {};
		Pair(const Pair&) = default;
		Pair(Pair&&) = default;

		Pair& operator=(const Pair&) = default;
		Pair& operator=(Pair&&) = default;
		template<typename U1, typename U2> Pair& operator=(const Pair<U1, U2>& right);

		~Pair() = default;

		void Swap(Pair& p);
	};

	template<typename T1, typename T2>
	template<typename U1, typename U2>
	inline Pair<T1, T2>& Pair<T1, T2>::operator=(const Pair<U1, U2>& right)
	{
		First = right.First;
		Second = right.Second;

		return *this;
	}

	template<typename T1, typename T2>
	inline void Pair<T1, T2>::Swap(Pair& p)
	{
		T1 temp_f(p.First);
		T2 temp_s(p.Second);

		p.First = First;
		p.Second = Second;

		First = temp_f;
		Second = temp_s;
	}

	template<typename T1, typename T2>
	inline void Swap(Pair<T1, T2>& left, Pair<T1, T2>& right)
	{
		left.Swap(right);
	}

	template<typename T>				bool Less(const T& left, const T& right)						{ return left < right; }
	template<typename T1, typename T2>	bool Less(const Pair<T1, T2>& left, const Pair<T1, T2>& right)	{return left.First < right.First;}

}

#ifndef __PLACEMENT_NEW_INLINE
#define __PLACEMENT_NEW_INLINE
inline void* operator new(size_t Size, void* Where) noexcept
{
	return Where;
}
#endif // !__PLACEMENT_NEW_INLINE

#endif // !DVTL_UTILITY_H
