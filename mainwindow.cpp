#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CanSatWindow) {
    ui->setupUi(this);

    logModel.setStringList(data.getLog());
    ui->listView_Log->setModel(&logModel);

    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(exit()));
    connect(ui->action_ConnectToWASP, SIGNAL(triggered()), this, SLOT(connectToWASP()));
    connect(ui->action_ParseLog, SIGNAL(triggered()), this, SLOT(parseFile()));
    connect(ui->action_SaveData, SIGNAL(triggered()), this, SLOT(saveData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit() {
    QApplication::exit();
}

void MainWindow::parseFile() {
    QMessageBox msg;
    msg.setText("To be implemented");
    msg.setInformativeText("parseFile");
    msg.exec();
}

void MainWindow::connectToWASP() {
    QMessageBox msg;
    msg.setText("To be implemented");
    msg.setInformativeText("connectToWASP");
    msg.exec();
}

void MainWindow::saveData() {
    QMessageBox msg;
    msg.setText("To be implemented");
    msg.setInformativeText("saveData");
    msg.exec();
}
