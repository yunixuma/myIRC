#include "Person.h"
#include <iostream> // これを追加
#include "Person.h"
#include "a.hpp"
#include <vector>

int main() {
    std::vector<Person> person_vector;
    std::vector<A> a;
	a.push_back(A("a"));
        std::cout << "Name: " << p.getName() << ", Age: " << p.getAge() << std::endl;
    // Person オブジェクトを作成し、ベクターに追加
    person_vector.push_back(Person("Alice", 30));
    person_vector.push_back(Person("Bob", 40));
    person_vector.push_back(Person("Charlie", 50));
    person_vector.push_back(Person("Lee", 60));
    
    // ベクターから要素を取り出して処理
    for (const Person& p : person_vector) {
        std::cout << "Name: " << p.getName() << ", Age: " << p.getAge() << std::endl;
    }
    
    return 0;
}
