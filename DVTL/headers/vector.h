#ifndef DVTL_VECTOR_H
#define DVTL_VECTOR_H

#include "allocator.h"
#include "unique_ptr.h"

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
		vector(vector&& source)					noexcept;
		vector<T>& operator=(const vector& source);
		vector<T>& operator=(vector&& source)	noexcept;

		~vector() noexcept;

		//getting vector data
		inline size_t	capacity()	const	noexcept { return m_capacity; }
		inline size_t	size()		const	noexcept { return m_size; }
		inline const T* data()		const	noexcept { return m_data; }
		inline T*		data()				noexcept { return m_data; }
		inline bool		empty()		const	noexcept { return m_size == 0; }

		//references to vector elements
		T& at(size_t index);
		T& front();
		T& back();
		T& operator[](size_t index)			noexcept;
		const T& at(size_t index)			const;
		const T& front()					const;
		const T& back()						const;
		const T& operator[](size_t index)	const noexcept;
	
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
		size_t m_capacity;
		size_t m_size;
		T* m_data;
	};
	
	

	template<typename T>
	inline vector<T>::vector() noexcept : m_capacity(0), m_size(0), m_data(nullptr){}

	template<typename T>
	inline vector<T>::vector(size_t size) : m_capacity(size), m_size(m_capacity), m_data(allocator<T>::allocate(m_capacity)) {}

	template<typename T>
	inline vector<T>::vector(size_t size, const T& value) : m_capacity(size), m_size(m_capacity), m_data(allocator::allocate<T>(m_capacity))
	{
		for (size_t i = 0; i < size; i++)
			allocator::construct(m_data, i, value);
	}

	template<typename T>
	inline vector<T>::vector(const vector& source) : m_capacity(source.m_size), m_size(m_capacity), m_data(allocator::allocate<T>(m_capacity))
	{
		for (size_t i = 0; i < m_size; i++)
			allocator::construct(m_data, i, source[i]);
	}

	template<typename T>
	inline vector<T>::vector(vector&& source) noexcept : m_capacity(source.m_capacity), m_size(source.m_size), m_data(source.m_data)
	{
		source.m_capacity = 0;
		source.m_size = 0;
		source.m_data = nullptr;
	}

	template<typename T>
	inline vector<T>& vector<T>::operator=(const vector& source)
	{
		if (source.m_data == m_data) return *this;

		if (m_data != nullptr) {
			for (size_t i = 0; i < m_size; i++)
				allocator::destroy(m_data, i);
			allocator::deallocate(m_data);
		}

		m_capacity = source.m_size;
		m_size = m_capacity;
		m_data = allocator::allocate<T>(m_capacity);
		for (size_t i = 0; i < m_size; i++)
			allocator::construct(m_data, i, source[i]);

		return *this;
	}

	template<typename T>
	inline vector<T>& vector<T>::operator=(vector&& source) noexcept
	{
		if (source.m_data == m_data) return *this;

		if (m_data != nullptr) {
			for (size_t i = 0; i < m_size; i++)
				allocator::destroy(m_data, i);
			allocator::deallocate(m_data);
		}

		m_capacity = source.m_capacity;
		m_size = source.m_size;
		m_data = source.m_data;

		source.m_capacity = 0;
		source.m_size = 0;
		source.m_data = nullptr;

		return *this;
	}

	template<typename T>
	inline vector<T>::~vector() noexcept
	{
		for (size_t i = 0; i < m_size; i++)
			allocator::destroy(m_data, i);
		allocator::deallocate(m_data);
	}


	template<typename T>
	inline T& vector<T>::at(size_t index)
	{
		if (index >= m_size) throw error;
		return m_data[index];
	}
	template<typename T> inline T& vector<T>::front()	{ return at(0); }
	template<typename T> inline T& vector<T>::back()	{ return at(m_size-1); }
	template<typename T> inline T& vector<T>::operator[](size_t index) noexcept { return m_data[index]; }

	template<typename T>
	inline const T& vector<T>::at(size_t index) const
	{
		if (index >= m_size) throw error;
		return m_data[index];
	}
	template<typename T> inline const T& vector<T>::front() const	{ return at(0); }
	template<typename T> inline const T& vector<T>::back()	const	{ return at(m_size - 1); }
	template<typename T> inline const T& vector<T>::operator[](size_t index) const noexcept { return m_data[index]; }

	template<typename T>
	inline void vector<T>::reserve(size_t count)
	{
		if (count <= m_capacity) return;

		T* newData = allocator::allocate<T>(count);
		unique_ptr<T> safePtr(newData);
		
		for (size_t i = 0; i < m_size; i++)
			allocator::construct(newData, i, m_data[i]);

		for (size_t i = 0; i < m_size; i++)
			allocator::destroy(m_data, i);

		allocator::deallocate(m_data);
		m_data = safePtr.release();
	}

	template<typename T>
	inline void vector<T>::resize(size_t new_size)
	{
	}

	template<typename T>
	inline void vector<T>::resize(size_t new_size, const T& value)
	{
	}

	template<typename T>
	inline void vector<T>::assign(size_t count, const T& value)
	{
	}

	template<typename T>
	inline void vector<T>::clear()
	{
	}

	template<typename T>
	inline void vector<T>::shrink_to_fit()
	{
	}

	template<typename T>
	inline void vector<T>::swap(vector& vector)
	{
	}

}





#endif // !DVTL_VECTOR_H