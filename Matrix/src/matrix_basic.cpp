#include "linear_solver.hpp"

Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
    A.assign(rows, vector<double>(cols, 0.0));
    b.assign(rows, 0.0);
}

Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;
    cols = other.cols;
    A = other.A;
    b = other.b;
}

void Matrix::readLeftMatrixFromFile(const string &filename)
{
    ifstream fin(filename);
    if (!fin)
        throw runtime_error("Cannot open file: " + filename);

    fin >> rows >> cols;

    if (rows <= 0 || cols <= 0)
        throw runtime_error("Invalid matrix size in file: " + filename);

    A.assign(rows, vector<double>(cols, 0.0));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!(fin >> A[i][j]))
                throw runtime_error("Invalid matrix data in file: " + filename);
        }
    }

    fin.close();
}

void Matrix::readRightVectorFromFile(const string &filename)
{
    ifstream fin(filename);
    if (!fin)
        throw runtime_error("Cannot open file: " + filename);

    int r, c;
    fin >> r >> c;

    if (rows == 0)
        throw runtime_error("Read left matrix first.");

    b.assign(rows, 0.0);

    if (r == rows && c == 1)
    {
        for (int i = 0; i < rows; i++)
        {
            if (!(fin >> b[i]))
                throw runtime_error("Invalid vector data in file: " + filename);
        }
    }
    else if (r == 1 && c == rows)
    {
        for (int i = 0; i < rows; i++)
        {
            if (!(fin >> b[i]))
                throw runtime_error("Invalid vector data in file: " + filename);
        }
    }
    else
    {
        throw runtime_error("Right vector size does not match left matrix.");
    }

    fin.close();
}

void Matrix::displaySystem(ostream &out) const
{
    out << fixed << setprecision(4);
    out << "\nSystem [A | b]\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            out << setw(12) << A[i][j] << " ";
        }
        if (!b.empty())
            out << " | " << setw(12) << b[i];
        out << endl;
    }
}

void Matrix::displayMatrixOnly(ostream &out) const
{
    out << fixed << setprecision(4);
    out << "\nMatrix A\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            out << setw(12) << A[i][j] << " ";
        }
        out << endl;
    }
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getCols() const
{
    return cols;
}

vector<vector<double>> Matrix::getA() const
{
    return A;
}

vector<double> Matrix::getB() const
{
    return b;
}

void Matrix::setSystem(const vector<vector<double>> &mat, const vector<double> &vec)
{
    rows = mat.size();
    cols = (rows > 0) ? mat[0].size() : 0;
    A = mat;
    b = vec;
}

bool Matrix::isSquare() const
{
    return rows == cols;
}

bool Matrix::isSymmetric() const
{
    if (!isSquare())
        return false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (fabs(A[i][j] - A[j][i]) > 1e-9)
                return false;
        }
    }
    return true;
}

bool Matrix::isIdentity() const
{
    if (!isSquare())
        return false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == j && fabs(A[i][j] - 1.0) > 1e-9)
                return false;
            if (i != j && fabs(A[i][j]) > 1e-9)
                return false;
        }
    }
    return true;
}

bool Matrix::isNull() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (fabs(A[i][j]) > 1e-9)
                return false;
        }
    }
    return true;
}

bool Matrix::isDiagonal() const
{
    if (!isSquare())
        return false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i != j && fabs(A[i][j]) > 1e-9)
                return false;
        }
    }
    return true;
}

bool Matrix::isDiagonallyDominant() const
{
    if (!isSquare())
        return false;

    for (int i = 0; i < rows; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < cols; j++)
        {
            if (i != j)
                sum += fabs(A[i][j]);
        }

        if (fabs(A[i][i]) < sum)
            return false;
    }

    return true;
}

bool Matrix::isTranspose(const Matrix &m) const
{
    if (rows != m.cols || cols != m.rows)
        return false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (fabs(A[i][j] - m.A[j][i]) > 1e-9)
                return false;
        }
    }

    return true;
}
