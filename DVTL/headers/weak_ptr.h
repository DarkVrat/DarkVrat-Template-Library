#ifndef DVTL_WEAK_PTR_H
#define DVTL_WEAK_PTR_H

namespace DVTL {
	struct control_block {
		control_block(size_t shared_count, size_t weak_count) noexcept :count_shared_ptr(shared_count), count_weak_ptr(weak_count) {}

		size_t count_shared_ptr;
		size_t count_weak_ptr;
	};

	template<typename T>
	class shared_ptr;

	template<typename T>
	class weak_ptr {
		constexpr				weak_ptr() noexcept;
		template<typename U>	weak_ptr(const weak_ptr<U>& other);
		template<typename U>	weak_ptr(weak_ptr<U>&& other);
		template<typename U>	weak_ptr(const shared_ptr<U>& other);
		weak_ptr(const shared_ptr<T>& other)	noexcept;
		weak_ptr(const weak_ptr<T>& other)		noexcept;
		weak_ptr(weak_ptr<T>&& other)			noexcept;

		template<typename U> weak_ptr& operator=(const weak_ptr<U>& right);
		template<typename U> weak_ptr& operator=(const shared_ptr<U>& right);
		weak_ptr& operator=(const weak_ptr& right) noexcept;
		weak_ptr& operator=(const shared_ptr<T>& right) noexcept;

		~weak_ptr();

		shared_ptr<T> lock()	const	noexcept;
		bool expired()			const	noexcept;
		long use_count()		const	noexcept;
		void reset()					noexcept;
		void swap(weak_ptr& right)		noexcept;

		template <typename U>  bool owner_before(const shared_ptr<U>& other)	const noexcept;
		template <typename U>  bool owner_before(const weak_ptr<U>& other)		const noexcept;

		friend class shared_ptr<T>;
	private:
		void decreaseCounter();

		control_block* m_control_block_ptr;
		T* m_data

	};

	template<typename T>
	inline constexpr weak_ptr<T>::weak_ptr() noexcept:m_control_block_ptr(nullptr), m_data(nullptr){}

	template<typename T>
	template<typename U>
	inline weak_ptr<T>::weak_ptr(const weak_ptr<U>& other):m_control_block_ptr(other.m_control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		++(m_control_block_ptr->count_weak_ptr);
	}

	template<typename T>
	template<typename U>
	inline weak_ptr<T>::weak_ptr(weak_ptr<U>&& other) :m_control_block_ptr(other.m_control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		other.m_control_block_ptr = nullptr;
		other.m_data = nullptr;
	}

	template<typename T>
	template<typename U>
	inline weak_ptr<T>::weak_ptr(const shared_ptr<U>& other) :m_control_block_ptr(other.m_control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		++(m_control_block_ptr->count_weak_ptr);
	}

	template<typename T>
	inline weak_ptr<T>::weak_ptr(const shared_ptr<T>& other) :m_control_block_ptr(other.m_control_block_ptr), m_data(other.m_data)
	{
		++(m_control_block_ptr->count_weak_ptr);
	}

	template<typename T>
	inline weak_ptr<T>::weak_ptr(const weak_ptr<T>& other) :m_control_block_ptr(other.m_control_block_ptr), m_data(other.m_data)
	{
		++(m_control_block_ptr->count_weak_ptr);
	}

	template<typename T>
	inline weak_ptr<T>::weak_ptr(weak_ptr<T>&& other) :m_control_block_ptr(other.m_control_block_ptr), m_data(other.m_data)
	{
		other.m_control_block_ptr = nullptr;
		other.m_data = nullptr;
	}

	template<typename T>
	template<typename U>
	inline weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<U>& right) noexcept
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;

		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = buffer;
		++(m_control_block_ptr->count_weak_ptr);

		return *this;
	}

	template<typename T>
	template<typename U>
	inline weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<U>& right) noexcept
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;

		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = buffer;
		++(m_control_block_ptr->count_weak_ptr);

		return *this;
	}

	template<typename T>
	inline weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<T>& right) noexcept
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = right.m_data;
		++(m_control_block_ptr->count_weak_ptr);

		return *this;
	}

	template<typename T>
	inline weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<T>& right) noexcept
	{
		if (m_control_block_ptr == right.m_control_block_ptr) return;

		decreaseCounter();

		m_control_block_ptr = right.m_control_block_ptr;
		m_data = right.m_data;
		++(m_control_block_ptr->count_weak_ptr);

		return *this;
	}

	template<typename T>
	inline weak_ptr<T>::~weak_ptr()
	{
		decreaseCounter();
	}

	template<typename T>
	inline shared_ptr<T> weak_ptr<T>::lock() const noexcept
	{
		return shared_ptr<T>(*this);
	}

	template<typename T>
	inline bool weak_ptr<T>::expired() const noexcept
	{
		return m_control_block_ptr->count_shared_ptr == 0;
	}

	template<typename T>
	inline long weak_ptr<T>::use_count() const noexcept
	{
		return m_control_block_ptr->count_shared_ptr;
	}

	template<typename T>
	inline void weak_ptr<T>::reset() noexcept
	{
		decreaseCounter();
	}

	template<typename T>
	inline void weak_ptr<T>::swap(weak_ptr& right) noexcept
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
	inline bool weak_ptr<T>::owner_before(const shared_ptr<U>& other) const noexcept
	{
		return m_data < other.m_data;
	}

	template<typename T>
	template<typename U>
	inline bool weak_ptr<T>::owner_before(const weak_ptr<U>& other) const noexcept
	{
		return m_data < other.m_data;
	}

	template<typename T>
	inline void weak_ptr<T>::decreaseCounter()
	{
		--(m_control_block_ptr->count_weak_ptr);

		if (m_control_block_ptr->count_shared_ptr == 0 && m_control_block_ptr->count_weak_ptr == 0) {
			delete m_control_block_ptr;
		}

		m_data = nullptr;
		m_control_block_ptr = nullptr;
	}
}

#endif // !DVTL_WEAK_PTR_H

