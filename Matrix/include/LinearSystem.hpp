#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class LinearSystemSolver {
private:
    vector<vector<double>> A;
    vector<double> b;
    int n;

public:
    LinearSystemSolver(const vector<vector<double>>& matrix,
                       const vector<double>& rhs);

    vector<double> solveGaussianElimination();

    static void writeSolution(ofstream& fout,
                              const string& title,
                              const vector<double>& x);
};

#endif