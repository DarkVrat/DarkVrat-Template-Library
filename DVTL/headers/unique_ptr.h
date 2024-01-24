#ifndef DVTL_UNIQUE_PTR_H
#define DVTL_UNIQUE_PTR_H

#include "utility.h"

namespace DVTL 
{
    template<typename T>
    class Unique_ptr 
    {
    public:
        //constructors, operators= and destructor
                    Unique_ptr()        noexcept;
        explicit    Unique_ptr(T* ptr)  noexcept;

        Unique_ptr(const Unique_ptr&)   = delete;
        Unique_ptr(Unique_ptr&& source) noexcept;

        Unique_ptr<T>& operator=(T* ptr);
        Unique_ptr<T>& operator=(const Unique_ptr&)     = delete;
        Unique_ptr<T>& operator=(Unique_ptr&& source)   noexcept;

        ~Unique_ptr() noexcept;

        //ptr functions
        T* Get() const;
        T* Release();
        void Reset(T* ptr);
        void Swap(Unique_ptr& right);

        operator bool() const noexcept;
        T& operator *() const noexcept;
        T* operator->() const noexcept;
    private:
        T* m_storage;
    };

    template<typename T>
    inline Unique_ptr<T>::Unique_ptr() noexcept : m_storage(nullptr) {}

    template<typename T>
    inline Unique_ptr<T>::Unique_ptr(T* ptr) noexcept : m_storage(ptr) {}

    template<typename T>
    inline Unique_ptr<T>::Unique_ptr(Unique_ptr&& source) noexcept : m_storage(source.m_storage)
    {
        source.m_storage = nullptr;
    }

    template<typename T>
    inline Unique_ptr<T>& Unique_ptr<T>::operator=(T* ptr)
    {
        reset(ptr);
        return *this;
    }

    template<typename T>
    inline Unique_ptr<T>& Unique_ptr<T>::operator=(Unique_ptr&& source) noexcept
    {
        if (m_storage == source.m_storage) return *this;

        delete m_storage;
        m_storage = source.m_storage;
        source.m_storage = nullptr;

        return *this;
    }

    template<typename T>
    inline Unique_ptr<T>::~Unique_ptr() noexcept
    {
        delete m_storage;
    }

    template<typename T>
    inline T* Unique_ptr<T>::Get() const
    {
        return m_storage;
    }

    template<typename T>
    inline T* Unique_ptr<T>::Release()
    {
        T* ret = m_storage;
        m_storage = nullptr;
        return ret;
    }

    template<typename T>
    inline void Unique_ptr<T>::Reset(T* ptr)
    {
        if (m_storage == ptr) return;

        delete m_storage;
        m_storage = ptr;
    }

    template<typename T>
    inline void Unique_ptr<T>::Swap(Unique_ptr& right)
    {
        T* temp = m_storage;
        m_storage = right.m_storage;
        right.m_storage = temp;
    }

    template<typename T>
    inline Unique_ptr<T>::operator bool() const noexcept
    {
        return static_cast<bool>(m_storage);
    }

    template<typename T>
    inline T& Unique_ptr<T>::operator*() const noexcept
    {
        return *m_storage;
    }

    template<typename T>
    inline T* Unique_ptr<T>::operator->() const noexcept
    {
        return m_storage;
    }
}

#endif // !DVTL_UNIQUE_PTR_H
