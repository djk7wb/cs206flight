#include "showgroupdialog.h"
#include "ui_showgroupdialog.h"

ShowGroupDialog::ShowGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowGroupDialog)
{
    ui->setupUi(this);
    seat = "";
}

ShowGroupDialog::~ShowGroupDialog()
{
    delete ui;
}

int ShowGroupDialog::doExec()
{
    if(seat != "")
    {
        ui->groupInfo->appendPlainText("Showing information for group at seat " + seat);
        int row = ((int)seat.at(0).toAscii()) - (int)'A';
        int col = ((int)seat.at(1).toAscii()) - (int)'1';
        Group *tmpGroup = reservation->getGroup(row, col);
        if(!tmpGroup) {
            QMessageBox::warning(this, "Error", "This seat is not occupied", QMessageBox::Ok);
            return 1;
        }
        groups.push_back(tmpGroup);
        group = tmpGroup;
    }
    else
    {
        ui->remove->setHidden(true);
    }

    int totalSatisfaction=0;

    for (int i=0; i<(int)groups.size(); i++) {
        if(i>0) {
            ui->groupInfo->appendPlainText("");
            ui->groupInfo->appendPlainText("------------------------------------");
            ui->groupInfo->appendPlainText("");
        }
        Group *tmpGroup = groups[i];
        vector<Person*> passengers = tmpGroup->getMembers();
        for(int i=0; i<(int)passengers.size(); i++) {
            Person *tmpPassenger = passengers[i];
            QString seat = tr("[%1%2]").arg((char)(tmpPassenger->getRow()+(int)'A')).arg(tmpPassenger->getCol()+1);
            ui->groupInfo->appendPlainText(tr("Passenger %1 %2: %3").arg(i+1).arg(seat).arg(tmpPassenger->getName().c_str()));
        }

        QString smokingPreference = "No";
        if(tmpGroup->smokingPreference) {
            smokingPreference = "Yes";
        }

        ui->groupInfo->appendPlainText("");
        ui->groupInfo->appendPlainText(tr("Smoking preference: %1").arg(smokingPreference));
        ui->groupInfo->appendPlainText(tr("Group satisfaction: %1").arg(tmpGroup->satisfaction));
        totalSatisfaction += tmpGroup->satisfaction;
    }

    if(seat == "") {
        ui->groupInfo->appendPlainText("");
        ui->groupInfo->appendPlainText("------------------------------------");
        ui->groupInfo->appendPlainText("");
        ui->groupInfo->appendPlainText(tr("Total satisfaction: %1").arg(totalSatisfaction));
        ui->groupInfo->appendPlainText(tr("Average satisfaction: %1").arg(((float)totalSatisfaction)/groups.size()));
    }

    return this->exec();
}

void ShowGroupDialog::setSeat(QString t)
{
    seat = t;
}

void ShowGroupDialog::setGroups(vector<Group*> g)
{
    groups = g;
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
    reservation->removeGroup(group);
    this->close();
}
