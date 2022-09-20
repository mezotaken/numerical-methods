#include "splinemodel.h"
double splinemodel::funclist(int srcfunc, int type,double x){
    switch (srcfunc) {
    case 0:
        switch (type) {
            case 0:
                if(x<=0)
                    return x*x*x+3*x*x;
                else
                    return -x*x*x+3*x*x;
            case 1:
                if(x<=0)
                    return 3*x*x+6*x;
                else
                    return -3*x*x+6*x;
            case 2:
            if(x<=0)
                return 6*x+6;
            else
                return -6*x+6;
        }
    case 1:
        switch (type) {
            case 0:
                return cos(exp(x));
            case 1:
                return -exp(x)*sin(exp(x));
            case 2:
                return -exp(x)*(sin(exp(x)) + exp(x)*cos(exp(x)));
        }
    case 2:
        switch (type) {
            case 0:
                return cos(exp(x)) + cos(10*x);
            case 1:
                return -exp(x)*sin(exp(x)) - 10*sin(10*x);
            case 2:
                return -exp(x)*(sin(exp(x)) + exp(x)*cos(exp(x))) - 100*cos(10*x);
        }
    case 3:
        switch (type) {
            case 0:
                return cos(exp(x)) + cos(100*x);
            case 1:
                return -exp(x)*sin(exp(x)) - 100*sin(100*x);
            case 2:
                return -exp(x)*(sin(exp(x)) + exp(x)*cos(exp(x))) - 10000*cos(100*x);
        }
    }
}
void splinemodel::formspline(int srcfunc,double a,double b,int n,double abrd, double bbrd,QVector<double>& X,QVector<QVector<double>>& coeff){
    coeff.resize(n+1);
    X.resize(n+1);
    double h = (b-a)/n;
    for(int i = 0;i<n+1;i++)
    {
        coeff[i].resize(4);
        X[i] = a+i*h;
        coeff[i][0] = funclist(srcfunc,0,X[i]);
    }

    QVector<double> A,B,C,fi,result;
    A.resize(n-1);
    B.resize(n-1);
    C.resize(n-1);
    fi.resize(n-1);
    A.fill(h);
    B.fill(h);
    C.fill(-4*h);
    for(int i = 1;i<n;i++)
    {
        fi[i-1] = -6*(coeff[i-1][0] - 2*coeff[i][0] + coeff[i+1][0])/h;
    }
    tridiagonal(A,B,C,abrd,bbrd,fi,result);
    for(int i = 0;i<n+1;i++)
        coeff[i][2] = result[i];
    for(int i= 0;i<n;i++)
    {
        coeff[i+1][1] = (coeff[i+1][0]-coeff[i][0])/h + coeff[i+1][2]*h/3 + coeff[i][2]*h/6;
        coeff[i+1][3] = (coeff[i+1][2]-coeff[i][2])/h;
    }
}

void splinemodel::errorcalc(int srcfunc, double a, double b, QVector<double>& X, QVector<QVector<double>>& coeff, int N,
               QVector<double>& Xaux, QVector<double>& F0, QVector<double>& S0, QVector<double>& FS0,
               QVector<double>& F1, QVector<double>& S1, QVector<double>& FS1,
                            QVector<double>& F2 ,QVector<double>& S2, QVector<double>& FS2){

    double H = (b-a)/N;
    Xaux.resize(N+1);
    F0.resize(N+1);
    F1.resize(N+1);
    F2.resize(N+1);
    S0.resize(N+1);
    S1.resize(N+1);
    S2.resize(N+1);
    FS0.resize(N+1);
    FS1.resize(N+1);
    FS2.resize(N+1);
    for(int i = 0,j = 1;i<N+1;i++)
    {
        Xaux[i]=a+i*H;
        F0[i] = funclist(srcfunc,0,Xaux[i]);
        F1[i] = funclist(srcfunc,1,Xaux[i]);
        F2[i] = funclist(srcfunc,2,Xaux[i]);
        if(Xaux[i]>=X[j])
            j++;
        if(Xaux[i]>=b)
            j--;
        S0[i] = coeff[j][0] + coeff[j][1]*(Xaux[i]-X[j])+coeff[j][2]*(Xaux[i]-X[j])*(Xaux[i]-X[j])/2 +
                coeff[j][3]*(Xaux[i]-X[j])*(Xaux[i]-X[j])*(Xaux[i]-X[j])/6;
        S1[i] = coeff[j][1] + coeff[j][2]*(Xaux[i]-X[j]) + coeff[j][3]*(Xaux[i]-X[j])*(Xaux[i]-X[j])/2;
        S2[i] = coeff[j][2] + coeff[j][3]*(Xaux[i]-X[j]);
        FS0[i] = std::abs(F0[i]-S0[i]);
        FS1[i] = std::abs(F1[i]-S1[i]);
        FS2[i] = std::abs(F2[i]-S2[i]);

    }
}


void splinemodel::tridiagonal(QVector<double>& A,QVector<double>& B,QVector<double>& C,double m1,double m2,QVector<double>& fi, QVector<double>& result)
{
    int n = A.size()+2;
    result.resize(n);
    QVector<double> a,b;
    a.resize(n-1);
    b.resize(n-1);
    a[0] = 0; b[0] = m1;
    for(int i = 0;i<n-2;i++)
    {
        a[i+1] = B[i]/(C[i] - a[i]*A[i]);
        b[i+1] = (fi[i] +A[i]*b[i])/(C[i] - A[i]*a[i]);
    }
    result[n-1] = m2;
    for(int i = n-2;i>=0;i--)
    {
        result[i] = a[i]*result[i+1]+b[i];
    }
}
