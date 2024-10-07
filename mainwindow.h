/**
 * @file mainwindow.h
 * @brief Déclaration de la classe MainWindow.
 * 
 * Cette classe gère l'interface utilisateur et les actions liées au chiffrement/déchiffrement
 * AES et RSA, ainsi que la génération de clés.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * MainWindow gérant l'interface principale.
 * Gère les interactions de l'utilisateur avec les boutons pour chiffrer, déchiffrer et générer des clés.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void on_btn_chif_aes_clicked(); //Chiffrement AES
    void on_btn_dechif_aes_clicked(); //Déchiffrement AES
    void on_btn_chif_rsa_clicked(); //Chiffrement RSA
    void on_btn_dechif_rsa_clicked(); // Déchiffrement RSA
    void on_btn_sha_clicked(); //Calcul du hash SHA-256

public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow(); 
    std::string generateAESKey(); 
    void generationClefs(const std::string& publicKey, const std::string& privateKey); 
private slots:
    void on_btn_clef_aes_clicked(); //Génération d'une clé AES
    void on_btn_clef_rsa_clicked(); //Génération d'une clé RSA

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
