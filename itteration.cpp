#define eps 0.0001 //требуемая точность вычислений
int N = 5;
void iteration(double a[N][N],double b[N],double x[N])
{
int i,j;
double norma; //чебышевская норма вектора
double xn[N]={0};//вектор для текущей итерации, начальное значение
//должно быть равно начальному приближению



do{
norma=0.0;
for(i=0;i < N;i++)
{
xn[i]=-b[i];

for(j=0;j < N;j++)
{
if(i!=j)
xn[i]+=a[i][j]*x[j];
}

xn[i]/=-a[i][i];
}

for(i=0;i < N;i++)
{
if(fabs(x[i]-xn[i]) > norma)
norma=fabs(x[i]-xn[i]); //Вычисление нормы вектора
x[i]=xn[i];
}

}
while(norma > eps); //проверка на необходимую точность вычислений


return;
}
