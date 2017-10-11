#ifndef TASK_H
#define TASK_H

#include <windows.h>
#include <random>

class Task
{
public:
	virtual void startTask()
	{
		if( m_task_in_progress )
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(50, 100000);
			std::cout << "Sleeping... \n" << "Thread id: " << std::this_thread::get_id() << std::endl;
			Sleep(dis(gen));
		}	
		else
			m_task_in_progress = true;
	}

	Task() : m_task_in_progress(true) {};
	virtual ~Task(){};
private:

	bool m_task_in_progress;
};

#endif // !TASK_H
