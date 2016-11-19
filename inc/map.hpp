#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>

#include "point.hpp"
#include "object.hpp"

#define DEFAULT_HEIGHT 10
#define DEFAULT_WIDTH 10

class Tile{
public:
	Tile() {}
	Tile(char t_icon) : icon(t_icon) {}
	Tile(int t_weight) : weight(t_weight) {}
	Tile(char t_icon, int t_weight) : icon(t_icon), weight(t_weight) {}
	char icon;
	int weight;
};

class Map{
public:
	Map();
	Map(int , int);
	~Map();
	void print();
	void addIcon(Point, char);
	void addIcon(Point, char, int);
	void addObject(Object*);
	void removeObject(Object);
	int getHeight() { return m_height;}
	int getWidth(){return m_width;}
	int getWeight(Point p){ return m_map[p.x][p.y].weight;}
	void addMud(Point);
	// find(Point);
private:
	std::vector<Object*> objects;
	Tile **m_map;
	void allocate(int, int);
	void clear();
	int m_height, m_width;
};

#endif