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

    vector<Person> passengers = tmpGroup->getMembers();
    for(int i=0; i<(int)passengers.size(); i++) {
        Person tmpPassenger = passengers.at(i);
        ui->groupInfo->appendPlainText(tr("Passenger %1: %2").arg(i+1).arg(tmpPassenger.getName().c_str()));
    }

    QString smokingPreference = "No";
    if(tmpGroup->smokingPreference) {
        smokingPreference = "Yes";
    }

    ui->groupInfo->appendPlainText("");
    ui->groupInfo->appendPlainText(tr("Smoking preference: %1").arg(smokingPreference));
    ui->groupInfo->appendPlainText(tr("Group satisfaction: %1").arg(tmpGroup->satisfaction));

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
