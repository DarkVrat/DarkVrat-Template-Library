#ifndef DVTL_ALGORITHM_H
#define DVTL_ALGORITHM_H

namespace DVTL {
	template<typename T_Iterator>
	T_Iterator Adjacent_find(T_Iterator first, T_Iterator last)
	{
		if (first == last) return last;

		T_Iterator temp = first++;

		while (first != last)
		{
			if (*temp == *first) return temp;

			temp = first;
			++first;
		}

		return last;
	}

	template<typename T_Iterator, typename T_Predicate>
	T_Iterator Adjacent_find(T_Iterator first, T_Iterator last, T_Predicate predicate)
	{
		if (first == last) return last;

		T_Iterator temp = first++;

		while (first != last)
		{
			if (predicate(*temp, *first)) return temp;

			temp = first;
			++first;
		}

		return last;
	}

	template<typename T_Iterator, typename T_Predicate>
	bool All_of(T_Iterator first, T_Iterator last, T_Predicate predicate)
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
	bool Any_of(T_Iterator first, T_Iterator last, T_Predicate predicate)
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
	bool Binary_search(T_Iterator first, T_Iterator last, const T_Type& value) 
	{
		while (first != last) {
			T_Iterator middle = first + (last - first) / 2;

			if (*middle == value) return true;
			else if (*middle < value) first = ++middle;
			else last = middle;
		}

		return false;
	}

	template<typename T_Iterator, typename T_Type, typename T_Predicate>
	bool Binary_search(T_Iterator first, T_Iterator last, const T_Type& value, T_Predicate predicate)
	{
		while (first < last) {
			T_Iterator middle = first + (last - first) / 2;

			if (predicate(*middle, value) == 0) return true;
			else if (predicate(*middle, value) < 0) first = middle + 1;
			else last = middle;
		}

		return false;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput>
	T_IteratorOutput Copy(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput output)
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
	T_IteratorOutput Copy_backward(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput output)
	{
		if (first == last) return output;

		while (first != last)
		{
			*(--output) = *(--last);
		}

		return output;
	}

	template<typename T_IteratorInput, typename T_IteratorOutput, typename T_Predicate>
	T_IteratorOutput Copy_if(T_IteratorInput first, T_IteratorInput last, T_IteratorOutput output, T_Predicate predicate)
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
	T_IteratorOutput Copy_if(T_IteratorInput first, size_t count, T_IteratorOutput output)
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
	size_t Count(T_Iterator first, T_Iterator last, const T_Type& value)
	{
		size_t result = 0;

		while (first != last) {
			if (*first == value)
				result++;

			++first;
		}

		return result;
	}

	template<typename T_Iterator, typename T_Type, typename T_Predicate>
	size_t Count_if(T_Iterator first, T_Iterator last, const T_Type& value, T_Predicate predicate)
	{
		size_t result = 0;

		while (first != last) {
			if (predicate(*first, value))
				result++;

			++first;
		}

		return result;
	}

	template<typename T_Iterator1, typename T_Iterator2>
	bool Equal(T_Iterator1 first1, T_Iterator2 last1, T_Iterator2 first2)
	{
		
	}
}

#endif // !DVTL_ALGORITHM_H

