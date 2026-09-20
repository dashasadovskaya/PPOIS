/**
 * @file Rectangle.cpp
 * @author Садовская Д.С.
 * @brief Реализация класса Rectangle.
 * @date 2026
 */

#include "Rectangle.h"
#include <algorithm>

// ---------------- Конструкторы / деструктор ----------------

Rectangle::Rectangle()
    : left(0), bottom(0), right(0), top(0) {}

Rectangle::Rectangle(int l, int b, int r, int t)
    : left(l), bottom(b), right(r), top(t) {
    normalize();
}

Rectangle::Rectangle(const Rectangle& other)
    : left(other.left), bottom(other.bottom),
      right(other.right), top(other.top) {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        left   = other.left;
        bottom = other.bottom;
        right  = other.right;
        top    = other.top;
    }
    return *this;
}

Rectangle::~Rectangle() = default;

// ---------------- Внутреннее ----------------

void Rectangle::normalize() {
    if (left > right)  std::swap(left, right);
    if (bottom > top)  std::swap(bottom, top);
}

// ---------------- Геттеры ----------------

int Rectangle::getLeft()   const { return left; }
int Rectangle::getBottom() const { return bottom; }
int Rectangle::getRight()  const { return right; }
int Rectangle::getTop()    const { return top; }
int Rectangle::getWidth()  const { return right - left; }
int Rectangle::getHeight() const { return top - bottom; }

long long Rectangle::getArea() const {
    return static_cast<long long>(getWidth()) * getHeight();
}

// ---------------- Модификаторы ----------------

Rectangle& Rectangle::move(int dx, int dy) {
    left   += dx;
    right  += dx;
    bottom += dy;
    top    += dy;
    return *this;
}

Rectangle& Rectangle::resize(int newWidth, int newHeight) {
    if (newWidth  < 0) newWidth  = 0;
    if (newHeight < 0) newHeight = 0;
    right = left + newWidth;
    top   = bottom + newHeight;
    return *this;
}

// ---------------- Инкремент / декремент ----------------

Rectangle& Rectangle::operator++() {
    --left;
    --bottom;
    ++right;
    ++top;
    return *this;
}

Rectangle Rectangle::operator++(int) {
    Rectangle tmp(*this);
    ++(*this);
    return tmp;
}

Rectangle& Rectangle::operator--() {
    int newWidth  = std::max(0, getWidth()  - 2);
    int newHeight = std::max(0, getHeight() - 2);
    ++left;
    ++bottom;
    right = left + newWidth;
    top   = bottom + newHeight;
    return *this;
}

Rectangle Rectangle::operator--(int) {
    Rectangle tmp(*this);
    --(*this);
    return tmp;
}

// ---------------- Объединение / пересечение ----------------

Rectangle Rectangle::operator+(const Rectangle& other) const {
    return Rectangle(
        std::min(left,   other.left),
        std::min(bottom, other.bottom),
        std::max(right,  other.right),
        std::max(top,    other.top)
    );
}

Rectangle& Rectangle::operator+=(const Rectangle& other) {
    *this = *this + other;
    return *this;
}

Rectangle Rectangle::operator-(const Rectangle& other) const {
    int l = std::max(left,   other.left);
    int b = std::max(bottom, other.bottom);
    int r = std::min(right,  other.right);
    int t = std::min(top,    other.top);

    if (l >= r || b >= t) {
        return Rectangle(l, b, l, b);
    }
    return Rectangle(l, b, r, t);
}

Rectangle& Rectangle::operator-=(const Rectangle& other) {
    *this = *this - other;
    return *this;
}

// ---------------- Сравнение ----------------

bool Rectangle::operator==(const Rectangle& other) const {
    return left   == other.left   &&
           bottom == other.bottom &&
           right  == other.right  &&
           top    == other.top;
}

bool Rectangle::operator!=(const Rectangle& other) const {
    return !(*this == other);
}

// ---------------- Потоковые операторы ----------------

std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
    os << '(' << r.left << ',' << r.bottom << ")-("
       << r.right << ',' << r.top << ')';
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& r) {
    is >> r.left >> r.bottom >> r.right >> r.top;
    r.normalize();
    return is;
}

// ---------------- Свободные функции ----------------
bool intersects(const Rectangle& a, const Rectangle& b) {
    return std::max(a.getLeft(), b.getLeft()) < std::min(a.getRight(), b.getRight()) &&
           std::max(a.getBottom(), b.getBottom()) < std::min(a.getTop(), b.getTop());
}