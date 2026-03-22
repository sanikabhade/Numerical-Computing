#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int n = 4;

void readMatrix(vector<vector<double>>& A) {
    ifstream fin("Atilda.txt");
    if (!fin) {
        cout << "Error opening Atilda.txt" << endl;
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> A[i][j];
        }
    }
}

void readVector(vector<double>& b) {
    ifstream fin("btilda.txt");
    if (!fin) {
        cout << "Error opening btilda.txt" << endl;
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fin >> b[i];
    }
}

vector<double> solveSystem(vector<vector<double>> A, vector<double> b) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];

            for (int k = i; k < n; k++) {
                A[j][k] = A[j][k] - factor * A[i][k];
            }

            b[j] = b[j] - factor * b[i];
        }
    }

    vector<double> x(n);

    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];

        for (int j = i + 1; j < n; j++) {
            x[i] = x[i] - A[i][j] * x[j];
        }

        x[i] = x[i] / A[i][i];
    }

    return x;
}

int main() {
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);

    readMatrix(A);
    readVector(b);

    vector<double> x = solveSystem(A, b);

    ofstream fout("output4.txt");
    if (!fout) {
        cout << "Error creating output4.txt" << endl;
        return 1;
    }

    fout << fixed << setprecision(6);
    fout << "Solution of A~ x = b~" << endl << endl;

    for (int i = 0; i < n; i++) {
        fout << "x" << i + 1 << " = " << x[i] << endl;
    }

    fout.close();

    cout << "Program executed successfully." << endl;
    cout << "Output saved in output4.txt" << endl;

    return 0;
}