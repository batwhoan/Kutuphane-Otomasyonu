#include "odunc_teslim.h"
#include "ui_odunc_teslim.h"

odunc_teslim::odunc_teslim(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::odunc_teslim)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);
    listele_alinan();
    listele_teslim();
}

odunc_teslim::~odunc_teslim()
{
    delete ui;
}

void odunc_teslim::listele_alinan()
{
    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_alinan->setModel(model);
}

void odunc_teslim::listele_teslim()
{
    sorgu->prepare("select * from odunc_teslim_edilen");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","hata","oke");
        return;
    }

    model2 = new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->tableView_teslim->setModel(model2);
}


void odunc_teslim::on_tableView_alinan_clicked(const QModelIndex &index)
{
    ui->ln_uye_no->setText(model->index(index.row(),0).data().toString());
    ui->ln_kitap_no->setText(model->index(index.row(),1).data().toString());
    tarihim=model->index(index.row(),2).data().toString();

}


void odunc_teslim::on_btn_ver_clicked()
{
    if(ui->ln_uye_no->text()=="" || ui->ln_kitap_no->text()=="")
    {
        QMessageBox::critical(this,"hata","Lutfen gerekli alanları doldurunuz","ok");
        return;
    }


    sorgu->prepare("select * from odunc_alinan where kitap_no=? and uye_no=?");
    sorgu->addBindValue(ui->ln_kitap_no->text().toInt());
    sorgu->addBindValue(ui->ln_uye_no->text().toInt());

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"hata","1.sorgu gerçeklestirilemedi","ok");
        return;
    }


    sorgu->prepare("insert into odunc_teslim_edilen(uye_no,kitap_no,alma_tarihi,verme_tarihi,borc) values(?,?,?,?,?)");
    sorgu->addBindValue(ui->ln_uye_no->text().toInt());
    sorgu->addBindValue(ui->ln_kitap_no->text().toInt());
    sorgu->addBindValue(tarihim);
    sorgu->addBindValue(ui->tarih->text());
    sorgu->addBindValue(0);

    if(!sorgu->exec())
        {
            QMessageBox::critical(this,"hata","2.sorgu gerçeklestirilemedi","ok");
            return;
        }


    sorgu->prepare("delete from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu->addBindValue(ui->ln_uye_no->text().toInt());
    sorgu->addBindValue(ui->ln_kitap_no->text().toInt());

    if(!sorgu->exec())
       {
            QMessageBox::critical(this,"hata","silme","oke");
            return;
       }


        listele_alinan();
        listele_teslim();

    }


