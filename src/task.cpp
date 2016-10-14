#include "task.hpp"

bool Task::operator<(const Task& first) const {
	return first.m_priority < m_priority;
}