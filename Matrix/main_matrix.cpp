#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

const int N = 4;

void readMatrix(const string& filename, vector<vector<double>>& A) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("Cannot open matrix file: " + filename);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(fin >> A[i][j])) {
                throw runtime_error("Invalid matrix data in file: " + filename);
            }
        }
    }
}

void readVector(const string& filename, vector<double>& b) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("Cannot open vector file: " + filename);
    }

    for (int i = 0; i < N; i++) {
        if (!(fin >> b[i])) {
            throw runtime_error("Invalid vector data in file: " + filename);
        }
    }
}

double determinant(vector<vector<double>> A) {
    double det = 1.0;
    int sign = 1;

    for (int i = 0; i < N; i++) {
        int pivotRow = i;
        for (int k = i + 1; k < N; k++) {
            if (fabs(A[k][i]) > fabs(A[pivotRow][i])) {
                pivotRow = k;
            }
        }

        if (fabs(A[pivotRow][i]) < 1e-12) {
            return 0.0;
        }

        if (pivotRow != i) {
            swap(A[i], A[pivotRow]);
            sign *= -1;
        }

        for (int k = i + 1; k < N; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < N; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        det *= A[i][i];
    }

    return det * sign;
}

vector<vector<double>> inverseMatrix(vector<vector<double>> A) {
    vector<vector<double>> inv(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; i++) {
        inv[i][i] = 1.0;
    }

    for (int i = 0; i < N; i++) {
        int pivotRow = i;
        for (int k = i + 1; k < N; k++) {
            if (fabs(A[k][i]) > fabs(A[pivotRow][i])) {
                pivotRow = k;
            }
        }

        if (fabs(A[pivotRow][i]) < 1e-12) {
            throw runtime_error("Matrix is singular, inverse does not exist.");
        }

        if (pivotRow != i) {
            swap(A[i], A[pivotRow]);
            swap(inv[i], inv[pivotRow]);
        }

        double pivot = A[i][i];
        for (int j = 0; j < N; j++) {
            A[i][j] /= pivot;
            inv[i][j] /= pivot;
        }

        for (int k = 0; k < N; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < N; j++) {
                    A[k][j] -= factor * A[i][j];
                    inv[k][j] -= factor * inv[i][j];
                }
            }
        }
    }

    return inv;
}

vector<double> multiplyMatrixVector(const vector<vector<double>>& A, const vector<double>& b) {
    vector<double> x(N, 0.0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x[i] += A[i][j] * b[j];
        }
    }

    return x;
}

int main() {
    vector<vector<double>> A(N, vector<double>(N));
    vector<double> b(N);

    try {
        readMatrix("input.txt", A);
        readVector("input1.txt", b);

        double detA = determinant(A);
        vector<vector<double>> invA = inverseMatrix(A);
        vector<double> x = multiplyMatrixVector(invA, b);

        ofstream fout("output.txt");
        if (!fout) {
            throw runtime_error("Cannot create output.txt");
        }

        fout << fixed << setprecision(6);

        fout << "Matrix A:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fout << setw(10) << A[i][j] << " ";
            }
            fout << "\n";
        }

        fout << "\nVector b:\n";
        for (int i = 0; i < N; i++) {
            fout << setw(10) << b[i] << "\n";
        }

        fout << "\nDeterminant of A = " << detA << "\n";

        fout << "\nInverse of A:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fout << setw(10) << invA[i][j] << " ";
            }
            fout << "\n";
        }

        fout << "\nSolution of Ax = b:\n";
        for (int i = 0; i < N; i++) {
            fout << "x" << i + 1 << " = " << x[i] << "\n";
        }

        fout.close();

        cout << "Program executed successfully.\n";
        cout << "Check output.txt\n";
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}