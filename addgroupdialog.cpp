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
    this->setTabOrder(ui->smokingPreference,passengerName[0]);
    for(int i=1; i<5; i++) {
        this->setTabOrder(passengerName[i-1], passengerName[i]);
    }
    this->setTabOrder(passengerName[4],ui->buttonBox);
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
    else if (type == "Family"){
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
        passengerName[i]->setText("");
    }
}

void AddGroupDialog::on_buttonBox_accepted()
{
    Group tmpGroup;
    if (ui->travelerType->currentText() == "Businessman") {
        tmpGroup.type = BUSINESS;
    }
    else if (ui->travelerType->currentText() == "Tourists") {
        tmpGroup.type = TOURISTS;
    }
    else if (ui->travelerType->currentText() == "Family") {
        tmpGroup.type = FAMILY;
    }

    for(int i=0; i<ui->numberOfTravelers->value(); i++) {
        Person tmpPerson;
        if(passengerName[i]->text() == "") {
            QMessageBox::critical(this, "Error", "Passenger name must be specified", QMessageBox::Ok | QMessageBox::Default);
            return;
        }
        tmpPerson.setName(passengerName[i]->text().toStdString());
        tmpGroup.addPerson(tmpPerson);
    }

    if(ui->smokingPreference->isChecked()) {
        tmpGroup.smokingPreference = true;
    }
    else {
        tmpGroup.smokingPreference = false;
    }

    if(!reservation->addGroup(tmpGroup)) {
        QMessageBox::critical(this, "Error", "Adding group failed. Possible causes include not enough remaining seats on flight.", QMessageBox::Ok | QMessageBox::Default);
        done(1);
    }
    done(0);
}

void AddGroupDialog::accept()
{
    return;
}
