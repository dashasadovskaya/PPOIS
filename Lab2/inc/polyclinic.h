
#pragma once
#include <string>
#include <iostream>
#include "Exceptions.h"

// Forward declarations
class Patient; class Doctor; class MedicalCard; class InsurancePolicy;
class Salary; class Schedule; class Appointment; class Cabinet;
class Medicine; class Equipment; class Polyclinic; class Payment;

class Address {
    std::string city;      ///< город
    std::string street;    ///< улица
    std::string house;     ///< дом
public:
    Address() : city(""), street(""), house("") {}
    Address(const std::string& c, const std::string& s, const std::string& h)
        : city(c), street(s), house(h) {}
    bool isValid() const { return !city.empty() && !street.empty(); }
    std::string full() const { return city + ", " + street + " " + house; }
};

class ContactInfo {
    std::string phone;     ///< телефон
    std::string email;     ///< email
public:
    ContactInfo() : phone(""), email("") {}
    bool hasPhone() const { return phone.size() >= 7; }
    void setPhone(const std::string& p) {
        if (p.size() < 7) throw InvalidMedicalDataException("Короткий телефон");
        phone = p;
    }
    std::string info() const { return phone + " / " + email; }
};

class Person {
protected:
    std::string firstName;  ///< имя
    std::string lastName;   ///< фамилия
    std::string birthDate;  ///< дата рождения
public:
    Person() : firstName(""), lastName(""), birthDate("") {}
    std::string fullName() const { return lastName + " " + firstName; }
    void setName(const std::string& f, const std::string& l) {
        if (f.empty() || l.empty()) throw InvalidMedicalDataException("Пустое имя");
        firstName = f; lastName = l;
    }
};

// 4-5. Специализация и болезнь

class Specialization {
    std::string name;      ///< название
    int minExperience;     ///< минимальный стаж
public:
    Specialization() : name(""), minExperience(0) {}
    Specialization(const std::string& n, int e) : name(n), minExperience(e) {}
    bool isSufficient(int exp) const { return exp >= minExperience; }
    std::string info() const { return name; }
};

class Disease {
    std::string name;      ///< название
    std::string icdCode;   ///< код МКБ
    int severity;          ///< тяжесть 1-5
public:
    Disease() : name(""), icdCode(""), severity(0) {}
    Disease(const std::string& n, const std::string& c, int s)
        : name(n), icdCode(c), severity(s) {}
    bool isDangerous() const { return severity >= 4; }
    std::string describe() const { return name + " [" + icdCode + "]"; }
};

// 6-8. Диагноз, рецепт, лекарство

class Diagnosis {
    Disease disease;       ///< болезнь
    std::string date;      ///< дата
    bool confirmed;        ///< подтверждён
public:
    Diagnosis() : date(""), confirmed(false) {}
    Diagnosis(const Disease& d, const std::string& dt)
        : disease(d), date(dt), confirmed(false) {}
    void confirm() { confirmed = true; }
    bool isValid() const { return !date.empty(); }
    std::string info() const { return disease.describe() + " от " + date; }
};

class Medicine {
    std::string name;      ///< название
    std::string dosage;    ///< дозировка
    double price;          ///< цена
    int quantity;          ///< количество
public:
    Medicine() : name(""), dosage(""), price(0), quantity(0) {}
    Medicine(const std::string& n, const std::string& d, double p, int q)
        : name(n), dosage(d), price(p), quantity(q) {}
    bool isAvailable() const { return quantity > 0; }
    void use(int n) {
        if (n > quantity) throw MedicineOutOfStockException(name);
        quantity -= n;
    }
    void restock(int n) { quantity += n; }
    std::string info() const { return name + " " + dosage; }
};

class Prescription {
    Medicine medicine;     ///< лекарство
    int durationDays;      ///< длительность
    Patient* patient;      ///< пациент
public:
    Prescription() : durationDays(0), patient(nullptr) {}
    void setPatient(Patient* p) { patient = p; }
    bool isLongTerm() const { return durationDays > 30; }
    void extend(int d) { durationDays += d; }
};

// 9-11. Медкарта, запись, направление

class MedicalCard {
    std::string number;     ///< номер карты
    Patient* patient;       ///< пациент
    std::string bloodType;  ///< группа крови
    std::string allergies;  ///< аллергии
public:
    MedicalCard() : number(""), patient(nullptr), bloodType(""), allergies("") {}
    void setPatient(Patient* p) { patient = p; }
    void setBloodType(const std::string& b) { bloodType = b; }
    void addAllergy(const std::string& a) { allergies += a + "; "; }
    bool hasAllergies() const { return !allergies.empty(); }
    std::string info() const { return "Карта " + number + ", кровь " + bloodType; }
};

class MedicalRecord {
    Patient* patient;       ///< пациент
    std::string complaint;  ///< жалоба
    std::string treatment;  ///< лечение
    std::string date;       ///< дата
public:
    MedicalRecord() : patient(nullptr), complaint(""), treatment(""), date("") {}
    void setPatient(Patient* p) { patient = p; }
    void addComplaint(const std::string& c) { complaint = c; }
    void addTreatment(const std::string& t) { treatment = t; }
    std::string summary() const { return complaint + " → " + treatment; }
};

class Referral {
    Patient* patient;       ///< пациент
    Doctor* doctor;         ///< врач
    std::string procedure;  ///< процедура
    bool used;              ///< использовано
public:
    Referral() : patient(nullptr), doctor(nullptr), procedure(""), used(false) {}
     void setPatient(Patient* p) { patient = p; }    
    void setDoctor(Doctor* d) { doctor = d; }  
    void markUsed() { used = true; }
    bool isActive() const { return !used; }
    bool isValid() const { return patient && doctor; }
};

// 12-14. Процедуры и анализы

class ProcedureType {
    std::string name;       ///< название
    int durationMinutes;    ///< длительность
public:
    ProcedureType() : name(""), durationMinutes(0) {}
    ProcedureType(const std::string& n, int d) : name(n), durationMinutes(d) {}
    bool isLong() const { return durationMinutes > 60; }
    std::string info() const { return name; }
};

class Procedure {
    ProcedureType type;     ///< тип
    Patient* patient;       ///< пациент
    Doctor* doctor;         ///< врач
    std::string date;       ///< дата
public:
    Procedure() : patient(nullptr), doctor(nullptr), date("") {}
    void setPatient(Patient* p) { patient = p; }
    void setDoctor(Doctor* d) { doctor = d; }
    bool isReady() const { return patient && doctor; }
};

class AnalysisType {
    std::string name;       ///< название
    std::string unit;       ///< единица измерения
public:
    AnalysisType() : name(""), unit("") {}
    AnalysisType(const std::string& n, const std::string& u) : name(n), unit(u) {}
    std::string info() const { return name + " [" + unit + "]"; }
};

class Analysis {
    AnalysisType type;      ///< тип
    Patient* patient;       ///< пациент
    std::string result;     ///< результат
    std::string date;       ///< дата
public:
    Analysis() : patient(nullptr), result(""), date("") {}
    void setPatient(Patient* p) { patient = p; }
    void setResult(const std::string& r) { result = r; }
    bool isReady() const { return !result.empty(); }
};

class Lab {
    std::string name;       ///< название
    std::string room;       ///< кабинет
    int capacity;           ///< вместимость
public:
    Lab() : name(""), room(""), capacity(0) {}
    Lab(const std::string& n, int c) : name(n), room(""), capacity(c) {}
    void setName(const std::string& n) { name = n; }
    bool hasCapacity(int current) const { return current < capacity; }
};

// 15-18. Время, расписание, кабинет

class TimeSlot {
    std::string start;      ///< начало
    std::string end;        ///< конец
    bool booked;            ///< занят
public:
    TimeSlot() : start(""), end(""), booked(false) {}
    TimeSlot(const std::string& s, const std::string& e) : start(s), end(e), booked(false) {}
    bool overlaps(const TimeSlot& o) const { return start < o.end && o.start < end; }
    void book() {
        if (booked) throw ScheduleConflictException("Слот занят");
        booked = true;
    }
    void free() { booked = false; }
};

class Schedule {
    Doctor* doctor;         ///< врач
    std::string weekStart;  ///< начало недели
    std::string weekEnd;    ///< конец недели
public:
    Schedule() : doctor(nullptr), weekStart(""), weekEnd("") {}
    void setDoctor(Doctor* d) { doctor = d; }
    bool isValid() const { return !weekStart.empty() && !weekEnd.empty(); }
    void setWeek(const std::string& s, const std::string& e) { weekStart = s; weekEnd = e; }
};

class WorkSchedule {
    Person* employee;       ///< сотрудник
    int hoursPerWeek;       ///< часов в неделю
public:
    WorkSchedule() : employee(nullptr), hoursPerWeek(0) {}
    void setEmployee(Person* e) { employee = e; }
    bool isOverworked() const { return hoursPerWeek > 40; }
    void setHours(int h) { hoursPerWeek = h; }
};

class Vacation {
    Person* employee;       ///< сотрудник
    std::string start;      ///< начало
    std::string end;        ///< конец
    bool approved;          ///< одобрен
public:
    Vacation() : employee(nullptr), start(""), end(""), approved(false) {}
    void setEmployee(Person* e) { employee = e; }
    void approve() { approved = true; }
    bool isApproved() const { return approved; }
};

class Cabinet {
    std::string number;     ///< номер
    Doctor* doctor;         ///< врач
    int capacity;           ///< вместимость
public:
    Cabinet() : number(""), doctor(nullptr), capacity(1) {}
    void setDoctor(Doctor* d) {
        if (doctor) throw ScheduleConflictException("Кабинет занят");
        doctor = d;
    }
    bool isFree() const { return doctor == nullptr; }
    std::string info() const { return "Каб. " + number; }
};

class Department {
    std::string name;       ///< название
    Doctor* head;           ///< заведующий
public:
    Department() : name(""), head(nullptr) {}
    void setName(const std::string& n) { name = n; }
    void setHead(Doctor* d) { head = d; }
    bool hasHead() const { return head != nullptr; }
    std::string info() const { return name; }
};

// 19-22. Сотрудники

class Employee : public Person {
protected:
    std::string employeeId;  ///< табельный номер
    std::string position;    ///< должность
    double baseSalary;       ///< оклад
public:
    Employee() : employeeId(""), position(""), baseSalary(0) {}
    void setBaseSalary(double s) {
        if (s < 0) throw PaymentException("Отрицательная зарплата");
        baseSalary = s;
    }
    void promote(const std::string& p) { position = p; }
    double monthly() const { return baseSalary / 12.0; }
};

class Doctor : public Employee {
    std::string license;    ///< лицензия
    Specialization* spec;   ///< специализация
    Schedule* schedule;     ///< расписание
    int experience;         ///< стаж
public:
    Doctor() : license(""), spec(nullptr), schedule(nullptr), experience(0) {}
    void setLicense(const std::string& l) {
        if (l.size() < 5) throw InvalidMedicalDataException("Короткая лицензия");
        license = l;
    }
    void attachSpec(Specialization* s) { spec = s; }
    void attachSchedule(Schedule* s) { schedule = s; }
    bool canTreat() const { return spec != nullptr && !license.empty(); }
    void addExperience() { ++experience; }
    bool isExperienced() const { return experience >= 5; }
};

class Nurse : public Employee {
    std::string shift;      ///< смена
    std::string qualification; ///< квалификация
public:
    Nurse() : shift(""), qualification("") {}
    void changeShift(const std::string& s) { shift = s; }
    bool canAssist() const { return !shift.empty(); }
    void upgrade(const std::string& q) { qualification = q; }
};

class Admin : public Employee {
    std::string workstation; ///< рабочее место
public:
    Admin() : workstation("") {}
    bool canRegister(const Patient& p) const;
    void processAppointment(const Appointment& a);
    void cancelAppointment(const Appointment& a);
};
// 23-25. Пациент и его данные

class Patient : public Person {
    std::string patientId;      ///< номер пациента
    std::string policyNumber;   ///< номер полиса
    std::string bloodType;      ///< группа крови
    MedicalCard* card;          ///< медкарта
    InsurancePolicy* insurance; ///< страховка
public:
    Patient() : patientId(""), policyNumber(""), bloodType(""),
                card(nullptr), insurance(nullptr) {}

    void setPatientId(const std::string& id) { patientId = id; }
    void setBloodType(const std::string& b) { bloodType = b; }

    void attachCard(MedicalCard* c) {
        if (!c) throw InvalidMedicalDataException("Пустая карта");
        card = c;
    }
    void attachInsurance(InsurancePolicy* i) {
        if (!i) throw InvalidMedicalDataException("Пустая страховка");
        insurance = i;
    }
    bool canBook() const { return !patientId.empty() && insurance != nullptr; }
    bool hasInsurance() const { return insurance != nullptr; }
    std::string info() const { return fullName() + " (" + patientId + ")"; }
};

class InsurancePolicy {
    std::string number;         ///< номер полиса
    Patient* patient;           ///< пациент
    std::string validUntil;     ///< действует до
    bool active;                ///< активен
public:
    InsurancePolicy() : number(""), patient(nullptr), validUntil(""), active(true) {}
    void setPatient(Patient* p) { patient = p; }
    bool isValid() const { return active && validUntil >= "2025-01-01"; }
    void deactivate() { active = false; }
    void renew(const std::string& until) {
        if (until < "2025-01-01") throw InsuranceExpiredException(number);
        validUntil = until;
        active = true;
    }
};

class InsuranceCompany {
    std::string name;   ///< название
    std::string inn;    ///< ИНН
public:
    InsuranceCompany() : name(""), inn("") {}
    InsuranceCompany(const std::string& n, const std::string& i) : name(n), inn(i) {}
    bool isValid() const { return !name.empty() && inn.size() == 10; }
    std::string info() const { return name; }
};

// 26-28. Запись, регистратура, колл-центр

class Appointment {
    std::string id;         ///< номер записи
    Patient* patient;       ///< пациент
    Doctor* doctor;         ///< врач
    TimeSlot slot;          ///< время
    Cabinet* cabinet;       ///< кабинет
    std::string status;     ///< статус
    Diagnosis diagnosis;    ///< диагноз
public:
    Appointment() : id(""), patient(nullptr), doctor(nullptr),
                    cabinet(nullptr), status("new") {}

    void setId(const std::string& s) { id = s; }
    void setPatient(Patient* p) { patient = p; }
    void setDoctor(Doctor* d) { doctor = d; }
    void setCabinet(Cabinet* c) { cabinet = c; }
    void confirm() { status = "confirmed"; }
    void cancel() { status = "cancelled"; }
    bool isActive() const { return status == "confirmed"; }
};

class Registry {
    Patient* lastPatient;   ///< последний пациент
    int todayCount;         ///< приёмов сегодня
public:
    Registry() : lastPatient(nullptr), todayCount(0) {}
    void registerPatient(Patient* p) { lastPatient = p; ++todayCount; }
    bool canAccept() const { return todayCount < 200; }
    void resetDaily() { todayCount = 0; }
    int today() const { return todayCount; }
};

class CallCenter {
    Patient* caller;        ///< звонящий
    int callsToday;         ///< звонков сегодня
public:
    CallCenter() : caller(nullptr), callsToday(0) {}
    void acceptCall(Patient* p) { caller = p; ++callsToday; }
    void endCall() { caller = nullptr; }
    int calls() const { return callsToday; }
};

// 29-32. Финансы

class Service {
    std::string name;       ///< название
    std::string code;       ///< код
    double basePrice;       ///< базовая цена
public:
    Service() : name(""), code(""), basePrice(0) {}
    Service(const std::string& n, double p) : name(n), code(""), basePrice(p) {}
    double withDiscount(double percent) const {
        if (percent < 0 || percent > 100) throw PaymentException("Плохая скидка");
        return basePrice * (1 - percent / 100.0);
    }
    std::string info() const { return name; }
};

class PriceList {
    Service* services;      ///< услуги
    int serviceCount;       ///< сколько услуг
public:
    PriceList() : services(nullptr), serviceCount(0) {}
    ~PriceList() { delete[] services; }
    void addService(const Service& s);
    double find(const std::string& name) const;
    int total() const { return serviceCount; }
};

class Payment {
    std::string id;         ///< номер
    Patient* patient;       ///< пациент
    double amount;          ///< сумма
    bool paid;              ///< оплачен
public:
    Payment() : id(""), patient(nullptr), amount(0), paid(false) {}
    void setPatient(Patient* p) { patient = p; }
    void setAmount(double a) {
        if (a < 0) throw PaymentException("Отрицательная сумма");
        amount = a;
    }
    void pay() {
        if (paid) throw PaymentException("Уже оплачено");
        paid = true;
    }
    bool isPaid() const { return paid; }
};

class Salary {
    Employee* employee;     ///< сотрудник
    double amount;          ///< сумма
    std::string month;      ///< месяц
    bool paid;              ///< выплачено
public:
    Salary() : employee(nullptr), amount(0), month(""), paid(false) {}
    void setEmployee(Employee* e) { employee = e; }
    double withTax(double rate) const { return amount * (1 - rate); }
    void pay() {
        if (paid) throw PaymentException("Уже выплачено");
        paid = true;
    }
    bool isPaid() const { return paid; }
};

class Cashier : public Employee {
    double cashInRegister;  ///< наличные в кассе
public:
    Cashier() : cashInRegister(0) {}
    void acceptPayment(Payment& p) {
        if (!p.isPaid()) throw PaymentException("Не оплачено");
        cashInRegister += 1;
    }
    double closeShift() { double t = cashInRegister; cashInRegister = 0; return t; }
    bool hasCash() const { return cashInRegister > 0; }
};

// 33-36. Руководство

class Director : public Employee {
    Polyclinic* polyclinic; ///< поликлиника
public:
    Director() : polyclinic(nullptr) {}
    void attachPolyclinic(Polyclinic* p) { polyclinic = p; }
    double budget() const { return baseSalary * 100; }
    void approveVacation(const Vacation& v);
    void hire(const Employee& e);
    void fire(const Employee& e);
};

class Accountant : public Employee {
    double taxRate;         ///< ставка налога
public:
    Accountant() : taxRate(0.13) {}
    double tax(double amount) const { return amount * taxRate; }
    double netSalary(const Salary& s) const { return s.withTax(taxRate); }
    void processPayment(const Payment& p);
};

// 37-39. Склад

class Equipment {
    std::string name;       ///< название
    std::string serial;     ///< серийный номер
    bool working;           ///< работает
public:
    Equipment() : name(""), serial(""), working(true) {}
    Equipment(const std::string& n, const std::string& s) : name(n), serial(s), working(true) {}
    bool isOperational() const { return working; }
    void markBroken() { working = false; }
    void repair() { working = true; }
};

class MedicineStock {
    Medicine* items;        ///< лекарства
    int itemCount;          ///< сколько
    std::string warehouse;  ///< склад
public:
    MedicineStock() : items(nullptr), itemCount(0), warehouse("") {}
    ~MedicineStock() { delete[] items; }
    void add(const Medicine& m);
    bool has(const std::string& name) const;
    int lowStock() const;
};

class EquipmentStock {
    Equipment* items;       ///< оборудование
    int itemCount;          ///< сколько
    std::string warehouse;  ///< склад
public:
    EquipmentStock() : items(nullptr), itemCount(0), warehouse("") {}
    ~EquipmentStock() { delete[] items; }
    void add(const Equipment& e);
    bool has(const std::string& name) const;
    int brokenCount() const;
};

class Inventory {
    Equipment* equipment;   ///< оборудование
    int equipmentCount;     ///< сколько
    Medicine* medicines;    ///< лекарства
    int medicineCount;      ///< сколько
public:
    Inventory() : equipment(nullptr), equipmentCount(0),
                  medicines(nullptr), medicineCount(0) {}
    ~Inventory() { delete[] equipment; delete[] medicines; }
    void addEquipment(const Equipment& e);
    void addMedicine(const Medicine& m);
    bool checkEquipment() const;
    int total() const { return equipmentCount + medicineCount; }
};

class StorageUnit {
    std::string name;       ///< название
    int capacity;           ///< вместимость
public:
    StorageUnit() : name(""), capacity(0) {}
    StorageUnit(const std::string& n, int c) : name(n), capacity(c) {}
    bool hasSpace(int current) const { return current < capacity; }
    std::string info() const { return name; }
};

class StorageZone {
    std::string name;       ///< название
    double temperature;     ///< температура
public:
    StorageZone() : name(""), temperature(20) {}
    bool suitableForMedicine() const { return temperature >= 2 && temperature <= 25; }
    void setTemperature(double t) { temperature = t; }
};

class Rack {
    std::string number;     ///< номер
    int shelves;            ///< полок
    int used;               ///< занято
public:
    Rack() : number(""), shelves(0), used(0) {}
    bool isFull() const { return used >= shelves; }
    void place() {
        if (isFull()) throw MedicineOutOfStockException(number);
        ++used;
    }
    void remove() { if (used > 0) --used; }
};

// 40-43. Отчёты, статистика, уведомления, отзывы

class Report {
    std::string title;      ///< заголовок
    Polyclinic* polyclinic; ///< поликлиника
    std::string content;    ///< содержимое
    std::string date;       ///< дата
public:
    Report() : title(""), polyclinic(nullptr), content(""), date("") {}
    void setTitle(const std::string& t) { title = t; }
    void append(const std::string& s) { content += s; }
    bool isEmpty() const { return content.empty(); }
    void clear() { content = ""; }
};

class Statistics {
    Report* report;         ///< отчёт
    int totalAppointments;  ///< всего записей
    int totalPatients;      ///< всего пациентов
    double averageLoad;     ///< средняя нагрузка
public:
    Statistics() : report(nullptr), totalAppointments(0), totalPatients(0), averageLoad(0) {}
    void setReport(Report* r) { report = r; }
    void calculate(int app, int docs) {
        if (docs <= 0) throw InvalidMedicalDataException("Нет врачей");
        averageLoad = (double)app / docs;
    }
    bool isOverloaded() const { return averageLoad > 20; }
    double load() const { return averageLoad; }
};

class AuditLog {
    std::string lastAction; ///< последнее действие
    std::string lastUser;   ///< пользователь
    int entryCount;         ///< всего записей
public:
    AuditLog() : lastAction(""), lastUser(""), entryCount(0) {}
    void log(const std::string& u, const std::string& a) {
        lastUser = u; lastAction = a; ++entryCount;
    }
    std::string last() const { return lastUser + ": " + lastAction; }
    int total() const { return entryCount; }
};

class Notification {
    Patient* patient;       ///< пациент
    std::string message;    ///< текст
    bool sent;              ///< отправлено
public:
    Notification() : patient(nullptr), message(""), sent(false) {}
    void setPatient(Patient* p) { patient = p; }
    void setMessage(const std::string& m) { message = m; }
    void send() {
        if (message.empty()) throw InvalidAppointmentException("Пустое уведомление");
        sent = true;
    }
    bool isSent() const { return sent; }
};

class Review {
    Patient* patient;       ///< пациент
    Doctor* doctor;         ///< врач
    int stars;              ///< оценка 1-5
    std::string text;       ///< текст
public:
    Review() : patient(nullptr), doctor(nullptr), stars(0), text("") {}
    void setPatient(Patient* p) { patient = p; }
    void setDoctor(Doctor* d) { doctor = d; }
    void setStars(int s) {
        if (s < 1 || s > 5) throw InvalidAppointmentException("Оценка 1-5");
        stars = s;
    }
    bool isValid() const { return stars >= 1 && stars <= 5 && !text.empty(); }
};

class Rating {
    Doctor* doctor;         ///< врач
    double average;         ///< средний балл
    int count;              ///< количество отзывов
public:
    Rating() : doctor(nullptr), average(0), count(0) {}
    void addReview(const Review& r);
    bool isHigh() const { return average >= 4.5; }
    double value() const { return average; }
};

// 44-46. Служебные классы

class SmsNotification {
    std::string phone;      ///< телефон
    std::string text;       ///< текст
public:
    SmsNotification() : phone(""), text("") {}
    bool isValid() const { return phone.size() >= 7 && !text.empty(); }
    void setPhone(const std::string& p) { phone = p; }
};

class QueueTicket {
    int number;             ///< номер талона
    std::string cabinet;    ///< кабинет
    bool served;            ///< обслужен
public:
    QueueTicket() : number(0), cabinet(""), served(false) {}
    QueueTicket(int n) : number(n), cabinet(""), served(false) {}
    void markServed() { served = true; }
    bool isWaiting() const { return !served; }
};

class MedicalCertificate {
    Patient* patient;       ///< пациент
    std::string purpose;    ///< цель
    std::string date;       ///< дата
    bool issued;            ///< выдана
public:
    MedicalCertificate() : patient(nullptr), purpose(""), date(""), issued(false) {}
    void setPatient(Patient* p) { patient = p; }
    void issue() {
        if (!patient) throw PatientNotFoundException("");
        issued = true;
    }
    bool isIssued() const { return issued; }
};

// 47. Главный класс

class Polyclinic {
    std::string name;       ///< название
    Address address;        ///< адрес
    int doctorCount;        ///< врачей
    int patientCount;       ///< пациентов
    int departmentCount;    ///< отделений
public:
    Polyclinic() : name(""), doctorCount(0), patientCount(0), departmentCount(0) {}
    void setName(const std::string& n) {
        if (n.empty()) throw InvalidMedicalDataException("Пустое название");
        name = n;
    }
    void setAddress(const Address& a) { address = a; }
    void hireDoctor() { ++doctorCount; }
    void registerPatient() { ++patientCount; }
    void addDepartment() { ++departmentCount; }
    double revenue() const { return doctorCount * 1000.0 + patientCount * 100.0; }
    std::string info() const { return name + " (" + address.full() + ")"; }
    int doctors() const { return doctorCount; }
    int patients() const { return patientCount; }
    int departments() const { return departmentCount; }
};

// 48-50. Последние три класса

class SickLeave {
    Patient* patient;       ///< пациент
    Doctor* doctor;         ///< врач
    int days;               ///< дней
    bool issued;            ///< выдан
public:
    SickLeave() : patient(nullptr), doctor(nullptr), days(0), issued(false) {}
    void setPatient(Patient* p) { patient = p; }
    void setDoctor(Doctor* d) { doctor = d; }    
    void setDays(int d) {
        if (d <= 0 || d > 365) throw InvalidMedicalDataException("Плохой срок");
        days = d;
    }
    void issue() {
        if (!patient || !doctor) throw InvalidMedicalDataException("Нет данных");
        issued = true;
    }
    bool isIssued() const { return issued; }
};

class Vaccination {
    Patient* patient;       ///< пациент
    std::string vaccine;    ///< вакцина
    std::string date;       ///< дата
public:
    Vaccination() : patient(nullptr), vaccine(""), date("") {}
    void setPatient(Patient* p) { patient = p; }
    void setVaccine(const std::string& v) { vaccine = v; }
    bool isValid() const { return patient && !vaccine.empty(); }
};

class Building {
    std::string name;       ///< название
    int floors;             ///< этажей
    int cabinetCount;       ///< кабинетов
public:
    Building() : name(""), floors(0), cabinetCount(0) {}
    Building(const std::string& n, int f) : name(n), floors(f), cabinetCount(0) {}
    bool isTall() const { return floors > 5; }
    void addCabinet() { ++cabinetCount; }
    int cabinets() const { return cabinetCount; }
};