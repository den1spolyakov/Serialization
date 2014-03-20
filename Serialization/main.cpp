#include "serialization.h"
#include <iostream>

class Test1
{
public:
	int a;
	std::string str;

	SAVE
		REG(a)
		REG(str)
	END
};

class Test2
{
public:
	int b;
	Test1 inner;
	
	SAVE
		REG(b)
		REG(inner)
	END
};

int main()
{
	Writer wr;

	Test2 t;
	t.b = 10;
	t.inner.a = 25;
	t.inner.str = "Hello!";

	wr << t;

	Reader rd(wr.getBuffer(), wr.getSize());

	Test2 t1;
	rd >> t1;
	
	std::cout << t1.b << " {" << t1.inner.a << " " << t1.inner.str << "}\n";

	std::cin.get();
}
