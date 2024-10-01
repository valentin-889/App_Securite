#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:

    void on_btn_chif_aes_clicked();
    void on_btn_dechif_aes_clicked();
    void on_btn_chif_rsa_clicked();
    void on_btn_dechif_rsa_clicked();
    void on_btn_sha_clicked();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 std::string generateAESKey();

private slots:
    void on_btn_clef_aes_clicked();

    void on_btn_clef_rsa_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
