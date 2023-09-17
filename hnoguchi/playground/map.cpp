#include <iostream>
#include <map>
#include <string>

typedef std::map<std::string, int>	stringMap;

int	main()
{
	stringMap	sample;

	// insert
	sample.insert(std::make_pair("first", 0));
	sample.insert(std::make_pair("second", 1));
	sample.insert(std::make_pair("third", 2));

	std::cout \
		<< sample.max_size() << "\n" \
		<< sample.size() << "\n" \
		<< std::boolalpha << sample.empty() << "\n" \
		<< std::endl;

	// access
	std::cout << sample["second"] << std::endl;
	sample["second"] = 100;
	sample["third"] = 200;
	std::cout << sample["second"] << std::endl;
	std::cout << sample["third"] << std::endl;

	// iteratorが指す先にあるのは、std::pair<const Key, T>です。
	// そのため、it->firstでキーが得られ、it->secondで要素の値が得られる。
	// ただし、イテレータを通して要素のキーを書き換えることはできない。
	// 要素を変更するSTLアルゴリズムにイテレータを渡してもいけない。

	// search (find, count)
	// find(); 
	// 発見できなかった場合は、end¸メンバ関数が返す結果と同じイテレータを返す。
	stringMap::iterator	it = sample.find("second");
	if (it != sample.end()) {
		std::cout << "FIND!!" << std::endl;
	}
	else {
		std::cout << "NOT FOUND!!" << std::endl;
	}
	// count();
	// mapの場合は、要素の重複を許さないので必ず０か１を返す。
	if (0 < sample.count("forth")) {
		std::cout << "FIND!!" << std::endl;
	}
	else {
		std::cout << "NOT FOUND!!" << std::endl;
	}

	// destruct
	// stringMap::iterator	it = sample.find("second");
	if (it != sample.end()) {
		sample.erase(it);
	}
}
