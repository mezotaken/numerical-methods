#include "mainwindow.h"
#include "model.h"
#include "ui_mainwindow.h"


static modeltest1 mdtest1;
static modeltest2 mdtest2;
static modelmain mdmain;

void MainWindow::paintGraph(QCustomPlot* dst,QCustomPlot* dsterr,QVector<double>& X,QVector<double>& V,QVector<double>& U)
{
    QPen pen;
    pen.setColor(Qt::GlobalColor(7));

    dst->clearGraphs();
    dsterr->clearGraphs();
    QVector<double> err(X.size());
    for(int i = 0;i<X.size();i++)
        err[i] = U[i]-V[i];
    dst->addGraph();
    dst->addGraph();
    dst->graph(0)->setData(X,V);
    dst->graph(1)->setData(X,U);
    dst->graph(1)->setPen(pen);
    double minE = err[0], maxE = err[0];
    for(int i = 1; i < err.size(); i++)
    {
        if(err[i]<minE) minE = err[i];
        if(err[i]>maxE) maxE = err[i];
    }
    dsterr->addGraph();
    dsterr->graph(0)->setPen(pen);
    dsterr->graph(0)->setData(X,err);
    dst->graph(0)->setName(QString("Числ. траект V(x)"));
    dst->graph(1)->setName(QString("Точн. траект U(x)"));
    dsterr->graph(0)->setName(QString("err"));
    dst->legend->setVisible(true);
    dsterr->legend->setVisible(true);
    dst->xAxis->setRange(X[0],X[X.size()-1]);
    dsterr->xAxis->setRange(X[0],X[X.size()-1]);
    dsterr->yAxis->setRange(minE,maxE);
    dst->replot();
    dsterr->replot();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("LabWork4");

    ui->table1->setColumnCount(5);
    ui->table1->setHorizontalHeaderLabels(QStringList()<< "№ узла"<<"x_i" <<"u(x_i)"<<"v(x_i)"<<"u(x_i)-v(x_i)");
    ui->table1->verticalHeader()->setVisible(false);

    ui->table2->setColumnCount(5);
    ui->table2->setHorizontalHeaderLabels(QStringList()<< "№ узла"<<"x_i" <<"u(x_i)"<<"v(x_i)"<<"u(x_i)-v(x_i)");
    ui->table2->verticalHeader()->setVisible(false);

    ui->table0->setColumnCount(5);
    ui->table0->setHorizontalHeaderLabels(QStringList()<< "№ узла"<<"x_i" <<"v(x_i)"<<"v2(x_i)"<<"v(x_i)-v2(x_i)");
    ui->table0->verticalHeader()->setVisible(false);

    ui->graph0->xAxis->setLabel("x");
    ui->graph0->yAxis->setLabel("V");
    ui->grapherr0->xAxis->setLabel("x");
    ui->grapherr0->yAxis->setLabel("err");

    ui->grapherr0->setInteraction(QCP::iRangeZoom,true);
    ui->grapherr0->setInteraction(QCP::iRangeDrag, true);
    ui->graph0->setInteraction(QCP::iRangeZoom,true);
    ui->graph0->setInteraction(QCP::iRangeDrag, true);

    ui->graph1->xAxis->setLabel("x");
    ui->graph1->yAxis->setLabel("V");
    ui->grapherr1->xAxis->setLabel("x");
    ui->grapherr1->yAxis->setLabel("err");
    ui->graph1->setInteraction(QCP::iRangeZoom,true);
    ui->graph1->setInteraction(QCP::iRangeDrag, true);
    ui->grapherr1->setInteraction(QCP::iRangeZoom,true);
    ui->grapherr1->setInteraction(QCP::iRangeDrag, true);

    ui->graph2->xAxis->setLabel("x");
    ui->graph2->yAxis->setLabel("V");
    ui->grapherr2->xAxis->setLabel("x");
    ui->grapherr2->yAxis->setLabel("err");
    ui->grapherr2->setInteraction(QCP::iRangeZoom,true);
    ui->grapherr2->setInteraction(QCP::iRangeDrag, true);
    ui->graph2->setInteraction(QCP::iRangeZoom,true);
    ui->graph2->setInteraction(QCP::iRangeDrag, true);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start1_clicked()
{
    QTableWidgetItem *tbl;
    QVector<double> X;
    QVector<double> V;
    QVector<double> U;

    int n = ui->n1fd->text().toInt();

    mdtest1.calculate(n,X,V);
    mdtest1.CorrectSol(n,U);
    double maxe = std::abs(U[0]-V[0]);
    int mind = 0;
    ui->table1->setRowCount(n+1);
    for(int i = 0;i<n+1;i++)
    {
        tbl = new QTableWidgetItem(QString::number(i));
        ui->table1->setItem(i,0,tbl);
        tbl = new QTableWidgetItem(QString::number(X[i]));
        ui->table1->setItem(i,1,tbl);
        tbl = new QTableWidgetItem(QString::number(U[i]));
        ui->table1->setItem(i,2,tbl);
        tbl = new QTableWidgetItem(QString::number(V[i]));
        ui->table1->setItem(i,3,tbl);
        tbl = new QTableWidgetItem(QString::number(U[i] - V[i]));
        ui->table1->setItem(i,4,tbl);
        if(std::abs(U[i]-V[i]) > maxe)
        {
            maxe = std::abs(U[i]-V[i]);
            mind = i;
        }
    }
    paintGraph(ui->graph1,ui->grapherr1,X,V,U);
    ui->me1lb->setText(QString::number(maxe));
    ui->mex1lb->setText(QString::number(X[mind]));
}


void MainWindow::on_clear1_clicked()
{
    ui->me1lb->clear();
    ui->mex1lb->clear();
    ui->table1->clear();
    ui->table1->setHorizontalHeaderLabels(QStringList()<< "№ узла"<<"x_i" <<"u(x_i)"<<"v(x_i)"<<"u(x_i)-v(x_i)");
    ui->graph1->clearGraphs();
    ui->grapherr1->clearGraphs();
    ui->graph1->replot();
    ui->grapherr1->replot();
}

void MainWindow::on_start2_clicked()
{
    QTableWidgetItem *tbl;
    QVector<double> X;
    QVector<double> V;
    QVector<double> U;
    int n = ui->n2fd->text().toInt();

    mdtest2.calculate(n,X,V);
    mdtest2.CorrectSol(n,U);

    double maxe = std::abs(U[0]-V[0]);
    int mind = 0;
    ui->table2->setRowCount(n+1);
    for(int i = 0;i<n+1;i++)
    {
        tbl = new QTableWidgetItem(QString::number(i));
        ui->table2->setItem(i,0,tbl);
        tbl = new QTableWidgetItem(QString::number(X[i]));
        ui->table2->setItem(i,1,tbl);
        tbl = new QTableWidgetItem(QString::number(U[i]));
        ui->table2->setItem(i,2,tbl);
        tbl = new QTableWidgetItem(QString::number(V[i]));
        ui->table2->setItem(i,3,tbl);
        tbl = new QTableWidgetItem(QString::number(U[i] - V[i]));
        ui->table2->setItem(i,4,tbl);
        if(std::abs(U[i]-V[i]) > maxe)
        {
            maxe = std::abs(U[i]-V[i]);
            mind = i;
        }
    }

    paintGraph(ui->graph2,ui->grapherr2,X,V,U);
    ui->me2lb->setText(QString::number(maxe));
    ui->mex2lb->setText(QString::number(X[mind]));
}



void MainWindow::on_clear2_clicked()
{
    ui->table2->clear();
    ui->table2->setHorizontalHeaderLabels(QStringList()<< "№ узла"<<"x_i" <<"u(x_i)"<<"v(x_i)"<<"u(x_i)-v(x_i)");
    ui->me2lb->clear();
    ui->mex2lb->clear();
    ui->graph2->clearGraphs();
    ui->grapherr2->clearGraphs();
    ui->graph2->replot();
    ui->grapherr2->replot();
}

void MainWindow::on_start0_clicked()
{
    QTableWidgetItem *tbl;
    QVector<double> X;
    QVector<double> V;
    QVector<double> V2;
    int n = ui->n0fd->text().toInt();
    mdmain.calculate(2*n,X,V2);
    X.clear();
    mdmain.calculate(n,X,V);


    double maxe = std::abs(V[0]-V2[0]);
    int mind = 0;
    ui->table0->setRowCount(n+1);
    for(int i = 0;i<n+1;i++)
    {
        tbl = new QTableWidgetItem(QString::number(i));
        ui->table0->setItem(i,0,tbl);
        tbl = new QTableWidgetItem(QString::number(X[i]));
        ui->table0->setItem(i,1,tbl);
        tbl = new QTableWidgetItem(QString::number(V[i]));
        ui->table0->setItem(i,2,tbl);
        tbl = new QTableWidgetItem(QString::number(V2[2*i]));
        ui->table0->setItem(i,3,tbl);
        tbl = new QTableWidgetItem(QString::number(V[i] - V2[2*i]));
        ui->table0->setItem(i,4,tbl);
        if(std::abs(V[i]-V2[2*i]) > maxe)
        {
            maxe = std::abs(V[i]-V2[2*i]);
            mind = i;
        }
    }
    QVector<double> V2set(X.size());
    for(int i = 0;i<X.size();i++)
    {
        V2set[i] = V2[2*i];
    }
    paintGraph(ui->graph0,ui->grapherr0,X,V,V2set);
    ui->me0lb->setText(QString::number(maxe));
    ui->mex0lb->setText(QString::number(X[mind]));
}

void MainWindow::on_clear0_clicked()
{
    ui->table0->clear();
    ui->mex0lb->clear();
    ui->table0->setHorizontalHeaderLabels(QStringList()<< "№ узла"<<"x_i" <<"v(x_i)"<<"v2(x_i)"<<"v(x_i)-v2(x_i)");
    ui->me0lb->clear();
    ui->graph0->clearGraphs();
    ui->grapherr0->clearGraphs();
    ui->graph0->replot();
    ui->grapherr0->replot();
}


void MainWindow::on_exit_triggered()
{
   QApplication::quit();
}
