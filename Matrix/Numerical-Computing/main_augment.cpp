#include <iostream>
#include <stdexcept>
#include "augment.hpp"

using namespace std;

int main()
{
    string leftFile = "MatrixA49l.txt";
    string rightFile = "Matrixb49r.txt";
    string outputFile = "output49.txt";

    try
    {
        AugmentMatrix obj;

        int leftRows, leftCols;
        int rightRows, rightCols;

        vector<vector<double>> A = obj.readLeftMatrix(leftFile, leftRows, leftCols);
        vector<double> b = obj.readRightVector(rightFile, rightRows, rightCols);

        if (leftRows != rightRows)
        {
            throw runtime_error("Row mismatch between left matrix and right vector.");
        }

        obj.writeAugmentedMatrix(outputFile, A, b);

        cout << "Augmented matrix created successfully." << endl;
        cout << "Output saved in file: " << outputFile << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}






// g++ main_augment.cpp src/augment.cpp -Iinclude -o augment
// ./augment
