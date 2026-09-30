#pragma once
#include <stdexcept>
#include <string>

class PolyclinicException : public std::runtime_error {
public:
    explicit PolyclinicException(const std::string& m) : std::runtime_error(m) {}
};

class PatientNotFoundException : public PolyclinicException {
public:
    explicit PatientNotFoundException(const std::string& id)
        : PolyclinicException("Пациент не найден: " + id) {}
};

class DoctorNotFoundException : public PolyclinicException {
public:
    explicit DoctorNotFoundException(const std::string& id)
        : PolyclinicException("Врач не найден: " + id) {}
};

class AppointmentNotFoundException : public PolyclinicException {
public:
    explicit AppointmentNotFoundException(const std::string& id)
        : PolyclinicException("Запись не найдена: " + id) {}
};

class InvalidAppointmentException : public PolyclinicException {
public:
    explicit InvalidAppointmentException(const std::string& m)
        : PolyclinicException("Некорректная запись: " + m) {}
};

class ScheduleConflictException : public PolyclinicException {
public:
    explicit ScheduleConflictException(const std::string& m)
        : PolyclinicException("Конфликт расписания: " + m) {}
};

class InvalidMedicalDataException : public PolyclinicException {
public:
    explicit InvalidMedicalDataException(const std::string& m)
        : PolyclinicException("Некорректные данные: " + m) {}
};

class PrescriptionException : public PolyclinicException {
public:
    explicit PrescriptionException(const std::string& m)
        : PolyclinicException("Ошибка назначения: " + m) {}
};

class InsuranceExpiredException : public PolyclinicException {
public:
    explicit InsuranceExpiredException(const std::string& m)
        : PolyclinicException("Страховка истекла: " + m) {}
};

class PaymentException : public PolyclinicException {
public:
    explicit PaymentException(const std::string& m)
        : PolyclinicException("Ошибка оплаты: " + m) {}
};

class MedicineOutOfStockException : public PolyclinicException {
public:
    explicit MedicineOutOfStockException(const std::string& n)
        : PolyclinicException("Лекарство закончилось: " + n) {}
};

class EquipmentNotAvailableException : public PolyclinicException {
public:
    explicit EquipmentNotAvailableException(const std::string& n)
        : PolyclinicException("Оборудование недоступно: " + n) {}
};