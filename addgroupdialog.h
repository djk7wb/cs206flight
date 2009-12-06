#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "ReservationSys.h"

namespace Ui {
    class AddGroupDialog;
}

class AddGroupDialog : public QDialog {
    Q_OBJECT
public:
    AddGroupDialog(QWidget *parent = 0);
    ~AddGroupDialog();
    void setReservationSys(ReservationSys *r);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AddGroupDialog *ui;
    ReservationSys *reservation;
    QLineEdit *passengerName[5];

private slots:
    void on_buttonBox_accepted();
    void on_numberOfTravelers_valueChanged(int );
    void on_travelerType_currentIndexChanged(QString );
};

#endif // ADDGROUPDIALOG_H
