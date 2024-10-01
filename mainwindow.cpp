#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HashGestion.h"
#include "AesGestion.h"
#include "RsaGestion.h"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

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
    QString filePath = QFileDialog::getOpenFileName(this, "Sélectionner un fichier", "", "Tous les fichiers (*.*)");


    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    if (fileData.isEmpty()) {

        return;
    }

    try {
        HashGestion SHA;
        QString hash = QString::fromStdString(SHA.CalculateSHA256(string(fileData.constData(), fileData.length())));
        cout << "Hash SHA-256 du fichier : " << hash.toStdString() << endl;
        QMessageBox::information(this, "Hash SHA-256", "Le hash SHA-256 du fichier est :\n" + hash);
    } catch (const exception& e) {

    }
}

void MainWindow::on_btn_clef_aes_clicked()
{

}


void MainWindow::on_btn_clef_rsa_clicked()
{

}

