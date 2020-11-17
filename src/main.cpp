#include <iostream>

#include "Ahp.h"

int main() {
    string data_path = "../data/data.txt";
    string solution_path_file = "../solution/solution.txt";
    std::cout << "Hello, AHP!" << std::endl;
    Loader loader(data_path);
    Ahp::ahpAlgorithm(loader, solution_path_file);
    return 0;
}
