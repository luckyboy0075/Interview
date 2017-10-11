#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>

class ThreadPool
{
public:
	static ThreadPool& getInstance()
	{
		static ThreadPool instance;
		return instance;
	}

	void processThreadQueue(std::thread* i_thread_to_add)
	{
		std::cout << "Tread was added to queue, thread id: \t" << i_thread_to_add->get_id() << std::endl;
		m_mutex.lock();

		m_thread_pool.push_back(i_thread_to_add);
		i_thread_to_add->join();

		m_mutex.unlock();
	}

	void deleteThreadQueue()
	{
		m_thread_pool.clear();
		std::cout << "Thread queue size equals: \t" << m_thread_pool.size() << std::endl;
	}
private:
	std::deque<std::thread*> m_thread_pool;
	std::mutex m_mutex;

private:
	ThreadPool() {};
	~ThreadPool() {};
	ThreadPool(const ThreadPool&) {};
	ThreadPool& operator=(const ThreadPool&) {};


};

#endif // !THREAD_POOL_H
