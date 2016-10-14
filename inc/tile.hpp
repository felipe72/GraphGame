#ifndef TILE_HPP
#define TILE_HPP

class Tile{
public:
	Tile(int , int);
	Tile();

	int x();
	int y();

private:
	int m_x, m_y;
};

#endif