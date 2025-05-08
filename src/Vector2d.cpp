#include "../include/Vector2d.hpp"

Vector2d::Vector2d() {
    x = 0;
    y = 0;
};

Vector2d::Vector2d(float x, float y) {
    this->x = x;
    this->y = y;
};

Vector2d& Vector2d::add(const Vector2d& v) {
    this->x += v.x;
    this->y += v.y;

    return *this;
};

Vector2d& Vector2d::subtract(const Vector2d& v) {
    this->x -= v.x;
    this->y -= v.y;

    return *this;
};

Vector2d& Vector2d::multiply(const Vector2d& v) {
    this->x *= v.x;
    this->y *= v.y;

    return *this;
};

Vector2d& Vector2d::divide(const Vector2d& v) {
    this->x /= v.x;
    this->y /= v.y;

    return *this;
};

Vector2d& operator+(Vector2d& v1, const Vector2d& v2) {
    return v1.add(v2);
};

Vector2d& operator-(Vector2d& v1, const Vector2d& v2) {
    return v1.subtract(v2);
};

Vector2d& operator*(Vector2d& v1, const Vector2d& v2) {
    return v1.multiply(v2);
};

Vector2d& operator/(Vector2d& v1, const Vector2d& v2) {
    return v1.divide(v2);
};

Vector2d& Vector2d::operator+=(const Vector2d& v) {
    return this->add(v);
};

Vector2d& Vector2d::operator-=(const Vector2d& v) {
    return this->subtract(v);
};

Vector2d& Vector2d::operator*=(const Vector2d& v) {
    return this->multiply(v);
};

Vector2d& Vector2d::operator/=(const Vector2d& v) {
    return this->divide(v);
};

Vector2d& Vector2d::operator*(const int& i) {
    this->x *= i;
    this->y *= i;

    return *this;
};

Vector2d& Vector2d::zero() {
    this->x = 0;
    this->y = 0;

    return *this;
};

std::ostream& operator<<(std::ostream& stream, const Vector2d& v) {
    stream << "(" << v.x << ", " << v.y << ")" << std::endl;
    return stream;
};