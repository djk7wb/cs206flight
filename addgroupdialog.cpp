#include "addgroupdialog.h"
#include "ui_addgroupdialog.h"

AddGroupDialog::AddGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGroupDialog)
{
    ui->setupUi(this);
}

AddGroupDialog::~AddGroupDialog()
{
    delete ui;
}

void AddGroupDialog::changeEvent(QEvent *e)
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

void AddGroupDialog::on_travelerType_currentIndexChanged(QString type)
{
    ui->numberOfTravelers->setMinimum(1);

    if (type == "Businessman") {
        ui->smokingPreference->setEnabled(true);
        ui->numberOfTravelers->setValue(1);
        ui->numberOfTravelers->setEnabled(false);
    }
    else if (type == "Tourists") {
        ui->smokingPreference->setEnabled(false);
        ui->numberOfTravelers->setValue(2);
        ui->numberOfTravelers->setEnabled(false);
    }
    else {
        ui->smokingPreference->setEnabled(false);
        ui->numberOfTravelers->setValue(3);
        ui->numberOfTravelers->setMinimum(3);
        ui->numberOfTravelers->setEnabled(true);

    }
}

void AddGroupDialog::on_numberOfTravelers_valueChanged(int passengers)
{
    ui->passenger1Name->setEnabled(false);
    ui->passenger2Name->setEnabled(false);
    ui->passenger3Name->setEnabled(false);
    ui->passenger4Name->setEnabled(false);
    ui->passenger5Name->setEnabled(false);

    switch (passengers) {
    case 5:
        ui->passenger5Name->setEnabled(true);
    case 4:
        ui->passenger4Name->setEnabled(true);
    case 3:
        ui->passenger3Name->setEnabled(true);
    case 2:
        ui->passenger2Name->setEnabled(true);
    case 1:
        ui->passenger1Name->setEnabled(true);
        break;
    }
}
