#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QDialog>

namespace Ui {
    class AddGroupDialog;
}

class AddGroupDialog : public QDialog {
    Q_OBJECT
public:
    AddGroupDialog(QWidget *parent = 0);
    ~AddGroupDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AddGroupDialog *ui;

private slots:
    void on_numberOfTravelers_valueChanged(int );
    void on_travelerType_currentIndexChanged(QString );
};

#endif // ADDGROUPDIALOG_H