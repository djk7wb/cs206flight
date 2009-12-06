#ifndef SHOWGROUPDIALOG_H
#define SHOWGROUPDIALOG_H

#include <QDialog>

namespace Ui {
    class ShowGroupDialog;
}

class ShowGroupDialog : public QDialog {
    Q_OBJECT
public:
    ShowGroupDialog(QWidget *parent = 0);
    ~ShowGroupDialog();
    void setSender(QString t);
    int doExec();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ShowGroupDialog *ui;
    QString sender;

private slots:
    void on_remove_clicked();
    void on_close_clicked();
};

#endif // SHOWGROUPDIALOG_H
