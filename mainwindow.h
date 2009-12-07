#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSpacerItem>
#include <QMessageBox>
#include "ReservationSys.h"
#include "addgroupdialog.h"
#include "showgroupdialog.h"

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
    void updateButtons();
    Ui::MainWindow *ui;
    QPushButton *btnSeats[ReservationSys::ROWS][ReservationSys::COLS];
    ReservationSys *reservations;

private slots:
    void on_action_Overall_Satisfaction_triggered();
    void on_action_Random_Poll_triggered();
    void on_addGroup_clicked();
    void on_action_New_Flight_triggered();
    void on_actionLoad_Flight_triggered();
    void on_actionSave_Flight_triggered();
    void on_actionQuit_triggered();
    void groupClicked();
};

#endif // MAINWINDOW_H
