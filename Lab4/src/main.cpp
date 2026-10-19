#include "Sorting.h"
#include "Graph.h"
#include <iostream>
#include <limits>
#include <string>

struct Student {
    std::string name;
    int grade;

    bool operator<(const Student& o) const { return grade < o.grade; }
    bool operator==(const Student& o) const { return grade == o.grade; }
};

std::ostream& operator<<(std::ostream& os, const Student& s) {
    return os << s.name << "(" << s.grade << ")";
}

static void demoSorting() {
    std::cout << "\n Library sort (int) \n";
    int a[] = {5, 3, 8, 1, 9, 2, 7};
    size_t n = sizeof(a)/sizeof(a[0]);
    librarySort(a, n);
    for (size_t i = 0; i < n; ++i) std::cout << a[i] << ' ';
    std::cout << '\n';

    std::cout << "\n Spread sort (int) \n";
    int b[] = {5, 3, 8, 1, 9, 2, 7};
    spreadSort(b, n);
    for (size_t i = 0; i < n; ++i) std::cout << b[i] << ' ';
    std::cout << '\n';

    std::cout << "\n Library sort (Student) \n";
    std::vector<Student> students = {
        {"Иван", 4}, {"Пётр", 5}, {"Аня", 3}, {"Оля", 5}, {"Максим", 2}
    };
    librarySort(students);
    for (auto& s : students) std::cout << s << ' ';
    std::cout << '\n';
}

static void demoGraph() {
    Graph<std::string> g;

    auto v1 = g.addVertex("Минск");
    auto v2 = g.addVertex("Гомель");
    auto v3 = g.addVertex("Брест");
    auto v4 = g.addVertex("Гродно");

    g.addEdge(v1, v2);
    g.addEdge(v1, v3);
    g.addEdge(v2, v4);
    g.addEdge(v3, v4);

    std::cout << g;
    std::cout << "Степень Минска: " << g.degree(v1) << '\n';
    std::cout << "Есть ребро Минск-Гомель? " << (g.hasEdge(v1, v2) ? "да" : "нет") << '\n';
}

static void printMenu() {
    std::cout << "\n МЕНЮ \n"
              << "1. Демонстрация сортировок\n"
              << "2. Демонстрация графа\n"
              << "0. Выход\n"
              << "Выбор: ";
}

int main() {
    try {
        int choice = -1;
        while (choice != 0) {
            printMenu();
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            switch (choice) {
                case 1: demoSorting(); break;
                case 2: demoGraph();   break;
                case 0: std::cout << "Пока!\n"; break;
                default: std::cout << "Неверный пункт\n"; break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    return 0;
}