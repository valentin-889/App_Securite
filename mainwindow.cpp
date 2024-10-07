/**
 * @file mainwindow.cpp
 * Implémentation de la classe MainWindow pour la gestion de l'interface graphique.
 * 
 * Ce fichier contient les méthodes de l'interface utilisateur
 * pour les opérations de chiffrement et de déchiffrement utilisant AES, RSA et 
 * le calcul de hash SHA-256.
 */

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

/**
 * Constructeur de la classe MainWindow.
 * 
 */
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

/**
 * Destructeur de la classe MainWindow.
 * 
 */
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

/**
 * chiffrement AES.
 * Sélection du fichier à chiffrer, Sélection du fichier de sortie pour sauvegarder le résultat et Chiffrement du fichier avec AES-256
 * 
 */
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

/**
 * déchiffrement AES.
 * Sélection du fichier chiffré, Sélection du fichier de sortie pour sauvegarder le fichier déchiffré et Déchiffrement du fichier avec AES-256
 */
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
        QMessageBox::information(this, "Echec", "Erreur de fichier de déchiffrement");
    }
}

/**
 * chiffrement RSA.
 * Sélection de la clé publique RSA, Sélection du fichier à chiffrer, Sélection du fichier de sortie pour sauvegarder le fichier chiffré
 * et Chargement de la clé publique et chiffrement du fichier
 */
void MainWindow::on_btn_chif_rsa_clicked()
{
    QString publicKey = QFileDialog::getOpenFileName(this, "Sélectionner la clé publique RSA", "", "Tous les fichiers (*.*)");
    if (publicKey.isEmpty()) return;

    QString inputPath = QFileDialog::getOpenFileName(this, "Sélectionner le fichier à chiffrer", "", "Tous les fichiers (*.*)");
    if (inputPath.isEmpty()) return;

    QString outputPath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier chiffré", "", "Tous les fichiers (*.*)");

    RsaGestion RSA;
    try {
        RSA.chargementClefsPublic(publicKey.toStdString());
        RSA.chiffrementFichier(inputPath.toStdString(), outputPath.toStdString(), 2048);
        QMessageBox::information(this, "Succès", "Fichier chiffré avec succès.");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", QString("Échec du chiffrement: %1").arg(e.what()));
    }
}

/**
 * déchiffrement RSA.
 * Sélection de la clé privée RSA, Sélection du fichier chiffré, Sélection du fichier de sortie pour sauvegarder le fichier déchiffré
 * et Chargement de la clé privée et déchiffrement du fichier
 */
void MainWindow::on_btn_dechif_rsa_clicked()
{
    QString privateKey = QFileDialog::getOpenFileName(this, "Sélectionner la clé privée RSA", "", "Tous les fichiers (*.*)");
    if (privateKey.isEmpty()) return;

    QString inputPath = QFileDialog::getOpenFileName(this, "Sélectionner le fichier chiffré", "", "Tous les fichiers (*.*)");
    if (inputPath.isEmpty()) return;
 
    QString outputPath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier déchiffré", "", "Tous les fichiers (*.*)");

    RsaGestion RSA;
    try {
        RSA.chargementClefsPrive(privateKey.toStdString());
        RSA.dechiffrementFichier(inputPath.toStdString(), outputPath.toStdString(), 2048);
        QMessageBox::information(this, "Succès", "Fichier déchiffré avec succès.");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Erreur", "Échec du déchiffrement.");
    }
}

/**
 *le calcul du hash SHA-256.
 * Sélection du fichier, Lecture des données du fichier et Calcul du hash SHA-256
 */
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
        QMessageBox::information(this, "Hash SHA-256", "Erreur de hashage.");
    }
}

/**
 * @brief Slot pour la génération de clé AES et Enregistrement de la clé générée
 * 
 */
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

/**
 * Sélection des fichiers pour enregistrer les clés publiques et privées et Génération de paire de clés RSA.
 * 
 */
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
