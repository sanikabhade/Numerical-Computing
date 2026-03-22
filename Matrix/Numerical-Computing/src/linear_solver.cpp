#include "linear_solver.hpp"

LUDecomposition::LUDecomposition() : Matrix() {}

void LUDecomposition::doolittle(vector<vector<double>> &L, vector<vector<double>> &U) const
{
    if (!isSquare())
        throw runtime_error("Doolittle requires a square matrix.");

    int n = rows;
    L.assign(n, vector<double>(n, 0.0));
    U.assign(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++)
    {
        for (int k = i; k < n; k++)
        {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
                sum += L[i][j] * U[j][k];

            U[i][k] = A[i][k] - sum;
        }

        L[i][i] = 1.0;

        for (int k = i + 1; k < n; k++)
        {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
                sum += L[k][j] * U[j][i];

            if (fabs(U[i][i]) < 1e-12)
                throw runtime_error("Zero pivot found in Doolittle method.");

            L[k][i] = (A[k][i] - sum) / U[i][i];
        }
    }
}

void LUDecomposition::crout(vector<vector<double>> &L, vector<vector<double>> &U) const
{
    if (!isSquare())
        throw runtime_error("Crout requires a square matrix.");

    int n = rows;
    L.assign(n, vector<double>(n, 0.0));
    U.assign(n, vector<double>(n, 0.0));

    for (int j = 0; j < n; j++)
    {
        U[j][j] = 1.0;

        for (int i = j; i < n; i++)
        {
            double sum = 0.0;
            for (int k = 0; k < j; k++)
                sum += L[i][k] * U[k][j];

            L[i][j] = A[i][j] - sum;
        }

        for (int i = j + 1; i < n; i++)
        {
            double sum = 0.0;
            for (int k = 0; k < j; k++)
                sum += L[j][k] * U[k][i];

            if (fabs(L[j][j]) < 1e-12)
                throw runtime_error("Zero pivot found in Crout method.");

            U[j][i] = (A[j][i] - sum) / L[j][j];      //   here is A is use
        }
    }
}

void LUDecomposition::cholesky(vector<vector<double>> &L) const
{
    if (!isSquare())
        throw runtime_error("Cholesky requires a square matrix.");

    if (!isSymmetric())
        throw runtime_error("Matrix is not symmetric.");

    int n = rows;
    L.assign(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < j; k++)
                sum += L[i][k] * L[j][k];

            if (i == j)
            {
                double value = A[i][i] - sum;
                if (value <= 0)
                    throw runtime_error("Matrix is not positive definite for Cholesky.");

                L[i][j] = sqrt(value);
            }
            else
            {
                if (fabs(L[j][j]) < 1e-12)
                    throw runtime_error("Zero diagonal in Cholesky.");

                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
}

vector<double> LUDecomposition::solveUsingLU(const vector<vector<double>> &L,
                                             const vector<vector<double>> &U) const
{
    int n = rows;
    vector<double> y(n, 0.0), x(n, 0.0);

    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < i; j++)
            sum += L[i][j] * y[j];

        if (fabs(L[i][i]) < 1e-12)
            throw runtime_error("Zero diagonal in forward substitution.");

        y[i] = (b[i] - sum) / L[i][i];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++)
            sum += U[i][j] * x[j];

        if (fabs(U[i][i]) < 1e-12)
            throw runtime_error("Zero diagonal in backward substitution.");

        x[i] = (y[i] - sum) / U[i][i];
    }

    return x;
}

void LUDecomposition::displayMatrix(const vector<vector<double>> &M,
                                    const string &name,
                                    ostream &out) const
{
    out << "\n" << name << ":\n";
    out << fixed << setprecision(4);

    for (const auto &row : M)
    {
        for (double val : row)
        {
            out << setw(12) << val << " ";
        }
        out << endl;
    }
}

