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

    void paintGraph2(QTableWidget* src, int N, int numbGraph);

    void on_exit_triggered();

    void on_phaseport_clicked();

    void on_startCount_clicked();

    void on_stopCount_clicked();

    void on_clear_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
