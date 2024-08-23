#ifndef ODUNC_TESLIM_H
#define ODUNC_TESLIM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class odunc_teslim;
}

class odunc_teslim : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_teslim(QSqlDatabase,QWidget *parent = nullptr);
    ~odunc_teslim();
    void listele_alinan();
    void listele_teslim();
    QString tarihim;

private slots:
    void on_tableView_alinan_clicked(const QModelIndex &index);
    void on_btn_ver_clicked();

private:
    Ui::odunc_teslim *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;

};

#endif // ODUNC_TESLIM_H
