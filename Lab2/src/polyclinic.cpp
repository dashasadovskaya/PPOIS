#include "Polyclinic.h"

bool Admin::canRegister(const Patient& p) const {
    return p.hasInsurance();
}

void Admin::processAppointment(const Appointment& a) {
    if (!a.isActive()) throw InvalidAppointmentException("Запись не активна");
}

void Admin::cancelAppointment(const Appointment& a) {
    if (!a.isActive()) throw AppointmentNotFoundException("Нет активной записи");
}

void Director::approveVacation(const Vacation& v) {
    if (!v.isApproved()) throw InvalidAppointmentException("Отпуск не одобрен");
}

void Director::hire(const Employee& e) {
    if (e.fullName().empty()) throw InvalidMedicalDataException("Пустое имя");
}

void Director::fire(const Employee& e) {
    if (e.fullName().empty()) throw InvalidMedicalDataException("Пустое имя");
}

void Accountant::processPayment(const Payment& p) {
    if (!p.isPaid()) throw PaymentException("Платёж не проведён");
}

void PriceList::addService(const Service& s) {
    Service* newArr = new Service[serviceCount + 1];
    for (int i = 0; i < serviceCount; ++i) newArr[i] = services[i];
    newArr[serviceCount] = s;
    delete[] services;
    services = newArr;
    ++serviceCount;
}

double PriceList::find(const std::string& name) const {
    for (int i = 0; i < serviceCount; ++i)
        if (services[i].info() == name) return services[i].withDiscount(0);
    throw PaymentException("Услуга не найдена: " + name);
}

void MedicineStock::add(const Medicine& m) {
    Medicine* newArr = new Medicine[itemCount + 1];
    for (int i = 0; i < itemCount; ++i) newArr[i] = items[i];
    newArr[itemCount] = m;
    delete[] items;
    items = newArr;
    ++itemCount;
}

bool MedicineStock::has(const std::string& name) const {
     (void)name;
    for (int i = 0; i < itemCount; ++i)
        if (items[i].isAvailable()) return true;
    return false;
}

int MedicineStock::lowStock() const {
    int n = 0;
    for (int i = 0; i < itemCount; ++i)
        if (!items[i].isAvailable()) ++n;
    return n;
}

void EquipmentStock::add(const Equipment& e) {
    Equipment* newArr = new Equipment[itemCount + 1];
    for (int i = 0; i < itemCount; ++i) newArr[i] = items[i];
    newArr[itemCount] = e;
    delete[] items;
    items = newArr;
    ++itemCount;
}

bool EquipmentStock::has(const std::string& name) const {
     (void)name;
    for (int i = 0; i < itemCount; ++i)
        if (items[i].isOperational()) return true;
    return false;
}

int EquipmentStock::brokenCount() const {
    int n = 0;
    for (int i = 0; i < itemCount; ++i)
        if (!items[i].isOperational()) ++n;
    return n;
}

void Inventory::addEquipment(const Equipment& e) {
    Equipment* newArr = new Equipment[equipmentCount + 1];
    for (int i = 0; i < equipmentCount; ++i) newArr[i] = equipment[i];
    newArr[equipmentCount] = e;
    delete[] equipment;
    equipment = newArr;
    ++equipmentCount;
}

void Inventory::addMedicine(const Medicine& m) {
    Medicine* newArr = new Medicine[medicineCount + 1];
    for (int i = 0; i < medicineCount; ++i) newArr[i] = medicines[i];
    newArr[medicineCount] = m;
    delete[] medicines;
    medicines = newArr;
    ++medicineCount;
}

bool Inventory::checkEquipment() const {
    for (int i = 0; i < equipmentCount; ++i)
        if (!equipment[i].isOperational()) return false;
    return true;
}

void Rating::addReview(const Review& r) {
    if (!r.isValid()) throw InvalidAppointmentException("Плохой отзыв");
    average = (average * count + 1) / (count + 1);
    ++count;
}