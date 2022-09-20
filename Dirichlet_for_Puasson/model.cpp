#include "model.h"
double modeltest::mu_y(double y) {
    return exp(-y*y);
}
double modeltest::mu_x(double x) {
    return exp(-x*x);
}

double modeltest::F(double x,double y) {
    return -4*exp(1 - x*x - y*y)*(x*x + y*y - 1);
}

double modelmain::mu_y(double y) {
    return -y*y+1;
}
double modelmain::mu_x(double x) {
    return std::abs(sin(M_PI*x));
}

double modelmain::F(double x,double y) {
    return std::abs(pow(sin(M_PI*x*y),3));
}


void model::Zeidel(QVector<QVector<double>>& V,QVector<QVector<double>>& f,QVector<QVector<double>>& rs,int n, int m, double n_max, double eps, double& s, double& eps_s){
    FillV(V,n,m);
    FillF(f,n,m);
    double h = 2.0/n;
    double k = 2.0/m;
    s=0;
    double h1=1/(h*h),k1=1/(k*k), A=-2*(h1+k1);
    eps_s=eps+1;
    double oldV;
    while (s<n_max && eps_s>eps)
    {
        s++;
        eps_s=0;
        for (int j = 1; j < m; j++)
            for (int i = 1; i < n; i++)
            {
                oldV=V[i][j];
                V[i][j] = 1/A*(-f[i][j] - h1*(V[i-1][j]+V[i+1][j]) - k1*(V[i][j-1]+V[i][j+1]));
                if (std::abs(oldV - V[i][j])>eps_s)
                    eps_s=std::abs(oldV - V[i][j]);
            }
    }
    for (int j = 1; j < m; j++)
        for (int i = 1; i < n; i++)
            rs[i][j]=A*V[i][j]+h1*(V[i+1][j]+V[i-1][j])+k1*(V[i][j-1]+V[i][j+1])+f[i][j];
}

void model::MinR(QVector<QVector<double>>& V,QVector<QVector<double>>& f,QVector<QVector<double>>& rs,int n, int m, double n_max, double eps, double& s, double& eps_s){
    FillV(V,n,m);
    FillF(f,n,m);
    double h = 2.0/n;
    double k = 2.0/m;
    s=0;
    double s1, s2;
    double h1=1/(h*h),k1=1/(k*k), A=-2*(h1+k1);
    eps_s=eps+1;
    double oldV;
    QVector<QVector<double>> Ars(n,QVector<double>(m));
    while (s < n_max && eps_s > eps)
    {
        s++;
        eps_s = 0;
        s1 = 0; s2 = 0;
        for (int j = 1; j < m; j++)
            for (int i = 1; i < n; i++)
                rs[i][j]=A*V[i][j]+h1*(V[i+1][j]+V[i-1][j])+k1*(V[i][j-1]+V[i][j+1])+f[i][j];

        for (int j = 1; j < m; j++)
            for (int i = 1; i < n; i++)
                Ars[i][j]=A*rs[i][j]+h1*(rs[i+1][j]+rs[i-1][j])+k1*(rs[i][j-1]+rs[i][j+1]);
        for (int j = 1; j < n; j++)
            for (int i = 1; i < m; i++) {
                s1+=Ars[i][j]*rs[i][j];
                s2+=Ars[i][j]*Ars[i][j];
            }
        double tau_s = s1/s2;

        for (int j = 1; j < m; j++)
            for (int i = 1; i < n; i++)
            {
                oldV=V[i][j];
                V[i][j] -= tau_s*rs[i][j];
                if (std::abs(oldV - V[i][j])>eps_s)
                    eps_s=std::abs(oldV - V[i][j]);
            }
    }
}

void model::FillV(QVector<QVector<double>>& V,int n, int m) {
    double h = 2.0/n, k = 2.0/m;
    for(int i = 0; i < n + 1; i++) {
        V[i][0] = V[i][m] = mu_x(-1+i*h);
    }
    for(int j = 0; j < m + 1; j++) {
        V[0][j] = V[n][j] = mu_y(-1+j*k);
    }
}

void model::FillF(QVector<QVector<double>>& f, int n, int m) {
    double h = 2.0/n, k = 2.0/m;
    for (int j = 1; j < m; j++)
        for (int i = 1; i < n; i++)
            f[i][j] = F(-1+i*h,-1+j*k);
}


void modeltest::MinR_topright(QVector<QVector<double>>& V,QVector<QVector<double>>& f,QVector<QVector<double>>& rs,int n, int m, double n_max, double eps, double& s, double& eps_s){
    double h = 2.0/n, k = 2.0/m;
    for(int i = 0; i < n + 1; i++) {
        V[i][0] = mu_x(-1+i*h);
        if(i < n/2 + 1)
            V[i][m] = mu_x(-1+i*h);
        else
            V[i][m/2] = exp(1-(-1+i*h)*(-1+i*h));
    }
    for(int j = 0; j < m + 1; j++) {
        V[0][j] = mu_y(-1+j*k);
        if(j < m/2 + 1)
            V[n][j] = mu_y(-1+j*k);
        else
            V[n/2][j] = exp(1-(-1+j*k)*(-1+j*k));
    }
    for (int j = 1; j < m; j++)
        for (int i = 1; i < n; i++)
            f[i][j] = F(-1+i*h,-1+j*k);
    V[n/2][m/2] = exp(1);
    s=0;
    double s1, s2;
    double h1=1/(h*h),k1=1/(k*k), A=-2*(h1+k1);
    eps_s=eps+1;
    double oldV;
    QVector<QVector<double>> Ars(n,QVector<double>(m));
    while (s < n_max && eps_s > eps)
    {
        s++;
        eps_s = 0;
        s1 = 0; s2 = 0;


        for (int j = 1; j < m/2; j++)
            for (int i = 1; i < n; i++)
                rs[i][j]=A*V[i][j]+h1*(V[i+1][j]+V[i-1][j])+k1*(V[i][j-1]+V[i][j+1])+f[i][j];

        for (int j = m/2; j < m; j++)
            for (int i = 1; i < n/2; i++)
                rs[i][j]=A*V[i][j]+h1*(V[i+1][j]+V[i-1][j])+k1*(V[i][j-1]+V[i][j+1])+f[i][j];



        for (int j = 1; j < m/2; j++)
            for (int i = 1; i < n; i++)
                Ars[i][j]=A*rs[i][j]+h1*(rs[i+1][j]+rs[i-1][j])+k1*(rs[i][j-1]+rs[i][j+1]);
        for (int j = m/2; j < m; j++)
            for (int i = 1; i < n/2; i++)
                Ars[i][j]=A*rs[i][j]+h1*(rs[i+1][j]+rs[i-1][j])+k1*(rs[i][j-1]+rs[i][j+1]);


        for (int j = 1; j < m/2; j++)
            for (int i = 1; i < n; i++) {
                s1+=Ars[i][j]*rs[i][j];
                s2+=Ars[i][j]*Ars[i][j];
            }
        for (int j = m/2; j < m; j++)
            for (int i = 1; i < n/2; i++) {
                s1+=Ars[i][j]*rs[i][j];
                s2+=Ars[i][j]*Ars[i][j];
            }

        double tau_s = s1/s2;

        for (int j = 1; j < m/2; j++)
            for (int i = 1; i < n; i++) {
                oldV=V[i][j];
                V[i][j] -= tau_s*rs[i][j];
                if (std::abs(oldV - V[i][j])>eps_s)
                    eps_s=std::abs(oldV - V[i][j]);
            }
        for (int j = m/2; j < m; j++)
            for (int i = 1; i < n/2; i++) {
                oldV=V[i][j];
                V[i][j] -= tau_s*rs[i][j];
                if (std::abs(oldV - V[i][j])>eps_s)
                    eps_s=std::abs(oldV - V[i][j]);
            }
    }
}

void modeltest::Zeidel_topright(QVector<QVector<double>>& V,QVector<QVector<double>>& f,QVector<QVector<double>>& rs,int n, int m, double n_max, double eps, double& s, double& eps_s){
    double h = 2.0/n, k = 2.0/m;
    for(int i = 0; i < n + 1; i++) {
        V[i][0] = mu_x(-1+i*h);
        if(i < n/2 + 1)
            V[i][m] = mu_x(-1+i*h);
        else
            V[i][m/2] = exp(1-(-1+i*h)*(-1+i*h));
    }
    for(int j = 0; j < m + 1; j++) {
        V[0][j] = mu_y(-1+j*k);
        if(j < m/2 + 1)
            V[n][j] = mu_y(-1+j*k);
        else
            V[n/2][j] = exp(1-(-1+j*k)*(-1+j*k));
    }
    for (int j = 1; j < m; j++)
        for (int i = 1; i < n; i++)
            f[i][j] = F(-1+i*h,-1+j*k);
    V[n/2][m/2] = exp(1);
    s=0;
    double h1=1/(h*h),k1=1/(k*k), A=-2*(h1+k1);
    eps_s=eps+1;
    double oldV;

    while (s < n_max && eps_s > eps) {
        s++;
        eps_s = 0;

        for (int j = 1; j < m/2; j++)
            for (int i = 1; i < n; i++) {
                oldV=V[i][j];
                V[i][j] = 1/A*(-f[i][j] - h1*(V[i-1][j]+V[i+1][j]) - k1*(V[i][j-1]+V[i][j+1]));
                if (std::abs(oldV - V[i][j])>eps_s)
                    eps_s=std::abs(oldV - V[i][j]);
            }
        for (int j = m/2; j < m; j++)
            for (int i = 1; i < n/2; i++) {
                oldV=V[i][j];
                V[i][j] = 1/A*(-f[i][j] - h1*(V[i-1][j]+V[i+1][j]) - k1*(V[i][j-1]+V[i][j+1]));
                if (std::abs(oldV - V[i][j])>eps_s)
                    eps_s=std::abs(oldV - V[i][j]);
            }
    }

    for (int j = 1; j < m/2; j++)
        for (int i = 1; i < n; i++)
            rs[i][j]=A*V[i][j]+h1*(V[i+1][j]+V[i-1][j])+k1*(V[i][j-1]+V[i][j+1])+f[i][j];
    for (int j = m/2; j < m; j++)
        for (int i = 1; i < n/2; i++)
            rs[i][j]=A*V[i][j]+h1*(V[i+1][j]+V[i-1][j])+k1*(V[i][j-1]+V[i][j+1])+f[i][j];
}

void modeltest::FillU(QVector<QVector<double>>& U, int n, int m){
    double h = 2.0/n, k = 2.0/m;
    for(int j = 0; j < m+1; j++)
        for(int i = 0; i < n+1; i++){
            U[i][j] = exp(1-(-1+i*h)*(-1+i*h)- (-1+j*k)*(-1+j*k));
        }
}

void modeltest::FillU_topright(QVector<QVector<double>>& U, int n, int m) {
    double h = 2.0/n, k = 2.0/m;
    for (int j = 0; j < m/2+1; j++)
        for (int i = 0; i < n+1; i++)
            U[i][j] = exp(1-(-1+i*h)*(-1+i*h)- (-1+j*k)*(-1+j*k));
    for (int j = m/2+1; j < m+1; j++)
        for (int i = 0; i < n/2+1; i++)
            U[i][j] = exp(1-(-1+i*h)*(-1+i*h)- (-1+j*k)*(-1+j*k));
}
