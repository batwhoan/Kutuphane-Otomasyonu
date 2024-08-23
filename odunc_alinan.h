#ifndef ODUNC_ALINAN_H
#define ODUNC_ALINAN_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>



namespace Ui {
class odunc_alinan;
}

class odunc_alinan : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_alinan(QSqlDatabase,QWidget *parent = nullptr);
    ~odunc_alinan();
    void listele_uye();
    void listele_kitaplar();
    void listele_alinanlar();


private slots:
    void on_tableView_uyeler_clicked(const QModelIndex &index);

    void on_tableView_kitaplar_clicked(const QModelIndex &index);

    void on_btn_odunc_al_clicked();

private:
    Ui::odunc_alinan *ui;
    QSqlQuery *sorgu;
    QSqlQuery *sorgu2;
    QSqlQueryModel *model;
    QSqlQueryModel *model_uye;
    QSqlQueryModel *model_kitap;

};

#endif // ODUNC_ALINAN_H
