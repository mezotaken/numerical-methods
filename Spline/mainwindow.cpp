#include "mainwindow.h"
#include "splinemodel.h"
#include "ui_mainwindow.h"
#include <qmath.h>

static splinemodel spl;

void MainWindow::paintGraph(QCustomPlot* dst,QVector<double>&X,QVector<double>& F,QVector<double>& S)
{
    QPen pen;
    pen.setColor(Qt::GlobalColor(7));
    dst->clearGraphs();

    dst->addGraph();
    dst->addGraph();

    dst->graph(0)->setData(X,F);
    dst->graph(1)->setData(X,S);
    dst->graph(1)->setPen(pen);

    double minF = F[0], maxF = F[0];
    for(int i = 1; i < F.size(); i++)
    {
        if(F[i]<minF) minF = F[i];
        if(F[i]>maxF) maxF = F[i];
    }

    dst->graph(0)->setName(QString("F"));
    dst->graph(1)->setName(QString("S"));
    dst->legend->setVisible(true);
    dst->xAxis->setRange(X[0],X[X.size()-1]);
    dst->yAxis->setRange(minF,maxF);
    dst->replot();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Spline Labwork");
    ui->splineTable->setColumnCount(5);
    ui->splineTable->setHorizontalHeaderLabels(QStringList()<< "i"<<"a_i"<<"b_i"<<"c_i"<<"d_i");
    ui->splineTable->verticalHeader()->setVisible(false);
    ui->splineTable->setColumnWidth(0,30);

    ui->errorTable->setColumnCount(11);
    ui->errorTable->setHorizontalHeaderLabels(QStringList()<< "№"<<"x"<<"f(x)"<<"S(x)"<<"|f(x)-S(x)|"<<"f'(x)"
                                               <<"S'(x)"<<"|f'(x)-S'(x)|"<<"f''(x)"<<"S''(x)"<<"|f''(x)-S''(x)|");
    ui->errorTable->verticalHeader()->setVisible(false);
    ui->errorTable->setColumnWidth(0,30);

    ui->funcPar->addItem("x^3+3x^2, x<=0\n-x^3+3x^2, x>=0");
    ui->funcPar->addItem("cos(e^x)");
    ui->funcPar->addItem("cos(e^x)+cos(10x)");
    ui->funcPar->addItem("cos(e^x)+cos(100x)");



    ui->graph0->setInteraction(QCP::iRangeZoom,true);
    ui->graph0->setInteraction(QCP::iRangeDrag, true);
    ui->graph1->setInteraction(QCP::iRangeZoom,true);
    ui->graph1->setInteraction(QCP::iRangeDrag, true);
    ui->graph2->setInteraction(QCP::iRangeZoom,true);
    ui->graph2->setInteraction(QCP::iRangeDrag, true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Нажатие на кнопку Старт
void MainWindow::on_startButton_clicked()
{
    //Рассчёт сплайна и занесение в таблицу коэффициентов
    int n = ui->numMainGrid->text().toInt();
    int N = ui->numAuxGrid->text().toInt();
    ui->splineTable->setRowCount(n);
    ui->errorTable->setRowCount(N+1);
    QTableWidgetItem *tbl;
    QVector<QVector<double>> coeff;
    QVector<double> X;

    spl.formspline(ui->funcPar->currentIndex(),
                   ui->a_rangePar->text().toDouble(),
                   ui->b_rangePar->text().toDouble(),
                   n,
                   ui->a_brdPar->text().toDouble(),
                   ui->b_brdPar->text().toDouble(),
                   X,
                   coeff);

    for(int i = 1; i<n+1;i++)
    {
        tbl = new QTableWidgetItem(QString::number(i));
        ui->splineTable->setItem(i-1,0,tbl);
        tbl = new QTableWidgetItem(QString::number(coeff[i][0]));
        ui->splineTable->setItem(i-1,1,tbl);
        tbl = new QTableWidgetItem(QString::number(coeff[i][1]));
        ui->splineTable->setItem(i-1,2,tbl);
        tbl = new QTableWidgetItem(QString::number(coeff[i][2]));
        ui->splineTable->setItem(i-1,3,tbl);
        tbl = new QTableWidgetItem(QString::number(coeff[i][3]));
        ui->splineTable->setItem(i-1,4,tbl);
    }

    //Оценка всех погрешностей
    QVector<double> Xaux,F0,F1,F2,S0,S1,S2,FS0,FS1,FS2;
    spl.errorcalc(ui->funcPar->currentIndex(),
                  ui->a_rangePar->text().toDouble(),
                  ui->b_rangePar->text().toDouble(),
                  X, coeff,N,
                  Xaux,F0,S0,FS0,F1,S1,FS1,F2,S2,FS2);
    double maxFS0 = FS0[0],xmaxFS0 = Xaux[0],maxFS1 = FS1[0],
           xmaxFS1 = Xaux[0],maxFS2 = FS2[0],xmaxFS2 = Xaux[0];
    for(int i = 0;i<N+1;i++)
    {
        tbl = new QTableWidgetItem(QString::number(i));
        ui->errorTable->setItem(i,0,tbl);
        tbl = new QTableWidgetItem(QString::number(Xaux[i]));
        ui->errorTable->setItem(i,1,tbl);
        tbl = new QTableWidgetItem(QString::number(F0[i]));
        ui->errorTable->setItem(i,2,tbl);
        tbl = new QTableWidgetItem(QString::number(S0[i]));
        ui->errorTable->setItem(i,3,tbl);
        tbl = new QTableWidgetItem(QString::number(FS0[i]));
        ui->errorTable->setItem(i,4,tbl);

        tbl = new QTableWidgetItem(QString::number(F1[i]));
        ui->errorTable->setItem(i,5,tbl);
        tbl = new QTableWidgetItem(QString::number(S1[i]));
        ui->errorTable->setItem(i,6,tbl);
        tbl = new QTableWidgetItem(QString::number(FS1[i]));
        ui->errorTable->setItem(i,7,tbl);

        tbl = new QTableWidgetItem(QString::number(F2[i]));
        ui->errorTable->setItem(i,8,tbl);
        tbl = new QTableWidgetItem(QString::number(S2[i]));
        ui->errorTable->setItem(i,9,tbl);
        tbl = new QTableWidgetItem(QString::number(FS2[i]));
        ui->errorTable->setItem(i,10,tbl);

        if(FS0[i]>maxFS0)
        {
           maxFS0 = FS0[i];
           xmaxFS0 = Xaux[i];
        }


        if(FS1[i]>maxFS1)
        {
           maxFS1 = FS1[i];
           xmaxFS1 = Xaux[i];
        }

        if(FS2[i]>maxFS2)
        {
           maxFS2 = FS2[i];
           xmaxFS2 = Xaux[i];
        }
    }

}

//Если изменить функцию
void MainWindow::on_funcPar_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->a_rangePar->setText(QString::number(-1));
        ui->b_rangePar->setText(QString::number(1));
    break;
    default:
        ui->a_rangePar->setText(QString::number(1));
        ui->b_rangePar->setText(QString::number(M_PI));
    break;
    }
    if(ui->brdCondPar->currentIndex() == 1)
    {
        ui->a_brdPar->setText(QString::number(  spl.funclist(index,2,ui->a_rangePar->text().toDouble())  ));
        ui->b_brdPar->setText(QString::number(  spl.funclist(index,2,ui->b_rangePar->text().toDouble())  ));
    }
}

//Если изменить тип граничных условий
void MainWindow::on_brdCondPar_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->a_brdPar->setDisabled(true);
        ui->b_brdPar->setDisabled(true);
        ui->a_brdPar->setText(QString::number(0));
        ui->b_brdPar->setText(QString::number(0));
    break;
    case 1:
        ui->a_brdPar->setDisabled(true);
        ui->b_brdPar->setDisabled(true);
        ui->a_brdPar->setText(QString::number(  spl.funclist(ui->funcPar->currentIndex(),2,ui->a_rangePar->text().toDouble())  ));
        ui->b_brdPar->setText(QString::number(  spl.funclist(ui->funcPar->currentIndex(),2,ui->b_rangePar->text().toDouble())  ));
    break;
    case 2:
        ui->a_brdPar->setDisabled(false);
        ui->b_brdPar->setDisabled(false);
    break;
    }
}

void MainWindow::on_clearButton_clicked()
{

}
