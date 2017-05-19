#ifndef WASPDATASET_HPP
#define WASPDATASET_HPP

#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QTime>
#include <QtMath>
#include <array>
#include <stdexcept>
#include <QDebug>

namespace WASP {
    struct Dataset {
        ulong timestamp;
        std::array<ushort, 3> magnetometer;
        std::array<ushort, 3> accelerometer;
        std::array<ushort, 3> gyroscope;
        std::array<uchar, 5> gases;
        ushort humidity;
        float temperature, pressure, altitude;
        QString GPS;

        Dataset();
        Dataset(ulong timestamp, std::array<ushort, 3> magnetometer, std::array<ushort, 3> accelerometer,
                                std::array<ushort, 3> gyroscope, std::array<uchar, 5> gases, ushort humidity,
                                float temperature, float pressure, float altitude, QString GPS);
        Dataset(QString &dataset);

        QString toString() const;
        int calcDegree() const;
        QTime timestampToTime() const;

        static QString getHeader();
    };
}

#endif // WASPDATASET_HPP
