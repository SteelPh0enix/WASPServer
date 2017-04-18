#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CanSatWindow),
    data(this, &logModel), reader(this) {
    ui->setupUi(this);

    ui->listView_Log->setModel(&logModel);
    ui->listView_GPS->setModel(&gpsModel);

    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(exit()));
    connect(ui->action_ConnectToWASP, SIGNAL(triggered()), this, SLOT(connectToWASP()));
    connect(ui->action_ParseLog, SIGNAL(triggered()), this, SLOT(parseFile()));
    connect(ui->action_SaveData, SIGNAL(triggered()), this, SLOT(saveData()));
    connect(&data, SIGNAL(dataAdded(WASP::Dataset)), this, SLOT(update(WASP::Dataset)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit() {
    QApplication::exit();
}

void MainWindow::parseFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Otwórz plik z logiem", QString(), "Pliki tekstowe (*.txt)");
    if (filename.isNull()) return;

    try {
        data.loadFromFile(filename);
    } catch (std::exception &e) {
        QMessageBox::critical(this, QString("Error"), e.what());
    }
    saveData();
}

void MainWindow::connectToWASP() {
    QMessageBox::information(this, QString("connectToWASP"), QString("To be implemented"));
}

void MainWindow::saveData() {
    QString filename = QFileDialog::getSaveFileName(this, "Wybierz plik do zapisu", QString(), "Pliki tekstowe (*.txt)");
    if (filename.isNull()) return;

    try {
        data.parseToFile(filename);
    } catch (std::exception &e) {
        QMessageBox::critical(this, QString("Error"), e.what());
    }
}

void MainWindow::update(const WASP::Dataset &data) {
    ui->lcdNumber_CH4->display(data.gases[0]);
    ui->lcdNumber_O3->display(data.gases[1]);
    ui->lcdNumber_H->display(data.gases[2]);
    ui->lcdNumber_LPG->display(data.gases[3]);
    ui->lcdNumber_CO->display(data.gases[4]);

    gpsModel.insertRow(gpsModel.rowCount());
    gpsModel.setData(gpsModel.index(gpsModel.rowCount()-1), data.GPS);

    ui->label_Gyro->setText(QString("%1 / %2 / %3").arg(data.gyroscope[0], data.gyroscope[1], data.gyroscope[2]));
    ui->label_Accel->setText(QString("%1 / %2 / %3").arg(data.accelerometer[0], data.accelerometer[1], data.accelerometer[2]));
    ui->label_Magnet->setText(QString("%1 / %2 / %3").arg(data.magnetometer[0], data.magnetometer[1], data.magnetometer[2]));

    ui->lcdNumber_Temperature->display(data.temperature);
    ui->lcdNumber_Humidity->display(data.humidity);

    ui->dial_Compass->setValue(data.calcDegree());

    ui->lcdNumber_Altitude->display(data.altitude);
    ui->lcdNumber_Pressure->display(data.pressure);

    ui->label_Time->setText(data.timestampToTime().toString("hh:mm:ss.zzz"));
}
