#ifndef DVTL_VECTOR_H
#define DVTL_VECTOR_H

#include "allocator.h"

namespace DVTL 
{
	template<typename T>
	class vector 
	{
	public:
		//constructors, operators= and destructor
					vector() noexcept;
		explicit	vector(size_t size);
		explicit	vector(size_t size, const T& value);

		vector(const vector& source);
		vector(vector&& source)	noexcept;
		vector& operator=(const vecotr& source);
		vector& operator=(vector&& source) noexcept;

		~vector() noexcept;

		//getting vector data
		inline size_t	capacity()	const	noexcept { return m_capacity; }
		inline size_t	size()		const	noexcept { return m_size; }
		inline const T* data()		const	noexcept { return m_data; }
		inline T*		data()				noexcept { return m_data; }
		inline bool		empty()		const	noexcept { return m_size == 0; }

		//references to vector elements
		T& front();
		T& back();
		T& at(size_t index);
		T& operator[](size_t index) noexcept;
		const T& front()	const;
		const T& back()		const;
		const T& at(size_t index) const;
		const T& operator[](size_t index) const noexcept;
	
		//working with data
		void reserve(size_t count);
		void resize(size_t new_size);
		void resize(size_t new_size, const T& value);
		void assign(size_t count, const T& value);
		void clear();
		void shrink_to_fit();
		void swap(vector& vector);

		//adding and removing elements to a vector
		void push_back(const T& value);
		void push_back(T&&);
		void pop_back();
		//template <class... Types> iterator emplace(const const_iterator& position, Types&&... args);
		//template <class... Types> iterator emplace_back(Types&&... args);
		//iterator inset(const const_iterator& position, const T& value);
		//iterator inset(const const_iterator& position, T&& value);
		//iterator inset(const const_iterator& position, size_t count, const T& value);
		//iterator erase(const const_iterator& position);
		//iterator erase(const const_iterator& first, const const_iterator& last);

		//getting iterators
		//iterator begin();
		//iterator end();
		//const_iterator begin()	const;
		//const_iterator end()		const;
		//const_iterator cbegin()	const;
		//const_iterator cend()		const;
		//reverse_iterator rbegin();
		//reverse_iterator rend();
		//const_reverse_iterator rbegin()	const;
		//const_reverse_iterator rend()		const;
		//const_reverse_iterator crbegin()	const;
		//const_reverse_iterator crend()	const;
	private:
		size_t m_size;
		size_t m_capacity;
		T* m_data;
	};
	
	template<typename T>
	inline void swap(vector<T>& left, vector<T>& right)
	{
		left.swap(right);
	}

}



#endif // !DVTL_VECTOR_H