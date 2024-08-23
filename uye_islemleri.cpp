#include "uye_islemleri.h"
#include "ui_uye_islemleri.h"

uye_islemleri::uye_islemleri(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uye_islemleri)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    listele();
}

uye_islemleri::~uye_islemleri()
{
    delete ui;
}

void uye_islemleri::listele()
{
    sorgu->prepare("select * from üye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_uyeler->setModel(model);
}



void uye_islemleri::on_tableView_uyeler_clicked(const QModelIndex &index)
{
    ui->ln_uye_no->setText(model->index(index.row(),0).data().toString());
    ui->ln_uye_ad->setText(model->index(index.row(),1).data().toString());
    ui->ln_uye_soyad->setText(model->index(index.row(),2).data().toString());

}


void uye_islemleri::on_btn_yeni_clicked()
{
    if(ui->ln_uye_ad->text()=="" || ui->ln_uye_soyad->text()=="")
    {
        QMessageBox::critical(this,"hata","Lutfen gerekli alanları doldurunuz","ok");
        return;
    }
    sorgu->prepare("insert into üye(uye_ad,uye_soyad) values(?,?)");
    sorgu->addBindValue(ui->ln_uye_ad->text());
    sorgu->addBindValue(ui->ln_uye_soyad->text());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }
    listele();
}


void uye_islemleri::on_btn_guncelle_clicked()
{
    if(ui->ln_uye_ad->text()=="" || ui->ln_uye_soyad->text()=="")
    {
        QMessageBox::critical(this,"hata","Lutfen gerekli alanları doldurunuz","ok");
        return;
    }
    sorgu->prepare("update üye set uye_ad=?, uye_soyad=? where uye_no=?");
    sorgu->addBindValue(ui->ln_uye_ad->text());
    sorgu->addBindValue(ui->ln_uye_soyad->text());
    sorgu->addBindValue(ui->ln_uye_no->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","guncell","oke");
        return;
    }
    listele();
}


void uye_islemleri::on_btn_sil_clicked()
{
    sorgu->prepare("select * from odunc_alinan where uye_no=?");
    sorgu->addBindValue(ui->ln_uye_no->text().toInt());
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
        QMessageBox::critical(this,"hata","ÜYENİN TESLİM ETMEDİĞİ KİTAPLAR VAR","oke");
        return;
    }

    else
    {
        sorgu->prepare("delete from üye where uye_no=?");
        sorgu->addBindValue(ui->ln_uye_no->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"hata","hata","oke");
            return;
        }
        listele();
    }
}

