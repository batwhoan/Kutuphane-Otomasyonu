#include "kitap_islemleri.h"
#include "ui_kitap_islemleri.h"

kitap_islemleri::kitap_islemleri(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kitap_islemleri)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    listele();

}

kitap_islemleri::~kitap_islemleri()
{
    delete ui;
}

void kitap_islemleri::listele()
{
    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_kitaplar->setModel(model);
}


void kitap_islemleri::on_tableView_kitaplar_clicked(const QModelIndex &index)
{
    ui->ln_kitap_no->setText(model->index(index.row(),0).data().toString());
    ui->ln_kitap_ad->setText(model->index(index.row(),1).data().toString());
    ui->ln_kitap_stok->setText(model->index(index.row(),2).data().toString());

    sorgu->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(ui->ln_kitap_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_alinan->setModel(model);


    sorgu->prepare("select * from odunc_teslim_edilen where kitap_no=?");
    sorgu->addBindValue(ui->ln_kitap_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }

    model2 = new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->tableView_tesilm->setModel(model2);

    listele();

}


void kitap_islemleri::on_btn_kayit_clicked()
{
    if(ui->ln_kitap_ad->text()=="" || ui->ln_kitap_stok->text()=="")
    {
        QMessageBox::critical(this,"hata","Lutfen gerekli alanları doldurunuz","ok");
        return;
    }

    sorgu->prepare("insert into kitap(kitap_ad,kitap_sayisi) values(?,?)");
    sorgu->addBindValue(ui->ln_kitap_ad->text());
    sorgu->addBindValue(ui->ln_kitap_stok->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }
    listele();
}





void kitap_islemleri::on_btn_guncelle_clicked()
{
    if(ui->ln_kitap_ad->text()=="" || ui->ln_kitap_stok->text()=="")
    {
        QMessageBox::critical(this,"hata","Lutfen gerekli alanları doldurunuz","ok");
        return;
    }

    sorgu->prepare("update kitap set kitap_ad=?, kitap_sayisi=? where kitap_no=?");
    sorgu->addBindValue(ui->ln_kitap_ad->text());
    sorgu->addBindValue(ui->ln_kitap_stok->text().toInt());
    sorgu->addBindValue(ui->ln_kitap_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","guncell","oke");
        return;
    }
    listele();
}


void kitap_islemleri::on_btn_sil_clicked()
{
    sorgu->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(ui->ln_kitap_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }
    int syc=0;
    while(sorgu->next())
    {
        syc++;
    }
    if(syc>0)
    {
        QMessageBox::critical(this,"hata","KİTAPLAR VAR","oke");
        return;
    }

    else
    {
        sorgu->prepare("delete from kitap where kitap_no=?");
        sorgu->addBindValue(ui->ln_kitap_no->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"hata","hata","oke");
            return;
        }
        listele();
    }
}

