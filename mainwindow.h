#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"MessageBox.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateMemoryView(int index);
    void initializeMemory();
    void refreshRegisterDisplays();
private slots:
    void on_Upload_file_pushButton_clicked();

    void on_Next_PushButto_clicked();

    void on_Start_Assemble_PushButton_clicked();

    void on_StopPushButto_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
