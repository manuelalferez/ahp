#include "Loader.h"

Loader::Loader(string &pathFile) :
        pairwise_comparisons() {
    ifstream fe;
    string line;

    fe.open(pathFile);

    if (fe.good()) {
        while (!fe.eof()) {
            skip(fe, 1, '\n');
            getline(fe, line);
            stringstream ss;
            ss << line;

            string term;
            float value;

            do {
                getline(ss, term, ';');
                this->alternatives.push_back(term);
            } while (!ss.eof());

            skip(fe, 2, '\n');
            getline(fe, line);
            ss.clear();
            ss << line;

            do {
                getline(ss, term, ';');
                this->criteria.push_back(term);
            } while (!ss.eof());

            skip(fe, 2, '\n');

            this->pairwise_comparisons.resize(this->criteria.size() + 1);
            this->pairwise_comparisons[0].resize(this->criteria.size());
            for (int i = 0; i < this->alternatives.size(); ++i) {
                getline(fe, line);
                ss.clear();
                ss << line;

                do {
                    getline(ss, term, ';');
                    if (isFraction(term)) {
                        value = fractionToFloat(term);
                    } else {
                        value = stof(term);
                    }
                    this->pairwise_comparisons.at(0).at(i).push_back(value);
                } while (!ss.eof());
            }
            skip(fe, 2, '\n');
            for (int j = 1; j < this->criteria.size() + 1; ++j) {
                this->pairwise_comparisons[j].resize(this->alternatives.size());
                for (int i = 0; i < this->alternatives.size(); ++i) {
                    getline(fe, line);
                    ss.clear();
                    ss << line;

                    do {
                        getline(ss, term, ';');
                        if (isFraction(term)) {
                            value = fractionToFloat(term);
                        } else {
                            value = stof(term);
                        }
                        this->pairwise_comparisons.at(j).at(i).push_back(value);
                    } while (!ss.eof());
                }
                skip(fe, 1, '\n');
            }
        }
        cout << "File charged successfully." << endl;
        fe.close();
    } else {
        cerr << "Cannot open file." << endl;
    }
}

void Loader::skip(istream &is, size_t n, char delimiter) {
    size_t i = 0;
    while (i++ < n)
        is.ignore(80, delimiter);
}

bool Loader::isFraction(string term) {
    auto found = term.find("/");
    return found != string::npos ? true : false;
}

float Loader::fractionToFloat(string fraction) {
    string numerator = fraction.substr(0, fraction.find('/'));
    string denominator = fraction.substr(2, fraction.find('/'));
    return stof(numerator) / stof(denominator);
}