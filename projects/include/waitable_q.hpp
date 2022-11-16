#ifndef __ILRD_RD127_128_WAITABLE_Q_HPP__
#define __ILRD_RD127_128_WAITABLE_Q_HPP__

#include <queue>
#include <boost/noncopyable.hpp>
#include <boost/chrono.hpp>
#include <condition_variable>
//boost::chrono::nanoseconds
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

            bool Dequeue(T& out_p, size_t time_out); //with timeout
            bool IsEmpty(void) const;
        private:
            Q m_queue_like; 
            std::mutex m_mutex;
            std::condition_variable m_cond_ready_to_read;
            typedef typename std::unique_lock<std::mutex> uni_lock;

    };

    template<class T, class Q> //default queue
    void WaitableQueue<T, Q>::Enqueue(const T& data)
    {
        uni_lock lock(m_mutex);
        m_queue_like.push(data);
        m_cond_ready_to_read.notify_all();
        
    }

    template<class T, class Q> //default queue
    bool WaitableQueue<T, Q>::Dequeue(T& out_p, size_t time_out)
    {
        
        uni_lock lock(m_mutex);
        std::chrono::system_clock::time_point AbsTimeOut
                    (std::chrono::_V2::system_clock::now() + 
                    static_cast<std::chrono::nanoseconds>(time_out));

        while (m_queue_like.empty())
        {
            if (std::cv_status::timeout == m_cond_ready_to_read.wait_until(lock, AbsTimeOut))
            {
                return false;
            }
        }
        out_p = m_queue_like.front();
        m_queue_like.pop();

        return true;
    }

    template<class T, class Q> //default queue
    void WaitableQueue<T, Q>::Dequeue(T& out_p)
    { 
        Dequeue(out_p, 1000);
    }

    template<class T, class Q> //default queue
    bool WaitableQueue<T, Q>::IsEmpty(void) const
    {
        return (m_queue_like.empty());
    }


}

#endif //__ILRD_RD127_128_WAITABLE_Q_HPP__