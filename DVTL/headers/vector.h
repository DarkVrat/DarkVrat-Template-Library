#ifndef DVTL_VECTOR_H
#define DVTL_VECTOR_H

#include "allocator.h"
#include "unique_ptr.h"
#include "initializer_list.h"

namespace DVTL 
{
	template<typename T>
	class vector 
	{
	public:
		//declaring iterators
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		//constructors, operators= and destructor
					vector() noexcept;
		explicit	vector(size_t size);
		explicit	vector(size_t size, const T& value);
					vector(initializer_list<T> init_list);

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
		void assign(initializer_list<T> init_list);
		void clear();
		void shrink_to_fit();
		void swap(vector& right);

		//adding and removing elements to a vector
		void push_back(const T& value);
		void push_back(T&&);
		void pop_back();
		template <class... Types> iterator emplace(const const_iterator& position, Types&&... args);
		template <class... Types> iterator emplace_back(Types&&... args);
		iterator inset(const const_iterator& position, const T& value);
		iterator inset(const const_iterator& position, T&& value);
		iterator inset(const const_iterator& position, size_t count, const T& value);
		iterator erase(const const_iterator& position);
		iterator erase(const const_iterator& first, const const_iterator& last);

		//getting iterators begin and end
		inline iterator begin()	{ return iterator(m_data); }
		inline iterator end()	{ return iterator(m_data + m_size); }
		inline const_iterator begin()	const { return const_iterator(m_data); }
		inline const_iterator end()		const { return const_iterator(m_data + m_size); }
		inline const_iterator cbegin()	const { return const_iterator(m_data); }
		inline const_iterator cend()	const { return const_iterator(m_data + m_size); }
		inline reverse_iterator rbegin()	{ return reverse_iterator(m_data + m_size - 1); }
		inline reverse_iterator rend()		{ return reverse_iterator(m_data - 1); }
		inline const_reverse_iterator rbegin()	const { return const_reverse_iterator(m_data + m_size - 1); }
		inline const_reverse_iterator rend()	const { return const_reverse_iterator(m_data - 1); }
		inline const_reverse_iterator crbegin()	const { return const_reverse_iterator(m_data + m_size - 1); }
		inline const_reverse_iterator crend()	const { return const_reverse_iterator(m_data - 1); }
	private:
		size_t m_capacity;
		size_t m_size;
		T* m_data;

		//helper functions
		void AllocateAndMove(size_t new_size);
		void DestroyAndDealloc();
		iterator ShiftLeft(size_t count, const const_iterator& position);
		iterator ShiftRight(size_t count, const const_iterator& position);
		void CheckValidIterInsert(const const_iterator& position);
		void CheckValidIterErase(const const_iterator& position);
		size_t CalculateNewCapacity(size_t capacity);
	};

	//defining an iterator interface
	template<typename T>
	class vector<T>::iterator 
	{
	public:
		//constructors, operators= and destructor
		iterator(T* ptr)								:ptr(ptr) {}
		iterator(const vector<T>::reverse_iterator& it) :ptr(++it.ptr) {}
		iterator(const iterator& right)					:ptr(right.ptr) {}
		iterator(iterator&& right) noexcept				:ptr(right.ptr) { right.ptr = nullptr; }
		iterator& operator=(const iterator& right)		{ ptr = right.ptr; return *this; }
		iterator& operator=(iterator&& right) noexcept	{ ptr = right.ptr; right.ptr = nullptr; return *this; }
		~iterator() {}

		//logical operators
		bool operator==(const iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const iterator& other) const { return ptr != other.ptr; }
		bool operator<=(const iterator& other) const { return ptr <= other.ptr; }
		bool operator>=(const iterator& other) const { return ptr >= other.ptr; }
		bool operator< (const iterator& other) const { return ptr <  other.ptr; }
		bool operator> (const iterator& other) const { return ptr >  other.ptr; }

		//data access
		T& operator*() const { return *ptr; }
		T* operator->() const { return ptr; }
		T& operator[](size_t index) const { return ptr[index]; }

		//mathematical operators
		iterator& operator++()			{ ++ptr; return *this; }
		iterator& operator--()			{ --ptr; return *this; }
		const iterator operator++(int)	{ iterator temp = *this; ++ptr; return temp; }
		const iterator operator--(int)	{ iterator temp = *this; --ptr; return temp; }
		iterator& operator+=(int n)		{ ptr += n; return *this; }
		iterator& operator-=(int n)		{ ptr -= n; return *this; }
		iterator operator+(int n) const	{ return iterator(ptr + n); }
		iterator operator-(int n) const { return iterator(ptr - n); }
		auto operator-(const iterator& other) const -> decltype(auto) {
			return ptr - other.ptr;
		}

		//transformation
		vector<T>::const_iterator get_const() const		{ return vector<T>::const_iterator(*this); }
		vector<T>::reverse_iterator get_revers() const	{ return vector<T>::reverse_iterator(*this); }

		friend class vector<T>;
	private:
		T* get() const { return ptr; }
		T* ptr;
	};

	template<typename T>
	class vector<T>::const_iterator
	{
	public:
		//constructors, operators= and destructor
		const_iterator(const T* ptr)								:ptr(ptr) {}
		const_iterator(const vector<T>::iterator& it)				:ptr(it.ptr) {}
		const_iterator(const vector<T>::const_reverse_iterator& it) :ptr(++it.ptr) {}
		const_iterator(const const_iterator& right)					:ptr(right.ptr) {}
		const_iterator(const_iterator&& right) noexcept				:ptr(right.ptr) { right.ptr = nullptr; }
		const_iterator& operator=(const const_iterator& right)		{ ptr = right.ptr; return *this; }
		const_iterator& operator=(const_iterator&& right) noexcept	{ ptr = right.ptr; right.ptr = nullptr; return *this; }
		~const_iterator() {}

		//logical operators
		bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }
		bool operator<=(const const_iterator& other) const { return ptr <= other.ptr; }
		bool operator>=(const const_iterator& other) const { return ptr >= other.ptr; }
		bool operator< (const const_iterator& other) const { return ptr <  other.ptr; }
		bool operator> (const const_iterator& other) const { return ptr >  other.ptr; }

		//data access
		const T& operator*() const { return *ptr; }
		const T* operator->() const { return ptr; }
		const T& operator[](size_t index) const { return ptr[index]; }

		//mathematical operators
		const_iterator& operator++()			{ ++ptr; return *this; }
		const_iterator& operator--()			{ --ptr; return *this; }
		const const_iterator operator++(int)	{ const_iterator temp = *this; ++ptr; return temp; }
		const const_iterator operator--(int)	{ const_iterator temp = *this; --ptr; return temp; }
		const_iterator& operator+=(int n)		{ ptr += n; return *this; }
		const_iterator& operator-=(int n)		{ ptr -= n; return *this; }
		const_iterator operator+(int n) const	{ return const_iterator(ptr + n); }
		const_iterator operator-(int n) const	{ return const_iterator(ptr - n); }
		auto operator-(const const_iterator& other) const -> decltype(auto) {
			return ptr - other.ptr;
		}

		//transformation
		vector<T>::const_reverse_iterator get_straight() const { return vector<T>::const_reverse_iterator(*this); }

		friend class vector<T>;
	private:
		T* get() const { return const_cast<T*>(ptr); }
		const T* ptr;
	};

	template<typename T>
	class vector<T>::reverse_iterator
	{
	public:
		//constructors, operators= and destructor
		reverse_iterator(T* ptr)							:ptr(ptr) {}
		reverse_iterator(const vector<T>::iterator& it)		:ptr(--it.ptr) {}
		reverse_iterator(const reverse_iterator& right)		:ptr(right.ptr) {}
		reverse_iterator(reverse_iterator&& right) noexcept :ptr(right.ptr) { right.ptr = nullptr; }
		reverse_iterator& operator=(const reverse_iterator& right)		{ ptr = right.ptr; return *this; }
		reverse_iterator& operator=(reverse_iterator right)	noexcept	{ ptr = right.ptr; right.ptr = nullptr; return *this; }
		~reverse_iterator() {}

		//logical operators
		bool operator==(const reverse_iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const reverse_iterator& other) const { return ptr != other.ptr; }
		bool operator<=(const reverse_iterator& other) const { return ptr >= other.ptr; }
		bool operator>=(const reverse_iterator& other) const { return ptr <= other.ptr; }
		bool operator< (const reverse_iterator& other) const { return ptr >  other.ptr; }
		bool operator> (const reverse_iterator& other) const { return ptr <  other.ptr; }

		//data access
		T& operator*() const { return *ptr; }
		T* operator->() const { return ptr; }

		//mathematical operators
		reverse_iterator& operator++()			{ --ptr; return *this; }
		reverse_iterator& operator--()			{ ++ptr; return *this; }
		const reverse_iterator operator++(int)	{ reverse_iterator temp = *this; --ptr; return temp; }
		const reverse_iterator operator--(int)	{ reverse_iterator temp = *this; ++ptr; return temp; }
		reverse_iterator& operator+=(int n)		{ ptr -= n; return *this; }
		reverse_iterator& operator-=(int n)		{ ptr += n; return *this; }
		reverse_iterator operator+(int n) const { return reverse_iterator(ptr - n); }
		reverse_iterator operator-(int n) const { return reverse_iterator(ptr + n); }
		auto operator-(const reverse_iterator& other) const -> decltype(auto) {
			return ptr - other.ptr;
		}

		//transformation
		vector<T>::const_reverse_iterator get_const() const { return vector<T>::const_reverse_iterator(&this); }
		vector<T>::iterator get_straight()	const			{ return vector<T>::iterator(*this); }

		friend class vector<T>;
	private:
		T* get() const { return ptr; }
		T* ptr;
	};

	template<typename T>
	class vector<T>::const_reverse_iterator
	{
	public:
		//constructors, operators= and destructor
		const_reverse_iterator(const T* ptr)							:ptr(ptr) {}
		const_reverse_iterator(const vector<T>::reverse_iterator& it)	:ptr(it.ptr) {}
		const_reverse_iterator(const vector<T>::const_iterator& it)		:ptr(--it.ptr) {}
		const_reverse_iterator(const const_reverse_iterator& right)		:ptr(right.ptr) {}
		const_reverse_iterator(const_reverse_iterator&& right) noexcept :ptr(right.ptr) { right.ptr = nullptr; }
		const_reverse_iterator& operator=(const const_reverse_iterator& right)		{ ptr = right.ptr; return *this; }
		const_reverse_iterator& operator=(const_reverse_iterator right) noexcept	{ ptr = right.ptr; right.ptr = nullptr; return *this; }
		~const_reverse_iterator() {}

		//logical operators
		bool operator==(const const_reverse_iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const const_reverse_iterator& other) const { return ptr != other.ptr; }
		bool operator<=(const const_reverse_iterator& other) const { return ptr >= other.ptr; }
		bool operator>=(const const_reverse_iterator& other) const { return ptr <= other.ptr; }
		bool operator< (const const_reverse_iterator& other) const { return ptr >  other.ptr; }
		bool operator> (const const_reverse_iterator& other) const { return ptr <  other.ptr; }

		//data access
		const T& operator*() const { return *ptr; }
		const T* operator->() const { return ptr; }

		//mathematical operators
		const_reverse_iterator& operator++()			{ --ptr; return *this; }
		const_reverse_iterator& operator--()			{ ++ptr; return *this; }
		const const_reverse_iterator operator++(int)	{ const_reverse_iterator temp = *this; --ptr; return temp; }
		const const_reverse_iterator operator--(int)	{ const_reverse_iterator temp = *this; ++ptr; return temp; }
		const_reverse_iterator& operator+=(int n)		{ ptr -= n; return *this; }
		const_reverse_iterator& operator-=(int n)		{ ptr += n; return *this; }
		const_reverse_iterator operator+(int n) const	{ return const_reverse_iterator(ptr - n); }
		const_reverse_iterator operator-(int n) const	{ return const_reverse_iterator(ptr + n); }
		auto operator-(const const_reverse_iterator& other) const -> decltype(auto) {
			return ptr - other.ptr;
		}

		//transformation
		vector<T>::const_iterator get_straight() const { return vector<T>::const_iterator(*this); }

		friend class vector<T>;
	private:
		T* get() const { return const_cast<T*>(ptr); }
		const T* ptr;
	};

	//constructors, operators= and destructor
	template<typename T>
	inline vector<T>::vector() noexcept : m_capacity(0), m_size(0), m_data(nullptr){}

	template<typename T>
	inline vector<T>::vector(size_t size) : m_capacity(size), m_size(m_capacity), m_data(allocator::allocate<T>(m_capacity)) 
	{
		for (size_t i = 0; i < size; i++)
			allocator::construct(m_data, i, T());
	}

	template<typename T>
	inline vector<T>::vector(size_t size, const T& value) : m_capacity(size), m_size(m_capacity), m_data(allocator::allocate<T>(m_capacity))
	{
		for (size_t i = 0; i < size; i++)
			allocator::construct(m_data, i, value);
	}

	template<typename T>
	inline vector<T>::vector(initializer_list<T> init_list) : m_capacity(init_list.size()), m_size(m_capacity), m_data(allocator::allocate<T>(m_capacity))
	{
		const T* beginInit = init_list.begin();
		for (size_t i = 0; i < m_size; i++)
			allocator::construct(m_data, i, *(beginInit+i));
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

		if (m_data != nullptr) DestroyAndDealloc();

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

		if (m_data != nullptr) DestroyAndDealloc();

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
		DestroyAndDealloc();
	}

	//references to vector elements
	template<typename T>
	inline T& vector<T>::at(size_t index)
	{
		if (index >= m_size) throw "out of range vector";
		return m_data[index];
	}
	template<typename T> inline T& vector<T>::front()	{ return at(0); }
	template<typename T> inline T& vector<T>::back()	{ return at(m_size-1); }
	template<typename T> inline T& vector<T>::operator[](size_t index) noexcept { return m_data[index]; }

	template<typename T>
	inline const T& vector<T>::at(size_t index) const
	{
		if (index >= m_size) throw "out of range vector";
		return m_data[index];
	}
	template<typename T> inline const T& vector<T>::front() const	{ return at(0); }
	template<typename T> inline const T& vector<T>::back()	const	{ return at(m_size - 1); }
	template<typename T> inline const T& vector<T>::operator[](size_t index) const noexcept { return m_data[index]; }

	//working with data
	template<typename T>
	inline void vector<T>::reserve(size_t count)
	{
		if (count <= m_capacity) return;
		AllocateAndMove(count);
	}

	template<typename T>
	inline void vector<T>::resize(size_t new_size)
	{
		resize(new_size, T());
	}

	template<typename T>
	inline void vector<T>::resize(size_t new_size, const T& value)
	{
		while (m_size > new_size) 
			allocator::destroy(m_data, --m_size);
		
		if (m_size == new_size) return;

		if (new_size > m_capacity) AllocateAndMove(new_size);
		while (m_size < new_size)
			allocator::construct(m_data, m_size++, value);
	}

	template<typename T>
	inline void vector<T>::assign(size_t count, const T& value)
	{
		clear();
		if (count > m_capacity) AllocateAndMove(count);

		while(m_size < count)
			allocator::construct(m_data, m_size++, value);
	}

	template<typename T>
	inline void vector<T>::assign(initializer_list<T> init_list)
	{
		clear();
		if (init_list.size() > m_capacity) AllocateAndMove(init_list.size());

		const T* beginInit = init_list.begin();
		while (m_size < init_list.size()) {
			allocator::construct(m_data, m_size, *(beginInit + m_size));
			++m_size;
		}
	}

	template<typename T>
	inline void vector<T>::clear()
	{
		while (m_size > 0)
			allocator::destroy(m_data, --m_size);
	}

	template<typename T>
	inline void vector<T>::shrink_to_fit()
	{
		AllocateAndMove(m_size);
	}

	template<typename T>
	inline void vector<T>::swap(vector& right)
	{
		T* temp_data = m_data;
		size_t temp_size = m_size;
		size_t temp_capacity = m_capacity;

		m_data = right.m_data;
		m_size = right.m_size;
		m_capacity = right.m_capacity;

		right.m_data = temp_data;
		right.m_size = temp_size;
		right.m_capacity = temp_capacity;
	}

	//adding and removing elements to a vector
	template<typename T>
	inline void vector<T>::push_back(const T& value)
	{
		if (m_size == m_capacity) 
			AllocateAndMove(CalculateNewCapacity(m_capacity));

		allocator::construct(m_data, m_size++, value);
	}

	template<typename T>
	inline void vector<T>::push_back(T&& value)
	{
		if (m_size == m_capacity)
			AllocateAndMove(CalculateNewCapacity(m_capacity));

		allocator::construct(m_data, m_size++, move(value));
	}

	template<typename T>
	inline void vector<T>::pop_back()
	{
		if (m_size == 0) throw "pop empty vector";
		allocator::destroy(m_data, --m_size);
	}

	template<typename T>
	template<class ...Types>
	inline typename vector<T>::iterator vector<T>::emplace(const const_iterator& position, Types && ...args)
	{
		CheckValidIterInsert(position);
		iterator newPosition = ShiftRight(1, position);

		new (newPosition.get()) T(forward<Types>(args)...);

		return newPosition;
	}

	template<typename T>
	template<class ...Types>
	inline typename vector<T>::iterator vector<T>::emplace_back(Types && ...args)
	{
		if (m_size == m_capacity)
			AllocateAndMove(CalculateNewCapacity(m_capacity));

		new (m_data + m_size++) T(forward<Types>(args)...);

		return vector<T>::iterator(m_data+m_size-1);
	}

	template<typename T>
	inline typename vector<T>::iterator vector<T>::inset(const const_iterator& position, const T& value)
	{
		CheckValidIterInsert(position);
		iterator newPosition = ShiftRight(1, position);

		allocator::construct(newPosition.get(), value);

		return newPosition;
	}

	template<typename T>
	inline typename vector<T>::iterator vector<T>::inset(const const_iterator& position, T&& value)
	{
		CheckValidIterInsert(position);
		iterator newPosition = ShiftRight(1, position);

		allocator::construct(newPosition.get(), move(value));

		return newPosition;
	}

	template<typename T>
	inline typename vector<T>::iterator vector<T>::inset(const const_iterator& position, size_t count, const T& value)
	{
		CheckValidIterInsert(position);
		iterator newPosition = ShiftRight(count, position);

		for (size_t i = 0; i < count; i++) 
			allocator::construct(newPosition.get()+i, value);
		

		return newPosition;
	}

	template<typename T>
	inline typename vector<T>::iterator vector<T>::erase(const const_iterator& position)
	{
		CheckValidIterErase(position);
		ShiftLeft(1, position);
		return vector<T>::iterator(position.get());
	}

	template<typename T>
	inline typename vector<T>::iterator vector<T>::erase(const const_iterator& first, const const_iterator& last)
	{
		if (first > last) return erase(last, first);

		CheckValidIterErase(first);
		CheckValidIterInsert(last);
		ShiftLeft(last - first, first);
		return vector<T>::iterator(first.get());
	}

	//helper functions
	template<typename T>
	inline void vector<T>::AllocateAndMove(size_t new_size)
	{
		T* newData = allocator::allocate<T>(new_size);
		unique_ptr<T> safePtr(newData);

		for (size_t i = 0; i < m_size; i++)
			allocator::construct(newData, i, m_data[i]);

		for (size_t i = 0; i < m_size; i++)
			allocator::destroy(m_data, i);

		m_capacity = new_size;
		allocator::deallocate(m_data);
		m_data = safePtr.release();
	}

	template<typename T>
	inline void vector<T>::DestroyAndDealloc()
	{
		for (size_t i = 0; i < m_size; i++)
			allocator::destroy(m_data, i);
		allocator::deallocate(m_data);
	}

	template<typename T>
	inline typename vector<T>::iterator vector<T>::ShiftLeft(size_t count, const const_iterator& position)
	{
		const_iterator startErase = position;
		const_iterator endErase = startErase + static_cast<int>(count);

		for (size_t i = 0; i < count; i++)
			allocator::destroy(position.get() + i);

		const_iterator endVec = cend();

		while (endErase != endVec) {
			allocator::construct(startErase.get(), *endErase);
			allocator::destroy(endErase.get());
			++endErase;
			++startErase;
		}

		m_size -= count;
		return vector<T>::iterator(position.get());
	}

	template<typename T>
	inline typename vector<T>::iterator vector<T>::ShiftRight(size_t count, const const_iterator& position)
	{
		size_t index = position - cbegin();

		if (m_size + count > m_capacity) {
			size_t new_capacity = CalculateNewCapacity(m_capacity);
			while (m_size + count > new_capacity)
				new_capacity = CalculateNewCapacity(new_capacity);
			AllocateAndMove(new_capacity);
		}

		const_iterator startInsert = cend() - 1;
		const_iterator endInsert = startInsert + static_cast<int>(count);
		const_iterator pos(m_data + index - 1);

		while (startInsert != pos) {
			allocator::construct(endInsert.get(), *startInsert);
			allocator::destroy(startInsert.get());
			--endInsert;
			--startInsert;
		}

		m_size += count;
		return vector<T>::iterator(m_data + index);
	}

	template<typename T>
	inline void vector<T>::CheckValidIterInsert(const const_iterator& position)
	{
		if (position < cbegin() || position > cend()) throw "vector emplace iterator outside range";
	}

	template<typename T>
	inline void vector<T>::CheckValidIterErase(const const_iterator& position)
	{
		if (position < cbegin() || position >= cend()) throw "vector emplace iterator outside range";
	}

	template<typename T>
	inline size_t vector<T>::CalculateNewCapacity(size_t capacity)
	{
		return capacity + capacity/2 + 1;
	}
}

#endif // !DVTL_VECTOR_H
