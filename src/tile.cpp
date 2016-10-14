#include "tile.hpp"

Tile::Tile() : m_x(0), m_y(0){}

Tile::Tile(int t_x, int t_y) : m_x(t_x), m_y(t_y) {}

int Tile::x(){
	return m_x;
}

int Tile::y(){
	return m_y;
}