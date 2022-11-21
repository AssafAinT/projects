#ifndef _WAITABLE_PQ_HPP__
#define _WAITABLE_PQ_HPP__

#include <queue>//std::queue
#include <boost/noncopyable.hpp>//noncopyable
#include <condition_variable>//std::condition_variable

namespace assaf
{
    //T must be copyable and assignable
    //Q must supply queue interface

    template<class T> //default queue
    class WaitablePQueue : private boost::noncopyable
    {
        public:
            void Enqueue(const T& data);
            void Dequeue(T& out_p); //without timeout

            bool Dequeue(T& out_p, size_t nano_time_out); //with timeout -nanoseconds
            bool IsEmpty(void) const;
        private:
            std::priority_queue<T>m_queue_like; 
            mutable std::mutex m_mutex;
            std::condition_variable m_cond_ready_to_read;
            typedef typename std::unique_lock<std::mutex> uni_lock;

    };

    template<class T> 
    void WaitablePQueue<T>::Enqueue(const T& data)
    {
        uni_lock lock(m_mutex);
        m_queue_like.push(data);
        m_cond_ready_to_read.notify_one();
        
    }

    template<class T> 
    bool WaitablePQueue<T>::Dequeue(T& out_p, size_t nano_time_out)
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
        out_p = m_queue_like.top();
        m_queue_like.pop();

        return true;
    }

    template<class T> 
    void WaitablePQueue<T>::Dequeue(T& out_p)
    { 
        uni_lock unique_lock(m_mutex);
        //std::cout << "hag " << std::endl;
        while (m_queue_like.empty())
        {
            
            m_cond_ready_to_read.wait(unique_lock); 
        }
        out_p =m_queue_like.top();
        m_queue_like.pop();
    }

    template<class T> 
    bool WaitablePQueue<T>::IsEmpty(void) const
    {
        uni_lock unique_lock(m_mutex);
        return (m_queue_like.empty());
    }

}


#endif 