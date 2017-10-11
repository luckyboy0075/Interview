#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include "Task.h"

class ThreadPool
{
public:
	static ThreadPool& getInstance()
	{
		static ThreadPool instance;
		return instance;
	}

	void generateTaskQueue(int i_amount) 
	{
		for (int i = 0; i < i_amount; ++i)
		{
			std::function<void()> callfunc = std::bind(&Task::startTask, Task());
			m_task_pool.push(callfunc);
		}

	}

	void processThreadQueue()
	{
		while (!m_task_pool.empty())
		{
			std::cout << "##################################" << std::endl;

			std::thread thread(m_task_pool.front());
			m_mutex.lock();

			std::cout << "Thread was added to queue, thread id: " << thread.get_id() << std::endl;
			m_thread_pool.push_back(&thread);

			thread.join();
			deleteThreadFromQueue();

		}
	}
	void deleteThreadFromQueue()
	{	
		std::cout << "Thread was deleted from queue, thread id: " << m_thread_pool.front()->get_id() << std::endl;
		m_mutex.unlock();

		m_thread_pool.pop_front();
		std::cout << "Thread queue size: " << m_thread_pool.size() << std::endl;
	}

private:
	std::deque<std::thread*> m_thread_pool;
	std::queue<std::function<void()>> m_task_pool;
	
	std::mutex m_mutex;

private:
	ThreadPool() {};
	~ThreadPool() {};
	ThreadPool(const ThreadPool&) {};
	ThreadPool& operator=(const ThreadPool&) {};


};

#endif // !THREAD_POOL_H
