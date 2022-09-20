#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void paintGraph(QCustomPlot* dst,QCustomPlot* dsterr,QVector<double>&X,QVector<double>& V,QVector<double>& U);

    void on_exit_triggered();

    void on_start1_clicked();

    void on_clear1_clicked();

    void on_start2_clicked();

    void on_clear2_clicked();

    void on_start0_clicked();

    void on_clear0_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
