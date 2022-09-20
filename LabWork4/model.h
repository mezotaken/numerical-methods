#include <qmath.h>
#include <QVector>

class model
{
public:
    model() {}
    virtual ~model() {}

    void tridiagonal(QVector<double>& A,QVector<double>& B,QVector<double>& C,double k1,double k2,double m1,double m2,QVector<double>& fi, QVector<double>& result);
    void calculate(int n, QVector<double>& X, QVector<double>& V);
    const double ksi = M_PI/4;
    virtual double a(double x,double h) = 0;
    virtual double d(double x,double h) = 0;
    virtual double fi(double x,double h) = 0;
};

class modelmain : public model
{
public:
    double a(double x,double h) override;
    double d(double x,double h) override;
    double fi(double x,double h) override;
};

class modeltest1 : public model
{
public:


    double a(double x,double h) override;
    double d(double x,double h) override;
    double fi(double x,double h) override;
    double u(double x) {return x*x-2*x+1;}
    void CorrectSol(int n, QVector<double>& U);
};

class modeltest2 : public model
{
public:
    double a(double x,double h) override;
    double d(double x,double h) override;
    double fi(double x,double h) override;
    double u(double x);
    void CorrectSol(int n, QVector<double>& U);
};

