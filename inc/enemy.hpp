#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "point.hpp"

class Enemy{
public:
	Enemy() : pos(0, 0) {}
	Enemy(Point t_pos) : pos(t_pos) {}
	void move(int, int);
	void doAI();
	Point pos;

// private:
};

#endif