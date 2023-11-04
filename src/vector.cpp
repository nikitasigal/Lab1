#include "vector.hpp"

using namespace std;

Vector::Vector() = default;

Vector::Vector(double x) : Vector(x, x) {}

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector::Vector(const Vector& other) = default;

Vector::Vector(Vector&& other) = default;

Vector::~Vector() = default;

Vector& Vector::operator=(const Vector& other) {
    if (this == &other)
        return *this;

    x = other.x;
    y = other.y;
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this == &other)
        return *this;

    x = other.x;
    y = other.y;
    return *this;
}

Vector& Vector::operator+=(const Vector& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector& Vector::operator*=(const double scale) {
    x *= scale;
    y *= scale;
    return *this;
}

Vector operator+(Vector lhs, const Vector& rhs) {
    lhs += rhs;
    return lhs;
}

Vector operator-(Vector lhs, const Vector& rhs) {
    lhs -= rhs;
    return lhs;
}

Vector operator*(Vector self, const double scale) {
    self *= scale;
    return self;
}

Vector operator*(const double scale, Vector self) {
    self *= scale;
    return self;
}

ostream& operator<<(ostream& os, const Vector& obj) {
    os << obj.x << " " << obj.y;
    return os;
}

istream& operator>>(istream& is, Vector& obj) {
    is >> obj.x >> obj.y;
    return is;
}

double operator!(const Vector& obj) {
    return sqrt(obj.x * obj.x + obj.y * obj.y);
}
