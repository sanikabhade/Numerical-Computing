#include "augment.hpp"
#include <fstream>
#include <iomanip>
#include <stdexcept>

vector<vector<double>> AugmentMatrix::readLeftMatrix(const string &filename, int &rows, int &cols)
{
    ifstream fin(filename);
    if (!fin)
    {
        throw runtime_error("Cannot open file: " + filename);
    }

    fin >> rows >> cols;

    if (!fin || rows <= 0 || cols <= 0)
    {
        throw runtime_error("Invalid matrix size in file: " + filename);
    }

    vector<vector<double>> A(rows, vector<double>(cols));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fin >> A[i][j];
            if (!fin)
            {
                throw runtime_error("Invalid matrix data in file: " + filename);
            }
        }
    }

    return A;
}

vector<double> AugmentMatrix::readRightVector(const string &filename, int &rows, int &cols)
{
    ifstream fin(filename);
    if (!fin)
    {
        throw runtime_error("Cannot open file: " + filename);
    }

    fin >> rows >> cols;

    if (!fin || rows <= 0 || cols != 1)
    {
        throw runtime_error("Right matrix must be of size n x 1 in file: " + filename);
    }

    vector<double> b(rows);

    for (int i = 0; i < rows; i++)
    {
        fin >> b[i];
        if (!fin)
        {
            throw runtime_error("Invalid vector data in file: " + filename);
        }
    }

    return b;
}

void AugmentMatrix::writeAugmentedMatrix(const string &filename,
                                         const vector<vector<double>> &A,
                                         const vector<double> &b)
{
    ofstream fout(filename);
    if (!fout)
    {
        throw runtime_error("Cannot create output file: " + filename);
    }

    int rows = A.size();
    int cols = A[0].size();

    fout << rows << " " << cols + 1 << "\n";
    fout << scientific << setprecision(7);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fout << setw(15) << A[i][j] << " ";
        }
        fout << setw(15) << b[i] << "\n";
    }
}