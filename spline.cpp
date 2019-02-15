#include <iostream> 
#include <cmath> 
#include <vector> 

using namespace std; 

vector<double> gauss(vector<vector<double> > A, vector<double> B, int N)
{
	//int N = (int)B.size();
	double e = 0.0001;
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


void interpolation_spline(vector <double> x, vector <double> f)
{
	int n = x.size();
	cout<< n << endl;
	for (int i = 0; i < n; i++)
	cout << x[i] << ' ';
	cout << endl;
	vector <double> x_ans(2 * n - 1), f_ans(2 * n -1);
	int m = n - 1;
	vector<vector <double> > A(4 * m, vector<double> (4 * m));
	vector <double> B(4 * m);
	for (int i = 0; i < m; i++){
		A[i][4 * i] = 1;
		B[i] = f[i];
		}
	for (int i = 0; i < m; i++){
		double h = x[i + 1] - x[i];
		A[m + i][4 * i] = 1;
		A[m + i][4 * i + 1] = h;
		A[m + i][4 * i + 2] = -h * h;
		A[m + i][4 * i + 3] = h * h * h;
		B[m + i] = f[i + 1];
	}	
	for (int i = 0; i < m - 1; i++){
		double h = x[i + 1] - x[i];
		A[2 * m + i][4 * i + 1] = 1;
		A[2 * m + i][4 * i + 2] = 2 * h;
		A[2 * m + i][4 * i + 3] = -3 * h * h;
		A[2 * m + i][4 * (i + 1) + 1] = -1;
		
	}
	for (int i = 0; i < m - 1; i++){
		double h = x[i + 1] - x[i];
		A[3 * m + i][4 * i + 2] = 2;
		A[3 * m + i][4 * i + 3] = 6 * h;
		A[3 * m + i][4 * (i + 1) + 2] = -2;
		
	}
	A[4 * m - 2][2] = 2;
	A[4 * m - 1][4 * (m - 1) + 2] = 2;
	A[4 * m - 1][4 * (m - 1) + 3] = 6 * (x[m] - x[m - 1]);

	vector <double> koef = gauss(A, B, n);
	
	for (int i = 0; i < 2 * n - 1; i++){
		
		if (i % 2 == 0) {
			x_ans[i] = x[i/2];
			f_ans[i] = f[i/2];
			}
			else {
				x_ans[i] = (x[i/2] + x[i/2 + 1]) / 2;
				double h = x_ans[i] - x[i/2];
				f_ans[i] = koef[i/2 * 4] + koef[i/2 * 4 + 1] * h + 
				koef[i/2 * 4 + 2] * h * h + koef[i/2 * 4 + 3] * h * h * h;
				
				}
		}
		
	for (int i = 0; i < 2 * n - 1; i++){
			cout << x_ans[i] << ' ';
			if (f_ans[i] < 0)
		     cout << " ";
			
			}
	 cout << " ";
	 for (int i = 0; i < 2 * n - 1; i++)
	 cout << f_ans[i] << ' ';
	 cout << " ";
	}
	
	int main(){
		int n;
		n = 5;
		vector <double> x;
		vector <double> f;
		x.push_back(0);
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		x.push_back(4);
		f.push_back(1);
		f.push_back(2);
		f.push_back(17);
		f.push_back(82);
		f.push_back(257);
		interpolation_spline(x, f);
		
		return 0;
		}
	
	
	
	
	
	
	
	
	
	
	
	
