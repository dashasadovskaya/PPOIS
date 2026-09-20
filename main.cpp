/**
 * @file main.cpp
 * @author Садовская Д.С.
 * @brief Консольный интерфейс для работы с классом Rectangle.
 * @details Интерфейс полностью отделён от реализации класса.
 * @date 2026
 */

#include "inc/Rectangle.h"
#include <iostream>
#include <limits>

/**
 * @brief Печатает главное меню.
 */
static void printMenu() {
    std::cout << "\n===== Меню =====\n"
              << " 1. Ввести прямоугольник A\n"
              << " 2. Ввести прямоугольник B\n"
              << " 3. Показать A и B\n"
              << " 4. Переместить A\n"
              << " 5. Изменить размер A\n"
              << " 6. ++A (префикс)\n"
              << " 7. A++ (постфикс)\n"
              << " 8. --A (префикс)\n"
              << " 9. A-- (постфикс)\n"
              << "10. C = A + B  (объединение)\n"
              << "11. C = A - B  (пересечение)\n"
              << "12. A += B\n"
              << "13. A -= B\n"
              << "14. A == B ?\n"
              << "15. Пересекаются ли A и B?\n"
              << "16. Показать площадь A\n"
              << " 0. Выход\n"
              << "Выбор: ";
}

/**
 * @brief Очищает поток ввода после ошибки.
 */
static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Точка входа.
 * @return 0 при успешном завершении
 */
int main() {
    Rectangle A, B;
    bool hasA = false, hasB = false;

    int choice = -1;
    while (choice != 0) {
        printMenu();
        if (!(std::cin >> choice)) {
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "Введите left bottom right top: ";
                std::cin >> A;
                hasA = true;
                break;

            case 2:
                std::cout << "Введите left bottom right top: ";
                std::cin >> B;
                hasB = true;
                break;

            case 3:
                std::cout << "A = " << (hasA ? "" : "(не задан) ") << A << '\n';
                std::cout << "B = " << (hasB ? "" : "(не задан) ") << B << '\n';
                break;

            case 4: {
                int dx, dy;
                std::cout << "dx dy: ";
                std::cin >> dx >> dy;
                A.move(dx, dy);
                std::cout << "A = " << A << '\n';
                break;
            }

            case 5: {
                int w, h;
                std::cout << "new width height: ";
                std::cin >> w >> h;
                A.resize(w, h);
                std::cout << "A = " << A << '\n';
                break;
            }

            case 6:  std::cout << "A = " << ++A << '\n'; break;
            case 7:  std::cout << "A = " << A++ << '\n'; break;
            case 8:  std::cout << "A = " << --A << '\n'; break;
            case 9:  std::cout << "A = " << A-- << '\n'; break;

            case 10:
                std::cout << "A + B = " << (A + B) << '\n';
                break;

            case 11:
                std::cout << "A - B = " << (A - B) << '\n';
                break;

            case 12:
                A += B;
                std::cout << "A = " << A << '\n';
                break;

            case 13:
                A -= B;
                std::cout << "A = " << A << '\n';
                break;

            case 14:
                std::cout << (A == B ? "равны\n" : "не равны\n");
                break;

            case 15:
                std::cout << (intersects(A, B) ? "да\n" : "нет\n");
                break;

            case 16:
                std::cout << "Площадь A = " << A.getArea() << '\n';
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