#ifndef WASPDATA_HPP
#define WASPDATA_HPP

#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringListModel>
#include <QMessageBox>
#include <stdexcept>
#include "waspdataset.hpp"

namespace WASP {
    class Data : public QObject {
        Q_OBJECT

        void msg(const QString &msg, const QString &msgTitle = "WASP Data");

        QVector<WASP::Dataset> m_data;
        QStringListModel *m_log;
    public:
        explicit Data(QObject *parent = 0, QStringListModel *logModel = Q_NULLPTR);

        void parseToFile(QString filepath);
        void loadFromFile(QString filepath);
        void clearData();
        bool isEmpty();
    signals:
        void dataAdded(const WASP::Dataset &data);
    public slots:
        void addData(WASP::Dataset data);
    };
}
#endif // WASPDATA_HPP
