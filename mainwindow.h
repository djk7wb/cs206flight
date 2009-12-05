#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSpacerItem>
#include "ReservationSys.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QPushButton *btnSeats[ReservationSys::ROWS][ReservationSys::COLS];

private slots:
    void on_action_New_Flight_triggered();
    void on_actionLoad_Flight_triggered();
    void on_actionSave_Flight_triggered();
    void on_actionQuit_triggered();
};

#endif // MAINWINDOW_H
