#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const int n = 4;

void readMatrix(vector<vector<double>> &A)
{
    ifstream fin("A_tilda.txt");

    if(!fin)
    {
        cout<<"Error opening A_tilda.txt"<<endl;
        exit(1);
    }

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            fin>>A[i][j];
}

void readVector(vector<double> &b)
{
    ifstream fin("input1.txt");

    if(!fin)
    {
        cout<<"Error opening input1.txt"<<endl;
        exit(1);
    }

    for(int i=0;i<n;i++)
        fin>>b[i];
}

vector<double> gaussian(vector<vector<double>> A, vector<double> b)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            double factor=A[j][i]/A[i][i];

            for(int k=i;k<n;k++)
                A[j][k]-=factor*A[i][k];

            b[j]-=factor*b[i];
        }
    }

    vector<double> x(n);

    for(int i=n-1;i>=0;i--)
    {
        x[i]=b[i];

        for(int j=i+1;j<n;j++)
            x[i]-=A[i][j]*x[j];

        x[i]/=A[i][i];
    }

    return x;
}

int main()
{
    vector<vector<double>> A(n,vector<double>(n));
    vector<double> b(n);

    readMatrix(A);
    readVector(b);

    vector<double> x=gaussian(A,b);

    cout<<"Solution of A~x = b"<<endl<<endl;

    for(int i=0;i<n;i++)
        cout<<"x"<<i+1<<" = "<<x[i]<<endl;
}