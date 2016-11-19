#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "map.hpp"
#include "object.hpp"
#include "point.hpp"

class Player : public Object{
	public:
	Player() : Object('p') {}
	Player(Point t_pos) : Object(t_pos, 'p') {}
	Player(Point t_pos, Map *t_map) : Object(t_pos, 'p') {map = t_map;}
	void input();
	bool SetEnemiesActive(){return setEnemiesActive;}

private:
	Map *map;
	bool setEnemiesActive = false;
};

#endif