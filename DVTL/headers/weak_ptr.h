#ifndef DVTL_WEAK_PTR_H
#define DVTL_WEAK_PTR_H

namespace DVTL {
	struct Control_block {
		Control_block(size_t shared_count, size_t weak_count) noexcept :count_Shared_ptr(shared_count), count_Weak_ptr(weak_count) {}

		size_t count_Shared_ptr;
		size_t count_Weak_ptr;
	};

	template<typename T>
	class Shared_ptr;

	template<typename T>
	class Weak_ptr {
		//constructors, operators= and destructor
		constexpr				Weak_ptr() noexcept;
		template<typename U>	Weak_ptr(const Weak_ptr<U>& other);
		template<typename U>	Weak_ptr(Weak_ptr<U>&& other);
		template<typename U>	Weak_ptr(const Shared_ptr<U>& other);
		Weak_ptr(const Shared_ptr<T>& other)	noexcept;
		Weak_ptr(const Weak_ptr<T>& other)		noexcept;
		Weak_ptr(Weak_ptr<T>&& other)			noexcept;

		template<typename U> Weak_ptr& operator=(const Weak_ptr<U>& right);
		template<typename U> Weak_ptr& operator=(const Shared_ptr<U>& right);
		Weak_ptr& operator=(const Weak_ptr& right) noexcept;
		Weak_ptr& operator=(const Shared_ptr<T>& right) noexcept;

		~Weak_ptr();

		//ptr functions
		Shared_ptr<T> Lock()	const	noexcept;
		bool Expired()			const	noexcept;
		long Use_count()		const	noexcept;
		void Reset()					noexcept;
		void Swap(Weak_ptr& right)		noexcept;

		template <typename U>  bool Owner_before(const Shared_ptr<U>& other)	const noexcept;
		template <typename U>  bool Owner_before(const Weak_ptr<U>& other)		const noexcept;

		friend class Shared_ptr<T>;
	private:
		void decreaseCounter();

		Control_block* m_Control_block_ptr;
		T* m_data

	};

	template<typename T>
	inline constexpr Weak_ptr<T>::Weak_ptr() noexcept:m_Control_block_ptr(nullptr), m_data(nullptr){}

	template<typename T>
	template<typename U>
	inline Weak_ptr<T>::Weak_ptr(const Weak_ptr<U>& other):m_Control_block_ptr(other.m_Control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		++(m_Control_block_ptr->count_Weak_ptr);
	}

	template<typename T>
	template<typename U>
	inline Weak_ptr<T>::Weak_ptr(Weak_ptr<U>&& other) :m_Control_block_ptr(other.m_Control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		other.m_Control_block_ptr = nullptr;
		other.m_data = nullptr;
	}

	template<typename T>
	template<typename U>
	inline Weak_ptr<T>::Weak_ptr(const Shared_ptr<U>& other) :m_Control_block_ptr(other.m_Control_block_ptr), m_data(dynamic_cast<T*>(other.m_data))
	{
		if (!m_data) throw "bad dynamic cast";
		++(m_Control_block_ptr->count_Weak_ptr);
	}

	template<typename T>
	inline Weak_ptr<T>::Weak_ptr(const Shared_ptr<T>& other) :m_Control_block_ptr(other.m_Control_block_ptr), m_data(other.m_data)
	{
		++(m_Control_block_ptr->count_Weak_ptr);
	}

	template<typename T>
	inline Weak_ptr<T>::Weak_ptr(const Weak_ptr<T>& other) :m_Control_block_ptr(other.m_Control_block_ptr), m_data(other.m_data)
	{
		++(m_Control_block_ptr->count_Weak_ptr);
	}

	template<typename T>
	inline Weak_ptr<T>::Weak_ptr(Weak_ptr<T>&& other) :m_Control_block_ptr(other.m_Control_block_ptr), m_data(other.m_data)
	{
		other.m_Control_block_ptr = nullptr;
		other.m_data = nullptr;
	}

	template<typename T>
	template<typename U>
	inline Weak_ptr<T>& Weak_ptr<T>::operator=(const Weak_ptr<U>& right) noexcept
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;

		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = buffer;
		++(m_Control_block_ptr->count_Weak_ptr);

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Weak_ptr<T>& Weak_ptr<T>::operator=(const Shared_ptr<U>& right) noexcept
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;

		T* buffer = dynamic_cast<T*>(right.m_data);
		if (!buffer) throw "bad dynamic cast";

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = buffer;
		++(m_Control_block_ptr->count_Weak_ptr);

		return *this;
	}

	template<typename T>
	inline Weak_ptr<T>& Weak_ptr<T>::operator=(const Weak_ptr<T>& right) noexcept
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = right.m_data;
		++(m_Control_block_ptr->count_Weak_ptr);

		return *this;
	}

	template<typename T>
	inline Weak_ptr<T>& Weak_ptr<T>::operator=(const Shared_ptr<T>& right) noexcept
	{
		if (m_Control_block_ptr == right.m_Control_block_ptr) return;

		decreaseCounter();

		m_Control_block_ptr = right.m_Control_block_ptr;
		m_data = right.m_data;
		++(m_Control_block_ptr->count_Weak_ptr);

		return *this;
	}

	template<typename T>
	inline Weak_ptr<T>::~Weak_ptr()
	{
		decreaseCounter();
	}

	template<typename T>
	inline Shared_ptr<T> Weak_ptr<T>::Lock() const noexcept
	{
		return Shared_ptr<T>(*this);
	}

	template<typename T>
	inline bool Weak_ptr<T>::Expired() const noexcept
	{
		return m_Control_block_ptr->count_Shared_ptr == 0;
	}

	template<typename T>
	inline long Weak_ptr<T>::Use_count() const noexcept
	{
		return m_Control_block_ptr->count_Shared_ptr;
	}

	template<typename T>
	inline void Weak_ptr<T>::Reset() noexcept
	{
		decreaseCounter();
	}

	template<typename T>
	inline void Weak_ptr<T>::Swap(Weak_ptr& right) noexcept
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
	inline bool Weak_ptr<T>::Owner_before(const Shared_ptr<U>& other) const noexcept
	{
		return m_data < other.m_data;
	}

	template<typename T>
	template<typename U>
	inline bool Weak_ptr<T>::Owner_before(const Weak_ptr<U>& other) const noexcept
	{
		return m_data < other.m_data;
	}

	template<typename T>
	inline void Weak_ptr<T>::decreaseCounter()
	{
		--(m_Control_block_ptr->count_Weak_ptr);

		if (m_Control_block_ptr->count_Shared_ptr == 0 && m_Control_block_ptr->count_Weak_ptr == 0) {
			delete m_Control_block_ptr;
		}

		m_data = nullptr;
		m_Control_block_ptr = nullptr;
	}
}

#endif // !DVTL_WEAK_PTR_H

