#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HashGestion.h"
#include "AesGestion.h"
#include "RsaGestion.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_chif_aes_clicked()
{


}

void MainWindow::on_btn_dechif_aes_clicked()
{


}


void MainWindow::on_btn_chif_rsa_clicked()
{


}


void MainWindow::on_btn_dechif_rsa_clicked()
{

    RsaGestion RSA;

}

void MainWindow::on_btn_sha_clicked()
{
    HashGestion SHA;
    cout << SHA.CalculateSHA256("c'est un chat") << endl;
}

void MainWindow::on_btn_chif_aes_2_clicked()
{

}


void MainWindow::on_btn_selec_clicked()
{

}

