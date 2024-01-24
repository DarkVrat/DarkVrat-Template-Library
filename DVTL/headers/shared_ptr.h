#ifndef DVTL_SHARED_PTR_H
#define DVTL_SHARED_PTR_H

#include "Weak_ptr.h"
#include "Unique_ptr.h"

namespace DVTL {
	template<typename T>
	class Shared_ptr {
		//constructors, operators= and destructor
		constexpr	Shared_ptr() noexcept;
		explicit	Shared_ptr(T* ptr);
		explicit	Shared_ptr(Unique_ptr<T>&& other);
		explicit	Shared_ptr(const Weak_ptr<T>& other);
		template<typename U> explicit	Shared_ptr(U* ptr);
		template<typename U> explicit	Shared_ptr(Unique_ptr<U>&& other);
		template<typename U> explicit	Shared_ptr(const Weak_ptr<U>& other);
		template<typename U> explicit	Shared_ptr(const Shared_ptr<U>& other);
		Shared_ptr(const Shared_ptr& other) noexcept;
		Shared_ptr(Shared_ptr&& other)		noexcept;

		template<typename U> Shared_ptr& operator=(Unique_ptr<U>&& right);
		template<typename U> Shared_ptr& operator=(Weak_ptr<U>&& right);
		template<typename U> Shared_ptr& operator=(const Shared_ptr<U>& right);
		template<typename U> Shared_ptr& operator=(Shared_ptr<U>&& right);
		Shared_ptr& operator=(Unique_ptr<T>&& right);
		Shared_ptr& operator=(Weak_ptr<T>&& right);
		Shared_ptr& operator=(const Shared_ptr& right)	noexcept;
		Shared_ptr& operator=(Shared_ptr&& right)		noexcept;

		~Shared_ptr();

		//ptr functions
		operator bool()		const		noexcept;
		T& operator*()		const		noexcept;
		T* operator->()		const		noexcept;
		T* Get()			const		noexcept;
		bool Unique()		const		noexcept;
		long Use_count()	const		noexcept;
		void Reset()					noexcept;
		void Reset(T* ptr);
		void Swap(Shared_ptr& right)	noexcept;
		
		template <typename U>	bool Owner_before(const Shared_ptr<U>& other)	const noexcept;
		template <typename U>	bool Owner_before(const Weak_ptr<U>& other)		const noexcept;
		template <typename U>	void Reset(U* ptr);

		friend class Weak_ptr<T>;
	private:
		void decreaseCounter();

		Control_block* m_Control_block_ptr;
		T* m_data
	};

	template<typename T>
	inline constexpr Shared_ptr<T>::Shared_ptr() noexcept: m_Control_block_ptr(nullptr), m_data(nullptr){}

	template<typename T>
	inline Shared_ptr<T>::Shared_ptr(T* ptr) : m_Control_block_ptr(new Control_block(1, 0)), m_data(ptr){}

	template<typename T>
	inline Shared_ptr<T>::Shared_ptr(Unique_ptr<T>&& other) : m_Control_block_ptr(new Control_block(1, 0)), m_data(other.release()){}

	template<typename T>
	inline Shared_ptr<T>::Shared_ptr(const Weak_ptr<T>& other):m_Control_block_ptr(other.m_Control_block_ptr), m_data(other.m_data)
	{
		if (m_Control_block_ptr->count_Shared_ptr == 0) throw "bad weak ptr";

		++(m_Control_block_ptr->count_Shared_ptr);
	}

	template<typename T>
	template<typename U>
	inline Shared_ptr<T>::Shared_ptr(U* ptr):m_Control_block_ptr(new Control_block(1, 0)), m_data(dynamic_cast<T*>(ptr))
	{
		if (!m_data) throw "bad dynamic cast";
	}

	template<typename T>
	template<typename U>
	inline Shared_ptr<T>::Shared_ptr(Unique_ptr<U>&& other) : m_Control_block_ptr(new Control_block<T>(1, 0)), m_data(dynamic_cast<T*>(other.get()))
	{
		if (!m_data) throw "bad dynamic cast";
		other.release();
	}

	template<typename T>
	template<typename U>
	inline Shared_ptr<T>::Shared_ptr(const Weak_ptr<U>& other) :m_Control_block_ptr(other.m_Control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		if (m_Control_block_ptr->count_Shared_ptr == 0) throw "bad weak ptr";

		++(m_Control_block_ptr->count_Shared_ptr);
	}

	template<typename T>
	template<typename U>
	inline Shared_ptr<T>::Shared_ptr(const Shared_ptr<U>& other) :m_Control_block_ptr(other.m_Control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		++(m_Control_block_ptr->count_Shared_ptr);
	}

	template<typename T>
	inline Shared_ptr<T>::Shared_ptr(const Shared_ptr& other) :m_Control_block_ptr(other.m_Control_block_ptr), m_data(other.m_data)
	{
		++(m_Control_block_ptr->count_Shared_ptr);
	}

	template<typename T>
	inline Shared_ptr<T>::Shared_ptr(Shared_ptr&& other) :m_Control_block_ptr(other.m_Control_block_ptr), m_data(other.m_data)
	{
		other.m_Control_block_ptr = nullptr;
		other.m_data = nullptr;
	}
	
	template<typename T>
	template<typename U>
	inline Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr<U>& right)
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;

		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = buffer;
		++(m_Control_block_ptr->count_Shared_ptr);

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Shared_ptr<T>& Shared_ptr<T>::operator=(Shared_ptr<U>&& right)
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;

		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = buffer;
		right.m_Control_block_ptr = nullptr;
		right.m_data = nullptr;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Shared_ptr<T>& Shared_ptr<T>::operator=(Unique_ptr<U>&& right)
	{
		T* buffer = dynamic_cast<T*>(right.get());
		if (!buffer) throw "bad dynamic cast";
		right.release();
		decreaseCounter();

		m_Control_block_ptr = new Control_block(1, 0);
		m_data = buffer;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Shared_ptr<T>& Shared_ptr<T>::operator=(Weak_ptr<U>&& right)
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;
		if (right.m_Control_block_ptr->count_Shared_ptr == 0) throw "bad weak ptr";
		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = buffer;
		++(m_Control_block_ptr->count_Shared_ptr);

		return *this;
	}

	template<typename T>
	inline Shared_ptr<T>& Shared_ptr<T>::operator=(Weak_ptr<T>&& right)
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;
		if (right.m_Control_block_ptr->count_Shared_ptr == 0) throw "bad weak ptr";

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = buffer;
		++(m_Control_block_ptr->count_Shared_ptr);

		return *this;
	}

	template<typename T>
	inline Shared_ptr<T>& Shared_ptr<T>::operator=(Unique_ptr<T>&& right)
	{
		decreaseCounter();

		m_Control_block_ptr = new Control_block(1, 0);
		m_data = right.release();;

		return *this;
	}

	template<typename T>
	inline Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr& right) noexcept
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = right.m_data;
		++(m_Control_block_ptr->count_Shared_ptr);

		return *this;
	}

	template<typename T>
	inline Shared_ptr<T>& Shared_ptr<T>::operator=(Shared_ptr&& right) noexcept
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = right.m_data;
		right.m_Control_block_ptr = nullptr;
		right.m_data = nullptr;

		return *this;
	}

	template<typename T>
	inline Shared_ptr<T>::~Shared_ptr()
	{
		decreaseCounter();
	}

	template<typename T>
	inline Shared_ptr<T>::operator bool() const noexcept
	{
		return static_cast<bool>(m_data);
	}

	template<typename T>
	inline T& Shared_ptr<T>::operator*() const noexcept
	{
		return *m_data;
	}

	template<typename T>
	inline T* Shared_ptr<T>::operator->() const noexcept
	{
		return m_data;
	}

	template<typename T>
	inline T* Shared_ptr<T>::Get() const noexcept
	{
		return m_data;
	}

	template<typename T>
	inline bool Shared_ptr<T>::Unique() const noexcept
	{
		return m_Control_block_ptr->count_Shared_ptr == 1;
	}

	template<typename T>
	inline long Shared_ptr<T>::Use_count() const noexcept
	{
		return m_Control_block_ptr->count_Shared_ptr;
	}

	template<typename T>
	inline void Shared_ptr<T>::Reset() noexcept
	{
		decreaseCounter();
	}

	template<typename T>
	inline void Shared_ptr<T>::Reset(T* ptr)
	{
		decreaseCounter();

		m_Control_block_ptr = new Control_block(1, 0);
		m_data = ptr;
	}

	template<typename T>
	inline void Shared_ptr<T>::Swap(Shared_ptr& right) noexcept
	{
		Control_block* temp_block = right.m_Control_block_ptr;
		T* temp_data = right.m_data;

		right.m_Control_block_ptr = m_Control_block_ptr;
		right.m_data = m_data;

		m_Control_block_ptr = temp_block;
		m_data = temp_data;
	}

	template<typename T>
	template<typename U>
	inline bool Shared_ptr<T>::Owner_before(const Shared_ptr<U>& other) const noexcept
	{
		return m_data < other.m_data;
	}

	template<typename T>
	template<typename U>
	inline bool Shared_ptr<T>::Owner_before(const Weak_ptr<U>& other) const noexcept
	{
		return m_data < other.m_data;
	}

	template<typename T>
	template<typename U>
	inline void Shared_ptr<T>::Reset(U* ptr)
	{
		T* buffer = dynamic_cast<T*>(ptr);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_Control_block_ptr = new Control_block(1, 0);
		m_data = buffer;
	}

	template<typename T>
	inline void Shared_ptr<T>::decreaseCounter()
	{
		if (m_data) {
			--(m_Control_block_ptr->count_Shared_ptr);

			if (m_Control_block_ptr->count_Shared_ptr == 0) {
				delete m_data;
				if (m_Control_block_ptr->count_Weak_ptr == 0) 
					delete m_Control_block_ptr;
			}

			m_data = nullptr;
			m_Control_block_ptr = nullptr;
		}
	}

}

#endif // !DVTL_SHARED_PTR_H
