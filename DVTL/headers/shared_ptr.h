#ifndef DVTL_SHARED_PTR_H
#define DVTL_SHARED_PTR_H

#include "unique_ptr.h"
#include "weak_ptr.h"

namespace DVTL {
	template<typename T>
	class shared_ptr {
		constexpr	shared_ptr() noexcept;
		explicit	shared_ptr(T* ptr);
		explicit	shared_ptr(unique_ptr<T>&& other);
		explicit	shared_ptr(const weak_ptr<T>& other);
		template<typename U> explicit	shared_ptr(U* ptr);
		template<typename U> explicit	shared_ptr(unique_ptr<U>&& other);
		template<typename U> explicit	shared_ptr(const weak_ptr<U>& other);
		template<typename U> explicit	shared_ptr(const shared_ptr<U>& other);
		shared_ptr(const shared_ptr& other) noexcept;
		shared_ptr(shared_ptr&& other)		noexcept;

		template<typename U> shared_ptr& operator=(unique_ptr<U>&& right);
		template<typename U> shared_ptr& operator=(weak_ptr<U>&& right);
		template<typename U> shared_ptr& operator=(const shared_ptr<U>& right);
		template<typename U> shared_ptr& operator=(shared_ptr<U>&& right);
		shared_ptr& operator=(unique_ptr<T>&& right);
		shared_ptr& operator=(weak_ptr<T>&& right);
		shared_ptr& operator=(const shared_ptr& right)	noexcept;
		shared_ptr& operator=(shared_ptr&& right)		noexcept;

		~shared_ptr();

		operator bool()		const		noexcept;
		T& operator*()		const		noexcept;
		T* operator->()		const		noexcept;
		T* get()			const		noexcept;
		bool unique()		const		noexcept;
		long use_count()	const		noexcept;
		void reset()					noexcept;
		void reset(T* ptr);
		void swap(shared_ptr& right)	noexcept;
		
		template <typename U>	bool owner_before(const shared_ptr<U>& other)	const noexcept;
		template <typename U>	bool owner_before(const weak_ptr<U>& other)		const noexcept;
		template <typename U>	void reset(U* ptr);

		friend class weak_ptr<T>;
	private:
		void decreaseCounter();

		control_block* m_control_block_ptr;
		T* m_data
	};

	template<typename T>
	inline constexpr shared_ptr<T>::shared_ptr() noexcept: m_control_block_ptr(nullptr), m_data(nullptr){}

	template<typename T>
	inline shared_ptr<T>::shared_ptr(T* ptr) : m_control_block_ptr(new control_block(1, 0)), m_data(ptr){}

	template<typename T>
	inline shared_ptr<T>::shared_ptr(unique_ptr<T>&& other) : m_control_block_ptr(new control_block<T>(1, 0)), m_data(other.release()){}

	template<typename T>
	inline shared_ptr<T>::shared_ptr(const weak_ptr<T>& other):m_control_block_ptr(other.m_control_block_ptr), m_data(other.m_data)
	{
		if (m_control_block_ptr->count_shared_ptr == 0) throw "bad weak ptr";

		++(m_control_block_ptr->count_shared_ptr);
	}

	template<typename T>
	template<typename U>
	inline shared_ptr<T>::shared_ptr(U* ptr):m_control_block_ptr(new control_block(1, 0)), m_data(dynamic_cast<T*>(ptr))
	{
		if (!m_data) throw "bad dynamic cast";
	}

	template<typename T>
	template<typename U>
	inline shared_ptr<T>::shared_ptr(unique_ptr<U>&& other) : m_control_block_ptr(new control_block<T>(1, 0)), m_data(dynamic_cast<T*>(other.get())) 
	{
		if (!m_data) throw "bad dynamic cast";
		other.release();
	}

	template<typename T>
	template<typename U>
	inline shared_ptr<T>::shared_ptr(const weak_ptr<U>& other) :m_control_block_ptr(other.m_control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		if (m_control_block_ptr->count_shared_ptr == 0) throw "bad weak ptr";

		++(m_control_block_ptr->count_shared_ptr);
	}

	template<typename T>
	template<typename U>
	inline shared_ptr<T>::shared_ptr(const shared_ptr<U>& other) :m_control_block_ptr(other.m_control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		++(m_control_block_ptr->count_shared_ptr);
	}

	template<typename T>
	inline shared_ptr<T>::shared_ptr(const shared_ptr& other) :m_control_block_ptr(other.m_control_block_ptr), m_data(other.m_data)
	{
		++(m_control_block_ptr->count_shared_ptr);
	}

	template<typename T>
	inline shared_ptr<T>::shared_ptr(shared_ptr&& other) :m_control_block_ptr(other.m_control_block_ptr), m_data(other.m_data)
	{
		other.m_control_block_ptr = nullptr;
		other.m_data = nullptr;
	}
	
	template<typename T>
	template<typename U>
	inline shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<U>& right)
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;

		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = buffer;
		++(m_control_block_ptr->count_shared_ptr);

		return *this;
	}

	template<typename T>
	template<typename U>
	inline shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<U>&& right)
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;

		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = buffer;
		right.m_control_block_ptr = nullptr;
		right.m_data = nullptr;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline shared_ptr<T>& shared_ptr<T>::operator=(unique_ptr<U>&& right)
	{
		T* buffer = dynamic_cast<T*>(right.get());
		if (!buffer) throw "bad dynamic cast";
		right.release();
		decreaseCounter();

		m_control_block_ptr = new control_block(1, 0);
		m_data = buffer;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline shared_ptr<T>& shared_ptr<T>::operator=(weak_ptr<U>&& right)
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;
		if (right.m_control_block_ptr->count_shared_ptr == 0) throw "bad weak ptr";
		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = buffer;
		++(m_control_block_ptr->count_shared_ptr);

		return *this;
	}

	template<typename T>
	inline shared_ptr<T>& shared_ptr<T>::operator=(weak_ptr<T>&& right)
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;
		if (right.m_control_block_ptr->count_shared_ptr == 0) throw "bad weak ptr";

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = buffer;
		++(m_control_block_ptr->count_shared_ptr);

		return *this;
	}

	template<typename T>
	inline shared_ptr<T>& shared_ptr<T>::operator=(unique_ptr<T>&& right)
	{
		decreaseCounter();

		m_control_block_ptr = new control_block(1, 0);
		m_data = right.release();;

		return *this;
	}

	template<typename T>
	inline shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& right) noexcept
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = right.m_data;
		++(m_control_block_ptr->count_shared_ptr);

		return *this;
	}

	template<typename T>
	inline shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& right) noexcept
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = right.m_data;
		right.m_control_block_ptr = nullptr;
		right.m_data = nullptr;

		return *this;
	}

	template<typename T>
	inline shared_ptr<T>::~shared_ptr()
	{
		decreaseCounter();
	}

	template<typename T>
	inline shared_ptr<T>::operator bool() const noexcept
	{
		return static_cast<bool>(m_data);
	}

	template<typename T>
	inline T& shared_ptr<T>::operator*() const noexcept
	{
		return *m_data;
	}

	template<typename T>
	inline T* shared_ptr<T>::operator->() const noexcept
	{
		return m_data;
	}

	template<typename T>
	inline T* shared_ptr<T>::get() const noexcept
	{
		return m_data;
	}

	template<typename T>
	inline bool shared_ptr<T>::unique() const noexcept
	{
		return m_control_block_ptr->count_shared_ptr == 1;
	}

	template<typename T>
	inline long shared_ptr<T>::use_count() const noexcept
	{
		return m_control_block_ptr->count_shared_ptr;
	}

	template<typename T>
	inline void shared_ptr<T>::reset() noexcept
	{
		decreaseCounter();
	}

	template<typename T>
	inline void shared_ptr<T>::reset(T* ptr)
	{
		decreaseCounter();

		m_control_block_ptr = new control_block(1, 0);
		m_data = ptr;
	}

	template<typename T>
	inline void shared_ptr<T>::swap(shared_ptr& right) noexcept
	{
		control_block* temp_block = right.m_control_block_ptr;
		T* temp_data = right.m_data;

		right.m_control_block_ptr = m_control_block_ptr;
		right.m_data = m_data;

		m_control_block_ptr = temp_block;
		m_data = temp_data;
	}

	template<typename T>
	template<typename U>
	inline bool shared_ptr<T>::owner_before(const shared_ptr<U>& other) const noexcept
	{
		return m_data < other.m_data;
	}

	template<typename T>
	template<typename U>
	inline bool shared_ptr<T>::owner_before(const weak_ptr<U>& other) const noexcept
	{
		return m_data < other.m_data;
	}

	template<typename T>
	template<typename U>
	inline void shared_ptr<T>::reset(U* ptr)
	{
		T* buffer = dynamic_cast<T*>(ptr);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_control_block_ptr = new control_block(1, 0);
		m_data = buffer;
	}

	template<typename T>
	inline void shared_ptr<T>::decreaseCounter()
	{
		if (m_data) {
			--(m_control_block_ptr->count_shared_ptr);

			if (m_control_block_ptr->count_shared_ptr == 0) {
				delete m_data;
				if (m_control_block_ptr->count_weak_ptr == 0) 
					delete m_control_block_ptr;
			}

			m_data = nullptr;
			m_control_block_ptr = nullptr;
		}
	}

}

#endif // !DVTL_SHARED_PTR_H
