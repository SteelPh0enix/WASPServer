#include "waspreader.hpp"

WASP::Reader::Reader(QObject *parent, QStringListModel *model) : QObject(parent), m_log(model), serial(this) {
    QObject::connect(&dialog, &PortSelectDialog::portSelected, this, &WASP::Reader::portIsSelected);
    serial.setBaudRate(QSerialPort::Baud38400);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
}

void WASP::Reader::connect() {
    if (serial.isOpen()) serial.close();
    dialog.selectPort();
}

void WASP::Reader::portIsSelected(QSerialPortInfo port) {
    serialInfo = port;
    serial.setPort(serialInfo);
    msg("Selected port: " + port.systemLocation());

    msg("Connecting to " + serialInfo.systemLocation() + "with baud 38400");
    if(!serial.open(QSerialPort::ReadWrite | QSerialPort::Text)) {
        msg("Error #" + QString::number(serial.error()) + " - couldn't connect!");
        msg(serial.errorString());
    }
}

void WASP::Reader::msg(const QString &msg, const QString &msgTitle) {
    if (m_log != Q_NULLPTR) {
        m_log->insertRow(m_log->rowCount());
        m_log->setData(m_log->index(m_log->rowCount()-1), msg);
    } else {
        QMessageBox::information(Q_NULLPTR, msgTitle, msg);
    }
}

void WASP::Reader::startReading() {
    worker = new SerialReader(this);
    worker->moveToThread(&readThread);
    QObject::connect(worker, &SerialReader::startWorking, this, &WASP::Reader::start);
    QObject::connect(worker, &SerialReader::stopWorking, this, &WASP::Reader::stop);
    QObject::connect(worker, &SerialReader::dataReaded, this, &WASP::Reader::moveData);
    readThread.start();
}

void WASP::Reader::stopReading() {
    emit stop();
}

void WASP::Reader::workerStopped() {
    readThread.quit();
    readThread.wait();
}

void WASP::Reader::moveData(WASP::Dataset data) {
    emit sendData(data);
}

WASP::SerialReader::SerialReader(QObject *parent) : QObject(parent), work(true), finished(false) {

}

void WASP::SerialReader::stopWorking() {
    work = false;
}

void WASP::SerialReader::startWorking() {
    work = true;
}

void WASP::SerialReader::readData(const QSerialPort &port) {
    WASP::Dataset readed;
    QString rawdata;
    while(work) {
        //TODO: go back to fucking signal&slot, because i fucked up hard
        //read the docs next time
        emit dataReaded(readed);
    }
    emit stopped();
}
