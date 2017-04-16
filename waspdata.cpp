#include "waspdata.hpp"

WASPData::WASPData(QObject *parent) : QObject(parent) {

}

void WASPData::addData(WASPDataset data) {
    m_data.append(data);
}

void WASPData::parseToFile(QString filepath) {
    if (m_data.isEmpty()) throw std::length_error("Data vector empty");

    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        throw std::invalid_argument(QString("Couldn't open file for writing: " + filepath).toStdString());

    QTextStream str(&file);
    str << WASPDataset::getHeader();
    for (const WASPDataset& e : m_data)
        str << e.toString();

    str.flush();
    file.close();
}

void WASPData::clearData() {
    m_data.clear();
}

void WASPData::loadFromFile(QString filepath) {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::invalid_argument(QString("Couldn't open file for reading: " + filepath).toStdString());
    }

    QTextStream str(&file);
    QString line = str.readLine();
    while(!line.isNull()) {
        try {
            m_data.append(WASPDataset(line));
        } catch (std::exception &e) {
            m_log.append(e.what());
        }
        line = str.readLine();
    }
}

const QStringList& WASPData::getLog() const {
    return m_log;
}
