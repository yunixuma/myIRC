#include <iostream>
#include <vector>


int main ()
{
using std::vector;
using std::cout;
using std::endl;
	vector<int> n = {1, 2, 3, 4, 5};
	n.push_back (6);
	// n.pop_back();
	n.pop_back();
	
	if(!n.empty()){
		cout << "First elements " << *n.begin() << endl;
		cout << "last elements " << n.back() << endl;
		// back() は参照返しているだけ
	}


	for(vector<int>::iterator it = n.begin();it != n.end();it++)
	cout << *it << " ";
	cout << endl;
}

// C++98標準でベクターを初期化するには、初期化子リストで、初期化できないので注意