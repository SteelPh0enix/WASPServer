#include "waspdataset.hpp"

WASP::Dataset::Dataset() {}

WASP::Dataset::Dataset(ulong timestamp, std::array<ushort, 3> magnetometer, std::array<ushort, 3> accelerometer,
                         std::array<ushort, 3> gyroscope, std::array<uchar, 5> gases, ushort humidity, float temperature, float pressure, float altitude, QString GPS)
                        : timestamp(timestamp), magnetometer(magnetometer), accelerometer(accelerometer), gyroscope(gyroscope),
                          gases(gases), humidity(humidity), temperature(temperature), pressure(pressure), altitude(altitude), GPS(GPS) {}

WASP::Dataset::Dataset(QString &dataset) {
    qDebug() << dataset << '\n';
    if (!(dataset[0] == '@')) return; //throw std::invalid_argument(QString("Corrupted dataset: '" + dataset[0] + "' in the beginning").toStdString());

    // @%d#%d|%d|%d#%d|%d|%d#%d|%d|%d#%d|%d|%d|%d|%d#%d|%d|%d|%d[#%s]
    // mag/accel/gyro/gases/thpa/[gps - optional]
    QStringList datasplit = dataset.split('#');

    if (datasplit.count() < 6) return; //throw std::invalid_argument(QString("Corrupted dataset: " + dataset).toStdString());

    timestamp = datasplit[0].remove(0, 1).toULong();

    QStringList tmplist = datasplit[1].split('|');
    if (tmplist.count() != 3) return; //throw std::invalid_argument(QString("Corrupted dataset - magnetometer readings: " + datasplit[1]).toStdString());
    for(size_t i = 0; i < 3; ++i) magnetometer[i] = tmplist[i].toUShort();

    tmplist = datasplit[2].split('|');
    if (tmplist.count() != 3) return; //throw std::invalid_argument(QString("Corrupted dataset - accelerometer readings: " + datasplit[2]).toStdString());
    for(size_t i = 0; i < 3; ++i) accelerometer[i] = tmplist[i].toUShort();

    tmplist = datasplit[3].split('|');
    if (tmplist.count() != 3) return; //throw std::invalid_argument(QString("Corrupted dataset - gyroscope readings: " + datasplit[3]).toStdString());
    for(size_t i = 0; i < 3; ++i) gyroscope[i] = tmplist[i].toUShort();

    tmplist = datasplit[4].split('|');
    if (tmplist.count() != 5) return; //throw std::invalid_argument(QString("Corrupted dataset - gases readings: " + datasplit[4]).toStdString());
    for(size_t i = 0; i < 5; ++i) gases[i] = tmplist[i].toUShort();

    tmplist = datasplit[5].split('|');
    if (tmplist.count() != 4) return; //throw std::invalid_argument(QString("Corrupted dataset - TPA readings: " + datasplit[5]).toStdString());
    temperature = static_cast<float>(tmplist[0].toShort() * 100);
    humidity = tmplist[1].toUShort();
    pressure = static_cast<float>(tmplist[2].toShort() * 100);
    altitude = static_cast<float>(tmplist[3].toShort() * 100);

    if (datasplit.count() == 7)
        GPS = datasplit[6];
    else
        GPS = "";
}

QString WASP::Dataset::toString() const {
    QString str;
    QTextStream stream(&str);
    stream << timestamp << '\t';
    for (const auto &x: magnetometer) stream << x << '\t';
    for (const auto &x: accelerometer) stream << x << '\t';
    for (const auto &x: gyroscope) stream << x << '\t';
    for (const auto &x: gases) stream << x << '\t';
    stream << temperature << '\t'
           << humidity << '\t'
           << pressure << '\t'
           << altitude << '\t'
           << GPS;
    stream.flush();
    return str;
}

int WASP::Dataset::calcDegree() const {
    return qAtan2(magnetometer[0], magnetometer[1]);
}

QTime WASP::Dataset::timestampToTime() const {
    return QTime::fromMSecsSinceStartOfDay(static_cast<int>(timestamp));
}

QString WASP::Dataset::getHeader() {
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
                   "humidity\t"
                   "pressure\t"
                   "altitude\t"
                   "GPS");
}
