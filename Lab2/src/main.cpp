/**
 * @file main.cpp
 * @author Иванов И.И.
 * @brief Консольное меню для работы с классами поликлиники.
 * @date 2025
 */
#include "Polyclinic.h"
#include <iostream>
#include <limits>

// Данные, которые «заданы заранее»
static Polyclinic clinic;
static Patient patient;
static Doctor doctor;
static MedicalCard card;
static InsurancePolicy policy;
static Address address("Минск", "Ленина", "5");
static ContactInfo contact;
static Specialization spec("Терапевт", 3);
static Disease disease("ОРВИ", "J06", 2);
static Diagnosis diagnosis(disease, "2025-01-15");
static Medicine medicine("Парацетамол", "500 мг", 50.0, 100);
static Prescription prescription;
static Service service("Консультация", 30.0);
static PriceList priceList;
static Cabinet cabinet;
static Department department;
static Building building("Главный корпус", 4);
static Appointment appointment;
static Schedule schedule;
static Salary salary;
static Cashier cashier;
static Rating rating;
static Review review;
static Report report;
static Statistics stats;
static AuditLog audit;
static Notification notification;
static SickLeave sickLeave;
static Vaccination vaccination;
static QueueTicket ticket(42);
static MedicalCertificate certificate;
static Referral referral;

static void printMenu() {
    std::cout << "\n ПОЛИКЛИНИКА \n"
              << " 1. Показать информацию о поликлинике\n"
              << " 2. Показать пациента\n"
              << " 3. Показать врача\n"
              << " 4. Показать медкарту\n"
              << " 5. Показать страховку\n"
              << " 6. Показать адрес\n"
              << " 7. Показать контакты\n"
              << " 8. Показать специализацию\n"
              << " 9. Показать болезнь\n"
              << "10. Показать диагноз\n"
              << "11. Показать лекарство\n"
              << "12. Показать рецепт\n"
              << "13. Показать услугу\n"
              << "14. Показать прайс-лист\n"
              << "15. Показать кабинет\n"
              << "16. Показать отделение\n"
              << "17. Показать корпус\n"
              << "18. Показать запись\n"
              << "19. Показать расписание\n"
              << "20. Показать зарплату\n"
              << "21. Показать кассу\n"
              << "22. Показать рейтинг\n"
              << "23. Показать отзыв\n"
              << "24. Показать отчёт\n"
              << "25. Показать статистику\n"
              << "26. Показать журнал\n"
              << "27. Показать уведомление\n"
              << "28. Показать больничный\n"
              << "29. Показать прививку\n"
              << "30. Показать талон\n"
              << "31. Показать справку\n"
              << "32. Показать направление\n"
              << " 0. Выход\n"
              << "Выбор: ";
}

static void initData() {
    // Поликлиника
    clinic.setName("Городская поликлиника №1");
    clinic.setAddress(address);

    // Пациент
    patient.setName("Иван", "Иванов");
    patient.setPatientId("P-001");
    patient.setBloodType("A+");

    // Врач
    doctor.setName("Пётр", "Петров");
    doctor.setLicense("LIC-12345");
    doctor.attachSpec(&spec);
    doctor.attachSchedule(&schedule);
    doctor.setBaseSalary(60000);
    doctor.promote("Терапевт");

    // Страховка
    policy.setPatient(&patient);
    patient.attachInsurance(&policy);

    // Медкарта
    card.setPatient(&patient);
    card.setBloodType("A+");
    card.addAllergy("Пенициллин");
    patient.attachCard(&card);

    // Контакты
    contact.setPhone("+375291234567");

    // Рецепт
    prescription.setPatient(&patient);
    prescription.extend(14);

    // Услуга и прайс
    priceList.addService(service);

    // Кабинет
    cabinet.setDoctor(&doctor);

    // Отделение
    department.setName("Терапевтическое");
    department.setHead(&doctor);

    // Корпус
    building.addCabinet();
    building.addCabinet();

    // Расписание
    schedule.setDoctor(&doctor);
    schedule.setWeek("2025-01-13", "2025-01-19");

    // Зарплата
    salary.setEmployee(&doctor);

    // Запись
    appointment.setId("A-001");
    appointment.setPatient(&patient);
    appointment.setDoctor(&doctor);
    appointment.setCabinet(&cabinet);
    appointment.confirm();

    // Отзыв и рейтинг
    review.setPatient(&patient);
    review.setDoctor(&doctor);
    review.setStars(5);

    // Отчёт
    report.setTitle("Отчёт за январь");
    report.append("Посещений: 120");

    // Статистика
    stats.setReport(&report);
    stats.calculate(120, 6);

    // Уведомление
    notification.setPatient(&patient);
    notification.setMessage("Напоминание о приёме");
    notification.send();

    // Больничный
    sickLeave.setPatient(&patient);
    sickLeave.setDays(7);

    // Прививка
    vaccination.setPatient(&patient);
    vaccination.setVaccine("Грипп");

    // Справка
    certificate.setPatient(&patient);

    // Направление
    referral.setPatient(&patient);
    referral.setDoctor(&doctor);

    // Журнал
    audit.log("admin", "Открытие смены");
}

int main() {
    initData();
    int choice = -1;

    while (choice != 0) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1:  std::cout << clinic.info() << '\n'; break;
                case 2:  std::cout << patient.info() << '\n'; break;
                case 3:  std::cout << doctor.fullName() << '\n'; break;
                case 4:  std::cout << card.info() << '\n'; break;
                case 5:  std::cout << (policy.isValid() ? "Полис действует\n" : "Истёк\n"); break;
                case 6:  std::cout << address.full() << '\n'; break;
                case 7:  std::cout << contact.info() << '\n'; break;
                case 8:  std::cout << spec.info() << '\n'; break;
                case 9:  std::cout << disease.describe() << '\n'; break;
                case 10: std::cout << diagnosis.info() << '\n'; break;
                case 11: std::cout << medicine.info() << '\n'; break;
                case 12: std::cout << (prescription.isLongTerm() ? "Долгий\n" : "Короткий\n"); break;
                case 13: std::cout << service.info() << '\n'; break;
                case 14: std::cout << "Услуг в прайсе: " << priceList.total() << '\n'; break;
                case 15: std::cout << cabinet.info() << '\n'; break;
                case 16: std::cout << department.info() << '\n'; break;
                case 17: std::cout << "Корпус: " << building.cabinets() << " каб.\n"; break;
                case 18: std::cout << (appointment.isActive() ? "Активна\n" : "Отменена\n"); break;
                case 19: std::cout << (schedule.isValid() ? "Расписание задано\n" : "Нет\n"); break;
                case 20: std::cout << "Оклад: " << salary.withTax(0.13) << '\n'; break;
                case 21: std::cout << (cashier.hasCash() ? "Есть наличные\n" : "Пусто\n"); break;
                case 22: std::cout << "Рейтинг: " << rating.value() << '\n'; break;
                case 23: std::cout << (review.isValid() ? "Отзыв корректный\n" : "Плохой\n"); break;
                case 24: std::cout << (report.isEmpty() ? "Пусто\n" : "Отчёт есть\n"); break;
                case 25: std::cout << "Средняя нагрузка: " << stats.load() << '\n'; break;
                case 26: std::cout << audit.last() << '\n'; break;
                case 27: std::cout << (notification.isSent() ? "Отправлено\n" : "Не отправлено\n"); break;
                case 28: std::cout << (sickLeave.isIssued() ? "Больничный выдан\n" : "Не выдан\n"); break;
                case 29: std::cout << (vaccination.isValid() ? "Прививка есть\n" : "Нет\n"); break;
                case 30: std::cout << (ticket.isWaiting() ? "Ждёт\n" : "Обслужен\n"); break;
                case 31: std::cout << (certificate.isIssued() ? "Справка выдана\n" : "Не выдана\n"); break;
                case 32: std::cout << (referral.isActive() ? "Направление активно\n" : "Использовано\n"); break;
                case 0:  std::cout << "Пока!\n"; break;
                default: std::cout << "Неверный пункт\n"; break;
            }
        } catch (const PolyclinicException& e) {
            std::cout << "Ошибка: " << e.what() << '\n';
        }
    }
    return 0;
}