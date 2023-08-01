#include <iostream>
#include <vector>


using std::vector;
using std::cout;
using std::endl;

int main ()
{
	vector<int> n = {1, 2, 3, 4, 5};

	for(vector<int>::iterator it = n.begin();it != n.rbegin();it++)
	cout << *it << " ";
std::cout << endl;
}
