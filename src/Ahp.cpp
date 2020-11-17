#include "Ahp.h"

void Ahp::ahpAlgorithm(Loader loader, string path_solution_file) {
    vector<vector<vector<float>>> pairwise_comparisons = loader.getPairwiseComparisons();
    normalizePairwiseComparisons(pairwise_comparisons);
}

void Ahp::normalizePairwiseComparisons(vector<vector<vector<float> > > &pairwise_comparisons) {
    for (int i = 0; i < pairwise_comparisons.size(); ++i) {
        for (int j = 0; j < pairwise_comparisons.at(i).size(); ++j) {
            float sum = 0;
            for (int k = 0; k < pairwise_comparisons.at(i).size(); ++k) {
                sum += pairwise_comparisons.at(i).at(k).at(j);
            }
            for (int k = 0; k < pairwise_comparisons.at(i).size(); ++k) {
                pairwise_comparisons.at(i).at(k).at(j) /= sum;
            }
        }
    }
}