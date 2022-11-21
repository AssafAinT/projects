#ifndef __ASSAF_THREAD_POOL_HPP__
#define __ASSAF_THREAD_POOL_HPP__


#include <thread> //std::thread
#include <fcntl.h> //o_flags
#include <functional> // function class
#include <cstddef>//size_t
#include <semaphore.h> // sempahore
#include <memory> // shared_ptr
#include <utility> // pair
#include <boost/noncopyable.hpp> // noncopyable calss
#include <unordered_map> //std::unordered_map
#include <iostream> //std::cout 
#include <cstdio> //printf
#include "waitable_pq.hpp"
namespace details
{
    
    inline sem_t CreateSem(sem_t *sem, unsigned int init_val)
    {
        if (-1 == sem_init(sem, 0, init_val))
        {
            std::__throw_bad_alloc();   
        }
        return *sem;
    }
}//namespace details
namespace assaf
{

class ThreadPool:private boost::noncopyable
{
    public:
    enum priority_ty
    {
        LOW = 0,
        MID = 1,
        HIGH = 2
    };

    class ITask
    {
    public:
        virtual ~ITask() {}
        virtual void Run() = 0;
    };
   
    class FunctionTask:public ITask 
    {
    public:
        FunctionTask(std::function<void()> func):m_func(func)
        {
            // empty ctor
        } // nonexplicit 
        virtual ~FunctionTask(); 
        virtual void Run();

    private:
        std::function<void(void)> m_func;
    };


    template <typename T>
    class FutureTask:public ITask 
    {
    public:
        FutureTask(std::function<T ()> func); // nonexplicit, by value to share ownership of object
        virtual ~FutureTask();
        virtual void Run();
        T Get();
    private:
        std::function<T ()> m_func;
        T m_ret;
        sem_t m_fsem;
    };
    


    explicit ThreadPool(size_t thread_amount);
    ~ThreadPool();
    void AddTask(std::shared_ptr<ITask> task, priority_ty priority);
    void Pause();
    void Resume();
    void SetNumberOfThreads(size_t thread_amount);
    


    private:
    assaf::WaitablePQueue<std::pair<int, std::shared_ptr<ITask> > > m_pqueue;

    size_t m_threadAmount;
    sem_t m_pauseSem; // c sem 
    sem_t m_sem_finish;
    std::unordered_map<std::thread::id, bool> m_enables;
    bool is_paused;
    // size_t m_to_resume;

    
    class PauseTask:public ITask 
    {
        public:
        PauseTask(sem_t &sem);
        ~PauseTask();
        void Run();

        private:
        sem_t &m_pauseSem;
        
    };

    class BadApple:public ITask 
    {
        public:
        BadApple(std::unordered_map<std::thread::id, bool> &u_map);
        ~BadApple();
        void Run();
        
        private:
        std::unordered_map<std::thread::id, bool> &m_enables; 

    };
    
};

template <typename T>
ThreadPool::FutureTask<T>::FutureTask(std::function<T ()> func): m_func(func), 
                                        m_fsem(details::CreateSem(&m_fsem, 0)) 
{
    //
}
template <typename T>
ThreadPool::FutureTask<T>::~FutureTask()
{
    sem_destroy(&m_fsem);
}
template <typename T>
T ThreadPool::FutureTask<T>::Get()
{
    sem_wait(&m_fsem);

    return (m_ret);
}
template <typename T>
void ThreadPool::FutureTask<T>::Run()
{
    m_ret = m_func();
    sem_post(&m_fsem);
}

}// namespace assaf

#endif //__ASSAF_RD127_128_THREAD_POOL_HPP__
