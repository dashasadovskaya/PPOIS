/**
 * @file main.cpp
 * @author Садовская Д.С.
 * @brief Консольный интерфейс для работы с Multiset.
 * @date 2026
 */

#include "Multiset.h"
#include <iostream>
#include <limits>

static void printMenu() {
    std::cout << "\n Меню \n"
              << " 1. Ввести множество A\n"
              << " 2. Ввести множество B\n"
              << " 3. Показать A и B\n"
              << " 4. Добавить атом в A\n"
              << " 5. Удалить атом из A\n"
              << " 6. Проверить принадлежность (A[x])\n"
              << " 7. Мощность A\n"
              << " 8. A + B  (объединение)\n"
              << " 9. A * B  (пересечение)\n"
              << "10. A - B  (разность)\n"
              << "11. Булеан A\n"
              << "12. A == B ?\n"
              << "13. A пусто?\n"
              << " 0. Выход\n"
              << "Выбор: ";
}

int main() {
    Multiset A, B;
    int choice = -1;

    while (choice != 0) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Введите A: ";
                std::cin >> A;
                break;
            case 2:
                std::cout << "Введите B: ";
                std::cin >> B;
                break;
            case 3:
                std::cout << "A = " << A << '\n';
                std::cout << "B = " << B << '\n';
                break;
            case 4: {
                std::string s;
                std::cout << "Атом: ";
                std::getline(std::cin, s);
                A.add(s);
                std::cout << "A = " << A << '\n';
                break;
            }
            case 5: {
                std::string s;
                std::cout << "Атом: ";
                std::getline(std::cin, s);
                std::cout << (A.remove(s) ? "Удалён\n" : "Не найден\n");
                std::cout << "A = " << A << '\n';
                break;
            }
            case 6: {
                std::string s;
                std::cout << "Атом: ";
                std::getline(std::cin, s);
                std::cout << (A[s] ? "есть\n" : "нет\n");
                break;
            }
            case 7:
                std::cout << "Мощность A = " << A.power() << '\n';
                break;
            case 8:
                std::cout << "A + B = " << (A + B) << '\n';
                break;
            case 9:
                std::cout << "A * B = " << (A * B) << '\n';
                break;
            case 10:
                std::cout << "A - B = " << (A - B) << '\n';
                break;
            case 11:
                std::cout << "Булеан A = " << A.boolean() << '\n';
                break;
            case 12:
                std::cout << (A == B ? "равны\n" : "не равны\n");
                break;
            case 13:
                std::cout << (A.empty() ? "пусто\n" : "не пусто\n");
                break;
            case 0:
                std::cout << "Пока!\n";
                break;
            default:
                std::cout << "Неверный пункт.\n";
                break;
        }
    }
    return 0;
}