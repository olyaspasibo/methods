#include <iostream>
#include <cmath>

using namespace std;

void sysout(double **a, double *y, int n)
{
  for (int i = 0; i < n; i++) 
  {
    for (int j = 0; j < n; j++) 
    {
      cout << a[i][j] << "*x" << j;
      if (j < n - 1)
        cout << " + ";
    }
    cout << " = " << y[i] << endl;
  }
  return;
}
double* xv(double a,double b,double step,int np)
{
  double *x,t;
  x=new double [np];
  t=a;
  for(int i=0;i<np;i++)
  {
    x[i]=t;
    t+=step;
  }
  return x;
}
 
double *yv(double *x,int np,double (*f)(double))
{
  double *y;
  y=new double [np];
  for(int i=0;i<np;i++)
  {
    y[i]=f(x[i]);
  }
  return y;
}
 
double* gaus(int n,double **a,double *b) //методом гауса
{
  double *x,t,s;
  x = new double [n];
  int i,j,k;
  for(k = 0; k < n - 1; k++)
  {
    for(i = k + 1; i < n; i++)
    {
      t = a[i][k] / a[k][k];
      b[i] = b[i] - t * b[k];
      for(j = 0; j < n; j++)
        a[i][j] = a[i][j] - t*a[k][j];
    }
  }
  for(k= n - 1; k >= 0; k--)
  {
    s = 0;
    for (j = k + 1; j < n; j++)
    s += a[k][j] * x[j];
    x[k] = (b[k] - s) / a[k][k];
  }
  return x;
}
 
double proiz(int i,int m,double *x,double *y)
{
  double res;
  if(i==0)
    res=(y[1]-y[0])/(x[1]-x[0]);
  else if(i==m-1)
    res=(y[m-1]-y[m-2])/(x[m-1]-x[m-2]);
  else
    res=(y[i+1]-y[i-1])/(x[i+1]-x[i-1]);
  return res;
}
 
double *mit(int m,double *x,double *y)
{
  int i,j;
  double *mi,**a,*b,h;
  a=new double *[m];
  for(i=0;i<m;i++) a[i]=new double [m];
  b=new double [m];
  for(i=0;i<m;i++)
  {
    for(j=0;j<m;j++)
      a[i][j]=0;
    if(i==0 || i==m-1) a[i][i]=1;
    else
    {
      a[i][i-1]=1;
      a[i][i]=4;
      a[i][i+1]=1;
      h=x[i]-x[i-1];
      if(i != 0 && i != m-1)
      b[i]=3*(y[i+1]-y[i-1])/h; //система из n+1 линейных уравнений относительно неизвестных m(i)
    }
    if(i==0) b[i]=proiz(0,m,x,y);
    else if(i==m-1) b[i]=proiz(m-1,m,x,y);
  }
  mi=gaus(m,a,b);
  if(a)
  {
    for(i=0;i<m;i++) delete []a[i];
    delete []a;
  }
  if(b) delete []b;
  return mi;
}
 
 
double spline_it(double xp,int m,double *x,double *y,double *mi)
{
  int i;
  double sp, drob1,drob2,drob3,drob4,xstep;
 
  for(i=1;i<m;i++)
  {
    if(x[i-1]<=xp && xp<=x[i])
    {
      xstep=x[i]-x[i-1];// Интерполяционный кубический сплайн
      drob1=(xp-x[i])*(xp-x[i])*(2*(xp-x[i-1])+xstep)/pow(xstep,3);
      drob2=(xp-x[i-1])*(xp-x[i-1])*(2*(x[i]-xp)+xstep)/pow(xstep,3);
      drob3=(xp-x[i])*(xp-x[i])*(xp-x[i-1])/pow(xstep,2);
      drob4=(xp-x[i-1])*(xp-x[i-1])*(xp-x[i])/pow(xstep,2);
      sp=y[i-1]*drob1+y[i]*drob2+mi[i-1]*drob3+mi[i]*drob4;
    }
  }
  return sp;
}
 
double spline(double xp,int m,double *x,double *y)
{
  double *mi,sp;
  mi = mit(m,x,y);
  sp = spline_it(xp,m,x,y,mi);
  if(mi) delete []mi;
  return sp;
}

int main() 
{
  double **a, *y, *x;
  int n;
  cout << "Введите количество уравнений: ";
  cin >> n;
  a = new double*[n];
  y = new double[n];
  for (int i = 0; i < n; i++) 
  {
    a[i] = new double[n];
    for (int j = 0; j < n; j++) 
    {
      cout << "a[" << i << "][" << j << "]= ";
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < n; i++) 
  {
    cout << "y[" << i << "]= ";
    cin >> y[i];
  }
  sysout(a, y, n);
  x = gaus(n, a, y);
  for (int i = 0; i < n; i++) 
    cout << "x[" << i << "]=" << x[i] << endl;
  cin.get(); 
  return 0;
}
 //x 1	 + 2x 2	 + 3x 3	  =   3
 //3x 1	 + 5x 2	 + 7x 3	  =   0
 //x 1	 + 3x 2	 + 4x 3	  =   1
// ответ -4 -13 11


