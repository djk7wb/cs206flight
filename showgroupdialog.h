#ifndef SHOWGROUPDIALOG_H
#define SHOWGROUPDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ReservationSys.h"

namespace Ui {
    class ShowGroupDialog;
}

class ShowGroupDialog : public QDialog {
    Q_OBJECT
public:
    ShowGroupDialog(QWidget *parent = 0);
    ~ShowGroupDialog();
    void setSender(QString t);
    void setReservationSys(ReservationSys *r);
    int doExec();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ShowGroupDialog *ui;
    QString sender;
    ReservationSys *reservation;

private slots:
    void on_remove_clicked();
    void on_close_clicked();
};

#endif // SHOWGROUPDIALOG_H
