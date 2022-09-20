#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"


static model2 md2;

int numbGraph2 = 0;

void MainWindow::paintGraph2(QTableWidget* src, int N, int numbGraph)
{
    QVector<double> X(N);
    QVector<double> V(N);
    QVector<double> VS(N);
    QVector<double> e(N);

    QPen pen;


    pen.setColor(Qt::GlobalColor(numbGraph+7));
    for(int i = 0; i < N; i++){
        X[i] = src->item(i,0)->text().toDouble();
        V[i] = src->item(i,1)->text().toDouble();
        VS[i] = src->item(i,2)->text().toDouble();
        e[i] = src->item(i,5)->text().toDouble()*16;
        }



    ui->uxgraph->addGraph();
    ui->usxgraph->addGraph();
    ui->errGraph->addGraph();
    ui->uxgraph->graph(numbGraph)->setData(X,V);
    ui->uxgraph->graph(numbGraph)->setPen(pen);
    ui->uxgraph->graph(numbGraph)->setName(QString("Числ. траект V(x) %1 (e)").arg(numbGraph+1));
    ui->usxgraph->graph(numbGraph)->setData(X,VS);
    ui->usxgraph->graph(numbGraph)->setPen(pen);
    ui->usxgraph->graph(numbGraph)->setName(QString("Числ. траект V '(x) %1 (e)").arg(numbGraph+1));
    ui->errGraph->graph(numbGraph)->setData(X,e);
    ui->errGraph->graph(numbGraph)->setPen(pen);

    ui->uxgraph->xAxis->setRange(X[0],X[N-1]);
    ui->usxgraph->xAxis->setRange(X[0],X[N-1]);
    ui->errGraph->xAxis->setRange(X[0],X[N-1]);

    double minV = V[0], maxV = V[0], minE = e[0], maxE = e[0],minVS = VS[0],maxVS = VS[0];
    for(int i = 1; i < N; i++)
    {
        if(V[i]<minV) minV = V[i];
        if(V[i]>maxV) maxV = V[i];
        if(VS[i]<minVS) minVS = VS[i];
        if(VS[i]>maxVS) maxVS = VS[i];
        if(e[i]<minE) minE = e[i];
        if(e[i]>maxE) maxE = e[i];
    }

    ui->uxgraph->yAxis->setRange(minV, maxV);
    ui->usxgraph->yAxis->setRange(minVS, maxVS);
    ui->errGraph->yAxis->setRange(minE, maxE);
    ui->uxgraph->legend->setVisible(true);
    ui->usxgraph->legend->setVisible(true);

    ui->uxgraph->replot();
    ui->usxgraph->replot();
    ui->errGraph->replot();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("LabWork2");


    //Инициализация таблицы
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v'_i"<<"v2_i"<<"v'2_i "<<"S"<<"h_i");

    //Инициализация основного графика
    ui->uxgraph->xAxis->setLabel("x");
    ui->uxgraph->yAxis->setLabel("V");
    ui->uxgraph->setInteraction(QCP::iRangeZoom,true);
    ui->uxgraph->setInteraction(QCP::iRangeDrag, true); // Включаем взаимодействие перетаскивания графика

    ui->usxgraph->xAxis->setLabel("x");
    ui->usxgraph->yAxis->setLabel("V '");
    ui->usxgraph->setInteraction(QCP::iRangeZoom,true);
    ui->usxgraph->setInteraction(QCP::iRangeDrag, true); // Включаем взаимодействие перетаскивания графика

    ui->uusgraph->xAxis->setLabel("V");
    ui->uusgraph->yAxis->setLabel("V '");
    ui->uusgraph->setInteraction(QCP::iRangeZoom,true);
    ui->uusgraph->setInteraction(QCP::iRangeDrag, true); // Включаем взаимодействие перетаскивания графика

    //Инициализация графика погрешностей
    ui->errGraph->xAxis->setLabel("x");
    ui->errGraph->yAxis->setLabel("err");
    ui->errGraph->setInteraction(QCP::iRangeZoom,true);
    ui->errGraph->setInteraction(QCP::iRangeDrag, true);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_triggered()
{
   QApplication::quit();
}



void MainWindow::on_phaseport_clicked()
{
    ui->uusgraph->clearPlottables();
    ui->uusgraph->replot();
    int pc = 49;
    int len = 10000;
    QCPCurve* test[2*pc];
    QVector<double> X(len);
    QVector<double> V(len);
    QVector<double> VS(len);
    QPen pen;
    pen.setColor(Qt::GlobalColor(7));
    ui->uusgraph->xAxis->setRange(-10,10);
    ui->uusgraph->yAxis->setRange(-10,10);
    int count = 0;
    for(double i = -3; i<4; i+=1)
        for(double k = -3; k<4;k+=1)
    {
        md2.set(0, i,k,
               0.0001, 1000,
               1e-6, 1e-7,
               len,true,ui->kfd->text().toDouble(),ui->mfd->text().toDouble(),ui->ffd->text().toDouble());
        md2.start();
        X[0] = md2.x;
        V[0] = md2.v1;
        VS[0] = md2.v2;
        int j = 1;
        while(j<md2.maxStep)
        {
            md2.iterate(1);
            X[j] = md2.x;
            V[j] = md2.v1;
            VS[j] = md2.v2;
            QCoreApplication::processEvents();
            j++;
        }
        test[count] = new QCPCurve(ui->uusgraph->xAxis, ui->uusgraph->yAxis);
        test[count]->setData(X,V,VS);
        test[count]->setPen(pen);
        count++;

        md2.set(0,i,k,
               0.0001, 1000,
               1e-6, 1e-7,
               len,true,ui->kfd->text().toDouble(),ui->mfd->text().toDouble(),ui->ffd->text().toDouble());
        md2.start();
        X[0] = md2.x;
        V[0] = md2.v1;
        VS[0] = md2.v2;
        j = 1;
        while(j<md2.maxStep)
        {
            md2.iterate(-1);
            X[j] = md2.x;
            V[j] = md2.v1;
            VS[j] = md2.v2;
            QCoreApplication::processEvents();
            j++;
        }
        test[count] = new QCPCurve(ui->uusgraph->xAxis, ui->uusgraph->yAxis);
        test[count]->setData(X,V,VS);
        test[count]->setPen(pen);
    }
    ui->uusgraph->replot();
}

void MainWindow::on_startCount_clicked()
{
    QTableWidgetItem *tbl;
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v'_i"<<"v2_i"<<"v'2_i "<<"S"<<"h_i");
    md2.set(ui->x0fd->text().toDouble(), ui->u0fd->text().toDouble(),ui->u0sfd->text().toDouble(),
           ui->stepfd->text().toDouble(), ui->endfd->text().toDouble(),
           ui->epsBrdfd->text().toDouble(), ui->epsCtrlfd->text().toDouble(),
           ui->maxStepfd->text().toInt(),ui->isStepFixedch->isChecked(),
           ui->kfd->text().toDouble(),ui->mfd->text().toDouble(),ui->ffd->text().toDouble());
    md2.start();


    ui->tableWidget->setRowCount(50);
    ui->Params->setDisabled(true);

    tbl = new QTableWidgetItem(QString::number(md2.x));
    ui->tableWidget->setItem(0,0,tbl);
    tbl = new QTableWidgetItem(QString::number(md2.v1));
    ui->tableWidget->setItem(0,1,tbl);
    tbl = new QTableWidgetItem(QString::number(md2.v2));
    ui->tableWidget->setItem(0,2,tbl);
    tbl = new QTableWidgetItem(QString::number(md2.v1));
    ui->tableWidget->setItem(0,3,tbl);
    tbl = new QTableWidgetItem(QString::number(md2.v2));
    ui->tableWidget->setItem(0,4,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget->setItem(0,5,tbl);
    tbl = new QTableWidgetItem(QString::number(md2.h));
    ui->tableWidget->setItem(0,6,tbl);


    int i = 1;
    while(md2.isRun && i<md2.maxStep && md2.end-md2.x > md2.epsBrd)
    {
        if(ui->tableWidget->rowCount() == i)
            ui->tableWidget->setRowCount(2*ui->tableWidget->rowCount());
        md2.iterate(1);
        tbl = new QTableWidgetItem(QString::number(md2.x));
        ui->tableWidget->setItem(i,0,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.v1));
        ui->tableWidget->setItem(i,1,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.v2));
        ui->tableWidget->setItem(i,2,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.v12));
        ui->tableWidget->setItem(i,3,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.v22));
        ui->tableWidget->setItem(i,4,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.s));
        ui->tableWidget->setItem(i,5,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.hprev));
        ui->tableWidget->setItem(i,6,tbl);
        QCoreApplication::processEvents();
        i++;
    }
        ui->stepUp->setText(QString::number(md2.stUp));
        ui->stepDwn->setText(QString::number(md2.stDwn));
        ui->maxS->setText(QString::number(md2.maxS));
        ui->minS->setText(QString::number(md2.minS));
        ui->xmaxS->setText(QString::number(md2.xmaxS));
        ui->xminS->setText(QString::number(md2.xminS));
        ui->maxH->setText(QString::number(md2.maxH));
        ui->minH->setText(QString::number(md2.minH));
        ui->xmaxH->setText(QString::number(md2.xmaxH));
        ui->xminH->setText(QString::number(md2.xminH));
        ui->n->setText(QString::number(i));
        ui->ebrd->setText(QString::number(md2.end-md2.x));
        ui->Params->setDisabled(false);
        md2.stop();


        paintGraph2(ui->tableWidget,i,numbGraph2);
        numbGraph2++;
}

void MainWindow::on_stopCount_clicked()
{
     md2.stop();
}

void MainWindow::on_clear_clicked()
{
        ui->tableWidget->clear();
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v'_i"<<"v2_i"<<"v'2_i "<<"S"<<"h_i");
        ui->stepUp->setText("");
        ui->stepDwn->setText("");
        ui->xmaxS->setText("");
        ui->maxS->setText("");
        ui->xminS->setText("");
        ui->minS->setText("");
        ui->xmaxH->setText("");
        ui->maxH->setText("");
        ui->xminH->setText("");
        ui->minH->setText("");
        ui->tableWidget->setRowCount(0); //устанавливаем количество строк в ноль
        ui->uxgraph->clearGraphs();
        ui->uxgraph->replot();
        ui->usxgraph->clearGraphs();
        ui->usxgraph->replot();
        ui->uusgraph->clearPlottables();
        ui->uusgraph->replot();
        ui->errGraph->clearGraphs();
        ui->errGraph->replot();
        numbGraph2 = 0;
}
