#ifndef AHP_AHP_H
#define AHP_AHP_H

#include <iostream>
#include <vector>
#include <string>
#include "Loader.h"

using namespace std;

namespace Ahp {
    void ahpAlgorithm(Loader &loader, string path_solution_file);

    void normalizePairwiseComparisons(vector<vector<vector<float>>> &pairwise_comparisons);

    vector<vector<float>> &calculateEigenVector(vector<vector<vector<float>>> &pairwise_comparisons);

    vector<float> &calculateMaximumEigenValue(vector<vector<vector<float>>> &pairwise_comparisons,
                                              vector<vector<float>> &eigen_vector);

    vector<float> &calculateConsistencyIndex(vector<float> &maximum_eigen_value, int n);

    vector<float> &calculateConsistencyRate(vector<float> &consistency_index, int n);

    void writeSolution(Loader &loader, string path_solution_file, vector<vector<float>> &eigen_vector,
                       vector<float> &consistency_index,  vector<float>& consistency_rate);
    vector<vector<int>> & getRanking(vector<vector<float>> &eigen_vector);
};


#endif //AHP_AHP_H
