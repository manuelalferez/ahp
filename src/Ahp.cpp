#include "Ahp.h"

void Ahp::ahpAlgorithm(Loader loader, string path_solution_file) {
    vector<vector<vector<float>>> pairwise_comparisons = loader.getPairwiseComparisons();
    vector<vector<vector<float>>> pairwise_comparisons_normalized = pairwise_comparisons;
    normalizePairwiseComparisons(pairwise_comparisons_normalized);
    vector<vector<float>> eigen_vector = calculateEigenVector(pairwise_comparisons_normalized);
    vector<float> maximum_eigen_value = calculateMaximumEigenValue(pairwise_comparisons, eigen_vector);
    vector<float> consistency_index = calculateConsistencyIndex(maximum_eigen_value, pairwise_comparisons.size() - 1);
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

vector<vector<float> > &Ahp::calculateEigenVector(vector<vector<vector<float> > > &pairwise_comparisons) {
    vector<vector<float>> *eigen_vector = new vector<vector<float>>(pairwise_comparisons.size());
    for (int i = 0; i < pairwise_comparisons.size(); ++i) {
        eigen_vector->at(i).resize(pairwise_comparisons.at(i).size());
        for (int j = 0; j < pairwise_comparisons.at(i).size(); ++j) {
            float sum = 0;
            for (int k = 0; k < pairwise_comparisons.at(i).size(); ++k) {
                sum += pairwise_comparisons.at(i).at(j).at(k);
            }
            eigen_vector->at(i).at(j) = sum / pairwise_comparisons.at(i).size();
        }
    }
    return *eigen_vector;
}

vector<float> &Ahp::calculateMaximumEigenValue(vector<vector<vector<float> > > &pairwise_comparisons,
                                               vector<vector<float> > &eigen_vector) {
    vector<float> *maximum_eigen_value = new vector<float>(pairwise_comparisons.size());
    for (int i = 0; i < pairwise_comparisons.size(); ++i) {
        for (int j = 0; j < pairwise_comparisons.at(i).size(); ++j) {
            float sum = 0;
            for (int k = 0; k < pairwise_comparisons.at(i).size(); ++k) {
                sum += pairwise_comparisons.at(i).at(k).at(j);
            }
            maximum_eigen_value->at(i) += sum * eigen_vector.at(i).at(j);
        }
    }
    return *maximum_eigen_value;
}

vector<float> &Ahp::calculateConsistencyIndex(vector<float> &maximum_eigen_value, int n) {
    vector<float> *consistency_index = new vector<float>(maximum_eigen_value.size());
    for (int i = 0; i < consistency_index->size(); ++i) {
        consistency_index->at(i) = (maximum_eigen_value.at(i) - n) / (n - 1);
    }
    return *consistency_index;
}