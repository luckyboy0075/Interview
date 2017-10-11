#ifndef TASK_H
#define TASK_H

#include <windows.h>
#include <random>

class Task
{
public:
	void startTask() 
	{
		if( m_task_in_progress )
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(50, 10000);
			std::cout << "\nSleeping... \t" << "Thread id: \t" << std::this_thread::get_id() << std::endl;
			Sleep(dis(gen));
		}	
		else
			m_task_in_progress = true;
	}

	void stopTask()
	{
		std::cout << "Stopping task execution from thread:"<< std::this_thread::get_id() << std::endl;
		m_task_in_progress = false;
	}

	bool checkTaskStatus()
	{
		return m_task_in_progress;
	}

	Task() : m_task_in_progress(true) {};
	~Task()
	{
		//stopTask();
	};
private:

	bool m_task_in_progress;
};

#endif // !TASK_H
