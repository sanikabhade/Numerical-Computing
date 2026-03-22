#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "gaussian.hpp"

using namespace std;

void printSolution(ostream &out, const vector<double> &x)
{
    out << "\nSolution:\n";
    for (int i = 0; i < (int)x.size(); i++)
    {
        out << "x" << i + 1 << " = "
            << fixed << setprecision(10) << x[i] << endl;
    }
}

int main()
{
    string leftFile = "MatrixA49l.txt";
    string rightFile = "Matrixb49r.txt";
    string outputFile = "output_gaussian.txt";

    ofstream fout(outputFile);

    if (!fout)
    {
        cout << "Error: Cannot create output file: " << outputFile << endl;
        return 1;
    }

    try
    {
        GaussianNoPivot g1;
        g1.readLeftMatrix(leftFile);
        g1.readRightVector(rightFile);

        fout << "\nGaussian Elimination WITHOUT Pivoting\n";
        g1.displaySystem(fout);

        vector<double> x1 = g1.solve();
        printSolution(fout, x1);

        GaussianPivot g2;
        g2.readLeftMatrix(leftFile);
        g2.readRightVector(rightFile);

        fout << "\nGaussian Elimination WITH Pivoting\n";
        g2.displaySystem(fout);

        vector<double> x2 = g2.solve();
        printSolution(fout, x2);

        fout << "\nProgram executed successfully.\n";
        fout.close();

        cout << "Program executed successfully." << endl;
        cout << "Output saved in " << outputFile << endl;
    }
    catch (const exception &e)
    {
        fout << "\nError: " << e.what() << endl;
        fout.close();

        cout << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}