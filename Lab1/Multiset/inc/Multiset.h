/**
 * @file Multiset.h
 * @author Садовская Д.С.
 * @brief Объявление класса Multiset (неориентированное мультимножество).
 * @details Элементом может быть атом (строка) или другое множество.
 *          Память под элементы выделяется динамически (new[] / delete[]).
 * @date 2026
 */

#pragma once

#include <iostream>
#include <string>
#include <memory>

/**
 * @brief Неориентированное мультимножество.
 * @details Элементы хранятся в динамическом массиве. Каждый элемент —
 *          либо атом (строка), либо вложенное множество. Кратности
 *          учитываются: {a, a, b} и {a, b} — разные мультимножества.
 */
class Multiset {
public:
    /**
     * @brief Один элемент мультимножества.
     * @details Либо атом (isAtom = true), либо подмножество (isAtom = false).
     */
    struct Element {
        bool isAtom;                        ///< true — атом, false — множество
        std::string atom;                   ///< Значение, если атом
        std::shared_ptr<Multiset> subset;   ///< Подмножество, если не атом

        static Element makeAtom(const std::string& s);
        static Element makeSubset(const Multiset& m);

        bool operator==(const Element& other) const;
        bool operator!=(const Element& other) const;
    };

private:
    Element* elements;      ///< Динамический массив элементов
    size_t   count;         ///< Сколько элементов сейчас
    size_t   capacity;      ///< Сколько вмещает без перевыделения

    /**
     * @brief Увеличивает вместимость массива вдвое.
     */
    void grow();

    /**
     * @brief Добавляет элемент в конец (с расширением при необходимости).
     */
    void append(const Element& e);

    /**
     * @brief Удаляет элемент по индексу (со сдвигом влево).
     */
    void removeAt(size_t index);

    /**
     * @brief Копирует массив из другого объекта.
     */
    void copyFrom(const Multiset& other);

    /**
     * @brief Освобождает память.
     */
    void free();


    static void skipSpaces(const std::string& s, size_t& pos);
    static Multiset parse(const std::string& s, size_t& pos);

public:

    Multiset();
    explicit Multiset(const char* str);
    explicit Multiset(const std::string& str);
    Multiset(const Multiset& other);
    Multiset& operator=(const Multiset& other);
    ~Multiset();


    bool empty() const;
    size_t power() const;

    void add(const std::string& atom);
    void add(const Multiset& subset);

    bool remove(const std::string& atom);
    bool remove(const Multiset& subset);

    bool operator[](const std::string& atom) const;
    bool operator[](const Multiset& subset) const;


    Multiset  operator+(const Multiset& other) const;
    Multiset& operator+=(const Multiset& other);

    Multiset  operator*(const Multiset& other) const;
    Multiset& operator*=(const Multiset& other);

    Multiset  operator-(const Multiset& other) const;
    Multiset& operator-=(const Multiset& other);

    /**
     * @brief Булеан — множество всех подмножеств.
     * @return Multiset, каждый элемент которого — подмножество.
     */
    Multiset boolean() const;


    bool operator==(const Multiset& other) const;
    bool operator!=(const Multiset& other) const;


    friend std::ostream& operator<<(std::ostream& os, const Multiset& m);
    friend std::istream& operator>>(std::istream& is, Multiset& m);

private:
    void print(std::ostream& os) const;
    size_t countAtom(const std::string& atom) const;
    size_t countSubset(const Multiset& subset) const;
};