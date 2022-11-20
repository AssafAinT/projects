#ifndef __ILRD_OL127_128_SCOPEDLOCK_HPP__
#define __ILRD_OL127_128_SCOPEDLOCK_HPP__

#include <boost/core/noncopyable.hpp> /* noncopyable obj */
#include <mutex>                      /* mutex */

namespace ilrd
{
    template <class T>
    class ScopedLock : private boost::noncopyable
    {
        public:
        explicit ScopedLock(T &lock) : m_lock(lock)
        {
            m_lock.lock();
        }

        ~ScopedLock()
        {
            m_lock.unlock();
        }

        private:
        T &m_lock;
        static void *operator new(size_t);
        static void *operator new[](size_t);
        static void operator delete(void *);
        static void operator delete[](void *);
    };
}

#endif /* __ILRD_OL127_128_SCOPEDLOCK_H__ */
