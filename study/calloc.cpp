#include <cstdlib>
#include <iostream>

int main() {
    int *i = (int*) calloc(2, sizeof(int));

    while (i != NULL) { // Always check if calloc or malloc was successful
        std::cout << *i << std::endl;
        // free(i); // Don't forget to free allocated memory!
    } 

    return 0;
}
