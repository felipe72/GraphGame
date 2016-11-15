#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "point.hpp"

enum Direction{
	UP, DOWN, LEFT, RIGHT
};

class Object{
public:
	Object() : pos(0, 0), icon('x') {}
	Object(char t_icon) : pos(0, 0), icon(t_icon) {}
	Object(Point t_pos, char t_icon) : pos(t_pos), icon(t_icon) {}
	Point getPos() {return pos;}
	char getIcon() {return icon;}
	void move(int, int);

protected:
	Point pos;
	char icon;
};

#endif