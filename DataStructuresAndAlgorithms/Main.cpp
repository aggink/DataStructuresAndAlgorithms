#include <iostream>
#include <stdexcept>
#include <string>
#include "OneList.h"

using namespace std;

int main(int argc, char const* argv[]) {
    OneList<char> charList;

    // Test the push_back function
    charList.push_back('A');
    if (charList.size() != 1 || charList.back() != 'A') {
        std::cerr << "Validation failed for push_back" << std::endl;
    }

    // Test the size and operator[] functions
    charList.push_back('B');
    if (charList.size() != 2 || charList[0] != 'A' || charList[1] != 'B') {
        std::cerr << "Validation failed for size and operator[]" << std::endl;
    }

    // Test the pop_back function
    charList.pop_back();
    if (charList.size() != 1 || charList.back() != 'A') {
        std::cerr << "Validation failed for pop_back" << std::endl;
    }

    // Test the clear function
    charList.clear();
    if (charList.size() != 0) {
        std::cerr << "Validation failed for clear" << std::endl;
    }

    // Test the push_front function
    charList.push_front('X');
    if (charList.size() != 1 || charList.front() != 'X') {
        std::cerr << "Validation failed for push_front" << std::endl;
    }

    // Report results
    if (!std::cerr) {
        std::cout << "Some validations failed!" << std::endl;
    }
    else {
        std::cout << "All validations passed!" << std::endl;
    }


    charList.clear();

    for (int i = 0; i < 1000; i++) {
        char character = 'A' + (i % 26); // Cycles through 'A' to 'Z'
        charList.push_back(character);
    }

    // Display the first 50 values on the screen
    for (int i = 0; i < 50 && i < charList.size(); i++) {
        std::cout << charList[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}