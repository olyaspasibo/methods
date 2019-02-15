#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double yx(double x)
{ 
	return 8.0 * x * x * (x - 1.0); 
}

double p(double x) 
{ 
	return (-1.0) * x * x; 
}

double q(double x) 
{ 
	return (-1.0) * x; 
}

double Y(double x) 
{
	return 48.0 * q(x) + 16.0 + p(x) * (24.0 * x * x + 16.0 * q(x)) + q(x) * yx(x);
}

int main() 
{
	double a = 0, b = 1;
	int n = 10;
	double h = (b - a) / n;
	double y0 = 0;
	double y1 = 0;
	vector<double> F(n + 1);
	vector<double> A(n);
	vector<double> B(n);
	vector<double> C(n);
	F[0] = y0;
	F[n] = y1;
	for (int i = 1; i < n; i++) 
	{
		double xi = a + h * i;
		A[i] = (1.0 / 2.0) * (1.0 + h / 2.0 * p(xi));
		B[i] = (1.0 / 2.0) * (1.0 - h / 2.0 * p(xi));
		C[i] = 1.0 + h * h / 2.0 * q(xi);
		F[i] = h * h / 2.0 * Y(xi);
	}
	vector<double> alpha(n);
	vector<double> beta(n);
	vector<double> y(n + 1);
	alpha[0] = 0;
	beta[0] = F[0];
	for (int i = 0; i < n - 1; i++) 
	{
		double currA = A[i + 1];
		double currB = B[i + 1];
		double currC = C[i + 1];
		alpha[i + 1] = currB / (currC - currA * alpha[i]);
		beta[i + 1] = (F[i + 1] + currA * beta[i]) / (currC - currA * alpha[i]);
	}
	y[n] = y1;
	for (int i = n - 1; i >= 0; i--)
		y[i] = alpha[i] * y[i + 1] + beta[i];
	cout << fixed << setprecision(2);
	for (int i = 0; i < n + 1; i++) 
	{
		double x = a + i * h;
		cout << "x: " << x << ", \ty: " << y[i] << ", \ty^(0): " << yx(x) << endl;
	}
}
