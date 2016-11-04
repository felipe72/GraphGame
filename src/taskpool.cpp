#include <mutex>
#include <iostream>

#include "taskpool.hpp"

void threadInit(){
	std::cout << "Thread initialized\n";
}

TaskPool::TaskPool(){
	checkTasks = std::thread(&TaskPool::taskLoop, this);
	for(int i=0; i<MAX_NUMBER_THREADS; i++){
		threadPool[i] = std::thread(threadInit);
	}
}

TaskPool::~TaskPool(){
	if(checkTasks.joinable()){
		checkTasks.join();
	}
	for(int i=0; i<MAX_NUMBER_THREADS; i++){
		threadPool[i].join();
	}
}

void TaskPool::add(typeFunction t_function, int priority=1){
	std::mutex mx;

	mx.lock();
	m_functions.push(Task(priority, t_function));
	mx.unlock();
}

void noFunction(){
	std::cout << "No functions left\n";
}

typeFunction TaskPool::remove(){
	std::mutex mx;
	Task task;

	// int priority;
	typeFunction function;

	if(not m_functions.empty()){
		mx.lock();
		task = m_functions.front();
		m_functions.pop();
		add(task.function());
		mx.unlock();

		// priority = task.priority();
		function = task.function();
	}
	else{
		// priority = -1;
		function = std::bind(noFunction);
	}

	return function;
}

void TaskPool::taskLoop(){
	while(active){
		// std::cout << "Oi\n";
		if(not m_functions.empty())
			invokeAll();
	}
}

void TaskPool::invokeAll(){
	for(int i=0; not m_functions.empty(); i = (i+1)%MAX_NUMBER_THREADS){
		typeFunction f = remove();
		if(threadPool[i].joinable()){
			threadPool[i].join();
			threadPool[i] = std::thread(f);
		}
	}
}


void TaskPool::terminate(){
	std::mutex mx;
	mx.lock();
	while(not m_functions.empty()){
		m_functions.pop();
	}
	active = false;
	mx.unlock();	
}