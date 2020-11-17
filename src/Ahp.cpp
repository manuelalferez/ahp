#include "Ahp.h"

void Ahp::ahpAlgorithm(Loader &loader, string path_solution_file) {
    vector<vector<vector<float>>> pairwise_comparisons = loader.getPairwiseComparisons();
    vector<vector<vector<float>>> pairwise_comparisons_normalized = pairwise_comparisons;
    normalizePairwiseComparisons(pairwise_comparisons_normalized);
    vector<vector<float>> eigen_vector = calculateEigenVector(pairwise_comparisons_normalized);
    vector<float> maximum_eigen_value = calculateMaximumEigenValue(pairwise_comparisons, eigen_vector);
    vector<float> consistency_index = calculateConsistencyIndex(maximum_eigen_value, pairwise_comparisons.size() - 1);
    vector<float> consistency_rate = calculateConsistencyRate(consistency_index, pairwise_comparisons.size() - 1);
    writeSolution(loader, path_solution_file, eigen_vector, consistency_index, consistency_rate);
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
    consistency_index->at(0) = (maximum_eigen_value.at(0) - n) / (n - 1);
    n = n - 1;
    for (int i = 1; i < consistency_index->size(); ++i) {
        consistency_index->at(i) = (maximum_eigen_value.at(i) - n) / (n - 1);
    }
    return *consistency_index;
}

vector<float> &Ahp::calculateConsistencyRate(vector<float> &consistency_index, int n) {
    float random_consistency_ratio[10] = {0, 0, 0.58, 0.9, 1.12, 1.24, 1.32, 1.41, 1.45, 1.49};
    vector<float> *consistency_rate = new vector<float>(consistency_index.size());
    float consistency_ratio = random_consistency_ratio[n - 1];
    consistency_rate->at(0) = consistency_index.at(0) / consistency_ratio;
    n = n - 1;
    consistency_ratio = random_consistency_ratio[n - 1];
    for (int i = 1; i < consistency_rate->size(); ++i) {
        consistency_rate->at(i) = consistency_index.at(i) / consistency_ratio;
    }
    return *consistency_rate;
}

void Ahp::writeSolution(Loader &loader, string path_solution_file, vector<vector<float> > &eigen_vector,
                        vector<float> &consistency_index, vector<float> &consistency_rate) {
    vector<string> criteria = loader.getCriteria();
    vector<string> alternatives = loader.getAlternatives();
    ofstream file;
    file.open(path_solution_file);
    if (file.good()) {
        vector<vector<int>> ranking = getRanking(eigen_vector);
        file << "Ranking" << endl;
        file << "------------------ " << endl;
        for (int k = 0; k < ranking.size(); ++k) {
            if (k == 0) {
                file << "CRITERIA VS CRITERIA" << endl;
                for (int j = 0; j < ranking.at(k).size(); ++j) {
                    file << "Criteria " << criteria.at(j) << ": " << ranking.at(k).at(j) << endl;
                }
            } else {
                file << "ALTERNATIVES VS ALTERNATIVES" << endl;
                file << "Criteria: " << criteria.at(k - 1) << endl;
                for (int j = 0; j < ranking.at(k).size(); ++j) {
                    file << "Alternative " << alternatives.at(j) << ": " << ranking.at(k).at(j) << endl;
                }
            }
            file << endl;
        }
        file << "Eigen vectors " << endl;
        file << "------------------ " << endl;
        for (int i = 0; i < eigen_vector.size(); ++i) {
            if (i == 0) {
                file << "CRITERIA VS CRITERIA" << endl;
                for (int j = 0; j < eigen_vector.at(i).size(); ++j) {
                    file << "Criteria " << criteria.at(j) << ": " << eigen_vector.at(i).at(j) << endl;
                }
            } else {
                file << "ALTERNATIVES VS ALTERNATIVES" << endl;
                file << "Criteria: " << criteria.at(i - 1) << endl;
                for (int j = 0; j < eigen_vector.at(i).size(); ++j) {
                    file << "Alternative " << alternatives.at(j) << ": " << eigen_vector.at(i).at(j) << endl;
                }
            }
            file << endl;
        }
        file << "Consistency index " << endl;
        file << "------------------ " << endl;
        for (int i = 0; i < consistency_index.size(); ++i) {
            if (i == 0) {
                file << "CRITERIA VS CRITERIA" << endl;
            } else {
                file << "ALTERNATIVES VS ALTERNATIVES" << endl;
                file << "Criteria " << criteria.at(i - 1) << ": ";
            }
            file << consistency_index.at(i);
            file << endl << endl;
        }
        file << "Consistency rate " << endl;
        file << "------------------ " << endl;
        for (int i = 0; i < consistency_rate.size(); ++i) {
            if (i == 0) {
                file << "CRITERIA VS CRITERIA" << endl;
            } else {
                file << "ALTERNATIVES VS ALTERNATIVES" << endl;
            }
            file << consistency_rate.at(i);
            file << endl << endl;
        }
    } else {
        cerr << "Cannot open file." << endl;
    }
}

vector<vector<int>> &Ahp::getRanking(vector<vector<float> > &eigen_vector) {
    vector<vector<int>> *ranking = new vector<vector<int>>(eigen_vector.size());
    for (int i = 0; i < eigen_vector.size(); ++i) {
        ranking->at(i).resize(eigen_vector.at(i).size());
        for (int k = 0; k < ranking->at(i).size(); ++k) {
            ranking->at(i).at(k) = 1;
        }
        int pos = 0;
        for (int j = 0; j < eigen_vector.at(i).size() - 1; ++j) {
            for (int k = j; k < eigen_vector.at(i).size(); ++k) {
                if (j != k) {
                    if (eigen_vector.at(i).at(j) < eigen_vector.at(i).at(k)) {
                        ranking->at(i).at(j) += 1;
                    } else {
                        ranking->at(i).at(k) += 1;
                    }
                }
            }
        }
    }
    return *ranking;
}