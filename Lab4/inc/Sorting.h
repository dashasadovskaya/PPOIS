#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>

class SortException : public std::runtime_error {
public:
    explicit SortException(const std::string& m) : std::runtime_error(m) {}
};

template<typename T>
void librarySort(T* arr, size_t n) {
    if (n <= 1) return;
    if (!arr) throw SortException("Нулевой указатель на массив");

    size_t cap = 2 * n + 1;
    std::vector<bool>  occupied(cap, false);
    std::vector<T>     slots(cap);

    size_t mid = cap / 2;
    slots[mid]    = arr[0];
    occupied[mid] = true;

    for (size_t i = 1; i < n; ++i) {
        std::vector<size_t> occ;
        for (size_t j = 0; j < cap; ++j)
            if (occupied[j]) occ.push_back(j);

        size_t lo = 0, hi = occ.size();
        while (lo < hi) {
            size_t m = (lo + hi) / 2;
            if (slots[occ[m]] < arr[i]) lo = m + 1;
            else hi = m;
        }

        size_t insertPos = cap;
        if (lo == 0) {
            for (size_t j = occ[0]; j > 0; --j)
                if (!occupied[j-1]) { insertPos = j-1; break; }
        } else if (lo == occ.size()) {
            for (size_t j = occ.back() + 1; j < cap; ++j)
                if (!occupied[j]) { insertPos = j; break; }
        } else {
            for (size_t j = occ[lo-1] + 1; j < occ[lo]; ++j)
                if (!occupied[j]) { insertPos = j; break; }
        }

        if (insertPos == cap) {
            std::vector<T> vals;
            for (size_t j = 0; j < cap; ++j)
                if (occupied[j]) vals.push_back(slots[j]);
            vals.push_back(arr[i]);
            std::sort(vals.begin(), vals.end());

            cap = cap * 2 + 1;
            slots.assign(cap, T());
            occupied.assign(cap, false);

            size_t step = cap / (vals.size() + 1);
            for (size_t j = 0; j < vals.size(); ++j) {
                size_t p = (j + 1) * step;
                if (p >= cap) p = cap - 1;
                slots[p]    = vals[j];
                occupied[p] = true;
            }
        } else {
            slots[insertPos]    = arr[i];
            occupied[insertPos] = true;
        }
    }

    size_t k = 0;
    for (size_t j = 0; j < cap && k < n; ++j)
        if (occupied[j]) arr[k++] = slots[j];
}

template<typename T>
void librarySort(std::vector<T>& v) {
    if (v.empty()) return;
    librarySort(v.data(), v.size());
}

template<typename T>
void spreadSort(T* arr, size_t n, size_t buckets = 8) {
    if (n <= 1) return;
    if (!arr) throw SortException("Нулевой указатель на массив");
    if (buckets == 0) throw SortException("Число корзин должно быть > 0");

    T mn = arr[0], mx = arr[0];
    for (size_t i = 1; i < n; ++i) {
        if (arr[i] < mn) mn = arr[i];
        if (mx < arr[i]) mx = arr[i];
    }

    if (!(mn < mx)) return;

    std::vector<std::vector<T>> bs(buckets);
    for (size_t i = 0; i < n; ++i) {
        double v  = static_cast<double>(arr[i]);
        double lo = static_cast<double>(mn);
        double hi = static_cast<double>(mx);
        size_t idx = static_cast<size_t>((v - lo) / (hi - lo) * buckets);
        if (idx >= buckets) idx = buckets - 1;
        bs[idx].push_back(arr[i]);
    }

    size_t k = 0;
    for (auto& b : bs) {
        std::sort(b.begin(), b.end());
        for (auto& x : b) arr[k++] = x;
    }
}

template<typename T>
void spreadSort(std::vector<T>& v, size_t buckets = 8) {
    if (v.empty()) return;
    spreadSort(v.data(), v.size(), buckets);
}