/**
 * Fonction principale de l'application.
 * 
 * Initialise l'application Qt et affiche la fenêtre principale.
 */

#include "mainwindow.h"
#include <QApplication>

/**
 * Point d'entrée de l'application.
 * 
 * Crée et affiche la fenêtre principale, puis lance la boucle d'événements Qt.
 * 
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
