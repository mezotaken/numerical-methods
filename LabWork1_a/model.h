#include <QMainWindow>

struct model0
{
public:
    bool isRun;             //Запущен ли счёт
    bool isStepFixed;       //Фиксирован ли шаг
    double x0,u0;           //Начальные условия задачи Коши
    int stDwn,stUp;         //Число удваиваний и делений шага
    double x,v;             //Текущая точка численной траектории
    double v2;              //Точка посчитанная с вдвое меньшим шагом
    double v1;              //Точка посчитанная обычным шагом
    double u;               //Текущая точка точной траектории
    double E;               //Глобальная погрешность
    double h;               //Текущий шаг
    double hprev;           //Предыдущий шаг
    double s;               //S оценка ЛП
    double minS,maxS;       //Макс. и Мин. |S|
    double xminS,xmaxS;     //Точки в которых |S| максимально(минимально)
    double minH,maxH;       //Макс. и Мин. H
    double xminH,xmaxH;     //
    double minE,maxE;       //Макс. и Мин. E
    double xminE,xmaxE;     //
    double end;             //Граничная точка
    double epsBrd,epsCtrl;  //Параметры контроля выхода на границу и контроля погрешности
    int maxStep;            //Максимальное число шагов

    model0() {}                                    //Констуктор
    double count(double x,double v);
    void set(double i_x0,double i_u0,
          double i_h, double i_end, double i_epsBrd,
          double i_epsCtrl, int i_maxStep, bool i_isStepFixed);
    void start();   //Начать счёт
    void stop();    //Остановить счёт
    double countNext(double th, double tx, double tv);          //Посчитать следующую точку
    double halfStepCountNext(double th, double tx, double tv);  //Посчитать следующую точку с вдвое меньшим шагом
    int ctrlLocalErr();   //Контроль локальной погрешности
    void halveStep();     //Поделить шаг пополам
    void doubleStep();    //Удвоить шаг
    double countCorrect(double tx);//Посчитать точное решение
    void iterate();

};



struct model1
{
public:
    bool isRun;             //Запущен ли счёт
    bool isStepFixed;       //Фиксирован ли шаг
    double x0,u0;           //Начальные условия задачи Коши
    int stDwn,stUp;         //Число удваиваний и делений шага
    double x,v;             //Текущая точка численной траектории
    double v2;              //Точка посчитанная с вдвое меньшим шагом
    double v1;              //Точка посчитанная обычным шагом
    double h;               //Текущий шаг
    double hprev;           //Предыдущий шаг
    double s;               //S оценка ЛП
    double minS,maxS;       //Макс. и Мин. |S|
    double xminS,xmaxS;     //Точки в которых |S| максимально(минимально)
    double minH,maxH;       //Макс. и Мин. H
    double xminH,xmaxH;     //
    double end;             //Граничная точка
    double epsBrd,epsCtrl;  //Параметры контроля выхода на границу и контроля погрешности
    int maxStep;            //Максимальное число шагов

    model1() {}                                    //Констуктор
    double count(double x,double v);
    void set(double i_x0,double i_u0,
          double i_h, double i_end, double i_epsBrd,
          double i_epsCtrl, int i_maxStep, bool i_isStepFixed);
    void start();   //Начать счёт
    void stop();    //Остановить счёт
    double countNext(double th, double tx, double tv);          //Посчитать следующую точку
    double halfStepCountNext(double th, double tx, double tv);  //Посчитать следующую точку с вдвое меньшим шагом
    int ctrlLocalErr();   //Контроль локальной погрешности
    void halveStep();     //Поделить шаг пополам
    void doubleStep();    //Удвоить шаг
    void iterate();

};


struct model2
{
public:
    double a,b;
    bool isRun;             //Запущен ли счёт
    bool isStepFixed;       //Фиксирован ли шаг
    double x0,u10,u20;           //Начальные условия задачи Коши
    int stDwn,stUp;         //Число удваиваний и делений шага
    double x,v1,v2;             //Текущая точка численной траектории
    double v12,v22;              //Точка посчитанная с вдвое меньшим шагом
    double v11,v21;              //Точка посчитанная обычным шагом
    double h;               //Текущий шаг
    double hprev;           //Предыдущий шаг
    double s;               //S оценка ЛП
    double minS,maxS;       //Макс. и Мин. |S|
    double xminS,xmaxS;     //Точки в которых |S| максимально(минимально)
    double minH,maxH;       //Макс. и Мин. H
    double xminH,xmaxH;     //
    double end;             //Граничная точка
    double epsBrd,epsCtrl;  //Параметры контроля выхода на границу и контроля погрешности
    int maxStep;            //Максимальное число шагов

    model2() {}                                  //Констуктор
    double f1(double x,double v1,double v2);
    double f2(double x,double v1,double v2);

    void set(double i_x0,double i_u10, double i_u20,
          double i_h, double i_end, double i_epsBrd,
          double i_epsCtrl, int i_maxStep, bool i_isStepFixed,
          double i_a, double i_b);
    void start();   //Начать счёт
    void stop();    //Остановить счёт
    void countNext(double& v1,double& v2,double th, double tx, double tv1, double tv2);          //Посчитать следующую точку
    void halfStepCountNext(double& v1, double& v2,double th, double tx, double tv1,double tv2);  //Посчитать следующую точку с вдвое меньшим шагом
    int ctrlLocalErr();   //Контроль локальной погрешности
    void halveStep();     //Поделить шаг пополам
    void doubleStep();    //Удвоить шаг
    void iterate(int dir);

};
