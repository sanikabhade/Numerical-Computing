#include "LinearSystem.hpp"
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

LinearSystemSolver::LinearSystemSolver(const vector<vector<double>>& matrix,
                                       const vector<double>& rhs) {
    A = matrix;
    b = rhs;
    n = A.size();

    if (A.empty() || A.size() != b.size()) {
        throw runtime_error("Invalid matrix or vector size.");
    }

    for (int i = 0; i < n; i++) {
        if ((int)A[i].size() != n) {
            throw runtime_error("Matrix must be square.");
        }
    }
}

vector<double> LinearSystemSolver::solveGaussianElimination() {
    vector<vector<double>> aug(n, vector<double>(n + 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug[i][j] = A[i][j];
        }
        aug[i][n] = b[i];
    }

    // Forward elimination with partial pivoting
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(aug[k][i]) > fabs(aug[maxRow][i])) {
                maxRow = k;
            }
        }

        swap(aug[i], aug[maxRow]);

        if (fabs(aug[i][i]) < 1e-12) {
            throw runtime_error("Matrix is singular or nearly singular.");
        }

        for (int k = i + 1; k < n; k++) {
            double factor = aug[k][i] / aug[i][i];
            for (int j = i; j <= n; j++) {
                aug[k][j] -= factor * aug[i][j];
            }
        }
    }

    // Back substitution
    vector<double> x(n);

    for (int i = n - 1; i >= 0; i--) {
        x[i] = aug[i][n];

        for (int j = i + 1; j < n; j++) {
            x[i] -= aug[i][j] * x[j];
        }

        x[i] /= aug[i][i];
    }

    return x;
}

void LinearSystemSolver::writeSolution(ofstream& fout,
                                       const string& title,
                                       const vector<double>& x) {
    fout << title << "\n";
    fout << "x = [";

    for (int i = 0; i < (int)x.size(); i++) {
        fout << fixed << setprecision(6) << x[i];
        if (i != (int)x.size() - 1) {
            fout << ", ";
        }
    }

    fout << "]^T\n\n";
}