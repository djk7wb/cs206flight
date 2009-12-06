#include "addgroupdialog.h"
#include "ui_addgroupdialog.h"

AddGroupDialog::AddGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGroupDialog)
{
    ui->setupUi(this);

    for(int i=0; i<5; i++) {
        passengerName[i] = new QLineEdit;
        if (i>0) {
            passengerName[i]->setEnabled(false);
        }
        ui->gridLayout->addWidget(passengerName[i],i+4,2);
    }
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

void AddGroupDialog::setReservationSys(ReservationSys *r)
{
    reservation = r;
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
    for(int i=0; i<passengers; i++) {
        passengerName[i]->setEnabled(true);
    }

    for(int i=passengers; i<5; i++) {
        passengerName[i]->setEnabled(false);
    }
}

void AddGroupDialog::on_buttonBox_accepted()
{
    Group tmpGroup;
    for(int i=0; i<ui->numberOfTravelers->value(); i++) {
        Person tmpPerson;
        tmpPerson.setName(passengerName[i]->text().toStdString());
        tmpGroup.addPerson(tmpPerson);
    }
    bool success = reservation->addGroup(tmpGroup);
}
