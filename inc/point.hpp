#ifndef POINT_HPP
#define POINT_HPP

class Point{
public:
	Point(int t_x, int t_y) : x(t_x), y(t_y) {}
	Point(const Point& t_point) : x(t_point.x), y(t_point.y) {}
	int x, y;
};

#endif
