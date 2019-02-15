#include <iostream>
#include <cmath>

using namespace std;

void solveMatrix (int n, double *a, double *c, double *b, double *f, double *x)
{
	double m;
	for (int i = 1; i < n; i++)
	{
		m = a[i]/c[i-1];
		c[i] = c[i] - m*b[i-1];
		f[i] = f[i] - m*f[i-1];
	}

	x[n-1] = f[n-1]/c[n-1];

	for (int i = n - 2; i >= 0; i--)
		x[i]=(f[i]-b[i]*x[i+1])/c[i];

}
int main() 
{
  int n;
  cout << "Введите количество уравнений: ";
  cin >> n;
  double *a = new double[n - 1 ];// диагональ, лежащая под главной (нумеруется: [1;n-1])
  double *b = new double[n - 1]; //диагональ, лежащая над главной (нумеруется: [0;n-2])
  double *c = new double[n - 1]; // главная диагональ
  double *f = new double[n];
  cout << "Введите главную диагональ: " << endl;
  for (int i = 0; i < n; i++) 
  {
    cout << "с[" << i << "]= ";
    cin >> c[i];
  }
  cout << "Введите диагональ над главной : " << endl;
  for (int i = 0; i < n - 1; i++) 
  {
    cout << "b[" << i << "]= ";
    cin >> b[i];
  }
  cout << "Введите диагональ под главной : " << endl;
  for (int i = 1; i < n; i++) 
  {
    cout << "a[" << i << "]= ";
    cin >> a[i];
  }
  cout << "Введите столбец значений : " << endl;
  for (int i = 0; i < n; i++) 
  {
    cout << "f[" << i << "]= ";
    cin >> f[i];
  }
  double *x = new double[n]; //значения Х
  solveMatrix (n, &*a, &*c, &*b, &*f, &*x);
  cout<< "Полученные корни уравнения: "<< endl;
  for (int i = 0; i < n; i++) 
  {
    cout << "x[" << i << "]= ";
    cout << x[i] << ' ';
  }
  return 0;
}
