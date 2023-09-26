// Person.h ファイル
#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
public:
    Person() : name_(""), age_(0) {}
    Person(const std::string& name, int age) : name_(name), age_(age) {}
    
    // Getter and Setter for name_
    std::string getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }
    
    // Getter and Setter for age_
    int getAge() const { return age_; }
    void setAge(int age) { age_ = age; }
    
private:
    std::string name_;
    int age_;
};

#endif // PERSON_H
