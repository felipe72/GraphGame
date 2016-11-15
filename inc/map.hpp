#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>

#include "point.hpp"
#include "object.hpp"

#define DEFAULT_HEIGHT 20
#define DEFAULT_WIDTH 20

class Map{
public:
	Map();
	Map(int , int);
	~Map();
	void print();
	void addIcon(Point, char);
	void addObject(Object*);
	void removeObject(Object);
	int getHeight() { return m_height;}
	int getWidth(){return m_width;}
	// find(Point);
private:
	std::vector<Object*> objects;
	char **m_map;
	void allocate(int, int);
	void clear();
	int m_height, m_width;
};

#endif