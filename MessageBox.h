#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include "qmessagebox.h"
#include <QFileDialog>
#include <QPixmap>
inline void ShowErrorMessageBox(QString Title,QString Text,QString intormation)

{
    QMessageBox msgBox;
    msgBox.setWindowTitle(Title);

    // Set a custom icon using an image from resources
    QPixmap pandaPixmap(":/prefix1/picture/Premium Vector _ Cute panda is angry and holding a baseball bat.png");
    msgBox.setIconPixmap(pandaPixmap);

    // Customize the message box text and buttons
    msgBox.setText(Text);
    msgBox.setInformativeText(intormation);
    msgBox.setDefaultButton(QMessageBox::Ok);

    // Set custom stylesheet for Panda theme
    msgBox.setStyleSheet(
        "QMessageBox { background-color: #f7f7f7; }"
        "QPushButton {"
        "  background-color: #fff;"
        "  border: 2px solid #3c3c3c;"
        "  border-radius: 5px;"
        "  padding: 5px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #e0e0e0;"
        "}"
    );

    // Display the message box
    msgBox.exec();
}
inline void ShowHappyMessageBox(QString Title,QString Text,QString intormation){
    QMessageBox msgBox;
    msgBox.setWindowTitle(Title);

    // Set a custom icon using an image from resources
    QPixmap pandaPixmap(":/prefix1/picture/Premium Vector _ Cute panda working on a laptop.png");
    msgBox.setIconPixmap(pandaPixmap);

    // Customize the message box text and buttons
    msgBox.setText(Text);
    msgBox.setInformativeText(intormation);
    msgBox.setDefaultButton(QMessageBox::Ok);

    // Set custom stylesheet for Panda theme
    msgBox.setStyleSheet(
        "QMessageBox { background-color: #f7f7f7; }"
        "QPushButton {"
        "  background-color: #fff;"
        "  border: 2px solid #3c3c3c;"
        "  border-radius: 5px;"
        "  padding: 5px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #e0e0e0;"
        "}"
    );

    // Display the message box
    msgBox.exec();
}
#endif // MESSAGEBOX_H
