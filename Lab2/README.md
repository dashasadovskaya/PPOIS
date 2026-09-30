# Поликлиника

Лабораторная работа №2. Предметная область: **Поликлиника**.

| Класс | Поля | Методы | Связи |
|---|---|---|---|
| Address | 3 | 2 | — |
| ContactInfo | 2 | 3 | — |
| Person | 3 | 2 | — |
| Specialization | 2 | 2 | — |
| Disease | 3 | 2 | — |
| Diagnosis | 3 | 3 | Disease |
| Medicine | 4 | 4 | — |
| Prescription | 3 | 3 | Medicine, Patient |
| MedicalCard | 4 | 4 | Patient |
| MedicalRecord | 4 | 4 | Patient |
| Referral | 4 | 3 | Patient, Doctor |
| ProcedureType | 2 | 2 | — |
| Procedure | 4 | 3 | Patient, Doctor |
| AnalysisType | 2 | 2 | — |
| Analysis | 4 | 3 | Patient |
| Lab | 3 | 3 | — |
| TimeSlot | 3 | 4 | — |
| Schedule | 3 | 3 | Doctor |
| WorkSchedule | 2 | 3 | Person |
| Vacation | 4 | 3 | Person |
| Cabinet | 3 | 3 | Doctor |
| Department | 2 | 4 | Doctor |
| Employee | 3 | 3 | Person |
| Doctor | 4 | 6 | Employee, Specialization, Schedule |
| Nurse | 2 | 3 | Employee |
| Admin | 1 | 3 | Employee, Patient, Appointment |
| Patient | 5 | 6 | Person, MedicalCard, InsurancePolicy |
| InsurancePolicy | 4 | 4 | Patient |
| InsuranceCompany | 2 | 2 | — |
| Appointment | 7 | 6 | Patient, Doctor, TimeSlot, Cabinet, Diagnosis |
| Registry | 2 | 4 | Patient |
| CallCenter | 2 | 3 | Patient |
| Service | 3 | 2 | — |
| PriceList | 2 | 3 | Service |
| Payment | 4 | 4 | Patient |
| Salary | 4 | 3 | Employee |
| Cashier | 1 | 3 | Employee, Payment |
| Director | 1 | 5 | Employee, Polyclinic, Vacation |
| Accountant | 1 | 3 | Employee, Salary, Payment |
| Equipment | 3 | 3 | — |
| MedicineStock | 3 | 3 | Medicine |
| EquipmentStock | 3 | 3 | Equipment |
| Inventory | 4 | 4 | Equipment, Medicine |
| StorageUnit | 2 | 2 | — |
| StorageZone | 2 | 2 | — |
| Rack | 3 | 3 | — |
| Report | 4 | 4 | Polyclinic |
| Statistics | 4 | 3 | Report |
| AuditLog | 3 | 3 | — |
| Notification | 3 | 3 | Patient |
| Review | 4 | 4 | Patient, Doctor |
| Rating | 3 | 2 | Doctor, Review |
| SmsNotification | 2 | 2 | — |
| QueueTicket | 3 | 2 | — |
| MedicalCertificate | 4 | 3 | Patient |
| Polyclinic | 4 | 8 | Address |
| SickLeave | 4 | 4 | Patient, Doctor |
| Vaccination | 3 | 3 | Patient |
| Building | 3 | 3 | — |

## Исключения (12)
PolyclinicException, PatientNotFoundException, DoctorNotFoundException,
AppointmentNotFoundException, InvalidAppointmentException, ScheduleConflictException,
InvalidMedicalDataException, PrescriptionException, InsuranceExpiredException,
PaymentException, MedicineOutOfStockException, EquipmentNotAvailableException.

## Итого
- Классы: 50
- Поля: 154
- Поведения: 104
- Ассоциации: 34
- Исключения: 12