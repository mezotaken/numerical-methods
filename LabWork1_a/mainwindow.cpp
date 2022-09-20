#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"







static model0 testmd;    //Модель
static model1 md1;
static model2 md2;

int numbGraph = 0;
int numbGraph1 = 0;
int numbGraph2 = 0;

void MainWindow::paintGraph0(QTableWidget* src, int N, int numbGraph)
{

    QVector<double> X(N);
    QVector<double> Y(N);
    QVector<double> E(N);
    QVector<double> U(N);
    QVector<double> e(N);

    QPen pen;
    QPen upen;


    pen.setColor(Qt::GlobalColor(numbGraph+7));
    upen.setStyle(Qt::DotLine);
    upen.setColor(Qt::GlobalColor(numbGraph+7));

    for(int i = 0; i < N; i++){
        X[i] = src->item(i,0)->text().toDouble();
        Y[i] = src->item(i,1)->text().toDouble();
        E[i] = src->item(i,8)->text().toDouble() - ui->tableWidget->item(i,1)->text().toDouble();
        U[i] = src->item(i,8)->text().toDouble();
        e[i] = src->item(i,4)->text().toDouble()*16;
        }



    ui->graph->addGraph();

    ui->graph->addGraph();
    ui->errGraph->addGraph();
    ui->errGraph->addGraph();
    ui->graph->graph(2*numbGraph)->setData(X,Y);
    ui->graph->graph(2*numbGraph)->setPen(pen);
    ui->graph->graph(2*numbGraph)->setName(QString("Числ. траект %1 (e)").arg(numbGraph+1));
    ui->graph->graph(2*numbGraph+1)->setData(X,U);
    ui->graph->graph(2*numbGraph+1)->setPen(upen);
    ui->graph->graph(2*numbGraph+1)->setName(QString("Точн. траект %1 (E)").arg(numbGraph+1));
    ui->errGraph->graph(2*numbGraph)->setData(X,E);
    ui->errGraph->graph(2*numbGraph)->setPen(upen);
    ui->errGraph->graph(2*numbGraph+1)->setData(X,e);
    ui->errGraph->graph(2*numbGraph+1)->setPen(pen);

    ui->graph->xAxis->setRange(X[0],X[N-1]);
    ui->errGraph->xAxis->setRange(X[0],X[N-1]);

    double minY = Y[0], maxY = Y[0], minE = E[0], maxE = E[0];
    for(int i = 1; i < N; i++)
    {
        if(Y[i]<minY) minY = Y[i];
        if(Y[i]>maxY) maxY = Y[i];
        if(E[i]<minE) minE = E[i];
        if(E[i]>maxE) maxE = E[i];
    }

    ui->graph->yAxis->setRange(minY, maxY);
    ui->errGraph->yAxis->setRange(minE, maxE);
    ui->graph->legend->setVisible(true);

    ui->graph->replot();
    ui->errGraph->replot();
}

void MainWindow::paintGraph1(QTableWidget* src, int N, int numbGraph)
{

    QVector<double> X(N);
    QVector<double> Y(N);
    QVector<double> e(N);

    QPen pen;


    pen.setColor(Qt::GlobalColor(numbGraph+7));
    for(int i = 0; i < N; i++){
        X[i] = src->item(i,0)->text().toDouble();
        Y[i] = src->item(i,1)->text().toDouble();
        e[i] = src->item(i,4)->text().toDouble()*16;
        }



    ui->graph_2->addGraph();

    ui->errGraph_2->addGraph();
    ui->graph_2->graph(numbGraph)->setData(X,Y);
    ui->graph_2->graph(numbGraph)->setPen(pen);
    ui->graph_2->graph(numbGraph)->setName(QString("Числ. траект %1 (e)").arg(numbGraph+1));
    ui->errGraph_2->graph(numbGraph)->setData(X,e);
    ui->errGraph_2->graph(numbGraph)->setPen(pen);

    ui->graph_2->xAxis->setRange(X[0],X[N-1]);
    ui->errGraph_2->xAxis->setRange(X[0],X[N-1]);

    double minY = Y[0], maxY = Y[0], minE = e[0], maxE = e[0];
    for(int i = 1; i < N; i++)
    {
        if(Y[i]<minY) minY = Y[i];
        if(Y[i]>maxY) maxY = Y[i];
        if(e[i]<minE) minE = e[i];
        if(e[i]>maxE) maxE = e[i];
    }

    ui->graph_2->yAxis->setRange(minY, maxY);
    ui->errGraph_2->yAxis->setRange(minE, maxE);
    ui->graph_2->legend->setVisible(true);

    ui->graph_2->replot();
    ui->errGraph_2->replot();
}

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
    ui->errGraph_3->addGraph();
    ui->uxgraph->graph(numbGraph)->setData(X,V);
    ui->uxgraph->graph(numbGraph)->setPen(pen);
    ui->uxgraph->graph(numbGraph)->setName(QString("Числ. траект V(x) %1 (e)").arg(numbGraph+1));
    ui->usxgraph->graph(numbGraph)->setData(X,VS);
    ui->usxgraph->graph(numbGraph)->setPen(pen);
    ui->usxgraph->graph(numbGraph)->setName(QString("Числ. траект V '(x) %1 (e)").arg(numbGraph+1));
    ui->errGraph_3->graph(numbGraph)->setData(X,e);
    ui->errGraph_3->graph(numbGraph)->setPen(pen);

    ui->uxgraph->xAxis->setRange(X[0],X[N-1]);
    ui->usxgraph->xAxis->setRange(X[0],X[N-1]);
    ui->errGraph_3->xAxis->setRange(X[0],X[N-1]);

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
    ui->errGraph_3->yAxis->setRange(minE, maxE);
    ui->uxgraph->legend->setVisible(true);
    ui->usxgraph->legend->setVisible(true);

    ui->uxgraph->replot();
    ui->usxgraph->replot();
    ui->errGraph_3->replot();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("LabWork");


    //Инициализация таблицы
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v2_i"<<"v_i - v2_i"<<"S"<<"h_i"<<"C1"<<"C2"<<"u_i"<<"|u_i - v_i|");

    ui->tableWidget_2->setColumnCount(8);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v2_i"<<"v_i - v2_i"<<"S"<<"h_i"<<"C1"<<"C2");
    
    ui->tableWidget_3->setColumnCount(9);
    ui->tableWidget_3->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v'_i"<<"v_i - v2_i"<<"v'_i - v'2_i "<<"S"<<"h_i"<<"C1"<<"C2");
    //Инициализация основного графика
    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("V");
    ui->graph->setInteraction(QCP::iRangeZoom,true);
    ui->graph->setInteraction(QCP::iRangeDrag, true); // Включаем взаимодействие перетаскивания графика

    ui->graph_2->xAxis->setLabel("x");
    ui->graph_2->yAxis->setLabel("V");
    ui->graph_2->setInteraction(QCP::iRangeZoom,true);
    ui->graph_2->setInteraction(QCP::iRangeDrag, true); // Включаем взаимодействие перетаскивания графика

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

    ui->errGraph_2->xAxis->setLabel("x");
    ui->errGraph_2->yAxis->setLabel("err");
    ui->errGraph_2->setInteraction(QCP::iRangeZoom,true);
    ui->errGraph_2->setInteraction(QCP::iRangeDrag, true);

    ui->errGraph_3->xAxis->setLabel("x");
    ui->errGraph_3->yAxis->setLabel("err");
    ui->errGraph_3->setInteraction(QCP::iRangeZoom,true);
    ui->errGraph_3->setInteraction(QCP::iRangeDrag, true);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_triggered()
{
   QApplication::quit();
}





void MainWindow::on_startCount_clicked()
{
    QTableWidgetItem *tbl;
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v2_i"<<"v_i - v2_i"<<"S"<<"h_i"<<"C1"<<"C2"<<"u_i"<<"|u_i - v_i|");
    testmd.set(ui->x0fd->text().toDouble(), ui->u0fd->text().toDouble(),
           ui->stepfd->text().toDouble(), ui->endfd->text().toDouble(),
           ui->epsBrdfd->text().toDouble(), ui->epsCtrlfd->text().toDouble(),
           ui->maxStepfd->text().toInt(),ui->isStepFixedch->isChecked());
    testmd.start();
    ui->tableWidget->setRowCount(50);
    ui->Params->setDisabled(true);

    tbl = new QTableWidgetItem(QString::number(testmd.x));
    ui->tableWidget->setItem(0,0,tbl);
    tbl = new QTableWidgetItem(QString::number(testmd.v));
    ui->tableWidget->setItem(0,1,tbl);
    tbl = new QTableWidgetItem(QString::number(testmd.v));
    ui->tableWidget->setItem(0,2,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget->setItem(0,3,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget->setItem(0,4,tbl);
    tbl = new QTableWidgetItem(QString::number(testmd.h));
    ui->tableWidget->setItem(0,5,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget->setItem(0,6,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget->setItem(0,7,tbl);
    tbl = new QTableWidgetItem(QString::number(testmd.v));
    ui->tableWidget->setItem(0,8,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget->setItem(0,9,tbl);


    int i = 1;
    while(testmd.isRun && i<testmd.maxStep && testmd.end-testmd.x > testmd.epsBrd)
    {
        if(ui->tableWidget->rowCount() == i)
            ui->tableWidget->setRowCount(2*ui->tableWidget->rowCount());
        testmd.iterate();
        tbl = new QTableWidgetItem(QString::number(testmd.x));
        ui->tableWidget->setItem(i,0,tbl);
        tbl = new QTableWidgetItem(QString::number(testmd.v));
        ui->tableWidget->setItem(i,1,tbl);
        tbl = new QTableWidgetItem(QString::number(testmd.v2));
        ui->tableWidget->setItem(i,2,tbl);
        tbl = new QTableWidgetItem(QString::number(testmd.v - testmd.v2));
        ui->tableWidget->setItem(i,3,tbl);
        tbl = new QTableWidgetItem(QString::number(testmd.s));
        ui->tableWidget->setItem(i,4,tbl);
        tbl = new QTableWidgetItem(QString::number(testmd.hprev));
        ui->tableWidget->setItem(i,5,tbl);
        tbl = new QTableWidgetItem(QString::number(testmd.stDwn));
        ui->tableWidget->setItem(i,6,tbl);
        tbl = new QTableWidgetItem(QString::number(testmd.stUp));
        ui->tableWidget->setItem(i,7,tbl);
        tbl = new QTableWidgetItem(QString::number(testmd.u));
        ui->tableWidget->setItem(i,8,tbl);
        tbl = new QTableWidgetItem(QString::number(std::abs(testmd.E)));
        ui->tableWidget->setItem(i,9,tbl);

        QCoreApplication::processEvents();
        i++;
    }
        ui->stepUp->setText(QString::number(testmd.stUp));
        ui->stepDwn->setText(QString::number(testmd.stDwn));
        ui->maxS->setText(QString::number(testmd.maxS));
        ui->minS->setText(QString::number(testmd.minS));
        ui->xmaxS->setText(QString::number(testmd.xmaxS));
        ui->xminS->setText(QString::number(testmd.xminS));
        ui->maxH->setText(QString::number(testmd.maxH));
        ui->minH->setText(QString::number(testmd.minH));
        ui->xmaxH->setText(QString::number(testmd.xmaxH));
        ui->xminH->setText(QString::number(testmd.xminH));
        ui->maxE->setText(QString::number(testmd.maxE));
        ui->minE->setText(QString::number(testmd.minE));
        ui->xmaxE->setText(QString::number(testmd.xmaxE));
        ui->xminE->setText(QString::number(testmd.xminE));
        ui->n->setText(QString::number(i));
        ui->ebrd->setText(QString::number(testmd.end-testmd.x));
        ui->Params->setDisabled(false);
        testmd.stop();


       paintGraph0(ui->tableWidget,i,numbGraph);
       numbGraph++;


}

void MainWindow::on_stopCount_clicked()
{
    testmd.stop();
}

void MainWindow::on_clear_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v2_i"<<"v_i - v2_i"<<"S"<<"h_i"<<"C1"<<"C2"<<"u_i"<<"|u_i - v_i|");
    ui->stepUp->setText("");
    ui->stepDwn->setText("");
    ui->xmaxS->setText("");
    ui->maxS->setText("");
    ui->xminS->setText("");
    ui->minS->setText("");
    ui->xmaxE->setText("");
    ui->maxE->setText("");
    ui->xminE->setText("");
    ui->minE->setText("");
    ui->xmaxH->setText("");
    ui->maxH->setText("");
    ui->xminH->setText("");
    ui->minH->setText("");
    ui->tableWidget->setRowCount(0); //устанавливаем количество строк в ноль
    ui->graph->clearGraphs();
    ui->graph->replot();
    ui->errGraph->clearGraphs();
    ui->errGraph->replot();
    numbGraph = 0;
}






void MainWindow::on_startCount_2_clicked()
{
    QTableWidgetItem *tbl;
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v2_i"<<"v_i - v2_i"<<"S"<<"h_i"<<"C1"<<"C2");
    md1.set(ui->x0fd_2->text().toDouble(), ui->u0fd_2->text().toDouble(),
           ui->stepfd_2->text().toDouble(), ui->endfd_2->text().toDouble(),
           ui->epsBrdfd_2->text().toDouble(), ui->epsCtrlfd_2->text().toDouble(),
           ui->maxStepfd_2->text().toInt(),ui->isStepFixedch_2->isChecked());
    md1.start();
    ui->tableWidget_2->setRowCount(50);
    ui->Params_2->setDisabled(true);

    tbl = new QTableWidgetItem(QString::number(md1.x));
    ui->tableWidget_2->setItem(0,0,tbl);
    tbl = new QTableWidgetItem(QString::number(md1.v));
    ui->tableWidget_2->setItem(0,1,tbl);
    tbl = new QTableWidgetItem(QString::number(md1.v));
    ui->tableWidget_2->setItem(0,2,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget_2->setItem(0,3,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget_2->setItem(0,4,tbl);
    tbl = new QTableWidgetItem(QString::number(md1.h));
    ui->tableWidget_2->setItem(0,5,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget_2->setItem(0,6,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget_2->setItem(0,7,tbl);


    int i = 1;
    while(md1.isRun && i<md1.maxStep && md1.end-md1.x > md1.epsBrd)
    {
        if(ui->tableWidget_2->rowCount() == i)
            ui->tableWidget_2->setRowCount(2*ui->tableWidget_2->rowCount());
        md1.iterate();
        tbl = new QTableWidgetItem(QString::number(md1.x));
        ui->tableWidget_2->setItem(i,0,tbl);
        tbl = new QTableWidgetItem(QString::number(md1.v));
        ui->tableWidget_2->setItem(i,1,tbl);
        tbl = new QTableWidgetItem(QString::number(md1.v2));
        ui->tableWidget_2->setItem(i,2,tbl);
        tbl = new QTableWidgetItem(QString::number(md1.v - md1.v2));
        ui->tableWidget_2->setItem(i,3,tbl);
        tbl = new QTableWidgetItem(QString::number(md1.s));
        ui->tableWidget_2->setItem(i,4,tbl);
        tbl = new QTableWidgetItem(QString::number(md1.hprev));
        ui->tableWidget_2->setItem(i,5,tbl);
        tbl = new QTableWidgetItem(QString::number(md1.stDwn));
        ui->tableWidget_2->setItem(i,6,tbl);
        tbl = new QTableWidgetItem(QString::number(md1.stUp));
        ui->tableWidget_2->setItem(i,7,tbl);

        QCoreApplication::processEvents();
        i++;
    }
        ui->stepUp_2->setText(QString::number(md1.stUp));
        ui->stepDwn_2->setText(QString::number(md1.stDwn));
        ui->maxS_2->setText(QString::number(md1.maxS));
        ui->minS_2->setText(QString::number(md1.minS));
        ui->xmaxS_2->setText(QString::number(md1.xmaxS));
        ui->xminS_2->setText(QString::number(md1.xminS));
        ui->maxH_2->setText(QString::number(md1.maxH));
        ui->minH_2->setText(QString::number(md1.minH));
        ui->xmaxH_2->setText(QString::number(md1.xmaxH));
        ui->xminH_2->setText(QString::number(md1.xminH));
        ui->n_2->setText(QString::number(i));
        ui->ebrd_2->setText(QString::number(md1.end-md1.x));
        ui->Params_2->setDisabled(false);
        md1.stop();


       paintGraph1(ui->tableWidget_2,i,numbGraph1);
       numbGraph1++;
}

void MainWindow::on_stopCount_2_clicked()
{
    md1.stop();
}

void MainWindow::on_clear_2_clicked()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v2_i"<<"v_i - v2_i"<<"S"<<"h_i"<<"C1"<<"C2");
    ui->stepUp_2->setText("");
    ui->stepDwn_2->setText("");
    ui->xmaxS_2->setText("");
    ui->maxS_2->setText("");
    ui->xminS_2->setText("");
    ui->minS_2->setText("");
    ui->xmaxH_2->setText("");
    ui->maxH_2->setText("");
    ui->xminH_2->setText("");
    ui->minH_2->setText("");
    ui->tableWidget_2->setRowCount(0); //устанавливаем количество строк в ноль
    ui->graph_2->clearGraphs();
    ui->graph_2->replot();
    ui->errGraph_2->clearGraphs();
    ui->errGraph_2->replot();
    numbGraph1 = 0;
}





void MainWindow::on_startCount_3_clicked()
{
    QTableWidgetItem *tbl;
    ui->tableWidget_3->clear();
    ui->tableWidget_3->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v'_i"<<"v_i - v2_i"<<"v'_i - v'2_i "<<"S"<<"h_i"<<"C1"<<"C2");
    md2.set(ui->x0fd_3->text().toDouble(), ui->u0fd_3->text().toDouble(),ui->u0sfd_3->text().toDouble(),
           ui->stepfd_3->text().toDouble(), ui->endfd_3->text().toDouble(),
           ui->epsBrdfd_3->text().toDouble(), ui->epsCtrlfd_3->text().toDouble(),
           ui->maxStepfd_3->text().toInt(),ui->isStepFixedch_3->isChecked(),ui->afd->text().toDouble(),ui->bfd->text().toDouble());
    md2.start();


    ui->tableWidget_3->setRowCount(50);
    ui->Params_3->setDisabled(true);

    tbl = new QTableWidgetItem(QString::number(md2.x));
    ui->tableWidget_3->setItem(0,0,tbl);
    tbl = new QTableWidgetItem(QString::number(md2.v1));
    ui->tableWidget_3->setItem(0,1,tbl);
    tbl = new QTableWidgetItem(QString::number(md2.v2));
    ui->tableWidget_3->setItem(0,2,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget_3->setItem(0,3,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget_3->setItem(0,4,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget_3->setItem(0,5,tbl);
    tbl = new QTableWidgetItem(QString::number(md2.h));
    ui->tableWidget_3->setItem(0,6,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget_3->setItem(0,7,tbl);
    tbl = new QTableWidgetItem("0");
    ui->tableWidget_3->setItem(0,7,tbl);


    int i = 1;
    while(md2.isRun && i<md2.maxStep && md2.end-md2.x > md2.epsBrd)
    {
        if(ui->tableWidget_3->rowCount() == i)
            ui->tableWidget_3->setRowCount(2*ui->tableWidget_3->rowCount());
        md2.iterate(1);
        tbl = new QTableWidgetItem(QString::number(md2.x));
        ui->tableWidget_3->setItem(i,0,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.v1));
        ui->tableWidget_3->setItem(i,1,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.v2));
        ui->tableWidget_3->setItem(i,2,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.v12 - md2.v1));
        ui->tableWidget_3->setItem(i,3,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.v22-md2.v2));
        ui->tableWidget_3->setItem(i,4,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.s));
        ui->tableWidget_3->setItem(i,5,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.hprev));
        ui->tableWidget_3->setItem(i,6,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.stDwn));
        ui->tableWidget_3->setItem(i,7,tbl);
        tbl = new QTableWidgetItem(QString::number(md2.stUp));
        ui->tableWidget_3->setItem(i,8,tbl);

        QCoreApplication::processEvents();
        i++;
    }
        ui->stepUp_3->setText(QString::number(md2.stUp));
        ui->stepDwn_3->setText(QString::number(md2.stDwn));
        ui->maxS_3->setText(QString::number(md2.maxS));
        ui->minS_3->setText(QString::number(md2.minS));
        ui->xmaxS_3->setText(QString::number(md2.xmaxS));
        ui->xminS_3->setText(QString::number(md2.xminS));
        ui->maxH_3->setText(QString::number(md2.maxH));
        ui->minH_3->setText(QString::number(md2.minH));
        ui->xmaxH_3->setText(QString::number(md2.xmaxH));
        ui->xminH_3->setText(QString::number(md2.xminH));
        ui->n_3->setText(QString::number(i));
        ui->ebrd_3->setText(QString::number(md2.end-md2.x));
        ui->Params_3->setDisabled(false);
        md2.stop();


       paintGraph2(ui->tableWidget_3,i,numbGraph2);
       numbGraph2++;
}

void MainWindow::on_stopCount_3_clicked()
{
    md2.stop();
}

void MainWindow::on_clear_3_clicked()
{
    ui->tableWidget_3->clear();
    ui->tableWidget_3->setHorizontalHeaderLabels(QStringList() << "x_i" << "v_i"<<"v'_i"<<"v_i - v2_i"<<"v'_i - v'2_i "<<"S"<<"h_i"<<"C1"<<"C2");
    ui->stepUp_3->setText("");
    ui->stepDwn_3->setText("");
    ui->xmaxS_3->setText("");
    ui->maxS_3->setText("");
    ui->xminS_3->setText("");
    ui->minS_3->setText("");
    ui->xmaxH_3->setText("");
    ui->maxH_3->setText("");
    ui->xminH_3->setText("");
    ui->minH_3->setText("");
    ui->tableWidget_3->setRowCount(0); //устанавливаем количество строк в ноль
    ui->uxgraph->clearGraphs();
    ui->uxgraph->replot();
    ui->usxgraph->clearGraphs();
    ui->usxgraph->replot();
    ui->uusgraph->clearPlottables();
    ui->uusgraph->replot();
    ui->errGraph_3->clearGraphs();
    ui->errGraph_3->replot();
    numbGraph2 = 0;
}



void MainWindow::on_phaseport_clicked()
{
    ui->uusgraph->clearPlottables();
    ui->uusgraph->replot();

    QCPCurve* test[400];
    QVector<double> X(100);
    QVector<double> V(100);
    QVector<double> VS(100);
    QPen pen;
    pen.setColor(Qt::GlobalColor(7));
    ui->uusgraph->xAxis->setRange(-10,10);
    ui->uusgraph->yAxis->setRange(-10,10);
    int count = 0;
    for(int i =-10; i<11; i+=2)
        for(int k = -10; k<11;k+=2)
    {
        md2.set(0, i,k,
               0.001, 1000,
               1e-6, 1e-7,
               100,false,ui->afd->text().toDouble(),ui->bfd->text().toDouble());
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
               0.001, 1000,
               1e-6, 1e-7,
               100,false,ui->afd->text().toDouble(),ui->bfd->text().toDouble());
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
