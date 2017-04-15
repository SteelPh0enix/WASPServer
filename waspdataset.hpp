#ifndef WASPDATASET_HPP
#define WASPDATASET_HPP

#include <QObject>
#include <QString>
#include <cinttypes>
#include "xyz.hpp"

class WASPDataset : public QObject {
    Q_OBJECT

    unsigned long m_timestamp;
    XYZ<uint16_t> m_magnetometer;
    XYZ<uint16_t> m_accelerometer;
    XYZ<uint16_t> m_gyroscope;
    uint8_t m_gas_CH4, m_gas_O3, m_gas_H, m_gas_LPG, m_gas_CO;
    float m_temperature, m_pressure, m_altitude;
    QString m_GPS;

public:
    explicit WASPDataset(QObject *parent = 0);
    explicit WASPDataset(unsigned long timestamp, XYZ<uint16_t> magnetometer, XYZ<uint16_t> accelerometer,
                            XYZ<uint16_t> gyroscope, uint8_t gas_CH4, uint8_t gas_O3, uint8_t gas_H,
                            uint8_t gas_LPG, uint8_t gas_CO, float temperature, float pressure,
                            float altitude, QString GPS, QObject *parent = 0);

    const unsigned long& getTimestamp() const;
    const XYZ<uint16_t>& getMagnetometer() const;
    const XYZ<uint16_t>& getAccelerometer() const;
    const XYZ<uint16_t>& getGyroscope() const;
    const uint8_t& getCH4() const;
    const uint8_t& getO3() const;
    const uint8_t& getH() const;
    const uint8_t& getLPG() const;
    const uint8_t& getCO() const;
    const float& getTemperature() const;
    const float& getPressure() const;
    const float& getAltitude() const;
    const QString& getGPS() const;

signals:

public slots:
};

#endif // WASPDATASET_HPP
