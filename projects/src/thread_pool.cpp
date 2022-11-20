#include "thread_pool.hpp"

namespace assaf
{
ThreadPool::ThreadPool(size_t thread_amount) : m_threadAmount(thread_amount),
                                               m_pauseSem(details::CreateSem(&m_pauseSem, 0)),
                                               m_sem_finish(details::CreateSem(&m_sem_finish, 0))
{
    for (size_t i = 0; i < thread_amount; ++i)
    {
        details::CreateAndDetachThread(std::ref(m_pqueue),
                                 std::ref(m_enables), 
                                 &m_sem_finish);

    }


}
ThreadPool::~ThreadPool()
{
    for (size_t i = 0; i < m_threadAmount; ++i)
    {
        std::shared_ptr<ITask > task  (new BadApple(m_enables));
        AddTask(task, static_cast<priority_ty>(3));
    }
    for (size_t i = 0; i < m_threadAmount; ++i)
    {
        sem_wait(&m_sem_finish);

    }
    sem_destroy(&m_pauseSem);
    sem_destroy(&m_sem_finish);
    printf("ThreadPool done \n");

}

void ThreadPool::AddTask(std::shared_ptr<ITask> task, priority_ty priority)
{
    m_pqueue.Enqueue(std::make_pair(static_cast<int >(priority), task));

}

void ThreadPool::Pause()
{
    for (size_t i = 0; i < m_threadAmount; ++i)
    {
        std::shared_ptr<ITask > task  (new PauseTask(m_pauseSem));
        AddTask(task, static_cast<priority_ty>(1));
    }
}


ThreadPool::PauseTask::PauseTask(sem_t &sem): m_pauseSem(sem)
{
    //
}
ThreadPool::PauseTask::~PauseTask()
{
    //
    printf("PauseTask done \n");
}
void ThreadPool::PauseTask::Run()
{
    printf("Pausing \n");
    sem_wait(&m_pauseSem);
}

ThreadPool::FunctionTask::~FunctionTask()
{
    //
    printf("FunctionTask done \n");
}

void ThreadPool::Resume()
{
    for (std::size_t i = 0; i < m_threadAmount ; ++i)
    {
        printf("Resuming \n");
        std::cout << "Resuming " << std::endl;
        sem_post(&m_pauseSem);
    }
}

void ThreadPool::FunctionTask::Run()
{
    m_func();
}

ThreadPool::BadApple::BadApple(std::unordered_map<std::thread::id, bool> &u_map) :
                        m_enables(u_map)
{
    //
}

ThreadPool::BadApple::~BadApple()
{

}
void ThreadPool::BadApple::Run()
{
    std::thread::id id = std::this_thread::get_id();
    m_enables[id] = false;
}

void ThreadPool::SetNumberOfThreads(size_t thread_amount)
{
    if (thread_amount > m_threadAmount)
    {
        for ( size_t i = 0; i <thread_amount -  m_threadAmount; ++i)
        {
            details::CreateAndDetachThread(std::ref(m_pqueue),
                                    std::ref(m_enables), 
                                    &m_sem_finish);
        }
        m_threadAmount = thread_amount;
    }
    if (thread_amount < m_threadAmount)
    {
        for (size_t i = 0; i < m_threadAmount - thread_amount; ++i)
        {
            std::shared_ptr<ITask > task  (new BadApple(m_enables));
            AddTask(task, static_cast<priority_ty>(3));
        }
        m_threadAmount = thread_amount;
    }
}

}