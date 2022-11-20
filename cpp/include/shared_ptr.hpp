#ifndef __ILRD_RD127_128_SHARED_PTR_HPP__
#define __ILRD_RD127_128_SHARED_PTR_HPP__

#include <cstddef> // size_t
#include <iostream> //ostream
#if _cplusplus<201104
#define noexcept throw()
#endif //#if _cplusplus<201104
namespace ilrd
{
    template <class T>
    class SharedPtr
    {
        public: 

        explicit SharedPtr(T *ptr = NULL);
        template <typename S>
        SharedPtr(const SharedPtr<S> & other);

        SharedPtr(const SharedPtr<T>& other);
        ~SharedPtr();
        SharedPtr& operator=(const SharedPtr<T> &other);
        T& operator *() const;
        T* operator->() const;
        size_t GetCounter();
        

        private:
        T *m_ptr;
        size_t *m_counter; 
        static void *operator new(size_t);// to preven from allocation on heap
        static void *operator new[](size_t);
        static void operator delete(void *);
        static void operator delete[](void *);
        void Deatach();
        template <typename S>
        friend class SharedPtr;

        friend std::ostream &operator<<(std::ostream &os, SharedPtr<T> &other)
        {
            os << "Address pointed : " << other.m_ptr << std::endl;
            os << *(other.m_counter) << std::endl;
            return os;
        }
    };
    
    template<class T>
    size_t SharedPtr<T>::GetCounter()
    {
        return *m_counter;
    }
    template<class T>
    template <typename S>
    SharedPtr<T>::SharedPtr(const SharedPtr<S> & other):m_ptr(other.m_ptr)
    {
        m_counter = other.m_counter;
        ++*m_counter;
    }

    template<class T>
    SharedPtr<T>::SharedPtr(T *ptr) : m_ptr(ptr), m_counter(new size_t(1))
    {
        //
    }
    
    template<class T>
    SharedPtr<T>::SharedPtr(const SharedPtr <T>& other): m_ptr(other.m_ptr)
    {
        m_counter = other.m_counter;
        ++*m_counter;
        std::cout << "Cctor counter : " << *m_counter << std::endl;
    }

    template<class T>
    SharedPtr<T>::~SharedPtr()
    {
        Deatach();
    }

    template<class T>
    T& SharedPtr<T>::operator *() const
    {
        return *m_ptr;
    }
    template<class T>
    T* SharedPtr<T>::operator->() const
    {
        return m_ptr;
    }
        
    template<class T>
    void SharedPtr<T>::Deatach()
    {
        --*m_counter;
        if ( 0 == *m_counter)
        {
            delete m_counter;
            delete m_ptr;
            m_counter = 0;
            m_ptr = 0;
        }
    }

    template<class T>
    SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T> &other)
    {
        if (m_ptr != other.m_ptr)
        {
            Deatach();
            m_ptr = other.m_ptr;
            m_counter = other.m_counter;    
            ++*m_counter;
        }
        return *this;
    }
    
}
#endif // __ILRD_RD127_128_SHARED_PTR
