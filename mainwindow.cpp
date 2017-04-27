#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CanSatWindow),
    data(this, &logModel), reader(this, &logModel) {
    ui->setupUi(this);

    ui->listView_Log->setModel(&logModel);
    ui->listView_GPS->setModel(&gpsModel);

    QObject::connect(ui->action_Exit, &QAction::triggered, this, &MainWindow::exit);
    QObject::connect(ui->action_ConnectToWASP, &QAction::triggered, this, &MainWindow::connectToWASP);
    QObject::connect(ui->action_ParseLog, &QAction::triggered, this, &MainWindow::parseFile);
    QObject::connect(ui->action_SaveData, &QAction::triggered, this, &MainWindow::saveData);
    QObject::connect(&data, &WASP::Data::dataAdded, this, &MainWindow::update);
    QObject::connect(&reader, &WASP::Reader::sendData, &data, &WASP::Data::addData);
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
   reader.connect();
}

void MainWindow::saveData() {
    if (data.isEmpty()) {
        QMessageBox::critical(this, "Error", "No data to save!");
        return;
    }

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
