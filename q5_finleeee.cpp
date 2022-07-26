#include <iostream>
#include <vector>
#include <string>

#define PI 3.14159265359

struct Point {
	Point() :
		x(0),
		y(0)
	{}
	Point(int x_, int y_) :
		x(x_),
		y(y_)
	{}
	int getY() const { return y; }
	int getX() const { return x; }

	friend std::ostream& operator<<(std::ostream& out, const Point& other) {
		out << "(" << other.getX() << "," << other.getY() << ")" << std::endl;
		return out;
	}

	int x;
	int y;
};

struct Size {

	Size() :
		width(0),
		height(0) {}

	Size(int width_, int height_) :
		width(width_),
		height(height_) {}

	int width;
	int height;
};


struct Radius {

	Radius() :
		lenght(0) {}

	Radius(int lenght_) :
		lenght(lenght_) {}

	int lenght;
};


class Shape {
public:
	virtual const Point& center() const = 0;
	virtual double area() const = 0;
	virtual std::string name() const = 0;

protected:
	float width;
	float height;
	Point m_center;
	Size  m_size;
};


class Rectangle :public Shape {
public:

	Rectangle(const Point& center, const Size& size) :
		m_center(center),
		m_size(size)
	{}

	const Size& size() const{
		return m_size;
	}

	const Point& center() const {
		return m_center;
	}

	double area() const
	{
		return m_size.width * (size_t)m_size.height;
	}
	std::string name() const
	{
		std::string n = "Rectangle";
		return n;
	}
protected:

	Point m_center;
	Size  m_size;
};


class Circle : public Shape {
public:
	Circle(const Point& center, const Radius& radius) :
		m_center(center),
		m_radios(radius)
	{}
	const Point& center() const {
		return m_center;
	}
	std::string name() const
	{
		std::string n = "Circle";
		return n;
	}
	double area() const
	{
		return PI * m_radios.lenght * m_radios.lenght;
	}

protected:
	Point m_center;
	Radius  m_radios;

};


int main(int argc, char** argv)
{
	//Do not change anything in this function body
	Circle circle1(Point(5, 5), 10);
	Rectangle rect1(Point(5, 5), Size(10, 10));
	Circle circle2(Point(8, 8), 4);
	Point point1(5, 7);
	std::cout << point1;
	std::vector<Shape*> shapes{ &circle1, &rect1, &circle2 };
	for (const Shape* shape : shapes) {
		std::cout << "Shape: " << shape->name() << " center: " << shape->center() << " area: " << shape->area() << std::endl;
	}

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}

