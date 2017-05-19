#include "waspreader.hpp"

WASP::Reader::Reader(QObject *parent, QStringListModel *model) : QObject(parent), m_log(model), serial(this) {
    QObject::connect(&dialog, &PortSelectDialog::portSelected, this, &WASP::Reader::portIsSelected);
    QObject::connect(&serial, &QSerialPort::readyRead, this, &WASP::Reader::readData);
    serial.setBaudRate(QSerialPort::Baud115200);
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

    msg("Connecting to " + serialInfo.systemLocation() + "with baud 115200");
    if(!serial.open(QIODevice::ReadWrite)) {
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

void WASP::Reader::readData() {
    QByteArray rawdata = serial.readLine();
    QString strdata = QString::fromLatin1(rawdata);
    //if (strdata[0] == '@' && strdata.length() > 80) {
    //QMessageBox::information(Q_NULLPTR, QString::number(strdata.length()), strdata);
    WASP::Dataset data(strdata);
    emit dataReceived(data);
    //}
}
