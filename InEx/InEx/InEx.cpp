// InEx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ThreadPool.h"

#define Pool ThreadPool::getInstance()

void main()
{
	Pool.generateTaskQueue(10);
	Pool.processThreadQueue();

	system("pause");
}