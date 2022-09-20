#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"

static modelmain mainmd;
static modeltest testmd;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->v_table->horizontalHeader()->setVisible(false);
    ui->v_table->verticalHeader()->setVisible(false);
    ui->uv2_table->horizontalHeader()->setVisible(false);
    ui->uv2_table->verticalHeader()->setVisible(false);
    ui->r_table->horizontalHeader()->setVisible(false);
    ui->r_table->verticalHeader()->setVisible(false);
    ui->vv2_table->horizontalHeader()->setVisible(false);
    ui->vv2_table->verticalHeader()->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    QTableWidgetItem* tbl;
    int nx = ui->nx->text().toInt();
    int ny = ui->ny->text().toInt();
    double h = 2.0/nx;
    double k = 2.0/ny;
    int n_max = ui->steplim->text().toInt();
    double eps = ui->prec->text().toDouble();
    QVector<QVector<double>> V(nx+1,QVector<double>(ny+1));
    QVector<QVector<double>> f(nx,QVector<double>(ny));
    QVector<QVector<double>> rs(nx+1,QVector<double>(ny+1));

    QVector<QVector<double>> UV2(2*(nx+1),QVector<double>(2*(ny+1)));
    QVector<QVector<double>> fV2(2*nx,QVector<double>(2*ny));
    QVector<QVector<double>> rsV2(2*(nx+1),QVector<double>(2*(ny+1)));

    double eps_s,s, eps_sv2 = 0,sv2 = 0;
    int mult = 1;
    switch(ui->task->currentIndex()) {
        case 0:
            testmd.FillU(UV2,nx,ny);
            if(ui->method->currentIndex() == 0)
                testmd.Zeidel(V, f,rs, nx, ny, n_max, eps, s, eps_s);
            else
                testmd.MinR(V, f,rs, nx, ny, n_max, eps, s, eps_s);
            break;
        case 1:
            mult = 2;
            if(ui->method->currentIndex() == 0) {
                mainmd.Zeidel(UV2, fV2,rsV2, 2*nx, 2*ny, n_max, eps, sv2, eps_sv2);
                mainmd.Zeidel(V, f,rs, nx, ny, n_max, eps, s, eps_s);
            } else {
                mainmd.MinR(UV2, fV2,rsV2, 2*nx, 2*ny, n_max, eps, sv2, eps_sv2);
                mainmd.MinR(V, f,rs, nx, ny, n_max, eps, s, eps_s);
            }
            break;
        case 2:
            testmd.FillU_topright(UV2,nx,ny);
            if(ui->method->currentIndex() == 0)
                testmd.Zeidel_topright(V, f,rs, nx, ny, n_max, eps, s, eps_s);
            else
                testmd.MinR_topright(V, f,rs, nx, ny, n_max, eps, s, eps_s);
            break;
    }
    ui->eps_s->setText(QString::number(eps_s) + "(V), " + QString::number(eps_sv2) + "(V_2)");
    ui->s->setText(QString::number(s) + "(V), " + QString::number(sv2) + "(V_2)");

    ui->v_table->setColumnCount(nx+2);
    ui->v_table->setRowCount(ny+2);
    ui->uv2_table->setColumnCount(nx+2);
    ui->uv2_table->setRowCount(ny+2);
    ui->r_table->setColumnCount(nx+2);
    ui->r_table->setRowCount(ny+2);
    ui->vv2_table->setColumnCount(nx+2);
    ui->vv2_table->setRowCount(ny+2);

    for(int i = 0;i<nx+1;i++) {
        tbl = new QTableWidgetItem(QString::number(-1+i*h));
        ui->v_table->setItem(0,i+1,tbl);
        tbl = new QTableWidgetItem(QString::number(-1+i*h));
        ui->uv2_table->setItem(0,i+1,tbl);
        tbl = new QTableWidgetItem(QString::number(-1+i*h));
        ui->r_table->setItem(0,i+1,tbl);
        tbl = new QTableWidgetItem(QString::number(-1+i*h));
        ui->vv2_table->setItem(0,i+1,tbl);
    }
    for(int j = 0;j<ny+1;j++) {
        tbl = new QTableWidgetItem(QString::number(1-j*k));
        ui->v_table->setItem(j+1,0,tbl);
        tbl = new QTableWidgetItem(QString::number(1-j*k));
        ui->uv2_table->setItem(j+1,0,tbl);
        tbl = new QTableWidgetItem(QString::number(1-j*k));
        ui->r_table->setItem(j+1,0,tbl);
        tbl = new QTableWidgetItem(QString::number(1-j*k));
        ui->vv2_table->setItem(j+1,0,tbl);
    }

    double maxd = 0, cur;
    double maxd_x = 0,maxd_y = 0;
    double maxrs = 0, maxrsv2 = 0;
    for(int j = 0;j<ny+1;j++)
        for(int i = 0;i<nx+1;i++) {
           cur = UV2[i*mult][(ny-j)*mult];
           tbl = new QTableWidgetItem(QString::number(V[i][ny-j]));
           ui->v_table->setItem(j+1,i+1,tbl);
           tbl = new QTableWidgetItem(QString::number(cur));
           ui->uv2_table->setItem(j+1,i+1,tbl);
           tbl = new QTableWidgetItem(QString::number(cur-V[i][ny-j]));
           ui->vv2_table->setItem(j+1,i+1,tbl);
           tbl = new QTableWidgetItem(QString::number(rs[i][ny-j]));
           ui->r_table->setItem(j+1,i+1,tbl);

           if(std::abs(rs[i][ny-j]) > maxrs)
               maxrs = std::abs(rs[i][ny-j]);
           if(std::abs(rsV2[i*2][j*2]) > maxrsv2)
               maxrsv2 = std::abs(rsV2[i*2][j*2]);
           if(std::abs(rsV2[i*2+1][j*2]) > maxrsv2)
               maxrsv2 = std::abs(rsV2[i*2+1][j*2]);
           if(std::abs(rsV2[i*2][j*2+1]) > maxrsv2)
               maxrsv2 = std::abs(rsV2[i*2][j*2+1]);
           if(std::abs(rsV2[i*2+1][j*2+1]) > maxrsv2)
               maxrsv2 = std::abs(rsV2[i*2+1][j*2+1]);

           if(std::abs(cur-V[i][ny-j]) > maxd) {
               maxd = std::abs(cur-V[i][ny-j]);
               maxd_x = -1+i*h; maxd_y = -1 + (ny-j)*k;
           }



        }
    ui->maxr->setText(QString::number(maxrs) + "(V), " + QString::number(maxrsv2) + "(V_2)");
    ui->maxd->setText(QString::number(maxd));
    ui->maxd_point->setText("x: " + QString::number(maxd_x) + ", y: " + QString::number(maxd_y));
}
