#include <QVector>

class splinemodel
{
public:
    splinemodel() {}
    ~splinemodel() {}
    void formspline(int srcfunc, double a, double b, int n, double abrd, double bbrd, QVector<double>& X, QVector<QVector<double>>& coeff);
    void errorcalc(int srcfunc, double a, double b, QVector<double>& X, QVector<QVector<double>>& coeff, int N,
                   QVector<double>& Xaux, QVector<double>& F0, QVector<double>& S0, QVector<double>& FS0,
                   QVector<double>& F1, QVector<double>& S1, QVector<double>& FS1,
                   QVector<double>& F2 ,QVector<double>& S2, QVector<double>& FS2);

    double funclist(int srcfunc,int type, double x);
    void tridiagonal(QVector<double>& A,QVector<double>& B,QVector<double>& C,double m1,double m2,QVector<double>& fi, QVector<double>& result);
};
