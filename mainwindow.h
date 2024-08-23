#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include "uye_islemleri.h"
#include "kitap_islemleri.h"
#include "odunc_alinan.h"
#include "odunc_teslim.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_uye_islemleri_clicked();

    void on_btn_kitap_islemleri_clicked();

    void on_btn_odunc_al_clicked();

    void on_btn_odunc_teslim_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery *sorgum;


};
#endif // MAINWINDOW_H
