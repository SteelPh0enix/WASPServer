#ifndef WASPDATASET_HPP
#define WASPDATASET_HPP

#include <QString>
#include <QTextStream>
#include <QStringList>
#include <array>
#include <stdexcept>

struct WASPDataset {
    ulong m_timestamp;
    std::array<ushort, 3> m_magnetometer;
    std::array<ushort, 3> m_accelerometer;
    std::array<ushort, 3> m_gyroscope;
    std::array<uchar, 5> m_gases;
    float m_temperature, m_pressure, m_altitude;
    QString m_GPS;

    WASPDataset();
    WASPDataset(ulong timestamp, std::array<ushort, 3> magnetometer, std::array<ushort, 3> accelerometer,
                            std::array<ushort, 3> gyroscope, std::array<uchar, 5> gases, float temperature,
                            float pressure, float altitude, QString GPS);
    WASPDataset(QString &dataset);

    const QString toString() const;
    static const QString getHeader();
};

#endif // WASPDATASET_HPP
