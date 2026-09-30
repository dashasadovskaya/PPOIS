#include <UnitTest++/UnitTest++.h>
#include "Polyclinic.h"

TEST(AddressValid) {
    Address a("Минск", "Ленина", "5");
    CHECK(a.isValid());
}

TEST(AddressEmpty) {
    Address a;
    CHECK(!a.isValid());
}

TEST(AddressFull) {
    Address a("Минск", "Ленина", "5");
    CHECK_EQUAL("Минск, Ленина 5", a.full());
}

TEST(ContactValidPhone) {
    ContactInfo c;
    c.setPhone("+375291234567");
    CHECK(c.hasPhone());
}

TEST(ContactShortPhoneThrows) {
    ContactInfo c;
    CHECK_THROW(c.setPhone("123"), InvalidMedicalDataException);
}

TEST(PersonFullName) {
    Person p;
    p.setName("Иван", "Иванов");
    CHECK_EQUAL("Иванов Иван", p.fullName());
}

TEST(PersonEmptyNameThrows) {
    Person p;
    CHECK_THROW(p.setName("", "Иванов"), InvalidMedicalDataException);
}

TEST(PatientCanBookAfterInsurance) {
    Patient p;
    p.setPatientId("P-001");
    CHECK(!p.canBook());

    InsurancePolicy policy;
    policy.setPatient(&p);
    p.attachInsurance(&policy);
    CHECK(p.canBook());
}

TEST(PatientHasInsurance) {
    Patient p;
    CHECK(!p.hasInsurance());
}

TEST(DoctorShortLicenseThrows) {
    Doctor d;
    CHECK_THROW(d.setLicense("ab"), InvalidMedicalDataException);
}

TEST(DoctorCanTreatAfterSpec) {
    Doctor d;
    d.setLicense("LIC-12345");
    CHECK(!d.canTreat());

    Specialization s("Терпевт", 3);
    d.attachSpec(&s);
    CHECK(d.canTreat());
}

TEST(DiseaseNotDangerous) {
    Disease d("ОРВИ", "J06", 2);
    CHECK(!d.isDangerous());
}

TEST(DiseaseDangerous) {
    Disease d("Грипп", "J10", 5);
    CHECK(d.isDangerous());
}

TEST(DiagnosisValid) {
    Disease d("ОРВИ", "J06", 2);
    Diagnosis diag(d, "2025-01-15");
    CHECK(diag.isValid());
}

TEST(DiagnosisConfirm) {
    Disease d("ОРВИ", "J06", 2);
    Diagnosis diag(d, "2025-01-15");
    diag.confirm();
    CHECK(diag.isValid());
}

TEST(MedicineAvailable) {
    Medicine m("Аспирин", "500 мг", 50.0, 10);
    CHECK(m.isAvailable());
}

TEST(MedicineUseReducesQuantity) {
    Medicine m("Аспирин", "500 мг", 50.0, 10);
    m.use(3);
    CHECK(m.isAvailable());
}

TEST(MedicineUseTooMuchThrows) {
    Medicine m("Аспирин", "500 мг", 50.0, 10);
    CHECK_THROW(m.use(100), MedicineOutOfStockException);
}

TEST(MedicineRestock) {
    Medicine m("Аспирин", "500 мг", 50.0, 0);
    CHECK(!m.isAvailable());
    m.restock(5);
    CHECK(m.isAvailable());
}

TEST(InsuranceRenew) {
    InsurancePolicy p;
    p.renew("2026-01-01");
    CHECK(p.isValid());
}

TEST(InsuranceExpiredThrows) {
    InsurancePolicy p;
    CHECK_THROW(p.renew("2020-01-01"), InsuranceExpiredException);
}

TEST(CabinetFree) {
    Cabinet c;
    CHECK(c.isFree());
}

TEST(CabinetBusyThrows) {
    Cabinet c;
    Doctor d1, d2;
    c.setDoctor(&d1);
    CHECK_THROW(c.setDoctor(&d2), ScheduleConflictException);
}

TEST(ServiceDiscount) {
    Service s("Консультация", 100.0);
    CHECK_EQUAL(50.0, s.withDiscount(50));
}

TEST(ServiceBadDiscountThrows) {
    Service s("Консультация", 100.0);
    CHECK_THROW(s.withDiscount(150), PaymentException);
}

TEST(PriceListAddAndFind) {
    PriceList pl;
    pl.addService(Service("Консультация", 100.0));
    CHECK_EQUAL(1, pl.total());
}

TEST(PaymentPay) {
    Payment p;
    p.setAmount(100.0);
    CHECK(!p.isPaid());
    p.pay();
    CHECK(p.isPaid());
}

TEST(PaymentDoublePayThrows) {
    Payment p;
    p.setAmount(100.0);
    p.pay();
    CHECK_THROW(p.pay(), PaymentException);
}

TEST(ReviewBadStarsThrows) {
    Review r;
    CHECK_THROW(r.setStars(10), InvalidAppointmentException);
}

TEST(PolyclinicEmptyNameThrows) {
    Polyclinic p;
    CHECK_THROW(p.setName(""), InvalidMedicalDataException);
}

TEST(PolyclinicCounts) {
    Polyclinic p;
    p.hireDoctor();
    p.hireDoctor();
    p.registerPatient();
    CHECK_EQUAL(2, p.doctors());
    CHECK_EQUAL(1, p.patients());
}

TEST(SickLeaveIssue) {
    SickLeave s;
    Patient patient;
    Doctor doctor;
    s.setPatient(&patient);
    s.setDoctor(&doctor);
    s.setDays(7);
    s.issue();
    CHECK(s.isIssued());
}

TEST(SickLeaveBadDaysThrows) {
    SickLeave s;
    CHECK_THROW(s.setDays(400), InvalidMedicalDataException);
}

TEST(VaccinationValid) {
    Vaccination v;
    Patient patient;
    v.setPatient(&patient);
    v.setVaccine("Грипп");
    CHECK(v.isValid());
}

TEST(BuildingTall) {
    Building b("Корпус", 7);
    CHECK(b.isTall());
}

TEST(StorageUnitHasSpace) {
    StorageUnit s("Склад", 100);
    CHECK(s.hasSpace(50));
    CHECK(!s.hasSpace(150));
}

TEST(QueueTicketServed) {
    QueueTicket t(42);
    CHECK(t.isWaiting());
    t.markServed();
    CHECK(!t.isWaiting());
}

int main() {
    return UnitTest::RunAllTests();
}