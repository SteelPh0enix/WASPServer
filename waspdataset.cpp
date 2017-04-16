#include "waspdataset.hpp"

WASPDataset::WASPDataset() {}

WASPDataset::WASPDataset(ulong timestamp, std::array<ushort, 3> magnetometer, std::array<ushort, 3> accelerometer,
                         std::array<ushort, 3> gyroscope, std::array<uchar, 5> gases, float temperature, float pressure, float altitude, QString GPS)
                        : m_timestamp(timestamp), m_magnetometer(magnetometer), m_accelerometer(accelerometer), m_gyroscope(gyroscope),
                          m_gases(gases), m_temperature(temperature), m_pressure(pressure), m_altitude(altitude), m_GPS(GPS) {}

WASPDataset::WASPDataset(QString &dataset) {
    if (!(dataset[0] == '@')) throw std::invalid_argument(QString("Corrupted dataset: '" + dataset[0] + "' in the beginning").toStdString());

    // @%d#%d|%d|%d#%d|%d|%d#%d|%d|%d#%d|%d|%d|%d|%d#%d|%d|%d[#%s]
    // mag/accel/gyro/gases/tpa/[gps - optional]
    QStringList datasplit = dataset.split('#');

    if (datasplit.count() < 6) throw std::invalid_argument(QString("Corrupted dataset: " + dataset).toStdString());

    m_timestamp = datasplit[0].remove(0, 1).toULong();

    QStringList tmplist = datasplit[1].split('|');
    if (tmplist.count() != 3) throw std::invalid_argument(QString("Corrupted dataset - magnetometer readings: " + datasplit[1]).toStdString());
    for(size_t i = 0; i < 3; ++i) m_magnetometer[i] = tmplist[i].toUShort();

    tmplist = datasplit[2].split('|');
    if (tmplist.count() != 3) throw std::invalid_argument(QString("Corrupted dataset - accelerometer readings: " + datasplit[2]).toStdString());
    for(size_t i = 0; i < 3; ++i) m_accelerometer[i] = tmplist[i].toUShort();

    tmplist = datasplit[3].split('|');
    if (tmplist.count() != 3) throw std::invalid_argument(QString("Corrupted dataset - gyroscope readings: " + datasplit[3]).toStdString());
    for(size_t i = 0; i < 3; ++i) m_gyroscope[i] = tmplist[i].toUShort();

    tmplist = datasplit[4].split('|');
    if (tmplist.count() != 5) throw std::invalid_argument(QString("Corrupted dataset - gases readings: " + datasplit[4]).toStdString());
    for(size_t i = 0; i < 5; ++i) m_gases[i] = tmplist[i].toUShort();

    tmplist = datasplit[5].split('|');
    if (tmplist.count() != 3) throw std::invalid_argument(QString("Corrupted dataset - TPA readings: " + datasplit[5]).toStdString());
    m_temperature = static_cast<float>(tmplist[0].toShort() * 100);
    m_pressure = static_cast<float>(tmplist[1].toShort() * 100);
    m_altitude = static_cast<float>(tmplist[2].toShort() * 100);

    if (datasplit.count() == 7)
        m_GPS = datasplit[6];
    else
        m_GPS = "";
}

const QString WASPDataset::toString() const {
    QString str;
    QTextStream stream(&str);
    stream << m_timestamp << '\t';
    for (const auto &x: m_magnetometer) stream << x << '\t';
    for (const auto &x: m_accelerometer) stream << x << '\t';
    for (const auto &x: m_gyroscope) stream << x << '\t';
    for (const auto &x: m_gases) stream << x << '\t';
    stream << m_temperature << '\t'
           << m_pressure << '\t'
           << m_altitude << '\t'
           << m_GPS;
    stream.flush();
    return str;
}

const QString WASPDataset::getHeader() {
    return QString("timestamp\t"
                   "magnetometerX\t"
                   "magnetometerY\t"
                   "magnetometerZ\t"
                   "accelerometerX\t"
                   "accelerometerY\t"
                   "accelerometerZ\t"
                   "gyroscopeX\t"
                   "gyroscopeY\t"
                   "gyroscopeZ\t"
                   "gasCH4\t"
                   "gasO3\t"
                   "gasH\t"
                   "gasLPG\t"
                   "gasCO\t"
                   "temperature\t"
                   "pressure\t"
                   "altitude\t"
                   "GPS");
}
