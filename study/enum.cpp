#include <iostream>
#include <map>
#include <string>

enum MyEnum {
    VALUE1,
    VALUE2,
    VALUE3
};

std::string EnumToString(MyEnum e) {
    switch(e) {
        case VALUE1: return "VALUE1";
        case VALUE2: return "VALUE2";
        case VALUE3: return "VALUE3";
        default: return "UNKNOWN";
    }
}

int main() {
    // MyEnumをキーとして使用
    std::map<MyEnum, int> myMap;
    myMap[VALUE1] = 10;
    myMap[VALUE2] = 20;
    myMap[VALUE3] = 30;

    // keyを探して出力
    for(std::map<MyEnum, int>::iterator iter = myMap.begin(); iter != myMap.end(); ++iter) {
        std::cout << "Key: " << EnumToString(iter->first)
                  << ", Value: " << iter->second << std::endl;
    }

    return 0;
}
