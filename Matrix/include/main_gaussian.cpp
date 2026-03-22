#include "gaussian.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void printSolution(const vector<double> &x)
{
    cout << "\nSolution:\n";

    for (int i = 0; i < x.size(); i++)
        cout << "x" << i + 1 << " = " << fixed << setprecision(10) << x[i] << endl;
}

int main()
{
    string leftFile = "MatrixA.txt";
    string rightFile = "Matrixb.txt";

    try
    {
        GaussianNoPivot g1;

        g1.readLeftMatrix(leftFile);
        g1.readRightVector(rightFile);

        cout << "\nGaussian Elimination WITHOUT Pivoting\n";
        g1.displaySystem();

        vector<double> x1 = g1.solve();
        printSolution(x1);

        GaussianPivot g2;

        g2.readLeftMatrix(leftFile);
        g2.readRightVector(rightFile);

        cout << "\nGaussian Elimination WITH Pivoting\n";
        g2.displaySystem();

        vector<double> x2 = g2.solve();
        printSolution(x2);
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
