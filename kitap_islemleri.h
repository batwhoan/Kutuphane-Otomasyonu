#ifndef KITAP_ISLEMLERI_H
#define KITAP_ISLEMLERI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>


namespace Ui {
class kitap_islemleri;
}

class kitap_islemleri : public QDialog
{
    Q_OBJECT

public:
    explicit kitap_islemleri(QSqlDatabase,QWidget *parent = nullptr);
    ~kitap_islemleri();
    void listele();
    void listele_alinan();
    void listele_teslim();

private slots:
    void on_tableView_kitaplar_clicked(const QModelIndex &index);

    void on_btn_kayit_clicked();

    void on_btn_guncelle_clicked();

    void on_btn_sil_clicked();

private:
    Ui::kitap_islemleri *ui;
    QSqlQuery *sorgu;

    QSqlQueryModel *model;
    QSqlQueryModel *model2;
};

#endif // KITAP_ISLEMLERI_H
