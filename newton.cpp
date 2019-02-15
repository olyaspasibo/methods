#include <iostream>

using namespace std;

double* coeffs (double *x, double *y, int n)
{

	double *k=new double[n];
	k[0]=y[0];
	for (int j=1; j<n; j++)
		for (int i=0; i<n-j; i++)
		{
			y[i]=(y[i+1]-y[i])/(x[i+j]-x[i]);
			k[j]=y[0];
		}
	return k;
}

double calc (double *k, double argx, double *x)
{
	/**
	 * argx, как вы догадались - это та точка, в которой мы хотим
	 * посчитать значение "загаданной функции" (я понимаю, что это тупо
	 * звучит, но так проще всего объяснить, в чём состоит смысл
	 * интерполяции. Читайте комментарий в файле lagrange.h, скачать - 
	 * http://photoroofers.ru/personal_stuff/lagrange.zip).
	 * А double *k - так мы передаём этот самый массив коэффициентов,
	 * полученный чуть выше, в методе coeffs().
	 **/
	double S=k[0], p=1;
	for (int i=1; i<n; i++)
	{
		p=p*(argx-x[i-1]);
		S+=k[i]*p;
	}
	return S;
}
int main () {
	int n;
	cout << "Input a number of dots"<< endl;
	cin >> n;
	double *x = new double[n];
	double *y = new double[n];
	

	//for (int i=0; i<n; i++)
	for (int i = 0; i< n; i++)
	{
		cout << "X[" << i+1 << "]=";
		cin >> x[i];
		cout << "Y[" << i+1 << "]=";
		cin >> y[i];
	}
	double *k=new double[n];
	k = coeffs(x,y,n);
	int s;
	cin >> s;
	double res = calc(k,s,x);
	
	/*for (int i=0; i<n; i++)
	{
	cout << "X[" << i+1 << "]=";
		cout << x[i];
		cout << "Y[" << i+1 << "]=";
		cout << y[i];
	}*/
	cout << s << ' ' <<res;
	return 0;
	}
