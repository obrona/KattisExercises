#include <iostream>
using namespace std;

#include <iostream>

int main() {
    int a, b;

    // Read the first pair of integers
    while (std::cin >> a >> b) {
        // Process the input
        std::cout << "a is " << a << ", b is " << b << std::endl;
    }

    // Check for the end-of-file or input error
    if (std::cin.eof()) {
        std::cout << "End of file reached." << std::endl;
    } else {
        std::cerr << "Input error occurred." << std::endl;
    }

    return 0;
}
