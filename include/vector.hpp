#pragma once
#include <iostream>

using namespace std;

class Vector {
   public:
    double x = 0, y = 0;
    Vector();
    Vector(double x);
    Vector(double x, double y);
    Vector(const Vector& other);
    Vector(Vector&& other);
    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(const double scale);

    friend Vector operator+(Vector lhs, const Vector& rhs);
    friend Vector operator-(Vector lhs, const Vector& rhs);
    friend Vector operator*(Vector self, const double scale);
    friend Vector operator*(const double scale, Vector self);

    friend ostream& operator<<(ostream& os, const Vector& obj);
    friend istream& operator>>(istream& is, Vector& obj);

    friend double operator!(const Vector& obj);
};

typedef Vector Point;