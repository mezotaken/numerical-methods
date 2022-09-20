#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

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

    void on_startCount_clicked();

    void on_stopCount_clicked();

    void on_clear_clicked();

    void paintGraph0(QTableWidget* src, int N, int numbGraph);

    void paintGraph1(QTableWidget* src, int N, int numbGraph);

    void paintGraph2(QTableWidget* src, int N, int numbGraph);

    void on_exit_triggered();

    void on_startCount_2_clicked();

    void on_stopCount_2_clicked();

    void on_clear_2_clicked();

    void on_stopCount_3_clicked();

    void on_clear_3_clicked();

    void on_startCount_3_clicked();

    void on_phaseport_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
