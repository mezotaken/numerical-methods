#include "model.h"

//model2


int model2::sgn(double v)
{
    if(v2 > 0) return 1;
    else if(v2 < 0)
        return -1;
    else return 0;
}
double model2::f1(double x,double v1,double v2)
{
    if(std::abs(v1) >= f*g*m/k || std::abs(v2)>1e-4)
     return v2;
    else return 0;

}
double model2::f2(double x,double v1,double v2)
{
   if(std::abs(v1) >= f*g*m/k || std::abs(v2)>1e-4)
    return -k/m*v1 - f*g*sgn(v2);
   else return 0;

}

void model2::set(double i_x0,double i_u10, double i_u20,
                 double i_h, double i_end, double i_epsBrd,
                 double i_epsCtrl, int i_maxStep, bool i_isStepFixed,
                 double i_k, double i_m, double i_f)
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
    k = i_k;
    m = i_m;
    f = i_f;
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
