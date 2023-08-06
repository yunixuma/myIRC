#include <iostream>
#include <stdexcept>

// A function that might throw an exception
double divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    return static_cast<double>(a) / b;
}

int main() {
    try {
        double result = divide(10, 0); // This will throw an exception
        std::cout << "The result is: " << result << std::endl;
    } catch (const std::exception& e) {
        // Handle the exception
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }
    return 0;
}
