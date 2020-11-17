#include <iostream>

#include "Loader.h"
int main() {
    string data_path = "../data/data.txt";
    std::cout << "Hello, AHP!" << std::endl;
    Loader loader(data_path);
    return 0;
}
