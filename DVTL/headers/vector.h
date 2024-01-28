#ifndef DVTL_VECTOR_H
#define DVTL_VECTOR_H

#include "Initializer_list.h"
#include "Allocator.h"
#include "Unique_ptr.h"

namespace DVTL 
{
	template<typename T>
	class Vector 
	{
	public:
		//declaring iterators
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		//constructors, operators= and destructor
					Vector() noexcept;
		explicit	Vector(size_t size);
		explicit	Vector(size_t size, const T& value);
					Vector(Initializer_list<T> init_list);

		Vector(const Vector& source);
		Vector(Vector&& source)					noexcept;
		Vector<T>& operator=(const Vector& source);
		Vector<T>& operator=(Vector&& source)	noexcept;

		~Vector() noexcept;

		//getting vector data
		inline size_t	Capacity()	const	noexcept { return m_capacity; }
		inline size_t	Size()		const	noexcept { return m_size; }
		inline const T* Data()		const	noexcept { return m_data; }
		inline T*		Data()				noexcept { return m_data; }
		inline bool		Empty()		const	noexcept { return m_size == 0; }

		//references to vector elements
		T& At(size_t index);
		T& Front();
		T& Back();
		T& operator[](size_t index)			noexcept;
		const T& At(size_t index)			const;
		const T& Front()					const;
		const T& Back()						const;
		const T& operator[](size_t index)	const noexcept;
	
		//working with data
		void Reserve(size_t count);
		void Resize(size_t new_size);
		void Resize(size_t new_size, const T& value);
		void Assign(size_t count, const T& value);
		void Assign(Initializer_list<T> init_list);
		void Clear();
		void Shrink_to_fit();
		void Swap(Vector& right);

		//adding and removing elements to a vector
		void Push_back(const T& value);
		void Push_back(T&&);
		void Pop_back();
		template <class... Types> iterator Emplace(const const_iterator& position, Types&&... args);
		template <class... Types> iterator Emplace_back(Types&&... args);
		iterator Inset(const const_iterator& position, const T& value);
		iterator Inset(const const_iterator& position, T&& value);
		iterator Inset(const const_iterator& position, size_t count, const T& value);
		iterator Erase(const const_iterator& position);
		iterator Erase(const const_iterator& first, const const_iterator& last);

		//getting iterators begin and end
		inline iterator Begin()	{ return iterator(m_data); }
		inline iterator End()	{ return iterator(m_data + m_size); }
		inline const_iterator Begin()	const { return const_iterator(m_data); }
		inline const_iterator End()		const { return const_iterator(m_data + m_size); }
		inline const_iterator CBegin()	const { return const_iterator(m_data); }
		inline const_iterator CEnd()	const { return const_iterator(m_data + m_size); }
		inline reverse_iterator RBegin()	{ return reverse_iterator(m_data + m_size - 1); }
		inline reverse_iterator REnd()		{ return reverse_iterator(m_data - 1); }
		inline const_reverse_iterator RBegin()	const { return const_reverse_iterator(m_data + m_size - 1); }
		inline const_reverse_iterator REnd()	const { return const_reverse_iterator(m_data - 1); }
		inline const_reverse_iterator CRBegin()	const { return const_reverse_iterator(m_data + m_size - 1); }
		inline const_reverse_iterator CREnd()	const { return const_reverse_iterator(m_data - 1); }
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
		static size_t CalculateNewCapacity(size_t capacity);
	};

	//defining an iterator interface
	template<typename T>
	class Vector<T>::iterator
	{
	public:
		//constructors, operators= and destructor
		iterator(T* ptr)											:ptr(ptr) {}
		iterator(const typename Vector<T>::reverse_iterator& it)	:ptr(++it.ptr) {}
		iterator(const iterator& right)								:ptr(right.ptr) {}
		iterator(iterator&& right) noexcept							:ptr(right.ptr) { right.ptr = nullptr; }
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
		typename Vector<T>::const_iterator get_const() const		{ return typename Vector<T>::const_iterator(*this); }
		typename Vector<T>::reverse_iterator get_revers() const		{ return typename Vector<T>::reverse_iterator(*this); }

		friend class Vector<T>;
	private:
		T* get() const { return ptr; }
		T* ptr;
	};

	template<typename T>
	class Vector<T>::const_iterator
	{
	public:
		//constructors, operators= and destructor
		const_iterator(const T* ptr)											:ptr(ptr) {}
		const_iterator(const typename Vector<T>::iterator& it)					:ptr(it.ptr) {}
		const_iterator(const typename Vector<T>::const_reverse_iterator& it)	:ptr(++it.ptr) {}
		const_iterator(const const_iterator& right)								:ptr(right.ptr) {}
		const_iterator(const_iterator&& right) noexcept							:ptr(right.ptr) { right.ptr = nullptr; }
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
		typename Vector<T>::const_reverse_iterator get_revers() const { return typename Vector<T>::const_reverse_iterator(*this); }

		friend class Vector<T>;
	private:
		T* get() const { return const_cast<T*>(ptr); }
		const T* ptr;
	};

	template<typename T>
	class Vector<T>::reverse_iterator
	{
	public:
		//constructors, operators= and destructor
		reverse_iterator(T* ptr)								:ptr(ptr) {}
		reverse_iterator(const typename Vector<T>::iterator& it):ptr(--it.ptr) {}
		reverse_iterator(const reverse_iterator& right)			:ptr(right.ptr) {}
		reverse_iterator(reverse_iterator&& right) noexcept		:ptr(right.ptr) { right.ptr = nullptr; }
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
			return other.ptr - ptr;
		}

		//transformation
		typename Vector<T>::const_reverse_iterator get_const() const	{ return typename Vector<T>::const_reverse_iterator(&this); }
		typename Vector<T>::iterator get_straight()	const				{ return typename Vector<T>::iterator(*this); }

		friend class Vector<T>;
	private:
		T* get() const { return ptr; }
		T* ptr;
	};

	template<typename T>
	class Vector<T>::const_reverse_iterator
	{
	public:
		//constructors, operators= and destructor
		const_reverse_iterator(const T* ptr)									:ptr(ptr) {}
		const_reverse_iterator(const typename Vector<T>::reverse_iterator& it)	:ptr(it.ptr) {}
		const_reverse_iterator(const typename Vector<T>::const_iterator& it)	:ptr(--it.ptr) {}
		const_reverse_iterator(const const_reverse_iterator& right)				:ptr(right.ptr) {}
		const_reverse_iterator(const_reverse_iterator&& right) noexcept			:ptr(right.ptr) { right.ptr = nullptr; }
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
			return other.ptr - ptr;
		}

		//transformation
		typename Vector<T>::const_iterator get_revers() const { return typename Vector<T>::const_iterator(*this); }

		friend class Vector<T>;
	private:
		T* get() const { return const_cast<T*>(ptr); }
		const T* ptr;
	};

	//constructors, operators= and destructor
	template<typename T>
	inline Vector<T>::Vector() noexcept : m_capacity(0), m_size(0), m_data(nullptr){}

	template<typename T>
	inline Vector<T>::Vector(size_t size) : m_capacity(size), m_size(m_capacity), m_data(Allocator::Allocate<T>(m_capacity))
	{
		for (size_t i = 0; i < size; i++)
			Allocator::Construct(m_data, i, T());
	}

	template<typename T>
	inline Vector<T>::Vector(size_t size, const T& value) : m_capacity(size), m_size(m_capacity), m_data(Allocator::Allocate<T>(m_capacity))
	{
		for (size_t i = 0; i < size; i++)
			Allocator::Construct(m_data, i, value);
	}

	template<typename T>
	inline Vector<T>::Vector(Initializer_list<T> init_list) : m_capacity(init_list.Size()), m_size(m_capacity), m_data(Allocator::Allocate<T>(m_capacity))
	{
		const T* beginInit = init_list.begin();
		for (size_t i = 0; i < m_size; i++)
			Allocator::Construct(m_data, i, *(beginInit+i));
	}

	template<typename T>
	inline Vector<T>::Vector(const Vector& source) : m_capacity(source.m_size), m_size(m_capacity), m_data(Allocator::Allocate<T>(m_capacity))
	{
		for (size_t i = 0; i < m_size; i++)
			Allocator::Construct(m_data, i, source[i]);
	}

	template<typename T>
	inline Vector<T>::Vector(Vector&& source) noexcept : m_capacity(source.m_capacity), m_size(source.m_size), m_data(source.m_data)
	{
		source.m_capacity = 0;
		source.m_size = 0;
		source.m_data = nullptr;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(const Vector& source)
	{
		if (source.m_data == m_data) return *this;

		if (m_data != nullptr) DestroyAndDealloc();

		m_capacity = source.m_size;
		m_size = m_capacity;
		m_data = Allocator::Allocate<T>(m_capacity);
		for (size_t i = 0; i < m_size; i++)
			Allocator::Construct(m_data, i, source[i]);

		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(Vector&& source) noexcept
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
	inline Vector<T>::~Vector() noexcept
	{
		DestroyAndDealloc();
	}

	//references to vector elements
	template<typename T>
	inline T& Vector<T>::At(size_t index)
	{
		if (index >= m_size) throw "out of range vector";
		return m_data[index];
	}
	template<typename T> inline T& Vector<T>::Front()	{ return At(0); }
	template<typename T> inline T& Vector<T>::Back()	{ return At(m_size-1); }
	template<typename T> inline T& Vector<T>::operator[](size_t index) noexcept { return m_data[index]; }

	template<typename T>
	inline const T& Vector<T>::At(size_t index) const
	{
		if (index >= m_size) throw "out of range vector";
		return m_data[index];
	}
	template<typename T> inline const T& Vector<T>::Front() const	{ return At(0); }
	template<typename T> inline const T& Vector<T>::Back()	const	{ return At(m_size - 1); }
	template<typename T> inline const T& Vector<T>::operator[](size_t index) const noexcept { return m_data[index]; }

	//working with data
	template<typename T>
	inline void Vector<T>::Reserve(size_t count)
	{
		if (count <= m_capacity) return;
		AllocateAndMove(count);
	}

	template<typename T>
	inline void Vector<T>::Resize(size_t new_size)
	{
		resize(new_size, T());
	}

	template<typename T>
	inline void Vector<T>::Resize(size_t new_size, const T& value)
	{
		while (m_size > new_size) 
			Allocator::Destroy(m_data, --m_size);
		
		if (m_size == new_size) return;

		if (new_size > m_capacity) AllocateAndMove(new_size);
		while (m_size < new_size)
			Allocator::Construct(m_data, m_size++, value);
	}

	template<typename T>
	inline void Vector<T>::Assign(size_t count, const T& value)
	{
		Clear();
		if (count > m_capacity) AllocateAndMove(count);

		while(m_size < count)
			Allocator::Construct(m_data, m_size++, value);
	}

	template<typename T>
	inline void Vector<T>::Assign(Initializer_list<T> init_list)
	{
		Clear();
		if (init_list.size() > m_capacity) AllocateAndMove(init_list.size());

		const T* beginInit = init_list.begin();
		while (m_size < init_list.size()) {
			Allocator::Construct(m_data, m_size, *(beginInit + m_size));
			++m_size;
		}
	}

	template<typename T>
	inline void Vector<T>::Clear()
	{
		while (m_size > 0)
			Allocator::Destroy(m_data, --m_size);
	}

	template<typename T>
	inline void Vector<T>::Shrink_to_fit()
	{
		AllocateAndMove(m_size);
	}

	template<typename T>
	inline void Vector<T>::Swap(Vector& right)
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
	inline void Vector<T>::Push_back(const T& value)
	{
		if (m_size == m_capacity) 
			AllocateAndMove(CalculateNewCapacity(m_capacity));

		Allocator::Construct(m_data, m_size++, value);
	}

	template<typename T>
	inline void Vector<T>::Push_back(T&& value)
	{
		if (m_size == m_capacity)
			AllocateAndMove(CalculateNewCapacity(m_capacity));

		Allocator::Construct(m_data, m_size++, Move(value));
	}

	template<typename T>
	inline void Vector<T>::Pop_back()
	{
		if (m_size == 0) throw "pop empty vector";
		Allocator::Destroy(m_data, --m_size);
	}

	template<typename T>
	template<class ...Types>
	inline typename Vector<T>::iterator Vector<T>::Emplace(const const_iterator& position, Types && ...args)
	{
		CheckValidIterInsert(position);
		iterator newPosition = ShiftRight(1, position);

		new (newPosition.get()) T(Forward<Types>(args)...);

		return newPosition;
	}

	template<typename T>
	template<class ...Types>
	inline typename Vector<T>::iterator Vector<T>::Emplace_back(Types && ...args)
	{
		if (m_size == m_capacity)
			AllocateAndMove(CalculateNewCapacity(m_capacity));

		new (m_data + m_size++) T(Forward<Types>(args)...);

		return Vector<T>::iterator(m_data+m_size-1);
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::Inset(const const_iterator& position, const T& value)
	{
		CheckValidIterInsert(position);
		iterator newPosition = ShiftRight(1, position);

		Allocator::Construct(newPosition.get(), value);

		return newPosition;
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::Inset(const const_iterator& position, T&& value)
	{
		CheckValidIterInsert(position);
		iterator newPosition = ShiftRight(1, position);

		Allocator::Construct(newPosition.get(), Move(value));

		return newPosition;
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::Inset(const const_iterator& position, size_t count, const T& value)
	{
		CheckValidIterInsert(position);
		iterator newPosition = ShiftRight(count, position);

		for (size_t i = 0; i < count; i++) 
			Allocator::Construct(newPosition.get()+i, value);
		

		return newPosition;
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::Erase(const const_iterator& position)
	{
		CheckValidIterErase(position);
		ShiftLeft(1, position);
		return Vector<T>::iterator(position.get());
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::Erase(const const_iterator& first, const const_iterator& last)
	{
		CheckValidIterErase(first);
		CheckValidIterInsert(last);
		ShiftLeft(last - first, first);
		return Vector<T>::iterator(first.get());
	}

	//helper functions
	template<typename T>
	inline void Vector<T>::AllocateAndMove(size_t new_size)
	{
		T* newData = Allocator::Allocate<T>(new_size);
		Unique_ptr<T> safePtr(newData);

		for (size_t i = 0; i < m_size; i++)
			Allocator::Construct(newData, i, m_data[i]);

		for (size_t i = 0; i < m_size; i++)
			Allocator::Destroy(m_data, i);

		m_capacity = new_size;
		Allocator::Deallocate(m_data);
		m_data = safePtr.Release();
	}

	template<typename T>
	inline void Vector<T>::DestroyAndDealloc()
	{
		for (size_t i = 0; i < m_size; i++)
			Allocator::Destroy(m_data, i);
		Allocator::Deallocate(m_data);
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::ShiftLeft(size_t count, const const_iterator& position)
	{
		const_iterator startErase = position;
		const_iterator endErase = startErase + static_cast<int>(count);

		for (size_t i = 0; i < count; i++)
			Allocator::Destroy(position.get() + i);

		const_iterator endVec = CEnd();

		while (endErase != endVec) {
			Allocator::Construct(startErase.get(), *endErase);
			Allocator::Destroy(endErase.get());
			++endErase;
			++startErase;
		}

		m_size -= count;
		return Vector<T>::iterator(position.get());
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::ShiftRight(size_t count, const const_iterator& position)
	{
		size_t index = position - CBegin();

		if (m_size + count > m_capacity) {
			size_t new_capacity = CalculateNewCapacity(m_capacity);
			while (m_size + count > new_capacity)
				new_capacity = CalculateNewCapacity(new_capacity);
			AllocateAndMove(new_capacity);
		}

		const_iterator startInsert = CEnd() - 1;
		const_iterator endInsert = startInsert + static_cast<int>(count);
		const_iterator pos(m_data + index - 1);

		while (startInsert != pos) {
			Allocator::Construct(endInsert.get(), *startInsert);
			Allocator::Destroy(startInsert.get());
			--endInsert;
			--startInsert;
		}

		m_size += count;
		return Vector<T>::iterator(m_data + index);
	}

	template<typename T>
	inline void Vector<T>::CheckValidIterInsert(const const_iterator& position)
	{
		if (position < CBegin() || position > CEnd()) throw "vector emplace iterator outside range";
	}

	template<typename T>
	inline void Vector<T>::CheckValidIterErase(const const_iterator& position)
	{
		if (position < CBegin() || position >= CEnd()) throw "vector emplace iterator outside range";
	}

	template<typename T>
	inline size_t Vector<T>::CalculateNewCapacity(size_t capacity)
	{
		return capacity + capacity/2 + 1;
	}
}

#endif // !DVTL_VECTOR_H
