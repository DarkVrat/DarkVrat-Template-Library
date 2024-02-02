#ifndef DVTL_ALGORITHM_H
#define DVTL_ALGORITHM_H

#include "Utility.h"
#include "Initializer_list.h"

namespace DVTL {
	template<typename T_Iterator>
	inline T_Iterator Adjacent_find(T_Iterator first, T_Iterator last)
	{
		if (first == last) return last;

		T_Iterator temp(first++);

		while (first != last)
		{
			if (*temp == *first) return temp;

			temp = first;
			++first;
		}

		return last;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Adjacent_find(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return last;

		T_Iterator temp(first++);

		while (first != last)
		{
			if (predicate(*temp, *first)) return temp;

			temp = first;
			++first;
		}

		return last;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline bool All_of(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		while (first != last)
		{
			if (!predicate(*first))
				return false;

			++first;
		}

		return true;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline bool Any_of(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		while (first != last)
		{
			if (predicate(*first))
				return true;

			++first;
		}

		return false;
	}

	template<typename T_Iterator, typename T_Type>
	inline bool Binary_search(T_Iterator first, T_Iterator last, const T_Type& value)
	{
		while (first != last) {
			T_Iterator middle(first + (last - first) / 2);

			if (*middle == value) return true;
			else if (*middle < value) first = ++middle;
			else last = middle;
		}

		return false;
	}

	template<typename T_Iterator, typename T_Type, typename T_Predicate>
	inline bool Binary_search(T_Iterator first, T_Iterator last, const T_Type& value, T_Predicate predicate)
	{
		while (first < last) {
			T_Iterator middle(first + (last - first) / 2);

			if (predicate(*middle, value) == 0) return true;
			else if (predicate(*middle, value) < 0) first = middle + 1;
			else last = middle;
		}

		return false;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput>
	inline T_IteratorOutput Copy(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput output)
	{
		while (first != last) 
		{
			*output = *first;
			++first;
			++output;
		}

		return output;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput>
	inline T_IteratorOutput Copy_backward(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput output)
	{
		if (first == last) return output;

		while (first != last)
		{
			*(--output) = *(--last);
		}

		return output;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput, typename T_Predicate>
	inline T_IteratorOutput Copy_if(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput output, T_Predicate predicate)
	{
		while (first != last)
		{
			if (predicate(*first))
			{
				*output = *first;
				++output;
			}
			++first;
		}

		return output;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput>
	inline T_IteratorOutput Copy_if(T_IteratorInput first, size_t count, T_IteratorOutput output)
	{
		for (size_t i = 0; i < count; i++)
		{
			*output = *first;
			++first;
			++output;
		}

		return output;
	}

	template<typename T_Iterator, typename T_Type>
	inline size_t Count(T_Iterator first, T_Iterator last, const T_Type& value)
	{
		size_t result(0);

		while (first != last) {
			if (*first == value)
				result++;

			++first;
		}

		return result;
	}

	template<typename T_Iterator, typename T_Type, typename T_Predicate>
	inline size_t Count_if(T_Iterator first, T_Iterator last, const T_Type& value, T_Predicate predicate)
	{
		size_t result(0);

		while (first != last) {
			if (predicate(*first, value))
				result++;

			++first;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline bool Equal(T_Iterator1 first1, T_Iterator2 last1, T_Iterator2 first2)
	{
		while (first1 != last1) {
			if ((*first1 < *first2) || (*first1 > *first2))
				return false;

			++first1;
			++first2;
		}

		return true;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline bool Equal(T_Iterator1 first1, T_Iterator2 last1, T_Iterator2 first2, T_Predicate predicate)
	{
		while (first1 != last1) {
			if (predicate(*first1, *first2))
				return false;

			++first1;
			++first2;
		}

		return true;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline bool Equal(T_Iterator1 first1, T_Iterator2 last1, T_Iterator2 first2, T_Iterator2 last2)
	{
		if ((last1 - first1) != (last2 - first2)) return false;

		while (first1 != last1) {
			if ((*first1 < *first2) || (*first1 > *first2))
				return false;

			++first1;
			++first2;
		}

		return true;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline bool Equal(T_Iterator1 first1, T_Iterator2 last1, T_Iterator2 first2, T_Iterator2 last2, T_Predicate predicate)
	{
		if ((last1 - first1) != (last2 - first2)) return false;

		while (first1 != last1) {
			if (predicate(*first1, *first2))
				return false;

			++first1;
			++first2;
		}

		return true;
	}

	template <typename T_Iterator, typename T_Type>
	inline T_Iterator Upper_bound(T_Iterator first, T_Iterator last, const T_Type& value)
	{
		while (first < last)
		{
			T_Iterator middle(first + (last - first) / 2);

			if (value < *middle) last = middle;
			else first = middle + 1;
		}

		return first;
	}

	template <typename T_Iterator, typename T_Type, typename T_Predicate>
	inline T_Iterator Upper_bound(T_Iterator first, T_Iterator last, const T_Type& value, T_Predicate predicate)
	{
		while (first < last)
		{
			T_Iterator middle(first + (last - first) / 2);

			if (predicate(value, *middle)) last = middle;
			else first = middle + 1;
		}

		return first;
	}

	template<typename T_Iterator, typename T_Type>
	inline T_Iterator Lower_bound(T_Iterator first, T_Iterator last, const T_Type& value)
	{
		while (first < last)
		{
			T_Iterator middle(first + (last - first) / 2);

			if (*middle < value) first = middle + 1;
			else last = middle;
		}

		return first;
	}

	template<typename T_Iterator, typename T_Type, typename T_Predicate>
	inline T_Iterator Lower_bound(T_Iterator first, T_Iterator last, const T_Type& value, T_Predicate predicate)
	{
		while (first < last)
		{
			T_Iterator middle(first + (last - first) / 2);

			if (predicate(*middle, value)) first = middle + 1;
			else last = middle;
		}

		return first;
	}

	template<typename T_Iterator, typename T_Type>
	inline Pair<T_Iterator, T_Iterator> Equal_range(T_Iterator first, T_Iterator last, const T_Type& value)
	{
		return Pair<T_Iterator, T_Iterator>(Lower_bound(first, last, value), Upper_bound(first, last, value));
	}

	template<typename T_Iterator, typename T_Type, typename T_Predicate>
	inline Pair<T_Iterator, T_Iterator> Equal_range(T_Iterator first, T_Iterator last, const T_Type& value, T_Predicate predicate)
	{
		return Pair<T_Iterator, T_Iterator>(Lower_bound(first, last, value, predicate), Upper_bound(first, last, value, predicate));
	}

	template<typename T_Iterator, typename T_Type>
	inline void Fill(T_Iterator first, T_Iterator last, const T_Type& value)
	{
		while (first != last)
		{
			*first = value;
			++first;
		}
	}

	template<typename T_Iterator, typename T_Type>
	inline void Fill_n(T_Iterator first, size_t count, const T_Type& value)
	{
		for (size_t i = 0; i < count; i++) 
		{
			*first = value;
			++first;
		}
	}

	template<typename T_Iterator, typename T_Type>
	inline T_Iterator Find(T_Iterator first, T_Iterator last, const T_Type& value)
	{
		while (first != last)
		{
			if (*first == value)
				break;

			++first;
		}

		return first;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline T_Iterator1 Find_end(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2)
	{
		if ((last1 - first1) >= (last2 - first2)) return false;

		T_Iterator1 result(last1);

		last1 -= last2 - first2;

		while (first1 != last1)
		{
			if (*first1 == *first2)
			{
				T_Iterator1 temp1(first1 + 1);
				T_Iterator2 temp2(first2 + 1);

				while ((temp2 != last2) && (*temp1 == *temp2))
				{
					++temp1;
					++temp2;
				}

				if (temp2 == last2)
					result = first1;
			}

			++first1;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline T_Iterator1 Find_end(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_Predicate predicate)
	{
		if ((last1 - first1) >= (last2 - first2)) return false;

		T_Iterator1 result(last1);

		last1 -= last2 - first2;

		while (first1 != last1)
		{
			if (*first1 == *first2)
			{
				T_Iterator1 temp1(first1 + 1);
				T_Iterator2 temp2(first2 + 1);

				while ((temp2 != last2) && predicate(*temp1, *temp2))
				{
					++temp1;
					++temp2;
				}

				if (temp2 == last2)
					result = first1;
			}

			++first1;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline T_Iterator1 Find_first_of(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2)
	{
		T_Iterator2 temp(first2);

		while (first1 != last1)
		{
			temp = first2;

			while (temp != last2)
			{
				if (*temp == *first1)
					return first1;

				++temp;
			}

			++first1;
		}

		return last1;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline T_Iterator1 Find_first_of(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_Predicate predicate)
	{
		T_Iterator2 temp(first2);

		while (first1 != last1)
		{
			temp = first2;

			while (temp != last2)
			{
				if (predicate(*first1, *temp))
					return first1;

				++temp;
			}

			++first1;
		}

		return last1;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Find_if(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		while (first != last)
		{
			if (predicate(*first))
				return first;

			++first;
		}

		return last;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Find_if_not(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		while (first != last)
		{
			if (!predicate(*first))
				return first;

			++first;
		}

		return last;
	}

	template<typename T_Iterator, typename T_Function>
	inline T_Function For_each(T_Iterator first, T_Iterator last, T_Function function)
	{
		while (first != last)
		{
			function(*first);
			++first;
		}

		return function;
	}

	template<typename T_Iterator, typename T_Function>
	inline T_Function For_each_n(T_Iterator first, size_t count, T_Function function)
	{
		for (size_t i = 0; i < count; i++)
		{
			function(*first);
			++first;
		}

		return function;
	}

	template<typename T_Iterator, typename T_Function>
	inline void Generate(T_Iterator first, T_Iterator last, T_Function function)
	{
		while (first != last)
		{
			*first = function();
			++first;
		}
	}

	template<typename T_Iterator, typename T_Function>
	inline void Generate_n(T_Iterator first, size_t count, T_Function function)
	{
		for (size_t i = 0; i < count; i++)
		{
			*first = function();
			++first;
		}
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline bool Includes(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2)
	{
		while (first1 != last1)
		{
			if (!(*first1<*first2 || *first1>*first2))
			{
				++first2;
				if (first2 == last2)
					return true;
			}

			++first1;
		}

		return false;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline bool Includes(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_Predicate predicate)
	{
		while (first1 != last1)
		{
			if (predicate(*first1, *first2))
			{
				++first2;
				if (first2 == last2)
					return true;
			}

			++first1;
		}

		return false;
	}

	template<typename T_Iterator>
	inline void Inplace_merge(T_Iterator first, T_Iterator middle, T_Iterator last)
	{
		T_Iterator last2(middle - 1);
		
		if (*last2 <= *middle) return;

		while (first <= last2 && middle != last)
		{
			if (*first <= *middle)
				++first;
			else
			{
				auto value = *middle;
				T_Iterator it = middle;

				while (it != first)
				{
					*it = *(it - 1);
					--it;
				}
				*first = value;

				++first;
				++middle;
				++last2;
			}
		}

	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Inplace_merge(T_Iterator first, T_Iterator middle, T_Iterator last, T_Predicate predicate)
	{
		T_Iterator last2(middle - 1);

		if (predicate(*last2, *middle)) return;

		while (first != last2 && middle != last)
		{
			if (predicate(*first, *middle))
				++first;
			else
			{
				auto value = *middle;
				T_Iterator it = middle;

				while (it != first)
				{
					*it = *(it - 1);
					--it;
				}
				*first = value;

				++first;
				++middle;
				++last2;
			}
		}

	}

	template<typename T_Iterator>
	inline T_Iterator Is_heap_until(T_Iterator first, T_Iterator last)
	{
		for (T_Iterator it(first); it != last; ++it) {
			T_Iterator parent(first + (it - first - 1) / 2);

			if (*it > *parent) {
				return it;
			}
		}

		return last;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Is_heap_until(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		for (T_Iterator it(first); it != last; ++it) {
			T_Iterator parent (first + (it - first - 1) / 2);

			if (predicate(*it, *parent)) {
				return it;
			}
		}

		return last;
	}

	template<typename T_Iterator>
	inline bool Is_heap(T_Iterator first, T_Iterator last)
	{
		return Is_heap_until(first, last) == last;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline bool Is_heap(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		return Is_heap_until(first, last, predicate) == last;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline bool Is_partitioned(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return false;

		T_Iterator it(first++);

		while (first != last)
		{
			if (!predicate(*it) && predicate(*first))
				return false;

			++it;
			++first;
		}

		return true;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline bool Is_permutation(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2)
	{
		T_Iterator2 last2(first2 + (last1 - first1));

		while (first1 != last1)
		{
			T_Iterator1 bufIt(first1);
			T_Iterator2 it(first2);
			while (it != last2)
			{
				if (*it == *first1)
				{
					++first1;
					break;
				}

				++it;
			}

			if (bufIt == first1)
				return false;
		}

		return true;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline bool Is_permutation(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Predicate predicate)
	{
		T_Iterator2 last2(first2 + (last1 - first1));

		while (first1 != last1)
		{
			T_Iterator1 bufIt(first1);
			T_Iterator2 it(first2);
			while (it != last2)
			{
				if (predicate(*it, *first1))
				{
					++first1;
					break;
				}

				++it;
			}

			if (bufIt == first1)
				return false;
		}

		return true;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline bool Is_permutation(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2)
	{
		if ((last1 - first1) != (last2 - first2)) return false;

		while (first1 != last1)
		{
			T_Iterator1 bufIt(first1);
			T_Iterator2 it(first2);
			while (it != last2)
			{
				if (*it == *first1)
				{
					++first1;
					break;
				}

				++it;
			}

			if (bufIt == first1)
				return false;
		}

		return true;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline bool Is_permutation(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_Predicate predicate)
	{
		if ((last1 - first1) != (last2 - first2)) return false;

		while (first1 != last1)
		{
			T_Iterator1 bufIt(first1);
			T_Iterator2 it(first2);
			while (it != last2)
			{
				if (predicate(*it, *first1))
				{
					++first1;
					break;
				}

				++it;
			}

			if (bufIt == first1)
				return false;
		}

		return true;
	}

	template<typename T_Iterator>
	inline T_Iterator Is_sorted_until(T_Iterator first, T_Iterator last)
	{
		if (first == last) return last;

		++first;

		while (first != last)
		{
			if (*first < *(first - 1))
				return first;
			++first;
		}

		return last;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Is_sorted_until(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return last;

		++first;

		while (first != last)
		{
			if (predicate(*first, *(first - 1)))
				return first;

			++first;
		}

		return last;
	}

	template<typename T_Iterator>
	inline bool Is_sorted(T_Iterator first, T_Iterator last)
	{
		return Is_sorted_until(first, last) == last;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline bool Is_sorted(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		return Is_sorted_until(first, last, predicate) == last;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline void Iter_swap(T_Iterator1 left, T_Iterator2 right)
	{
		auto val = *left;
		*left = *right;
		*right = val;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline bool Lexicographical_compare(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;

			++first1;
			++first2;
		}

		return (first1 == last1) && (first2 != last2);
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline bool Lexicographical_compare(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_Predicate predicate)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (predicate(*first1, *first2))
				return true;
			if (predicate(*first2, *first1))
				return false;

			++first1;
			++first2;
		}

		return (first1 == last1) && (first2 != last2);
	}

	template<typename T_Type>
	constexpr const T_Type& Max(const T_Type& left, const T_Type& right)
	{
		if (left > right) return left;
		return right;
	}

	template<typename T_Type, typename T_Predicate>
	constexpr const T_Type& Max(const T_Type& left, const T_Type& right, T_Predicate predicate)
	{
		if (predicate(left, right)) return left;
		return right;
	}

	template<typename T_Type>
	constexpr const T_Type& Max(Initializer_list<T_Type> ilist)
	{
		auto begin = ilist.Begin();
		auto end = ilist.End();
		auto Max = begin;

		while (begin != end) {
			if (*begin > *Max)
				Max = begin;

			++begin;
		}

		return *Max;
	}

	template<typename T_Type, typename T_Predicate>
	constexpr const T_Type& Max(Initializer_list<T_Type> ilist, T_Predicate predicate)
	{
		auto begin = ilist.Begin();
		auto end = ilist.End();
		auto Max = begin;

		while (begin != end) {
			if (predicate(*begin, *Max))
				Max = begin;

			++begin;
		}

		return *Max;
	}

	template<typename T_Iterator>
	constexpr T_Iterator Max_element(T_Iterator first, T_Iterator last)
	{
		T_Iterator Max = first;
		while (first != last)
		{
			if (*Max < *first)
				Max = first;

			++first;
		}
		return Max;
	}

	template<typename T_Iterator, typename T_Predicate>
	constexpr T_Iterator Max_element(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		T_Iterator Max = first;
		while (first != last)
		{
			if (predicate(*Max, *first))
				Max = first;

			++first;
		}
		return Max;
	}

	template<typename T_Type>
	constexpr const T_Type& Min(const T_Type& left, const T_Type& right)
	{
		if (left < right) return left;
		return right;
	}

	template<typename T_Type, typename T_Predicate>
	constexpr const T_Type& Min(const T_Type& left, const T_Type& right, T_Predicate predicate)
	{
		if (predicate(left, right)) return left;
		return right;
	}

	template<typename T_Type>
	constexpr const T_Type& Min(Initializer_list<T_Type> ilist)
	{
		auto begin = ilist.Begin();
		auto end = ilist.End();
		auto Min = begin;

		while (begin != end) {
			if (*begin < *Min)
				Min = begin;

			++begin;
		}

		return *Min;
	}

	template<typename T_Type, typename T_Predicate>
	constexpr const T_Type& Min(Initializer_list<T_Type> ilist, T_Predicate predicate)
	{
		auto begin = ilist.Begin();
		auto end = ilist.End();
		auto Min = begin;

		while (begin != end) {
			if (predicate(*begin, *Min))
				Min = begin;

			++begin;
		}

		return *Min;
	}

	template<typename T_Iterator>
	constexpr T_Iterator Min_element(T_Iterator first, T_Iterator last)
	{
		T_Iterator Min(first);
		while (first != last)
		{
			if (*Min > *first)
				Min = first;

			++first;
		}
		return Min;
	}

	template<typename T_Iterator, typename T_Predicate>
	constexpr T_Iterator Min_element(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		T_Iterator Min(first);
		while (first != last)
		{
			if (predicate(*Min, *first))
				Min = first;

			++first;
		}
		return Min;
	}

	template<typename T_Type>
	constexpr Pair<const T_Type&, const T_Type&> MinMax(const T_Type& left, const T_Type& right)
	{
		if (left < right) return Pair<const T_Type&, const T_Type&>(left, right);
		return Pair<const T_Type&, const T_Type&>(right, left);
	}

	template<typename T_Type, typename T_Predicate>
	constexpr const T_Type& MinMax(const T_Type& left, const T_Type& right, T_Predicate predicate)
	{
		if (predicate(left, right)) return Pair<const T_Type&, const T_Type&>(left, right);
		return Pair<const T_Type&, const T_Type&>(right, left);
	}

	template<typename T_Type>
	constexpr const T_Type& MinMax(Initializer_list<T_Type> ilist)
	{
		auto begin = ilist.Begin();
		auto end = ilist.End();
		auto Min = begin;
		auto Max = begin;

		while (begin != end) {
			if (*begin < *Min)
				Min = begin;
			if (*begin > *Max)
				Max = begin;

			++begin;
		}

		return Pair<const T_Type&, const T_Type&>(Min, Max);
	}

	template<typename T_Type, typename T_Predicate>
	constexpr const T_Type& MinMax(Initializer_list<T_Type> ilist, T_Predicate predicate)
	{
		auto begin = ilist.Begin();
		auto end = ilist.End();
		auto Min = begin;
		auto Max = begin;

		while (begin != end) {
			if (predicate(*begin, *Min))
				Min = begin;
			if (predicate(*Max, *begin))
				Max = begin;

			++begin;
		}

		return Pair<const T_Type&, const T_Type&>(Min, Max);
	}

	template<typename T_Iterator>
	constexpr T_Iterator MinMax_element(T_Iterator first, T_Iterator last)
	{
		T_Iterator Min(first);
		T_Iterator Max(first);

		while (first != last)
		{
			if (*Min > *first)
				Min = first;
			if (*Max < *first)
				Max = first;

			++first;
		}

		return Pair<T_Iterator, T_Iterator>(Min, Max);
	}

	template<typename T_Iterator, typename T_Predicate>
	constexpr T_Iterator MinMax_element(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		T_Iterator Min(first);
		T_Iterator Max(first);

		while (first != last)
		{
			if (predicate(*Min, *first))
				Min = first;
			if (predicate(*first, *Max))
				Max = first;

			++first;
		}
		return Pair<T_Iterator, T_Iterator>(Min, Max);
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput>
	inline T_IteratorOutput Merge(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++first1;
				++result;
			}
			else
			{
				*result = *first2;
				++first2;
				++result;
			}
		}

		while (first1 != last1)
		{
			*result = *first1;
			++first1;
			++result;
		}

		while (first2 != last2)
		{
			*result = *first2;
			++first2;
			++result;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput, typename T_Predicate>
	inline T_IteratorOutput Merge(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result, T_Predicate predicate)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (predicate(*first1, *first2))
			{
				*result = *first1;
				++first1;
				++result;
			}
			else
			{
				*result = *first2;
				++first2;
				++result;
			}
		}

		while (first1 != last1)
		{
			*result = *first1;
			++first1;
			++result;
		}

		while (first2 != last2)
		{
			*result = *first2;
			++first2;
			++result;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline Pair<T_Iterator1, T_Iterator2> Mismatch(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			++first1;
			++first2;
		}

		return Pair<T_Iterator1, T_Iterator2>(first1, first2);
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline Pair<T_Iterator1, T_Iterator2> Mismatch(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Predicate predicate)
	{
		while (first1 != last1 && predicate(*first1, *first2))
		{
			++first1;
			++first2;
		}

		return Pair<T_Iterator1, T_Iterator2>(first1, first2);
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline Pair<T_Iterator1, T_Iterator2> Mismatch(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2)
	{
		if ((last1 - first1) != (last2 - first2)) return Pair<T_Iterator1, T_Iterator2>(first1, first2);

			while (first1 != last1 && *first1 == *first2)
			{
				++first1;
				++first2;
			}

		return Pair<T_Iterator1, T_Iterator2>(first1, first2);
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline Pair<T_Iterator1, T_Iterator2> Mismatch(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_Predicate predicate)
	{
		if ((last1 - first1) != (last2 - first2)) return Pair<T_Iterator1, T_Iterator2>(first1, first2);

		while (first1 != last1 && predicate(*first1, *first2))
		{
			++first1;
			++first2;
		}

		return Pair<T_Iterator1, T_Iterator2>(first1, first2);
	}

	template<typename T_IteratorInput, typename T_IteratorOutput>
	inline T_IteratorOutput Move(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput output)
	{
		while (first != last)
		{
			output = Move(*first);

			++first;
			++output;
		}

		return output;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput>
	inline T_IteratorOutput Move_backward(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput output)
	{
		while (first != last)
		{
			--last;
			--output;
			output = Move(*last);
		}

		return output;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline bool None_of(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		while (first != last)
		{
			if (predicate(*first))
				return false;

			++first;
		}
		return true;
	}

	template<typename T_Iterator>
	inline T_Iterator Nth_element(T_Iterator first, T_Iterator nth, T_Iterator last)
	{
		--last;
		Iter_swap(nth, last);
		nth = last;

		T_Iterator i = first;
		for (T_Iterator j = first; j < last; ++j) {
			if (*j <= *nth) {
				Iter_swap(i, j);
				++i;
			}
		}

		Iter_swap(i, last);
		return i;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Nth_element(T_Iterator first, T_Iterator nth, T_Iterator last, T_Predicate predicate)
	{
		--last;
		Iter_swap(nth, last);
		nth = last;

		T_Iterator i = first;
		for (T_Iterator j = first; j < last; ++j) {
			if (predicate(*j, *nth)) {
				Iter_swap(i, j);
				++i;
			}
		}

		Iter_swap(i, last);
		return i;
	}

	template<typename T_Iterator>
	inline void Partial_sort(T_Iterator first, T_Iterator sortEnd, T_Iterator last)
	{
		while (first != sortEnd)
		{
			T_Iterator min(first);
			T_Iterator it(first);

			while (it != last)
			{
				if (*it < *min)
					min = it;

				++it;
			}

			Iter_swap(first, min);

			++first;
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Partial_sort(T_Iterator first, T_Iterator sortEnd, T_Iterator last, T_Predicate predicate)
	{
		while (first != sortEnd)
		{
			T_Iterator temp(first);
			T_Iterator it(first);

			while (it != last)
			{
				if (predicate(*it, *temp))
					temp = it;

				++it;
			}

			Iter_swap(first, temp);

			++first;
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Partition(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return first;

		--last;

		while (first < last)
		{
			while (predicate(*first))
				++first;

			while (!predicate(*last))
				--last;

			if (last > first)
				Iter_swap(first, last);
		}

		return first;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput1, typename T_IteratorOutput2, typename T_Predicate>
	inline Pair<T_IteratorOutput1, T_IteratorOutput2> Partition_copy(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput1 out1, T_IteratorOutput2 out2, T_Predicate predicate)
	{
		while (first != last)
		{
			if (predicate(*first))
			{
				*out1 = *first;
				++out1;
			}
			else
			{
				*out2 = *first;
				++out2;
			}

			++first;
		}
		return Pair<T_IteratorOutput1, T_IteratorOutput2>(out1, out2);
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Partition_point(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		while (first != last && predicate(*first))
			++first;

		return first;
	}

	template<typename T_Iterator>
	inline void Push_heap(T_Iterator first, T_Iterator last)
	{
		if (first == last) return;
		
		--last;
		size_t index = last - first;
		size_t parent = (index - 1) / 2;
		while (index > 0)
		{
			T_Iterator it_index = first + index;
			T_Iterator it_parent = first + parent;
			if (*it_index > *it_parent) {
				Iter_swap(it_index, it_parent);
				index = parent;
				parent = (index - 1) / 2;
			}
			else
				break;
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Push_heap(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return;

		--last;
		size_t index = last - first;
		size_t parent = (index - 1) / 2;
		while (index>0)
		{
			T_Iterator it_index = first + index;
			T_Iterator it_parent = first + parent;
			if (predicate(*it_index, *it_parent)) {
				Iter_swap(it_index, it_parent);
				index = parent;
				parent = (index - 1) / 2;
			}
			else
				break;
		}
	}

	template<typename T_Iterator>
	inline void Pop_heap(T_Iterator first, T_Iterator last)
	{
		if (first == last) return;
		Iter_swap(first, --last);
		
		size_t index = 0;
		size_t left = 1;
		size_t right = 2;
		size_t Size = last - first;
		while (left < Size) {
			T_Iterator it_index = first + index;
			T_Iterator it_left = first + left;
			T_Iterator it_right = first + right;

			if (right == Size) {
				if(*it_left > *it_index)
					Iter_swap(it_index, it_left);

				break;
			}

			if (*it_index > *it_left)
			{
				if (*it_index > *it_right)
					break;
				else
				{
					Iter_swap(it_index, it_right);
					index = right;
				}
			}
			else
			{
				if (*it_index > *it_right)
				{
					Iter_swap(it_index, it_left);
					index = left;
				}
				else
				{
					if (*it_right > *it_left)
					{
						Iter_swap(it_index, it_right);
						index = right;
					}
					else
					{
						Iter_swap(it_index, it_left);
						index = left;
					}
				}
			}

			left = index * 2 - 1;
			right = index * 2;
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Pop_heap(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return;
		Iter_swap(first, --last);

		size_t index = 0;
		size_t left = 1;
		size_t right = 2;
		size_t Size = last - first;
		while (left < Size) {
			T_Iterator it_index = first + index;
			T_Iterator it_left = first + left;
			T_Iterator it_right = first + right;

			if (right == Size) {
				if (predicate(*it_left, *it_index))
					Iter_swap(it_index, it_left);

				break;
			}

			if (predicate(*it_index, *it_left))
			{
				if (predicate(*it_index, *it_right))
					break;
				else
				{
					Iter_swap(it_index, it_right);
					index = right;
				}
			}
			else
			{
				if (predicate(*it_index, *it_right))
				{
					Iter_swap(it_index, it_left);
					index = left;
				}
				else
				{
					if (predicate(*it_right, *it_left))
					{
						Iter_swap(it_index, it_right);
						index = right;
					}
					else
					{
						Iter_swap(it_index, it_left);
						index = left;
					}
				}
			}

			left = index * 2 - 1;
			right = index * 2;
		}
	}

	template<typename T_Iterator>
	inline void Make_heap(T_Iterator first, T_Iterator last)
	{
		T_Iterator it=first+1;
		while (it != last) 
		{
			Push_heap(first, it);
			++it;
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Make_heap(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		T_Iterator it = first + 1;
		while (it != last)
		{
			Push_heap(first, it, predicate);
			++it;
		}
	}

	template<typename T_Iterator, typename T_Type>
	inline T_Iterator Remove(T_Iterator first, T_Iterator last, const T_Type& value) 
	{
		T_Iterator it = first;
		
		while (it != last)
		{
			if (*it == value)
				++it;
			else
			{
				*first = *it;
				++first;
				++it;
			}
		}

		return first;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput, typename T_Type>
	inline T_IteratorOutput Remove_copy(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput result, const T_Type& value)
	{
		while (first != last)
		{
			if (*first != value)
			{
				*result = *first;
				++result;
			}
			++first;
		}
		return result;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput, typename T_Predicate>
	inline T_IteratorOutput Remove_copy_if(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput result, T_Predicate predicate)
	{
		while (first != last)
		{
			if (!predicate(*first))
			{
				*result = *first;
				++result;
			}
			++first;
		}
		return result;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Remove_if(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		T_Iterator it = first;

		while (it != last)
		{
			if (predicate(*it))
				++it;
			else
			{
				*first = *it;
				++first;
				++it;
			}
		}

		return first;
	}

	template<typename T_Iterator, typename T_Type>
	inline void Replace(T_Iterator first, T_Iterator last, const T_Type& oldVal, const T_Type& newVal)
	{
		while (first != last)
		{
			if (*first == oldVal)
				*first = newVal;

			++first;
		}
	}

	template<typename T_Iterator, typename T_IteratorOutput, typename T_Type>
	inline T_IteratorOutput Replace_copy(T_Iterator first, T_Iterator last, T_IteratorOutput result, const T_Type& oldVal, const T_Type& newVal)
	{
		while (first != last)
		{
			if (*first == oldVal)
				*result = newVal;
			else
				*result = *first;

			++result;
			++first;
		}

		return result;
	}

	template<typename T_Iterator, typename T_IteratorOutput, typename T_Type, typename T_Predicate>
	inline T_IteratorOutput Replace_copy_if(T_Iterator first, T_Iterator last, T_IteratorOutput result, T_Predicate predicate, const T_Type& value)
	{
		while (first != last)
		{
			if (predicate(*first))
				*result = value;
			else
				*result = *first;

			++result;
			++first;
		}

		return result;
	}

	template<typename T_Iterator, typename T_Type, typename T_Predicate>
	inline void Replace_if(T_Iterator first, T_Iterator last, T_Predicate predicate, const T_Type& value)
	{
		while (first != last)
		{
			if (predicate(*first))
				*first = value;

			++first;
		}
	}

	template<typename T_Iterator>
	inline void Reverse(T_Iterator first, T_Iterator last)
	{
		if (first == last) return;

		--last;

		while (last > first)
		{
			Iter_swap(first, last);
			++first;
			--last;
		}
	}

	template<typename T_Iterator, typename T_IteratorOutput>
	inline void Reverse_copy(T_Iterator first, T_Iterator last, T_IteratorOutput result)
	{
		while (last != first)
		{
			--last;
			*result = *last;
			++result;
		}
	}

	template<typename T_Iterator>
	inline void Rotate(T_Iterator first, T_Iterator middle, T_Iterator last)
	{
		if (first == middle || middle == last)
			return;

		T_Iterator next(middle);

		while (first != next)
		{
			Iter_swap(first, next);
			++first;
			++next;

			if (next == last)
				next = middle;
			else if (first == middle)
				middle = next;
		}
	}

	template<typename T_Iterator, typename T_IteratorOutput>
	inline T_IteratorOutput Rotate_copy(T_Iterator first, T_Iterator middle, T_Iterator last, T_IteratorOutput result)
	{
		T_Iterator currentSrc(middle);
		while (currentSrc != last)
		{
			*result = *currentSrc;
			++result;
			++currentSrc;
		}

		currentSrc = first;
		while (currentSrc != middle)
		{
			*result = *currentSrc;
			++result;
			++currentSrc;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline T_Iterator1 Search(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2)
	{
		if (first2 == last2)
			return first1;

		while (first1 != last1)
		{
			T_Iterator1 current1(first1);
			T_Iterator2 current2(first2);

			while (*current1 == *current2)
			{
				++current1;
				++current2;

				if (current2 == last2)
					return first1;
			}

			++first1;
		}

		return last1;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline T_Iterator1 Search(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_Predicate predicate)
	{
		if (first2 == last2)
			return first1;

		while (first1 != last1)
		{
			T_Iterator1 current1(first1);
			T_Iterator2 current2(first2);

			while (predicate(*current1, *current2))
			{
				++current1;
				++current2;

				if (current2 == last2)
					return first1;
			}

			++first1;
		}

		return last1;
	}

	template<typename T_Iterator, typename T_Type>
	inline T_Iterator Search_n(T_Iterator first, T_Iterator last, size_t count, const T_Type& value)
	{
		if (count == 0)
			return first;

		while (first != last)
		{
			T_Iterator current(first);
			size_t currentCount(0);

			while (*current == value)
			{
				++current;
				++currentCount;

				if (currentCount == count)
					return first;
			}

			++first;
		}

		return last;
	}

	template<typename T_Iterator, typename T_Type, typename T_Predicate>
	inline T_Iterator Search_n(T_Iterator first, T_Iterator last, size_t count, const T_Type& value, T_Predicate predicate)
	{
		if (count == 0)
			return first;

		while (first != last)
		{
			T_Iterator current(first);
			size_t currentCount(0);

			while (predicate(*current, value))
			{
				++current;
				++currentCount;

				if (currentCount == count)
					return first;
			}

			++first;
		}

		return last;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput>
	inline T_IteratorOutput Set_difference(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++result;
				++first1;
			}
			else if (*first2 < *first1)
			{
				++first2;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		while (first1 != last1)
		{
			*result = *first1;
			++result;
			++first1;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput, typename T_Predicate>
	inline T_IteratorOutput Set_difference(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result, T_Predicate predicate)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (predicate(*first1, *first2))
			{
				*result = *first1;
				++result;
				++first1;
			}
			else if (predicate(*first2, *first1))
			{
				++first2;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		while (first1 != last1)
		{
			*result = *first1;
			++result;
			++first1;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput>
	inline T_IteratorOutput Set_intersection(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				++first1;
			}
			else if (*first2 < *first1)
			{
				++first2;
			}
			else
			{
				*result = *first1;
				++result;
				++first1;
				++first2;
			}
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput, typename T_Predicate>
	inline T_IteratorOutput Set_intersection(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result, T_Predicate predicate)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (predicate(*first1, *first2))
			{
				++first1;
			}
			else if (predicate(*first2, *first1))
			{
				++first2;
			}
			else
			{
				*result = *first1;
				++result;
				++first1;
				++first2;
			}
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput>
	inline T_IteratorOutput Set_symmetric_difference(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++result;
				++first1;
			}
			else if (*first2 < *first1)
			{
				*result = *first2;
				++result;
				++first2;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		while (first1 != last1)
		{
			*result = *first1;
			++result;
			++first1;
		}

		while (first2 != last2)
		{
			*result = *first2;
			++result;
			++first2;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput, typename T_Predicate>
	inline T_IteratorOutput Set_symmetric_difference(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result, T_Predicate predicate)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (predicate(*first1, *first2))
			{
				*result = *first1;
				++result;
				++first1;
			}
			else if (predicate(*first2, *first1))
			{
				*result = *first2;
				++result;
				++first2;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		while (first1 != last1)
		{
			*result = *first1;
			++result;
			++first1;
		}

		while (first2 != last2)
		{
			*result = *first2;
			++result;
			++first2;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput>
	inline T_IteratorOutput Set_union(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++result;
				++first1;
			}
			else if (*first2 < *first1)
			{
				*result = *first2;
				++result;
				++first2;
			}
			else
			{
				*result = *first1;
				++result;
				++first1;
				++first2;
			}
		}

		while (first1 != last1)
		{
			*result = *first1;
			++result;
			++first1;
		}

		while (first2 != last2)
		{
			*result = *first2;
			++result;
			++first2;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput, typename T_Predicate>
	inline T_IteratorOutput Set_union(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result, T_Predicate predicate)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (predicate(*first1, *first2))
			{
				*result = *first1;
				++result;
				++first1;
			}
			else if (predicate(*first2, *first1))
			{
				*result = *first2;
				++result;
				++first2;
			}
			else
			{
				*result = *first1;
				++result;
				++first1;
				++first2;
			}
		}

		while (first1 != last1)
		{
			*result = *first1;
			++result;
			++first1;
		}

		while (first2 != last2)
		{
			*result = *first2;
			++result;
			++first2;
		}

		return result;
	}

	template<typename T_Iterator>
	inline void Sort_heap(T_Iterator first, T_Iterator last)
	{
		T_Iterator it = DVTL::Is_sorted_until(first, last, [](int a, int b) {return a > b; });

		while (it != last) {
			DVTL::Make_heap(it - 1, last);
			it = DVTL::Is_sorted_until(first, last, [](int a, int b) {return a > b; });
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Sort_heap(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		T_Iterator it = DVTL::Is_sorted_until(first, last, predicate);

		while (it != last) {
			DVTL::Make_heap(it - 1, last, predicate);
			it = DVTL::Is_sorted_until(first, last, predicate);
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Stable_partition(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) {
			return;
		}

		T_Iterator left = first;
		T_Iterator right = Find_if_not(first, last, predicate);

		while (right != last) {
			Iter_swap(left, right);
			++left;
			right = Find_if_not(right + 1, last, predicate);
		}
	}

	template<typename T_Type>
	inline void Swap(T_Type& left, T_Type& right)
	{
		T_Type temp = left;
		left = right;
		right = temp;
	}

	template<typename T_Type, size_t N>
	constexpr void Swap(T_Type(&left)[N], T_Type(&right)[N])
	{
		for (size_t i = 0; i < N; ++i)
		{
			T_Type temp = left[i];
			left[i] = right[i];
			right[i] = temp;
		}
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline void Swap_ranges(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2)
	{
		while (first1 != last1) {
			T_Iterator2 temp = first2;
			*first2 = *first1;
			*first1 = *temp;

			++first1;
			++first2;
		}
	}

	template<typename T_Iterator, typename T_IteratorOutput, typename T_Predicate>
	inline T_IteratorOutput Transform(T_Iterator first, T_Iterator last, T_IteratorOutput result, T_Predicate predicate)
	{
		while (first != last)
		{
			*result = predicate(*first);
			++first;
			++result;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_IteratorOutput, typename T_Predicate>
	inline T_IteratorOutput Transform(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_IteratorOutput result, T_Predicate predicate)
	{
		while (first1 != last1)
		{
			*result = predicate(*first1, *first2);
			++first1;
			++first2;
			++result;
		}

		return result;
	}

	template<typename T_Iterator>
	inline T_Iterator Unique(T_Iterator first, T_Iterator last)
	{
		if (first == last) {
			return last;
		}

		T_Iterator result = first;
		++first;

		while (first != last) {
			if (*result != *first) {
				++result;
				*result = *first;
			}
			++first;
		}

		return ++result;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Unique(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) {
			return last;
		}

		T_Iterator result = first;
		++first;

		while (first != last) {
			if (predicate(*result, *first)) {
				++result;
				*result = *first;
			}
			++first;
		}

		return ++result;
	}

	template<typename T_Iterator, typename T_Iterator2>
	inline T_Iterator2 Unique_copy(T_Iterator first, T_Iterator last, T_Iterator2 result)
	{
		if (first == last) {
			return result;
		}

		*result = *first;
		++result;
		++first;

		while (first != last) {
			if (*first != *(first - 1)) {
				*result = *first;
				++result;
			}

			++first;
		}

		return result;
	}

	template<typename T_Iterator, typename T_Iterator2, typename T_Predicate>
	inline T_Iterator2 Unique_copy(T_Iterator first, T_Iterator last, T_Iterator2 result, T_Predicate predicate)
	{
		if (first == last) {
			return result;
		}

		*result = *first;
		++result;
		++first;

		while (first != last) {
			if (predicate(*first, *(first - 1))) {
				*result = *first;
				++result;
			}

			++first;
		}

		return result;
	}

	template<typename T_Iterator>
	inline bool Next_permutation(T_Iterator first, T_Iterator last)
	{
		if (first == last)return false;

		T_Iterator i = last;

		if (first == --i) return false;

		while (true) {
			T_Iterator i1=i;

			--i;

			if (*i < *i1) {
				T_Iterator i2 = last-1;

				while (!(*i < *i2)) --i2;

				Iter_swap(i, i2);
				Reverse(i1, last);
				return true;
			}

			if (i == first) {
				Reverse(first, last);
				return false;
			}
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline bool Next_permutation(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return false;

		T_Iterator i = last;

		if (first == --i) return false;

		while (true) {
			T_Iterator i1 = i;

			--i;

			if (predicate(*i, *i1)) {
				T_Iterator i2 = last - 1;

				while (!predicate(*i, *i2)) --i2;

				Iter_swap(i, i2);
				Reverse(i1, last);
				return true;
			}

			if (i == first) {
				Reverse(first, last);
				return false;
			}
		}
	}

	template<typename T_Iterator>
	inline bool Prev_permutation(T_Iterator first, T_Iterator last) 
	{
		if (first == last) return false;

		T_Iterator i = last;

		if (first == --i) return false;

		while (true) {
			T_Iterator i1 = i;

			--i;

			if (*i1 < *i) {
				T_Iterator i2 = last-1;

				while (!(*i2 < *i)) --i2;

				Iter_swap(i, i2);
				Reverse(i1, last);
				return true;
			}

			if (i == first) {
				Reverse(first, last);
				return false;
			}
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline bool Prev_permutation(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return false;

		T_Iterator i = last;

		if (first == --i) return false;

		while (true) {
			T_Iterator i1 = i;

			--i;

			if (predicate(*i1, *i)) {
				T_Iterator i2 = last - 1;

				while (!predicate(*i2, *i)) --i2;

				Iter_swap(i, i2);
				Reverse(i1, last);
				return true;
			}

			if (i == first) {
				Reverse(first, last);
				return false;
			}
		}
	}

	template<typename T_Iterator1, typename T_Iterator2>
	inline T_Iterator2 Partial_sort_copy(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2)
	{
		if (first1 == last1 || first2 == last2) return last2;

		T_Iterator1 current = first1;
		T_Iterator1 lastMin = first1;
		T_Iterator1 Max = first1;

		while (current != last1)
		{
			if (*current < *lastMin)
				lastMin = current;

			if (*Max < *current)
				Max = current;

			++current;
		}

		*first2 = *lastMin;
		++first2;

		while (first2 != last2)
		{
			T_Iterator1 Min = Max;
			current = first1;

			while (current != last1)
			{
				if (*current < *Min)
				{
					if (*lastMin < *current) Min = current;
					else if (*lastMin == *current && current > lastMin)
					{
						Min = current;
						break;
					}
				}

				++current;
			}

			*first2 = *Min;
			lastMin = Min;
			++first2;
		}
		return first2;
	}

	template<typename T_Iterator1, typename T_Iterator2, typename T_Predicate>
	inline T_Iterator2 Partial_sort_copy(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_Predicate predicate)
	{
		if (first1 == last1 || first2 == last2) return last2;

		T_Iterator1 current = first1;
		T_Iterator1 lastMin = first1;
		T_Iterator1 Max = first1;

		while (current != last1)
		{
			if (predicate(*current, *lastMin))
				lastMin = current;

			if (predicate(*Max, *current))
				Max = current;

			++current;
		}

		*first2 = *lastMin;
		++first2;

		while (first2 != last2)
		{
			T_Iterator1 Min = Max;
			current = first1;

			while (current != last1)
			{
				if (predicate(*current, *Min))
				{
					if (predicate(*lastMin, *current)) Min = current;
					else if (!(predicate(*lastMin, *current) || predicate(*current, *lastMin)) && current > lastMin)
					{
						Min = current;
						break;
					}
				}

				++current;
			}

			*first2 = *Min;
			lastMin = Min;
			++first2;
		}
		return first2;
	}

	template<typename T_Iterator>
	inline void Sort(T_Iterator first, T_Iterator last)
	{
		if (last - first < 6)
		{
			Partial_sort(first, last, last);
			return;
		}

		T_Iterator nth = first + (last - first) / 2;
		nth = Nth_element(first, nth, last);

		Sort(first, nth);
		Sort(nth + 1, last);
	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Sort(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (last - first < 6)
		{
			Partial_sort(first, last, last, predicate);
			return;
		}

		T_Iterator nth = first + (last - first) / 2;
		nth = Nth_element(first, nth, last, predicate);

		Sort(first, nth, predicate);
		Sort(nth + 1, last, predicate);
	}

	template<typename T_Iterator>
	inline void Stable_sort(T_Iterator first, T_Iterator last)
	{
		size_t size = last-first;

		if (size > 1) {
			T_Iterator middle = first + size / 2;

			Stable_sort(first, middle);
			Stable_sort(middle, last);

			Inplace_merge(first, middle, last);
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Stable_sort(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		size_t size = last - first;

		if (size > 1) {
			T_Iterator middle = first + size / 2;

			Stable_sort(first, middle, predicate);
			Stable_sort(middle, last, predicate);

			Inplace_merge(first, middle, last, predicate);
		}
	}
}

#endif // !DVTL_ALGORITHM_H

