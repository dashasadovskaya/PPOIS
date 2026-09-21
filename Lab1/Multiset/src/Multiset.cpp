/**
 * @file Multiset.cpp
 * @author Садовская Д.С.
 * @brief Реализация класса Multiset.
 * @date 2026
 */

#include "Multiset.h"
#include <algorithm>
#include <sstream>
#include <cctype>

Multiset::Element Multiset::Element::makeAtom(const std::string& s) {
    Element e;
    e.isAtom = true;
    e.atom = s;
    e.subset = nullptr;
    return e;
}

Multiset::Element Multiset::Element::makeSubset(const Multiset& m) {
    Element e;
    e.isAtom = false;
    e.subset = std::make_shared<Multiset>(m);
    return e;
}

bool Multiset::Element::operator==(const Element& other) const {
    if (isAtom != other.isAtom) return false;
    if (isAtom) return atom == other.atom;
    return *subset == *other.subset;
}

bool Multiset::Element::operator!=(const Element& other) const {
    return !(*this == other);
}

void Multiset::grow() {
    size_t newCap = (capacity == 0) ? 4 : capacity * 2;
    Element* newArr = new Element[newCap];
    for (size_t i = 0; i < count; ++i) {
        newArr[i] = elements[i];
    }
    delete[] elements;
    elements = newArr;
    capacity = newCap;
}

void Multiset::append(const Element& e) {
    if (count == capacity) grow();
    elements[count++] = e;
}

void Multiset::removeAt(size_t index) {
    for (size_t i = index; i + 1 < count; ++i) {
        elements[i] = elements[i + 1];
    }
    --count;
}

void Multiset::copyFrom(const Multiset& other) {
    count = other.count;
    capacity = other.capacity;
    if (capacity == 0) {
        elements = nullptr;
        return;
    }
    elements = new Element[capacity];
    for (size_t i = 0; i < count; ++i) {
        elements[i] = other.elements[i];
    }
}

void Multiset::free() {
    delete[] elements;
    elements = nullptr;
    count = 0;
    capacity = 0;
}

Multiset::Multiset()
    : elements(nullptr), count(0), capacity(0) {}

Multiset::Multiset(const char* str)
    : elements(nullptr), count(0), capacity(0) {
    std::string s(str);
    size_t pos = 0;
    Multiset tmp = parse(s, pos);
    copyFrom(tmp);
}

Multiset::Multiset(const std::string& str)
    : elements(nullptr), count(0), capacity(0) {
    size_t pos = 0;
    Multiset tmp = parse(str, pos);
    copyFrom(tmp);
}

Multiset::Multiset(const Multiset& other)
    : elements(nullptr), count(0), capacity(0) {
    copyFrom(other);
}

Multiset& Multiset::operator=(const Multiset& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Multiset::~Multiset() {
    free();
}

void Multiset::skipSpaces(const std::string& s, size_t& pos) {
    while (pos < s.size() &&
           std::isspace(static_cast<unsigned char>(s[pos]))) {
        ++pos;
    }
}

Multiset Multiset::parse(const std::string& s, size_t& pos) {
    Multiset result;
    skipSpaces(s, pos);

    if (pos >= s.size() || s[pos] != '{') {
        return result;
    }
    ++pos;   // пропустили '{'

    while (pos < s.size() && s[pos] != '}') {
        skipSpaces(s, pos);
        if (pos >= s.size() || s[pos] == '}') break;

        if (s[pos] == '{') {
            Multiset sub = parse(s, pos);
            result.add(sub);
        } else {
            std::string atom;
            while (pos < s.size() && s[pos] != ',' && s[pos] != '}') {
                atom += s[pos];
                ++pos;
            }
            while (!atom.empty() &&
                   std::isspace(static_cast<unsigned char>(atom.back()))) {
                atom.pop_back();
            }
            if (!atom.empty()) result.add(atom);
        }

        skipSpaces(s, pos);
        if (pos < s.size() && s[pos] == ',') ++pos;
    }

    if (pos < s.size() && s[pos] == '}') ++pos;
    return result;
}

bool Multiset::empty() const {
    return count == 0;
}

size_t Multiset::power() const {
    return count;
}

void Multiset::add(const std::string& atom) {
    append(Element::makeAtom(atom));
}

void Multiset::add(const Multiset& subset) {
    append(Element::makeSubset(subset));
}

bool Multiset::remove(const std::string& atom) {
    for (size_t i = 0; i < count; ++i) {
        if (elements[i].isAtom && elements[i].atom == atom) {
            removeAt(i);
            return true;
        }
    }
    return false;
}

bool Multiset::remove(const Multiset& subset) {
    for (size_t i = 0; i < count; ++i) {
        if (!elements[i].isAtom && *elements[i].subset == subset) {
            removeAt(i);
            return true;
        }
    }
    return false;
}

size_t Multiset::countAtom(const std::string& atom) const {
    size_t n = 0;
    for (size_t i = 0; i < count; ++i) {
        if (elements[i].isAtom && elements[i].atom == atom) ++n;
    }
    return n;
}

size_t Multiset::countSubset(const Multiset& subset) const {
    size_t n = 0;
    for (size_t i = 0; i < count; ++i) {
        if (!elements[i].isAtom && *elements[i].subset == subset) ++n;
    }
    return n;
}

bool Multiset::operator[](const std::string& atom) const {
    return countAtom(atom) > 0;
}

bool Multiset::operator[](const Multiset& subset) const {
    return countSubset(subset) > 0;
}

Multiset Multiset::operator+(const Multiset& other) const {
    Multiset result(*this);
    for (size_t i = 0; i < other.count; ++i) {
        const Element& e = other.elements[i];
        if (e.isAtom) {
            size_t need = other.countAtom(e.atom);
            size_t have = result.countAtom(e.atom);
            while (have < need) {
                result.add(e.atom);
                ++have;
            }
        } else {
            size_t need = other.countSubset(*e.subset);
            size_t have = result.countSubset(*e.subset);
            while (have < need) {
                result.add(*e.subset);
                ++have;
            }
        }
    }
    return result;
}

Multiset& Multiset::operator+=(const Multiset& other) {
    *this = *this + other;
    return *this;
}

Multiset Multiset::operator*(const Multiset& other) const {
    Multiset result;
    for (size_t i = 0; i < count; ++i) {
        const Element& e = elements[i];
        if (e.isAtom) {
            size_t a = countAtom(e.atom);
            size_t b = other.countAtom(e.atom);
            size_t take = std::min(a, b);
            size_t already = result.countAtom(e.atom);
            while (already < take) {
                result.add(e.atom);
                ++already;
            }
        } else {
            size_t a = countSubset(*e.subset);
            size_t b = other.countSubset(*e.subset);
            size_t take = std::min(a, b);
            size_t already = result.countSubset(*e.subset);
            while (already < take) {
                result.add(*e.subset);
                ++already;
            }
        }
    }
    return result;
}

Multiset& Multiset::operator*=(const Multiset& other) {
    *this = *this * other;
    return *this;
}

Multiset Multiset::operator-(const Multiset& other) const {
    Multiset result;
    for (size_t i = 0; i < count; ++i) {
        const Element& e = elements[i];
        if (e.isAtom) {
            size_t a = countAtom(e.atom);
            size_t b = other.countAtom(e.atom);
            size_t take = (a > b) ? (a - b) : 0;
            size_t already = result.countAtom(e.atom);
            while (already < take) {
                result.add(e.atom);
                ++already;
            }
        } else {
            size_t a = countSubset(*e.subset);
            size_t b = other.countSubset(*e.subset);
            size_t take = (a > b) ? (a - b) : 0;
            size_t already = result.countSubset(*e.subset);
            while (already < take) {
                result.add(*e.subset);
                ++already;
            }
        }
    }
    return result;
}

Multiset& Multiset::operator-=(const Multiset& other) {
    *this = *this - other;
    return *this;
}

Multiset Multiset::boolean() const {
    Multiset result;
    result.add(Multiset());   // пустое подмножество

    for (size_t i = 0; i < count; ++i) {
        size_t n = result.count;
        for (size_t j = 0; j < n; ++j) {
            Multiset copy = *result.elements[j].subset;
            if (elements[i].isAtom) {
                copy.add(elements[i].atom);
            } else {
                copy.add(*elements[i].subset);
            }
            result.add(copy);
        }
    }
    return result;
}

bool Multiset::operator==(const Multiset& other) const {
    if (count != other.count) return false;

    bool* used = new bool[other.count]();
    bool ok = true;

    for (size_t i = 0; i < count && ok; ++i) {
        bool found = false;
        for (size_t j = 0; j < other.count; ++j) {
            if (!used[j] && elements[i] == other.elements[j]) {
                used[j] = true;
                found = true;
                break;
            }
        }
        if (!found) ok = false;
    }

    delete[] used;
    return ok;
}

bool Multiset::operator!=(const Multiset& other) const {
    return !(*this == other);
}

void Multiset::print(std::ostream& os) const {
    os << '{';
    for (size_t i = 0; i < count; ++i) {
        if (i > 0) os << ", ";
        if (elements[i].isAtom) {
            os << elements[i].atom;
        } else {
            elements[i].subset->print(os);
        }
    }
    os << '}';
}

std::ostream& operator<<(std::ostream& os, const Multiset& m) {
    m.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Multiset& m) {
    std::string line;
    std::getline(is, line);
    size_t pos = 0;
    m = Multiset::parse(line, pos);
    return is;
}