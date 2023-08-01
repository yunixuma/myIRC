#include <iostream>
#include <string>

class Dog {
public:
    std::string name;
    std::string barkSound;

    Dog(std::string name, std::string barkSound) {
        this->name = name;
        this->barkSound = barkSound;
    }

    void bark() {
        std::cout << name << " says: " << barkSound << "!" << std::endl;
    }
};

int main() {
    Dog dog1("Fido", "Woof");
    Dog dog2("Spot", "Ruff");

    dog1.bark();  // Outputs: Fido says: Woof!
    dog2.bark();  // Outputs: Spot says: Ruff!
}
