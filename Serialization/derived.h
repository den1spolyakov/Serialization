#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"
#include <string>

class Derived1 : public Base
{
public:
	Derived1(int x = 0, int y = 0, const std::string &str = "empty") 
		: m_x(x), m_y(y), m_str(str)
	{
		REGISTER(int, m_x);
		REGISTER(int, m_y);
		REGISTER(std::string, m_str);
	}

	friend std::ostream& operator<<(std::ostream &os, const Derived1 &derived);
	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }
private:
	int m_x;
	int m_y;
	std::string m_str;
};

std::ostream& operator<<(std::ostream &os, const Derived1 &derived)
{
	os << derived.m_x << " " << derived.m_y << " " <<derived.m_str << std::endl;
	return os;
}

#endif