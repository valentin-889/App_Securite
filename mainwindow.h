#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_sha_clicked();
    void on_btn_chif_aes_clicked();
    void on_btn_chif_rsa_clicked();
    void on_btn_dechif_aes_clicked();
    void on_btn_dechif_rsa_clicked();
    void on_btn_chif_aes_2_clicked();
    void on_btn_selec_clicked();

private:
    Ui::MainWindow *ui;
};

class mafenetre : public QWidget // On hérite de QWidget
{
    Q_OBJECT

public:
    mafenetre();

public slots:
    void ouvrirDialogue();

private:
    QPushButton *boutonDialogue;
};

#endif // MAINWINDOW_H
