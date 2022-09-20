#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>

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
    void paintGraph(QCustomPlot* dst,QVector<double>&X,QVector<double>& F,QVector<double>& S);

    void on_startButton_clicked();

    void on_funcPar_currentIndexChanged(int index);

    void on_brdCondPar_currentIndexChanged(int index);

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
