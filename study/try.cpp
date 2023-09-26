#include <iostream>
#include <stdexcept>
void f(int i)
{
	if(i >= 0)
	throw std::exception();
}

int main ()
{
	try{

	f(-1);
	}catch(const std::exception& e){
		std::cerr << "invalid" <<std::endl;
	}
	
	
}

