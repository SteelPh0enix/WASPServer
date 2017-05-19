#ifndef WASPREADER_HPP
#define WASPREADER_HPP

#include "portselectdialog.hpp"
#include "waspdataset.hpp"
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QStringListModel>
#include <QMessageBox>

namespace WASP {
    class Reader : public QObject
    {
        Q_OBJECT
        QStringListModel *m_log;

        void msg(const QString &msg, const QString &msgTitle = "WASP Reader");

        PortSelectDialog dialog;
        QSerialPort serial;
        QSerialPortInfo serialInfo;

    public:
        explicit Reader(QObject *parent = 0, QStringListModel *model = Q_NULLPTR);

        void connect();

    signals:
        void connected();
        void dataReceived(WASP::Dataset data);
    private slots:
        void portIsSelected(QSerialPortInfo port);
        void readData();
    };
}

#endif // WASPREADER_HPP
