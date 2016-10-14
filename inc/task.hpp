#ifndef TASK_HPP
#define TASK_HPP

#include "functiontype.hpp"

class Task{
public:
	bool operator<(const Task& first) const;
	Task() {};
	Task(int t_priority, typeFunction t_function) : m_priority(t_priority), m_function(t_function) {};
	int priority() { return m_priority; }
	typeFunction function() {return m_function;}
private:
	int m_priority;
	typeFunction m_function;
};

#endif