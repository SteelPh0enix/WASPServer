#include "waspdata.hpp"

WASP::Data::Data(QObject *parent, QStringListModel *logModel) : QObject(parent), m_log(logModel) {

}

void WASP::Data::addData(WASP::Dataset data) {
    m_data.append(data);
    emit dataAdded(data);
}

void WASP::Data::parseToFile(QString filepath) {
    if (m_data.isEmpty()) throw std::length_error("Data vector empty");

    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        throw std::invalid_argument(QString("Couldn't open file for writing: " + filepath).toStdString());

    QTextStream str(&file);
    str << WASP::Dataset::getHeader() << '\n';
    for (const WASP::Dataset& e : m_data)
        str << e.toString() << '\n';

    str.flush();
    file.close();

    msg("Parsed data to " + filepath);
}

void WASP::Data::clearData() {
    m_data.clear();
}

void WASP::Data::loadFromFile(QString filepath) {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::invalid_argument(QString("Couldn't open file for reading: " + filepath).toStdString());
    }

    QTextStream str(&file);
    QString line = str.readLine();
    while(!line.isNull()) {
        try {
            m_data.append(WASP::Dataset(line));
        } catch (std::exception &e) {
            msg(e.what(), "Error while parsing!");
        }
        line = str.readLine();
    }

   msg("Loaded data from " + filepath);
}

void WASP::Data::msg(const QString &msg, const QString &msgTitle) {
    if (m_log != Q_NULLPTR) {
        m_log->insertRow(m_log->rowCount());
        m_log->setData(m_log->index(m_log->rowCount()-1), msg);
    } else {
        QMessageBox::information(Q_NULLPTR, msgTitle, msg);
    }
}
