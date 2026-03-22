#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LinearSystem
{
protected:
    int n;
    vector<vector<double>> A;
    vector<double> b;

public:
    LinearSystem();

    void readLeftMatrix(const string &file);
    void readRightVector(const string &file);

    void displaySystem(ostream &out) const;

    int size() const;

    virtual vector<double> solve() = 0;
};

class GaussianNoPivot : public LinearSystem
{
public:
    vector<double> solve() override;
};

class GaussianPivot : public LinearSystem
{
public:
    vector<double> solve() override;
};

#endif