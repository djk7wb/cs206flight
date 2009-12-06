#include "showgroupdialog.h"
#include "ui_showgroupdialog.h"

ShowGroupDialog::ShowGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowGroupDialog)
{
    ui->setupUi(this);
}

ShowGroupDialog::~ShowGroupDialog()
{
    delete ui;
}

int ShowGroupDialog::doExec()
{
    ui->groupInfo->appendPlainText("Showing information for group at seat " + sender);
    return this->exec();
}

void ShowGroupDialog::setSender(QString t)
{
    sender = t;
}

void ShowGroupDialog::setReservationSys(ReservationSys *r)
{
    reservation = r;
}

void ShowGroupDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ShowGroupDialog::on_close_clicked()
{
    this->close();
}

void ShowGroupDialog::on_remove_clicked()
{
    this->close();
}
