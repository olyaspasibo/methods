#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

const double V = 8.0;
const double a = 0.0;
double b = 1.0;
const double lambda = 1.0;
const int n = 11;
const double h = (b - a) / (n - 1);

const double e = 0.0001;

vector<double> Gauss(vector<vector<double> > A, vector<double> B)
{
	int N = (int)B.size();
	vector<vector<double> > T(N, vector<double> (N, 0.0));
	for (int k = 0; k < N - 1; k++) 
	{
		int m = 0;
		double Amax = 0.0;
		for (int i = k; i < N; i++) 
		{
			double Aabs = abs(A[i][k]);
			if (Aabs > Amax) 
			{
				m = i;
				Amax = Aabs;
			}
		}
		if (Amax + e > 0.0 && Amax - e < 0.0) 
			return B;
		swap(B[k], B[m]);
		for (int j = k; j < N; j++)
			swap(A[k][j], A[m][j]);
		for (int i = k + 1; i < N; i++) 
		{
			T[i][k] = A[i][k] / A[k][k];
			B[i] -= T[i][k] * B[k];
			for (int j = k + 1; j < N; j++) 
				A[i][j] -= T[i][k] * A[k][j];
		}
	}
	vector<double> X(N, 0.0);
	X[N - 1] = B[N - 1] / A[N - 1][N - 1];
	for (int k = N - 2; k >= 0; k--) 
	{
		double sum = 0.0;
		for (int j = k + 1; j < N; j++) 
			sum += A[k][j] * X[j];
		X[k] = (1 / A[k][k]) * (B[k] - sum);
	}
	return X;
}

double y(double x) 
{
	return pow(x, 3) + V * x;
}

double A(double x, double t) 
{
	return pow(x, 2) * pow(t, 2) + pow(x, 3) * pow(t, 3) + pow(x, 4) * pow(t, 4);
}

double f(double x) 
{
	return V * x + pow(x, 2) * (1.0 / 6.0 + V / 4.0) + pow(x, 3) * (8.f / 7.f + V / 5.f) + pow(x, 4) * (1.f / 8.f + V / 6.f);
}

vector<double> Quadra() 
{
	vector<vector<double> > C(n, vector<double>(n));
	vector<double> V(n);
	vector<double> res(n);
	for (int i = 0; i < n; i++) 
	{
		double currX = a + h * i; //a = 0.0, h - расстояние между соседними x_i
		V[i] = f(currX); //массив значений СЛАУ
		for (int j = 0; j < n; j++) 
		{
			double currT = a + h * j; //a = 0.0 по условию, h - расстояние между соседними y_j
			C[i][j] = lambda * h * A(currX, currT);
		}
		
		C[i][i]++;
	}
	return Gauss(C, V);
}

int main() 
{
	vector<double> root = Quadra();
	for (int i = 0; i < n; i++) 
	{
		double currX = a + h * i;
		if (currX == 0 || currX == 1)
			cout << "x: " << currX << ", \t\tres: " << root[i] << ", \t\ty_tochn: " << y(currX)<< endl;
		else
			cout << "x: " << currX << ", \tres: " << root[i] << ", \t\ty_tochn: " << y(currX)<< endl;
	}
	
}
