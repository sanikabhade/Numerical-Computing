#ifndef AUGMENT_HPP
#define AUGMENT_HPP

#include <vector>
#include <string>

using namespace std;

class AugmentMatrix
{
public:
    vector<vector<double>> readLeftMatrix(const string &filename, int &rows, int &cols);
    vector<double> readRightVector(const string &filename, int &rows, int &cols);
    void writeAugmentedMatrix(const string &filename,
                              const vector<vector<double>> &A,
                              const vector<double> &b);
};

#endif