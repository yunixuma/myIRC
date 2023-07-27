#include <vector>
#include <iostream>
#include <map>
int main ()
{

using std::string;
using std::map;

std::map<std::string, int> ages;
ages["10"] = 1;  // []演算子を使った方法

std::map<std::string, int> ages;
ages.insert(std::pair<std::string, int>("10", 1));  // insert メソッドを使った方法

std::map<std::string, int> ages;
ages.insert({"10", 1});  // insert メソッドを使った方法（C++11以降）

map<std::string, int> ages;
ages = map<"10", 1>;


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

ages:
{
  "a": 25,
  "b": 25
}