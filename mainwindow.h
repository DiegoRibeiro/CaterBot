#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "process.h"
#include "catermodule.h"
#include "remotethread.h"
#include "pipethread.h"
#include "pipeclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_attachBtn_clicked();

    void on_detachBtn_clicked();

    void on_startServerBtn_clicked();

    void on_stopServerBtn_clicked();

private:
    Ui::MainWindow *ui;
    Process process;
    RemoteThread remoteThread;
    CaterModule caterModule;
    PipeThread thread;
    PipeClient client;
};
#endif // MAINWINDOW_H
