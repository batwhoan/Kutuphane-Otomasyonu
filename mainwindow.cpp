#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db.setDatabaseName("C:/Users/batuh/Desktop/Kitap/üye.db");
    if(!db.open())
    {
        ui->statusbar->showMessage("VERİTABANINA BAĞLANILAMADI");
    }
    else
    {
        ui->statusbar->showMessage("VERİTABANINA bağlanıldı");

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_uye_islemleri_clicked()
{
    uye_islemleri *uye = new uye_islemleri(db);
    uye->show();
}


void MainWindow::on_btn_kitap_islemleri_clicked()
{
    kitap_islemleri *kit = new kitap_islemleri(db);
    kit->show();
}


void MainWindow::on_btn_odunc_al_clicked()
{
    odunc_alinan *odn_al = new odunc_alinan(db);
    odn_al->show();

}




void MainWindow::on_btn_odunc_teslim_clicked()
{
    odunc_teslim *teslim_et = new odunc_teslim(db);
    teslim_et->show();

}

