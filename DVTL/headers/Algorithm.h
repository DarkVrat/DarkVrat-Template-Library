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
	inline T_Iterator Find_not(T_Iterator first, T_Iterator last, T_Predicate predicate)
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

		while (first != last2 && middle != last)
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
			if (*(first - 1) > *first)
				break;

			++first;
		}

		return first;
	}

	template<typename T_Iterator, typename T_Predicate>
	inline T_Iterator Is_sorted_until(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return last;

		++first;

		while (first != last)
		{
			if (!predicate(*(first - 1), first))
				break;

			++first;
		}

		return first;
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
	void Iter_swap(T_Iterator1 left, T_Iterator2 right)
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

	template<typename T_Iterator>
	inline void Make_heap(T_Iterator first, T_Iterator last)
	{
		bool retry = true;
		T_Iterator stop = first;
		while (retry)
		{
			retry = false;

			for (T_Iterator it(last + 1); it != stop; --it) {
				T_Iterator parent(first + (it - first - 1) / 2);

				if (*it > *parent) {
					Iter_swap(it, parent);
					retry = true;
				}
			}

			stop = first + (stop - first + 1) * 2;
		}
	}

	template<typename T_Iterator, typename T_Predicate>
	inline void Make_heap(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		bool retry = true;
		T_Iterator stop = first;

		while (retry)
		{
			retry = false;

			for (T_Iterator it(last + 1); it != stop; --it) {
				T_Iterator parent(first + (it - first - 1) / 2);

				if (predicate(*it, *parent)) {
					Iter_swap(it, parent);
					retry = true;
				}
			}

			stop = first + (stop - first + 1) * 2;
		}
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
	T_IteratorOutput Merge(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result)
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
	T_IteratorOutput Merge(T_Iterator1 first1, T_Iterator1 last1, T_Iterator2 first2, T_Iterator2 last2, T_IteratorOutput result, T_Predicate predicate)
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


}

#endif // !DVTL_ALGORITHM_H

