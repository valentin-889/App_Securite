#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HashGestion.h"
#include "AesGestion.h"
#include "RsaGestion.h"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include <string>

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

QByteArray generateAESKey(int length = 32) {
    QByteArray key;
    for (int i = 0; i < length; i++) {

    }
    return key;
}

void MainWindow::on_btn_chif_aes_clicked()
{
    QString inputPath = QFileDialog::getOpenFileName(this, "Sélectionner le fichier à chiffrer", "", "Tous les fichiers (*.*)");
    if (inputPath.isEmpty()) return;

    QString outputPath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier chiffré", "", "Tous les fichiers (*.*)");
    if (outputPath.isEmpty()) return;

    AesGestion AES;
    try {
        AES.EncryptFileAES256(inputPath.toStdString(), outputPath.toStdString());
        QMessageBox::information(this, "Succès", "Fichier chiffré avec succès.");
    } catch (const std::exception& e) {
            }
}

void MainWindow::on_btn_dechif_aes_clicked()
{
        QString inputPath = QFileDialog::getOpenFileName(this, "Sélectionner le fichier chiffré", "", "Tous les fichiers (*.*)");
    if (inputPath.isEmpty()) return;

    QString outputPath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier déchiffré", "", "Tous les fichiers (*.*)");
    if (outputPath.isEmpty()) return;

    AesGestion AES;
    try {
        AES.DecryptFileAES256(inputPath.toStdString(), outputPath.toStdString());
        QMessageBox::information(this, "Succès", "Fichier déchiffré avec succès.");
    } catch (const std::exception& e) {
    }


}

void MainWindow::on_btn_chif_rsa_clicked()
{

}




void MainWindow::on_btn_dechif_rsa_clicked()
{

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
        QMessageBox::information(this, "Hash SHA-256", "Le hash SHA-256 du fichier est: " + hash);
    } catch (const exception& e) {

    }
}





void MainWindow::on_btn_clef_aes_clicked()
{

    QByteArray aesKey = ::generateAESKey(32);

    QString keyPath = QFileDialog::getSaveFileName(this, "Enregistrer la clé AES", "", "Clé AES (*.key)");
    if (keyPath.isEmpty()) return;

    QFile keyFile(keyPath);
    if (!keyFile.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'enregistrer la clé.");
        return;
    }
    keyFile.write(aesKey);
    keyFile.close();

    QMessageBox::information(this, "Succès", "Clé générée.");
}

void MainWindow::on_btn_clef_rsa_clicked()
{

}
