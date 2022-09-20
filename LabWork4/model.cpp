#include "model.h"


double modeltest1::a(double x,double h)
{
        return 1.0;
}

double modeltest1::d(double x,double h)
{
        return 1.0;
}

double modeltest1::fi(double x,double h)
{
        return x*x-2*x-1;
}

double modeltest2::a(double x,double h)
{
    if(x<=ksi)
        return 1/sqrt(2)+1;
    else if(x-h>=ksi)
        return 1/2.0;
    else
        return h/((ksi - x+h)/(1/sqrt(2)+1) + (x-ksi)*2);
}

double modeltest2::d(double x,double h)
{
    if(x+h/2<=ksi)
        return 1;
    else if(x-h/2>=ksi)
        return M_PI*M_PI/8;
    else
        return ((ksi - x +h/2) + (x +h/2-ksi)*M_PI*M_PI/8)/h;
}

double modeltest2::fi(double x,double h)
{
    if(x+h/2<=ksi)
        return 1;
    else if(x-h/2>=ksi)
        return sqrt(2)/2;
    else
        return ((ksi - x +h/2) + (x +h/2-ksi)*sqrt(2)/2)/h;

}

double modelmain::a(double x,double h)
{
    if(x<=ksi)
        return sin(x-h/2)+1;
    else if(x-h>=ksi)
        return cos(x-h/2)*cos(x-h/2);
    else
        return h/((ksi - x+h)/(sin((x-h+ksi)/2)+1) + (x-ksi)/(cos((x-h+ksi)/2)*cos((x-h+ksi)/2)));

}

double modelmain::d(double x,double h)
{
    if(x+h/2<=ksi)
        return 1;
    else if(x-h/2>=ksi)
        return 2*x*x;
    else
        return ((ksi - x +h/2) + (x +h/2-ksi)*(2*((x+h/2+ksi)/2)*((x+h/2+ksi)/2)))/h;
}

double modelmain::fi(double x,double h)
{
    if(x+h/2<=ksi)
        return sin(2*x);
    else if(x-h/2>=ksi)
        return cos(x);
    else
        return ((ksi - x +h/2)*(sin(2*((x-h/2+ksi)/2))) + (x +h/2-ksi)*(cos(((x+h/2+ksi)/2))))/h;
    return 1;
}


void modeltest1::CorrectSol(int n, QVector<double>& U)
{
    double h = 1.0/n;
    double x = 0;
    for(int i = 0;i<n;i++)
    {
        U.push_back(u(x));
        x+=h;
    }
    U.push_back(0);
}

 double modeltest2::u(double x)
 {
     if(x<=ksi)
         return -0.3787567381181188*exp(sqrt(2/(2+sqrt(2)))*x) + 0.3787567381181188*exp(-sqrt(2/(2+sqrt(2)))*x) +1;
     else
         return -0.22586883718533526*exp(M_PI*x/2) + 2.4695921220659307*exp(-M_PI*x/2) + 4*sqrt(2)/(M_PI*M_PI);
 }

void modeltest2::CorrectSol(int n, QVector<double>& U)
{
    double h = 1.0/n;
    double x = 0;
    for(int i = 0;i<n;i++)
    {
        U.push_back(u(x));
        x+=h;
    }
    U.push_back(0);

}

void model::calculate(int n, QVector<double>& X, QVector<double>& V)
{
    QVector<double> A,B,C,f;
    double h = 1.0/n;
    double x = 0;
    X.push_back(x);
    for(int i = 1;i<n;i++)
    {
        x+=h;
        X.push_back(x);
        A.push_back(a(x,h)/(h*h));
        B.push_back(a(x+h,h)/(h*h));
        C.push_back(a(x,h)/(h*h)+a(x+h,h)/(h*h) + d(x,h));
        f.push_back(fi(x,h));
    }
    X.push_back(1);
    tridiagonal(A,B,C,0,0,1,0,f,V);
}

void model::tridiagonal(QVector<double>& A,QVector<double>& B,QVector<double>& C,double k1,double k2,double m1,double m2,QVector<double>& fi, QVector<double>& result)
{
    int n = A.size()+2;
    result.resize(n);
    QVector<double> a,b;
    a.resize(n-1);
    b.resize(n-1);
    a[0] = k1; b[0] = m1;
    for(int i = 0;i<n-2;i++)
    {
        a[i+1] = B[i]/(C[i] - a[i]*A[i]);
        b[i+1] = (fi[i] +A[i]*b[i])/(C[i] - A[i]*a[i]);
    }
    result[n-1] = (m2+b[n-2]*k2)/(1-a[n-2]*k2);
    for(int i = n-2;i>=0;i--)
    {
        result[i] = a[i]*result[i+1]+b[i];
    }
}
