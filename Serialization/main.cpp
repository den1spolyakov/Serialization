#include "derived.h"

int main()
{
	Derived1 d;
	
	d.load("test1.txt");
	d.setX(23);
	d.setY(-9);
	d.save("test2.txt");
	
	
	std::cin.get();
	return 0;
}