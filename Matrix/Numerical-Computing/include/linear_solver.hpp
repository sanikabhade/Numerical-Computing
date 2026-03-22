#ifndef LINEAR_SOLVER_HPP
#define LINEAR_SOLVER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

class Matrix
{
protected:
    int rows, cols;
    vector<vector<double>> A;
    vector<double> b;

public:
    Matrix();
    Matrix(int r, int c);
    Matrix(const Matrix &other);

    void readLeftMatrixFromFile(const string &filename);
    void readRightVectorFromFile(const string &filename);
    void displaySystem(ostream &out) const;
    void displayMatrixOnly(ostream &out) const;

    int getRows() const;
    int getCols() const;
    vector<vector<double>> getA() const;
    vector<double> getB() const;

    void setSystem(const vector<vector<double>> &mat, const vector<double> &vec);

    bool isSquare() const;
    bool isSymmetric() const;
    bool isIdentity() const;
    bool isNull() const;
    bool isDiagonal() const;
    bool isDiagonallyDominant() const;
    bool isTranspose(const Matrix &m) const;

    Matrix transpose() const;
    double determinant() const;
    Matrix inverse() const;
};

class LUDecomposition : public Matrix
{
public:
    LUDecomposition();

    void doolittle(vector<vector<double>> &L, vector<vector<double>> &U) const;
    void crout(vector<vector<double>> &L, vector<vector<double>> &U) const;
    void cholesky(vector<vector<double>> &L) const;

    vector<double> solveUsingLU(const vector<vector<double>> &L,
                                const vector<vector<double>> &U) const;

    void displayMatrix(const vector<vector<double>> &M,
                       const string &name,
                       ostream &out) const;
};

#endif
