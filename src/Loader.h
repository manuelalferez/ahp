#ifndef AHP_LOADER_H
#define AHP_LOADER_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <climits>

using namespace std;

class Loader {
public:
    explicit Loader(string &pathFile);
private:
    static void skip(std::istream &is, size_t n, char delimiter);
    bool isFraction(string term);
    float fractionToFloat(string fraction);

private:
    vector<vector<vector<float>>> pairwise_comparisons;
    vector<string> alternatives;
    vector<string> criteria;
};

#endif //AHP_LOADER_H
