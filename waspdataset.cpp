#include "waspdataset.hpp"

WASPDataset::WASPDataset(QObject *parent) : QObject(parent) {}

WASPDataset::WASPDataset(unsigned long timestamp, XYZ<uint16_t> magnetometer, XYZ<uint16_t> accelerometer,
                         XYZ<uint16_t> gyroscope, uint8_t gas_CH4, uint8_t gas_O3, uint8_t gas_H,
                         uint8_t gas_LPG, uint8_t gas_CO, float temperature, float pressure, float altitude, QString GPS, QObject *parent)
                        : QObject(parent), m_timestamp(timestamp), m_magnetometer(magnetometer), m_accelerometer(accelerometer),
                          m_gyroscope(gyroscope), m_gas_CH4(gas_CH4), m_gas_O3(gas_O3), m_gas_H(gas_H), m_gas_LPG(gas_LPG),
                          m_gas_CO(gas_CO), m_temperature(temperature), m_pressure(pressure), m_altitude(altitude), m_GPS(GPS) {}

