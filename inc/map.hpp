#ifndef MAP_HPP
#define MAP_HPP

#include "point.hpp"

#define DEFAULT_HEIGHT 10
#define DEFAULT_WIDTH 10

class Map{
public:
	Map();
	Map(int , int);
	~Map();
	find(Point);
private: 
	char **m_map;
	void allocate(int, int);
};

#endif