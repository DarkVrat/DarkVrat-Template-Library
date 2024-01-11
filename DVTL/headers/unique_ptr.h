#ifndef DVTL_UNIQUE_PTR_H
#define DVTL_UNIQUE_PTR_H

#include "utility.h"

namespace DVTL 
{
    template<typename T>
    class unique_ptr 
    {
    public:
                    unique_ptr()        noexcept;
        explicit    unique_ptr(T* ptr)  noexcept;

        unique_ptr(const unique_ptr&)   = delete;
        unique_ptr(unique_ptr&& source) noexcept;

        unique_ptr<T>& operator=(T* ptr);
        unique_ptr<T>& operator=(const unique_ptr&)     = delete;
        unique_ptr<T>& operator=(unique_ptr&& source)   noexcept;

        ~unique_ptr() noexcept;

        T* get() const;
        T* release();
        void reset(T* ptr);
        void swap(unique_ptr& right);

        operator bool() const noexcept;
        T& operator *() const noexcept;
        T* operator->() const noexcept;
    private:
        T* m_storage;
    };

    template<typename T>
    inline unique_ptr<T>::unique_ptr() noexcept : m_storage(nullptr) {}

    template<typename T>
    inline unique_ptr<T>::unique_ptr(T* ptr) noexcept : m_storage(ptr) {}

    template<typename T>
    inline unique_ptr<T>::unique_ptr(unique_ptr&& source) noexcept : m_storage(source.m_storage)
    {
        source.m_storage = nullptr;
    }

    template<typename T>
    inline unique_ptr<T>& unique_ptr<T>::operator=(T* ptr)
    {
        reset(ptr);
        return *this;
    }

    template<typename T>
    inline unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& source) noexcept
    {
        if (m_storage == source.m_storage) return *this;

        delete m_storage;
        m_storage = source.m_storage;
        source.m_storage = nullptr;

        return *this;
    }

    template<typename T>
    inline unique_ptr<T>::~unique_ptr() noexcept
    {
        delete m_storage;
    }

    template<typename T>
    inline T* unique_ptr<T>::get() const
    {
        return m_storage;
    }

    template<typename T>
    inline T* unique_ptr<T>::release()
    {
        T* ret = m_storage;
        m_storage = nullptr;
        return ret;
    }

    template<typename T>
    inline void unique_ptr<T>::reset(T* ptr)
    {
        if (m_storage == ptr) return;

        delete m_storage;
        m_storage = ptr;
    }

    template<typename T>
    inline void unique_ptr<T>::swap(unique_ptr& right)
    {
        T* temp = m_storage;
        m_storage = right.m_storage;
        right.m_storage = temp;
    }

    template<typename T>
    inline unique_ptr<T>::operator bool() const noexcept
    {
        return static_cast<bool>(m_storage);
    }

    template<typename T>
    inline T& unique_ptr<T>::operator*() const noexcept
    {
        return *m_storage;
    }

    template<typename T>
    inline T* unique_ptr<T>::operator->() const noexcept
    {
        return m_storage;
    }
}

#endif // !DVTL_UNIQUE_PTR_H