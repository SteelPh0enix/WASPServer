#ifndef WASPREADER_HPP
#define WASPREADER_HPP

#include "portselectdialog.hpp"
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QStringListModel>
#include <QMessageBox>
#include <QThread>
#include "waspdataset.hpp"

namespace WASP {
    class SerialReader : public QObject {
        Q_OBJECT

        bool work, finished;

    public:
        explicit SerialReader(QObject *parent = 0);
    public slots:
        void stopWorking();
        void startWorking();
        void readData(const QSerialPort &port);
    signals:
        void dataReaded(WASP::Dataset data);
        void stopped();
    };

    class Reader : public QObject
    {
        Q_OBJECT
        QStringListModel *m_log;

        void msg(const QString &msg, const QString &msgTitle = "WASP Reader");

        PortSelectDialog dialog;
        QSerialPort serial;
        QSerialPortInfo serialInfo;
        SerialReader *worker;
        QThread readThread;

        void stopped();
    public:
        explicit Reader(QObject *parent = 0, QStringListModel *model = Q_NULLPTR);

        void connect();
        void startReading();
        void stopReading();
    signals:
        void connected();
        void stop();
        void start();
        void sendData(WASP::Dataset data);
    private slots:
        void portIsSelected(QSerialPortInfo port);
        void workerStopped();
        void moveData(WASP::Dataset data);
    };
}

#endif // WASPREADER_HPP
