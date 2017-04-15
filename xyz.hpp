#ifndef XYZ_HPP
#define XYZ_HPP

#include <stdexcept>
#include <string>

template<typename T>
struct XYZ {
    T x, y, z;

    XYZ() {}
    XYZ(T arg_x, T arg_y, T arg_z) : x(arg_x), y(arg_y), z(arg_z) {}
    XYZ(const XYZ<T>& other) : x(other.x), y(other.y), z(other.z) {}
    template<typename N>
    XYZ(const XYZ<N>& other) : x(static_cast<N>(other.x)), y(static_cast<N>(other.y)), z(static_cast<N>(other.z)) {}
};

#endif // XYZ_HPP
