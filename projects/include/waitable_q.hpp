#ifndef _WAITABLE_Q_HPP__
#define _WAITABLE_Q_HPP__

#include <queue>//std::queue
#include <boost/noncopyable.hpp>//noncopyable
#include <condition_variable>//std::condition_variable

namespace ilrd
{
    //T must be copyable and assignable
    //Q must supply queue interface

    template<class T, class Q = std::queue<T> > //default queue
    class WaitableQueue : private boost::noncopyable
    {
        public:
            void Enqueue(const T& data);
            void Dequeue(T& out_p); //without timeout

            bool Dequeue(T& out_p, size_t nano_time_out); //with timeout -nanoseconds
            bool IsEmpty(void) const;
        private:
            Q m_queue_like; 
            std::mutex m_mutex;
            std::condition_variable m_cond_ready_to_read;
            typedef typename std::unique_lock<std::mutex> uni_lock;

    };

    template<class T, class Q> 
    void WaitableQueue<T, Q>::Enqueue(const T& data)
    {
        uni_lock lock(m_mutex);
        m_queue_like.push(data);
        m_cond_ready_to_read.notify_one();
        
    }

    template<class T, class Q> 
    bool WaitableQueue<T, Q>::Dequeue(T& out_p, size_t nano_time_out)
    {
        
        uni_lock lock(m_mutex);
        std::chrono::nanoseconds timeout(nano_time_out);
        std::cv_status timeout_stat;

        while (m_queue_like.empty())
        {
            timeout_stat = m_cond_ready_to_read.wait_for(lock, timeout);
            if (std::cv_status::timeout == timeout_stat)
            {
                return false;
            }
        }
        out_p = m_queue_like.front();
        m_queue_like.pop();

        return true;
    }

    template<class T, class Q> 
    void WaitableQueue<T, Q>::Dequeue(T& out_p)
    { 
        Dequeue(out_p, 1000);
    }

    template<class T, class Q> 
    bool WaitableQueue<T, Q>::IsEmpty(void) const
    {
        return (m_queue_like.empty());
    }


}


#endif 