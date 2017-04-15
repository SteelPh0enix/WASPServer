#ifndef XYZ_HPP
#define XYZ_HPP

#include <stdexcept>
#include <string>

template<typename T>
class XYZ
{
    T m_x, m_y, m_z;
public:
    XYZ() {}
    XYZ(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}
    XYZ(const XYZ<T>& other) : m_x(other.getX()), m_y(other.getY()), m_z(other.getZ()) {}
    template<typename N>
    XYZ(const XYZ<N>& other) : m_x(static_cast<N>(other.getX())), m_y(static_cast<N>(other.getY())), m_z(static_cast<N>(other.getZ())) {}

    const T getX() const { return m_x; }
    const T getY() const { return m_y; }
    const T getZ() const { return m_z; }

    void setX(T x) { m_x = x; }
    void setY(T y) { m_y = y; }
    void setZ(T z) { m_z = z; }

    T& operator [](char key) {
        switch(key) {
        case 'x' : return m_x;
            break;
        case 'y' : return m_y;
            break;
        case 'z' : return m_z;
            break;
        default:
            throw std::invalid_argument(key + std::string(" - invalid argument for XYZ<T>[]"));
        }
    }

    const T& operator [](char key) const {
        return const_cast<XYZ<T>*>(this)->operator [](key);
    }
};

#endif // XYZ_HPP
