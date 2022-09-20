#include "model.h"

//Реализация функций структуры model0

double model0::count(double x,double v)
{
    return -5*v/2;
}


void model0::set(double i_x0,double i_u0,
             double i_h, double i_end, double i_epsBrd,
             double i_epsCtrl, int i_maxStep, bool i_isStepFixed)
{
    x0 = i_x0;
    u0 = i_u0;
    h = i_h;
    end = i_end;
    epsBrd = i_epsBrd;
    epsCtrl = i_epsCtrl;
    maxStep = i_maxStep;
    isStepFixed = i_isStepFixed;
}

void model0::start()
{
    x = x0;
    v = u0;
    isRun = true;
    hprev = h;
    maxS = 0;
    xmaxS = x0;
    minS =  10;
    xminS = x0;
    maxH = 0;
    xmaxH = x0;
    minH = 10;
    xminH = x0;
    maxE = 0;
    xmaxE = x0;
    minE = 10;
    xminE = x0;
}

void model0::stop()
{
    isRun = false;
    stDwn = stUp = 0;
}

double model0::countNext(double th, double tx, double tv)
{
    double k1,k2,k3,k4;
    double res;
    k1 = count(tx,tv);
    k2 = count(tx+th/2,tv+th/2*k1);
    k3 = count(tx+th/2,tv+th/2*k2);
    k4 = count(tx+th,tv+th*k3);
    res = tv+th/6*(k1+2*k2+2*k3+k4);
    return res;
}

double model0::halfStepCountNext(double th, double tx, double tv)
{
    return countNext(th/2,tx+th/2,countNext(th/2,tx,tv));
}

int model0::ctrlLocalErr()
{
    int res;
    if(std::abs(s)<epsCtrl/32)
        res = -1;
    else if(std::abs(s)<=epsCtrl)
        res = 0;
    else res = 1;
        return res;
}

void model0::halveStep()
{
    h/=2; stDwn++;
}

void model0::doubleStep()
{
    h*=2; stUp++;
}

double model0::countCorrect(double tx)
{

    double c = u0*exp(5*x0/2);
    return c*exp(-5*tx/2);

}

void model0::iterate()
{
    if(x+h>end)
        h = end-x;
    v2 = halfStepCountNext(h,x,v);
    v1 = countNext(h,x,v);

    s = (v2-v1)/15;
    if(!isStepFixed)
    {
        int ctrl = ctrlLocalErr();

        while(ctrl == 1)
        {

            halveStep();
            v2 = halfStepCountNext(h,x,v);
            v1 = countNext(h,x,v);
            s = (v2-v1)/15;
            ctrl = ctrlLocalErr();
        }
         hprev = h;

        if(ctrl == -1)
            doubleStep();

    }

    x = x+hprev;
    v = v1;
    u = countCorrect(x);
    E = u-v;
    if(hprev>maxH)
    {
        maxH = hprev;
        xmaxH = x;
    }
    if(hprev<minH)
    {
        minH = hprev;
        xminH = x;
    }
    if(std::abs(s)>maxS)
    {
        maxS = std::abs(s);
        xmaxS = x;
    }
    if(std::abs(s)<minS)
    {
        minS = std::abs(s);
        xminS = x;
    }
    if(std::abs(E)>maxE)
    {
        maxE = std::abs(E);
        xmaxE = x;
    }
    if(std::abs(E)<minE)
    {
        minE = std::abs(E);
        xminE = x;
    }
}

//model1

double model1::count(double x,double v)
{
    return log(x+1)/(x*x+1)*v*v+v-v*v*v*sin(10*x);
}


void model1::set(double i_x0,double i_u0,
             double i_h, double i_end, double i_epsBrd,
             double i_epsCtrl, int i_maxStep, bool i_isStepFixed)
{
    x0 = i_x0;
    u0 = i_u0;
    h = i_h;
    end = i_end;
    epsBrd = i_epsBrd;
    epsCtrl = i_epsCtrl;
    maxStep = i_maxStep;
    isStepFixed = i_isStepFixed;
}

void model1::start()
{
    x = x0;
    v = u0;
    isRun = true;
    hprev = h;
    maxS = 0;
    xmaxS = x0;
    minS =  10;
    xminS = x0;
    maxH = 0;
    xmaxH = x0;
    minH = 10;
    xminH = x0;
}

void model1::stop()
{
    isRun = false;
    stDwn = stUp = 0;
}

double model1::countNext(double th, double tx, double tv)
{
    double k1,k2,k3,k4;
    double res;
    k1 = count(tx,tv);
    k2 = count(tx+th/2,tv+th/2*k1);
    k3 = count(tx+th/2,tv+th/2*k2);
    k4 = count(tx+th,tv+th*k3);
    res = tv+th/6*(k1+2*k2+2*k3+k4);
    return res;
}

double model1::halfStepCountNext(double th, double tx, double tv)
{
    return countNext(th/2,tx+th/2,countNext(th/2,tx,tv));
}

int model1::ctrlLocalErr()
{
    int res;
    if(std::abs(s)<epsCtrl/32)
        res = -1;
    else if(std::abs(s)<=epsCtrl)
        res = 0;
    else res = 1;
        return res;
}

void model1::halveStep()
{
    h/=2; stDwn++;
}

void model1::doubleStep()
{
    h*=2; stUp++;
}

void model1::iterate()
{
    if(x+h>end)
        h = end-x;
    v2 = halfStepCountNext(h,x,v);
    v1 = countNext(h,x,v);

    s = (v2-v1)/15;
    if(!isStepFixed)
    {
        int ctrl = ctrlLocalErr();

        while(ctrl == 1)
        {

            halveStep();
            v2 = halfStepCountNext(h,x,v);
            v1 = countNext(h,x,v);
            s = (v2-v1)/15;
            ctrl = ctrlLocalErr();
        }
         hprev = h;

        if(ctrl == -1)
            doubleStep();

    }

    x = x+hprev;
    v = v1;

    if(hprev>maxH)
    {
        maxH = hprev;
        xmaxH = x;
    }
    if(hprev<minH)
    {
        minH = hprev;
        xminH = x;
    }
    if(std::abs(s)>maxS)
    {
        maxS = std::abs(s);
        xmaxS = x;
    }
    if(std::abs(s)<minS)
    {
        minS = std::abs(s);
        xminS = x;
    }
}

//model2

double model2::f1(double x,double v1,double v2)
{
    return v2;
}
double model2::f2(double x,double v1,double v2)
{
    return -a*v2*v2-b*sin(v1);
}

void model2::set(double i_x0,double i_u10, double i_u20,
                 double i_h, double i_end, double i_epsBrd,
                 double i_epsCtrl, int i_maxStep, bool i_isStepFixed,
                 double i_a, double i_b)
{
    x0 = i_x0;
    u10 = i_u10;
    u20 = i_u20;
    h = i_h;
    end = i_end;
    epsBrd = i_epsBrd;
    epsCtrl = i_epsCtrl;
    maxStep = i_maxStep;
    isStepFixed = i_isStepFixed;
    a = i_a;
    b = i_b;
}

void model2::start()
{
    x = x0;
    v1 = u10;
    v2 = u20;
    isRun = true;
    hprev = h;
    maxS = 0;
    xmaxS = x0;
    minS =  10;
    xminS = x0;
    maxH = 0;
    xmaxH = x0;
    minH = 10;
    xminH = x0;
}

void model2::stop()
{
    isRun = false;
    stDwn = stUp = 0;
}

void model2::countNext(double& v1,double& v2,double th, double tx, double tv1, double tv2)
{
    double k11,k21,k12,k22,k13,k23,k14,k24;

    k11 = f1(tx,tv1,tv2);
    k21 = f2(tx,tv1,tv2);
    k12 = f1(tx+th/2,tv1+th/2*k11,tv2+th/2*k21);
    k22 = f2(tx+th/2,tv1+th/2*k11,tv2+th/2*k21);
    k13 = f1(tx+th/2,tv1+th/2*k12,tv2+th/2*k22);
    k23 = f2(tx+th/2,tv1+th/2*k12,tv2+th/2*k22);
    k14 = f1(tx+th,tv1+th*k13,tv2+th*k23);
    k24 = f2(tx+th,tv1+th*k13,tv2+th*k23);
    v1 = tv1+th/6*(k11+2*k12+2*k13+k14);
    v2 = tv2+th/6*(k21+2*k22+2*k23+k24);
}

void model2::halfStepCountNext(double& v1, double& v2,double th, double tx, double tv1,double tv2)
{
   double tempv1,tempv2;
   countNext(tempv1,tempv2,th/2,tx,tv1,tv2);
   countNext(v1,v2,th/2,tx+th/2,tempv1,tempv2);
}
int model2::ctrlLocalErr()
{
    int res;
    if(std::abs(s)<epsCtrl/32)
        res = -1;
    else if(std::abs(s)<=epsCtrl)
        res = 0;
    else res = 1;
        return res;
}
void model2::halveStep()
{
    h/=2; stDwn++;
}

void model2::doubleStep()
{
    h*=2; stUp++;
}

void model2::iterate(int dir)
{
    if(x+h>end)
        h = end-x;
    halfStepCountNext(v12,v22,dir*h,x,v1,v2);
    countNext(v11,v21,dir*h,x,v1,v2);
    s = sqrt(((v12-v11)*(v12-v11)+(v22-v21)*(v22-v21))/225);
    if(!isStepFixed)
    {
        int ctrl = ctrlLocalErr();

        while(ctrl == 1)
        {

            halveStep();
            halfStepCountNext(v12,v22,dir*h,x,v1,v2);
            countNext(v11,v21,dir*h,x,v1,v2);
            s = sqrt(((v12-v11)*(v12-v11)+(v22-v21)*(v22-v21))/225);
            ctrl = ctrlLocalErr();
        }
         hprev = h;

        if(ctrl == -1)
            doubleStep();

    }

    x = x+dir*hprev;
    v1 = v11;
    v2 = v21;
    if(dir == 1)
    {
        if(hprev>maxH)
        {
            maxH = hprev;
            xmaxH = x;
        }
        if(hprev<minH)
        {
            minH = hprev;
            xminH = x;
        }
        if(std::abs(s)>maxS)
        {
            maxS = std::abs(s);
            xmaxS = x;
        }
        if(std::abs(s)<minS)
        {
            minS = std::abs(s);
            xminS = x;
        }
    }
}
