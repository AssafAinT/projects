#include "thread_pool.hpp"
namespace details
{
    
    
    inline void ThreadFunc(assaf::WaitablePQueue<std::
                          pair<int, std::shared_ptr<assaf::ThreadPool::ITask> > > 
                          &m_pqueue ,
                          std::unordered_map<std::thread::id, bool> &m_enables,
                          sem_t *m_sem_finish)
    {
        sem_post(m_sem_finish);
        std::thread::id id = std::this_thread::get_id(); 
        m_enables.insert({id, true});
    
        while (m_enables[id])
        {
            std::pair <int, std::shared_ptr<assaf::ThreadPool::ITask> >ret;
            m_pqueue.Dequeue(ret);
            ret.second->Run();
        }
    
        sem_post(m_sem_finish);
    }
    inline void CreateAndDetachThread(assaf::WaitablePQueue
                                     <std::pair<int, std::shared_ptr
                                     <assaf::ThreadPool::ITask> > > &m_pqueue,
                                     std::unordered_map<std::thread::id, bool>
                                     &m_enables,
                                     sem_t *m_sem_finish)
    {
        std::thread task_executer(details::ThreadFunc,
                                 std::ref(m_pqueue),
                                 std::ref(m_enables), 
                                 m_sem_finish);
        task_executer.detach();
    }

    
}
namespace assaf
{
ThreadPool::ThreadPool(size_t thread_amount) : m_threadAmount(0),
                                               m_pauseSem(details::CreateSem(&m_pauseSem, 0)),
                                               m_sem_finish(details::CreateSem(&m_sem_finish, 0)),
                                               is_paused(false)
{
    for (size_t i = 0; i < thread_amount; ++i)
    {
        details::CreateAndDetachThread(std::ref(m_pqueue),
                                 std::ref(m_enables), 
                                 &m_sem_finish);
        sem_wait(&m_sem_finish);
    }
    m_threadAmount = thread_amount;


}
ThreadPool::~ThreadPool()
{
    for (size_t i = 0; i < m_threadAmount; ++i)
    {
        std::shared_ptr<ITask > task(new BadApple(m_enables));
        AddTask(task, static_cast<priority_ty>(HIGH+2));
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
    // m_to_resume = m_threadAmount;
    is_paused = true;
    for (size_t i = 0; i < m_threadAmount; ++i)
    {
        printf("Pausing \n");
        std::shared_ptr<ITask > task(new PauseTask(m_pauseSem));
        AddTask(task, static_cast<priority_ty>(HIGH+2));
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
    sem_wait(&m_pauseSem);
}

ThreadPool::FunctionTask::~FunctionTask()
{
    //
    printf("FunctionTask done \n");
}

void ThreadPool::Resume()
{
    // printf("thread amount for resume %d\n", m_to_resume);
    is_paused = false;
    for (std::size_t i = 0; i < m_threadAmount ; ++i)
    {
        printf("Resuming \n");
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
    int diff = thread_amount - m_threadAmount;
    if (is_paused)
    {
        throw std::string("illegal state");
    }
    if (diff > 0)
    {
        for (int i = 0; i < diff ; ++i)
        {
            details::CreateAndDetachThread(std::ref(m_pqueue),
                                    std::ref(m_enables), 
                                    &m_sem_finish);
            sem_wait(&m_sem_finish);
        }
    }
    else
    {
        for (int i = diff; i != 0; ++i)
        {
            std::shared_ptr<ITask > task(new BadApple(m_enables));
            AddTask(task, static_cast<priority_ty>(HIGH+2));
        }
        for (int i = diff; i != 0; ++i)
        {
            sem_wait(&m_sem_finish);

        }
       
    }
    m_threadAmount = thread_amount;
}

}
