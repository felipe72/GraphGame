#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "point.hpp"
#include "object.hpp"
#include "player.hpp"
#include "map.hpp"

class Enemy : public Object{
public:
	Enemy() : Object('e') {}
	Enemy(Point t_pos, Player *t_player, Map *t_map) : Object(t_pos, 'e') { player = t_player; map = t_map;}
	void doAI();

private:
	std::vector<Direction> movement;
	Map *map;
	void Dijkstra(int, int);
	Player *player;
};

#endif