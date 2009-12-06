#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i <= ReservationSys::ROWS; i++) {
        if(i==ReservationSys::ROWS-ReservationSys::SMOKE_ROWS) {
            ui->gridLayout->setRowMinimumHeight(i,20);
        }
        else {
            for (int j = 0; j <= ReservationSys::COLS; j++) {
                if(j==ReservationSys::COLS/2) {
                    ui->gridLayout->setColumnMinimumWidth(j,20);
                }
                else {
                    int row = i;
                    int col = j;
                    if(i > ReservationSys::ROWS - ReservationSys::SMOKE_ROWS) {
                        row--;
                    }
                    if(j > ReservationSys::COLS/2) {
                        col--;
                    }
                    btnSeats[row][col] = new QPushButton(tr("%1%2").arg(char(row+65)).arg(col+1));
                    btnSeats[row][col]->setStyleSheet("font-size: 8pt;");
                    btnSeats[row][col]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                    btnSeats[row][col]->resize(10, 10);
                    connect(btnSeats[row][col], SIGNAL(clicked()), this, SLOT(groupClicked()));
                    ui->gridLayout->addWidget(btnSeats[row][col], i, j);
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}

void MainWindow::on_actionSave_Flight_triggered()
{

}

void MainWindow::on_actionLoad_Flight_triggered()
{

}

void MainWindow::on_action_New_Flight_triggered()
{

}

void MainWindow::on_addGroup_clicked()
{
    AddGroupDialog d;
    d.setReservationSys(&reservations);
    d.exec();
}

void MainWindow::groupClicked()
{
    ShowGroupDialog d;
    QPushButton *sender = (QPushButton*) this->sender();
    d.setSender(sender->text());
    d.doExec();
}
