#include <iostream>

int main() {
    int x = 10;

    if (x > 5) {
        std::cout << "x is greater than 5." << std::endl;
    } else {
        std::cout << "x is less than or equal to 5." << std::endl;
    }

    for (int i = 0; i < x; ++i) {
        std::cout << i << std::endl;
    }

    return 0;
}
