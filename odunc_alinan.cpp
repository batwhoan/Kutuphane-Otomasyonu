#include "odunc_alinan.h"
#include "ui_odunc_alinan.h"

odunc_alinan::odunc_alinan(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::odunc_alinan)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    int stok_kitap=0;
    listele_alinanlar();
    listele_kitaplar();
    listele_uye();
}

odunc_alinan::~odunc_alinan()
{
    delete ui;
}

void odunc_alinan::listele_uye()
{
    sorgu->prepare("select * from üye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }

    model_uye = new QSqlQueryModel();
    model_uye->setQuery(*sorgu);
    ui->tableView_uyeler->setModel(model_uye);

}

void odunc_alinan::listele_kitaplar()
{
    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }

    model_kitap = new QSqlQueryModel();
    model_kitap->setQuery(*sorgu);
    ui->tableView_kitaplar->setModel(model_kitap);

}

void odunc_alinan::listele_alinanlar()
{

    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_odunc_alinanlar->setModel(model);

}

void odunc_alinan::on_tableView_uyeler_clicked(const QModelIndex &index)
{
     ui->ln_uye_no->setText(model_uye->index(index.row(),0).data().toString());
}


void odunc_alinan::on_tableView_kitaplar_clicked(const QModelIndex &index)
{
    ui->ln_kitap_no->setText(model_kitap->index(index.row(),0).data().toString());

}


void odunc_alinan::on_btn_odunc_al_clicked()
{

    if(ui->ln_uye_no->text()=="" || ui->ln_kitap_no->text()=="")
    {
        QMessageBox::critical(this,"hata","Lutfen gerekli alanları doldurunuz","ok");
        return;
    }

    sorgu->prepare("select * from odunc_alinan where kitap_no=? and uye_no=?");
    sorgu->addBindValue(ui->ln_kitap_no->text().toInt());
    sorgu->addBindValue(ui->ln_uye_no->text().toInt());

    int syc=0;
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","1.sorgu gerçeklestirilemedi","ok");
        return;
    }
    while(sorgu->next())
    {
        syc++;
    }

    if(syc>0)
    {
        QMessageBox::critical(this,"hata","AYNI KİTAPTAN 2 TANE ALINAMAZ","ok");
        return;
    }
    else
    {
        sorgu->prepare("insert into odunc_alinan(uye_no,kitap_no,odunc_alma_tarihi) values(?,?,?)");
        sorgu->addBindValue(ui->ln_uye_no->text().toInt());
        sorgu->addBindValue(ui->ln_kitap_no->text().toInt());
        sorgu->addBindValue(ui->tarih->text());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"hata","2.sorgu gerçeklestirilemedi","ok");
            return;
        }

        listele_alinanlar();

    }



}

