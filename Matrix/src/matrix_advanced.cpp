#include "linear_solver.hpp"

Matrix Matrix::transpose() const
{
    Matrix T(cols, rows);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            T.A[j][i] = A[i][j];
        }
    }

    return T;
}

double Matrix::determinant() const
{
    if (!isSquare())
        throw runtime_error("Determinant is defined only for square matrices.");

    int n = rows;

    if (n == 1)
        return A[0][0];

    if (n == 2)
        return A[0][0] * A[1][1] - A[0][1] * A[1][0];

    double det = 0.0;

    for (int p = 0; p < n; p++)
    {
        Matrix sub(n - 1, n - 1);

        for (int i = 1; i < n; i++)
        {
            int subCol = 0;
            for (int j = 0; j < n; j++)
            {
                if (j == p)
                    continue;
                sub.A[i - 1][subCol] = A[i][j];
                subCol++;
            }
        }

        det += (p % 2 == 0 ? 1 : -1) * A[0][p] * sub.determinant();
    }

    return det;
}

Matrix Matrix::inverse() const
{
    if (!isSquare())
        throw runtime_error("Inverse exists only for square matrices.");

    int n = rows;
    Matrix temp(*this);
    Matrix inv(n, n);

    for (int i = 0; i < n; i++)
        inv.A[i][i] = 1.0;

    for (int i = 0; i < n; i++)
    {
        double pivot = temp.A[i][i];

        if (fabs(pivot) < 1e-12)
        {
            int swapRow = -1;
            for (int r = i + 1; r < n; r++)
            {
                if (fabs(temp.A[r][i]) > 1e-12)
                {
                    swapRow = r;
                    break;
                }
            }

            if (swapRow == -1)
                throw runtime_error("Matrix is singular. Inverse does not exist.");

            swap(temp.A[i], temp.A[swapRow]);
            swap(inv.A[i], inv.A[swapRow]);
            pivot = temp.A[i][i];
        }

        for (int j = 0; j < n; j++)
        {
            temp.A[i][j] /= pivot;
            inv.A[i][j] /= pivot;
        }

        for (int r = 0; r < n; r++)
        {
            if (r != i)
            {
                double factor = temp.A[r][i];
                for (int c = 0; c < n; c++)
                {
                    temp.A[r][c] -= factor * temp.A[i][c];
                    inv.A[r][c] -= factor * inv.A[i][c];
                }
            }
        }
    }

    return inv;
}
