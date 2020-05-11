#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , process("SimpleClient.exe")
    , remoteThread()
    , caterModule("MyDll.dll")
    , thread()
    , client()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_attachBtn_clicked()
{
    QMessageBox box;

    if(!process.open()) {
        box.setText(process.getLastError());
        box.exec();
        return;
    }

    if(!remoteThread.inject(process, caterModule)) {
        box.setText(remoteThread.getLastError());
        box.exec();
        return;
    }
}

void MainWindow::on_detachBtn_clicked()
{
    this->remoteThread.shutdown();
    this->process.free();
    this->process.close();
}

void MainWindow::on_startServerBtn_clicked()
{
    QMessageBox box;

    if(!thread.start()) {
        box.setText(thread.getLastError());
        box.exec();
    }
}

void MainWindow::on_stopServerBtn_clicked()
{
    QMessageBox box;

    if(!client.connect()) {
        box.setText(client.getLastError());
        box.exec();
    }

    LPCTSTR str = TEXT("bye");
    std::wcout << "send " << str << std::endl;
    if(!client.sendMessage(str)) {
        box.setText(client.getLastError());
        box.exec();
    }
}
