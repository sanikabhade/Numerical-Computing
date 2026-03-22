#include "linear_solver.hpp"

void displaySolution(const vector<double> &x, const string &methodName, ostream &out)
{
    out << "\nSolution using " << methodName << ":\n";
    for (int i = 0; i < (int)x.size(); i++)
    {
        out << "x" << i + 1 << " = " << fixed << setprecision(6) << x[i] << "\n";
    }
}

vector<vector<double>> transposeRawMatrix(const vector<vector<double>> &L)
{
    int n = L.size();
    vector<vector<double>> T(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            T[j][i] = L[i][j];

    return T;
}

int main()
{
    string leftFile = "MatrixA49l.txt";
    string rightFile = "Matrixb49r.txt";
    string outputFile = "output.txt";

    try
    {
        LUDecomposition lu;
        lu.readLeftMatrixFromFile(leftFile);
        lu.readRightVectorFromFile(rightFile);

        ofstream fout(outputFile);

        if (!fout)
            throw runtime_error("Cannot create output file.");

        fout << "READING FILES SUCCESSFUL\n";

        lu.displaySystem(fout);

        fout << "\n----- MATRIX PROPERTIES -----\n";
        fout << "Is Square? " << (lu.isSquare() ? "Yes" : "No") << endl;
        fout << "Is Symmetric? " << (lu.isSymmetric() ? "Yes" : "No") << endl;
        fout << "Is Identity? " << (lu.isIdentity() ? "Yes" : "No") << endl;
        fout << "Is Null? " << (lu.isNull() ? "Yes" : "No") << endl;
        fout << "Is Diagonal? " << (lu.isDiagonal() ? "Yes" : "No") << endl;
        fout << "Is Diagonally Dominant? " << (lu.isDiagonallyDominant() ? "Yes" : "No") << endl;

        Matrix T = lu.transpose();

        fout << "\n----- TRANSPOSE OF MATRIX -----\n";
        T.displayMatrixOnly(fout);

        if (lu.isSquare())
        {
            try
            {
                double det = lu.determinant();

                fout << "\nDeterminant = " << det << endl;

                if (fabs(det) > 1e-12)
                {
                    Matrix inv = lu.inverse();

                    fout << "\n----- INVERSE OF MATRIX -----\n";
                    inv.displayMatrixOnly(fout);
                }
                else
                {
                    fout << "\nInverse does not exist because determinant is zero\n";
                }
            }
            catch (const exception &e)
            {
                fout << "\nDeterminant / Inverse skipped: " << e.what() << endl;
            }
        }

        vector<vector<double>> L, U;

        lu.doolittle(L, U);

        lu.displayMatrix(L, "Doolittle L Matrix", fout);
        lu.displayMatrix(U, "Doolittle U Matrix", fout);

        vector<double> ansDoolittle = lu.solveUsingLU(L, U);

        displaySolution(ansDoolittle, "Doolittle Method", fout);

        lu.crout(L, U);

        lu.displayMatrix(L, "Crout L Matrix", fout);
        lu.displayMatrix(U, "Crout U Matrix", fout);

        vector<double> ansCrout = lu.solveUsingLU(L, U);

        displaySolution(ansCrout, "Crout Method", fout);

        try
        {
            vector<vector<double>> LC;

            lu.cholesky(LC);

            vector<vector<double>> UC = transposeRawMatrix(LC);

            lu.displayMatrix(LC, "Cholesky L Matrix", fout);
            lu.displayMatrix(UC, "Cholesky U = L^T Matrix", fout);

            vector<double> ansCholesky = lu.solveUsingLU(LC, UC);

            displaySolution(ansCholesky, "Cholesky Method", fout);
        }
        catch (const exception &e)
        {
            fout << "\nCholesky method skipped: " << e.what() << endl;
        }

        fout.close();
    }
    catch (const exception &e)
    {
        ofstream fout("output.txt");
        fout << "ERROR: " << e.what() << endl;
        fout.close();
        return 1;
    }

    return 0;
}





// g++ main.cpp src/matrix_basic.cpp src/matrix_advanced.cpp src/linear_solver.cpp -Iinclude -o matrixapp
// ./matrixapp
