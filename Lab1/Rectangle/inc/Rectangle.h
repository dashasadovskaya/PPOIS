/**
 * @file Rectangle.h
 * @author Садовская Д.С.
 * @brief Объявление класса Rectangle.
 * @details Прямоугольник со сторонами, параллельными осям координат,
 *          с целочисленными координатами вершин.
 * @date 2026
 * @version 1.0
 */

#pragma once

#include <iostream>

/**
 * @brief Прямоугольник со сторонами, параллельными осям координат.
 * @details Задаётся двумя точками: (left, bottom) — левый нижний угол,
 *          (right, top) — правый верхний угол.
 *          Инвариант: left <= right, bottom <= top.
 * @see intersects
 */
class Rectangle {
private:
    int left;   ///< X левого нижнего угла
    int bottom; ///< Y левого нижнего угла
    int right;  ///< X правого верхнего угла
    int top;    ///< Y правого верхнего угла

    /**
     * @brief Приводит координаты к инварианту left <= right, bottom <= top.
     */
    void normalize();

public:
    // ---------------- Конструкторы / деструктор ----------------

    /**
     * @brief Конструктор по умолчанию.
     * @details Создаёт вырожденный прямоугольник в точке (0,0).
     */
    Rectangle();

    /**
     * @brief Конструктор по двум углам.
     * @param l X левого нижнего угла
     * @param b Y левого нижнего угла
     * @param r X правого верхнего угла
     * @param t Y правого верхнего угла
     */
    Rectangle(int l, int b, int r, int t);

    /**
     * @brief Конструктор копирования.
     * @param other копируемый объект
     */
    Rectangle(const Rectangle& other);

    /**
     * @brief Оператор присваивания.
     * @param other присваиваемый объект
     * @return ссылка на себя
     */
    Rectangle& operator=(const Rectangle& other);

    /**
     * @brief Деструктор.
     */
    ~Rectangle();

    // ---------------- Геттеры ----------------

    /// @return X левого нижнего угла
    int getLeft()   const;
    /// @return Y левого нижнего угла
    int getBottom() const;
    /// @return X правого верхнего угла
    int getRight()  const;
    /// @return Y правого верхнего угла
    int getTop()    const;
    /// @return ширина прямоугольника
    int getWidth()  const;
    /// @return высота прямоугольника
    int getHeight() const;
    /// @return площадь прямоугольника
    long long getArea() const;

    // ---------------- Модификаторы ----------------

    /**
     * @brief Перемещает прямоугольник.
     * @param dx смещение по X
     * @param dy смещение по Y
     * @return ссылка на себя
     */
    Rectangle& move(int dx, int dy);

    /**
     * @brief Изменяет размер, не меняя левый нижний угол.
     * @param newWidth новая ширина (отрицательная → 0)
     * @param newHeight новая высота (отрицательная → 0)
     * @return ссылка на себя
     */
    Rectangle& resize(int newWidth, int newHeight);

    // ---------------- Инкремент / декремент ----------------

    /// @brief Префиксный ++: расширяет на 1 по каждой оси.
    Rectangle& operator++();
    /// @brief Постфиксный ++.
    Rectangle  operator++(int);
    /// @brief Префиксный --: сужает на 1 по каждой оси.
    Rectangle& operator--();
    /// @brief Постфиксный --.
    Rectangle  operator--(int);

    // ---------------- Объединение / пересечение ----------------

    /**
     * @brief Наименьший прямоугольник, содержащий оба.
     * @param other второй прямоугольник
     * @return новый прямоугольник
     */
    Rectangle  operator+(const Rectangle& other) const;

    /**
     * @brief Наименьший прямоугольник, содержащий оба, с присваиванием.
     * @param other второй прямоугольник
     * @return ссылка на себя
     */
    Rectangle& operator+=(const Rectangle& other);

    /**
     * @brief Пересечение двух прямоугольников.
     * @details Если пересечения нет, возвращается вырожденный
     *          прямоугольник с нулевой шириной и высотой.
     * @param other второй прямоугольник
     * @return новый прямоугольник
     */
    Rectangle  operator-(const Rectangle& other) const;

    /**
     * @brief Пересечение с присваиванием.
     * @param other второй прямоугольник
     * @return ссылка на себя
     */
    Rectangle& operator-=(const Rectangle& other);

    // ---------------- Сравнение ----------------

    /// @brief Полное равенство (совпадают все 4 координаты).
    bool operator==(const Rectangle& other) const;
    /// @brief Отрицание operator==.
    bool operator!=(const Rectangle& other) const;

    // ---------------- Потоковые операторы ----------------

    /**
     * @brief Вывод в поток в формате "(left,bottom)-(right,top)".
     * @param os выходной поток
     * @param r прямоугольник
     * @return ссылка на поток
     */
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& r);

    /**
     * @brief Ввод из потока: 4 целых числа (left bottom right top).
     * @param is входной поток
     * @param r прямоугольник
     * @return ссылка на поток
     */
    friend std::istream& operator>>(std::istream& is, Rectangle& r);
};

/**
 * @brief Проверка: пересекаются ли два прямоугольника.
 * @param a первый
 * @param b второй
 * @return true, если пересечение непусто
 */
bool intersects(const Rectangle& a, const Rectangle& b);