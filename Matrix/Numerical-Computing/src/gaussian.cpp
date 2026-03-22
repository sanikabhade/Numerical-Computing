#include "gaussian.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <algorithm>

LinearSystem::LinearSystem() : n(0) {}

void LinearSystem::readLeftMatrix(const string &file)
{
    ifstream fin(file);

    if (!fin)
        throw runtime_error("Cannot open matrix file: " + file);

    int rows, cols;
    fin >> rows >> cols;

    if (!fin)
        throw runtime_error("Invalid matrix file format: " + file);

    if (rows != cols)
        throw runtime_error("Matrix must be square");

    n = rows;
    A.assign(n, vector<double>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> A[i][j];
            if (!fin)
                throw runtime_error("Invalid matrix data in file: " + file);
        }
    }

    fin.close();
}

void LinearSystem::readRightVector(const string &file)
{
    ifstream fin(file);

    if (!fin)
        throw runtime_error("Cannot open vector file: " + file);

    int rows, cols;
    fin >> rows >> cols;

    if (!fin)
        throw runtime_error("Invalid vector file format: " + file);

    if (rows != n)
        throw runtime_error("Row mismatch between matrix and vector");

    b.assign(rows, 0.0);

    for (int i = 0; i < rows; i++)
    {
        fin >> b[i];
        if (!fin)
            throw runtime_error("Invalid vector data in file: " + file);
    }

    fin.close();
}

void LinearSystem::displaySystem(ostream &out) const
{
    out << "\nAugmented Matrix:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            out << setw(14) << A[i][j] << " ";
        }
        out << " | " << setw(14) << b[i] << endl;
    }
}

int LinearSystem::size() const
{
    return n;
}

vector<double> GaussianNoPivot::solve()
{
    vector<vector<double>> mat = A;
    vector<double> rhs = b;

    int n = size();

    for (int i = 0; i < n - 1; i++)
    {
        if (fabs(mat[i][i]) < 1e-12)
            throw runtime_error("Zero pivot encountered in Gaussian elimination without pivoting");

        for (int j = i + 1; j < n; j++)
        {
            double factor = mat[j][i] / mat[i][i];

            for (int k = i; k < n; k++)
                mat[j][k] -= factor * mat[i][k];

            rhs[j] -= factor * rhs[i];
        }
    }

    if (fabs(mat[n - 1][n - 1]) < 1e-12)
        throw runtime_error("Zero pivot encountered during back substitution");

    vector<double> x(n);

    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = rhs[i];

        for (int j = i + 1; j < n; j++)
            x[i] -= mat[i][j] * x[j];

        if (fabs(mat[i][i]) < 1e-12)
            throw runtime_error("Division by zero during back substitution");

        x[i] /= mat[i][i];
    }

    return x;
}

vector<double> GaussianPivot::solve()
{
    vector<vector<double>> mat = A;
    vector<double> rhs = b;

    int n = size();

    for (int i = 0; i < n - 1; i++)
    {
        int pivot = i;

        for (int j = i + 1; j < n; j++)
        {
            if (fabs(mat[j][i]) > fabs(mat[pivot][i]))
                pivot = j;
        }

        if (fabs(mat[pivot][i]) < 1e-12)
            throw runtime_error("Zero pivot encountered in Gaussian elimination with pivoting");

        if (pivot != i)
        {
            swap(mat[i], mat[pivot]);
            swap(rhs[i], rhs[pivot]);
        }

        for (int j = i + 1; j < n; j++)
        {
            double factor = mat[j][i] / mat[i][i];

            for (int k = i; k < n; k++)
                mat[j][k] -= factor * mat[i][k];

            rhs[j] -= factor * rhs[i];
        }
    }

    if (fabs(mat[n - 1][n - 1]) < 1e-12)
        throw runtime_error("Zero pivot encountered during back substitution");

    vector<double> x(n);

    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = rhs[i];

        for (int j = i + 1; j < n; j++)
            x[i] -= mat[i][j] * x[j];

        if (fabs(mat[i][i]) < 1e-12)
            throw runtime_error("Division by zero during back substitution");

        x[i] /= mat[i][i];
    }

    return x;
}