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
    int row = ((int)sender.at(0).toAscii()) - (int)'A';
    int col = ((int)sender.at(1).toAscii()) - (int)'1';
    Person *tmpPerson = reservation->getSeat(row, col);
    if(!tmpPerson) {
        QMessageBox::warning(this, "Error", "This seat is not occupied", QMessageBox::Ok);
        return 1;
    }
    Group *tmpGroup = tmpPerson->getGroup();



    QString smokingPreference = "No";
    if(tmpGroup->smokingPreference) {
        smokingPreference = "Yes";
    }

    ui->groupInfo->appendPlainText("");
    ui->groupInfo->appendPlainText("Smoking preference: " + smokingPreference);
    ui->groupInfo->appendPlainText("Group satisfaction: " + QString().setNum(tmpGroup->satisfaction));

    group = tmpGroup;

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
