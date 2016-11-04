#ifndef TASK_POOL_HPP
#define TASK_POOL_HPP

#include <queue>
#include <thread>

#include "game.hpp"
#include "functiontype.hpp"
#include "task.hpp"

#define MAX_NUMBER_THREADS 2

class TaskPool{
public:
	TaskPool();
	~TaskPool();
	void add(typeFunction, int);
	void terminate();

private:
	bool active = true;
	typeFunction remove();
	void invokeAll();
	void taskLoop();
	std::queue<Task> m_functions;
	std::thread checkTasks;
	std::thread threadPool[MAX_NUMBER_THREADS];
};

#endif