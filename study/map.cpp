#include <vector>
#include <iostream>
#include <map>
int main ()
{

using std::string;
using std::map;

map<std::string, int> ages;
map<std::string, std::string> age;
ages["a"] = 25;
ages["b"] = 25;
age["c"] = "30";


int i = ages["a"];
int j = ages["b"];
std::string k = age["c"];
std::cout << "Alice's age: " << i<< std::endl; 
std::cout << "Alice's age: " << j<< std::endl; 
std::cout << "Alice's age: " << k<< std::endl; 


}