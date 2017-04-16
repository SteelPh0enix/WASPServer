#ifndef WASPDATA_HPP
#define WASPDATA_HPP

#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <stdexcept>
#include "waspdataset.hpp"

class WASPData : public QObject {
    Q_OBJECT

    QVector<WASPDataset> m_data;
    QStringList m_log;
public:
    explicit WASPData(QObject *parent = 0);

    void parseToFile(QString filepath);
    void loadFromFile(QString filepath);
    void clearData();
    const QStringList& getLog() const;
signals:
    void dataAdded(WASPDataset data);
public slots:
    void addData(WASPDataset data);
};

#endif // WASPDATA_HPP
