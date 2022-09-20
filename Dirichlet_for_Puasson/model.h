#include <cmath>
#include <QVector>

class model
{
public:
    model() {}
    virtual ~model() {}
    virtual double mu_y(double y) = 0;
    virtual double mu_x(double x) = 0;
    virtual  double F(double x,double y) = 0;
    void Zeidel(QVector<QVector<double>>& V,QVector<QVector<double>>& f,QVector<QVector<double>>& rs,int n, int m, double n_max, double eps, double& s, double& eps_s);
    void MinR(QVector<QVector<double>>& V,QVector<QVector<double>>& f,QVector<QVector<double>>& rs, int n, int m, double n_max, double eps, double& s, double& eps_s);
    void FillV(QVector<QVector<double>>& V,int n,int m);
    void FillF(QVector<QVector<double>>& f, int n, int m);
};

class modelmain : public model
{
public:
    double F(double x,double y) override;
    double mu_y(double y) override;
    double mu_x(double x) override;
};

class modeltest : public model
{
public:
    void Zeidel_topright(QVector<QVector<double>>& V,QVector<QVector<double>>& f,QVector<QVector<double>>& rs,int n, int m, double n_max, double eps, double& s, double& eps_s);
    void MinR_topright(QVector<QVector<double>>& V,QVector<QVector<double>>& f,QVector<QVector<double>>& rs,int n, int m, double n_max, double eps, double& s, double& eps_s);
    double F(double x,double y) override;
    double mu_y(double y) override;
    double mu_x(double x) override;
    void FillU(QVector<QVector<double>>& U, int n, int m);
    void FillU_topright(QVector<QVector<double>>& U, int n, int m);
};

