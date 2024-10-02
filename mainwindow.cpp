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

    QString buttonStyle =
        "QPushButton {"
        "   background-color: #007AFF;"
        "   color: white;"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "   font-size: 16px;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #005AD5;"
        "}";

    // Application du style aux boutons
    ui->btn_chif_aes->setStyleSheet(buttonStyle);
    ui->btn_dechif_aes->setStyleSheet(buttonStyle);
    ui->btn_chif_rsa->setStyleSheet(buttonStyle);
    ui->btn_dechif_rsa->setStyleSheet(buttonStyle);
    ui->btn_sha->setStyleSheet(buttonStyle);
    ui->btn_chif_aes->setStyleSheet(buttonStyle);
    ui->btn_chif_rsa->setStyleSheet(buttonStyle);
    ui->btn_clef_rsa->setStyleSheet(buttonStyle);
    ui->btn_clef_aes->setStyleSheet(buttonStyle);
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
         QMessageBox::information(this, "Echec", "Erreur de fichier.");
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
        QMessageBox::information(this, "Echec", "Erreur de fichierdechiffrement");
    }
}


void MainWindow::on_btn_chif_rsa_clicked()
{
    QString publicKey = QFileDialog::getOpenFileName(this, "Sélectionner la clé publique RSA", "", "Tous les fichiers (*.*)");
    if (publicKey.isEmpty()) return;

    QString inputPath = QFileDialog::getOpenFileName(this, "Sélectionner le fichier à chiffrer", "", "Tous les fichiers (*.*)");
    if (inputPath.isEmpty()) return;

    QString outputPath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier chiffré", "", "Tous les fichiers (*.*)");
   // if (outputPath.isEmpty()) return;

    RsaGestion RSA;
    try {
        RSA.chargementClefsPublic(publicKey.toStdString() );
        RSA.chiffrementFichier(inputPath.toStdString(),outputPath.toStdString(),2048 );
        QMessageBox::information(this, "Succès", "Fichier chiffré avec succès.");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Échec du chiffrement: %1").arg(e.what()));
    }
}

void MainWindow::on_btn_dechif_rsa_clicked()
{
    QString privateKey = QFileDialog::getOpenFileName(this, "Sélectionner la clé privée RSA", "", "Tous les fichiers (*.*)");
    if (privateKey.isEmpty()) return;

    QString inputPath = QFileDialog::getOpenFileName(this, "Sélectionner le fichier chiffré", "", "Tous les fichiers (*.*)");
    if (inputPath.isEmpty()) return;

    QString outputPath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier déchiffré", "", "Tous les fichiers (*.*)");
   // if (outputPath.isEmpty()) return;

    RsaGestion RSA;
    try {
        RSA.chargementClefsPublic(privateKey.toStdString() );
        RSA.dechiffrementFichier(outputPath.toStdString(),inputPath.toStdString(),2048 );
        QMessageBox::information(this, "Succès", "Fichier déchiffré avec succès.");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", "Échec du déchiffrement: ");
    }
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
     QMessageBox::information(this, "Hash SHA-256", "erreur de hashage: ");
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
    QString publicKeyFileName = QFileDialog::getSaveFileName(this, "Enregistrer la clé publique RSA", "", "Tous les fichiers (*.*)");
    if (publicKeyFileName.isEmpty()) return;

    QString privateKeyFileName = QFileDialog::getSaveFileName(this, "Enregistrer la clé privée RSA", "", "Tous les fichiers (*.*)");
    if (privateKeyFileName.isEmpty()) return;

    RsaGestion RSA;

    try {
        RSA.generationClef(publicKeyFileName.toStdString(), privateKeyFileName.toStdString(), 2048);
        QMessageBox::information(this, "Succès", "Paire de clés RSA générée avec succès.");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", "Échec de la génération des clés: " + QString::fromStdString(e.what()));
    }
}

