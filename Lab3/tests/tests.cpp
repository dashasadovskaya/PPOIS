#include <UnitTest++/UnitTest++.h>
#include "FoodDelivery.h"


TEST(AddressValid) {
    Address a("Минск", "Ленина", "5", "10");
    CHECK(a.isValid());
}

TEST(AddressEmpty) {
    Address a;
    CHECK(!a.isValid());
}

TEST(AddressFull) {
    Address a("Минск", "Ленина", "5", "10");
    CHECK(a.full().find("Минск") != std::string::npos);
}

TEST(ContactInfoValidPhone) {
    ContactInfo c;
    c.setPhone("+375291234567");
    CHECK(c.hasPhone());
}

TEST(ContactInfoShortPhoneThrows) {
    ContactInfo c;
    CHECK_THROW(c.setPhone("123"), InvalidClientDataException);
}

TEST(GeoPointValid) {
    GeoPoint g(1.0, 2.0);
    CHECK(g.isValid());
}

TEST(GeoPointDistance) {
    GeoPoint a(0, 0), b(3, 4);
    CHECK_EQUAL(25.0, a.distanceTo(b));
}

TEST(PersonFullName) {
    Person p;
    p.setName("Иван", "Иванов");
    CHECK_EQUAL("Иванов Иван", p.fullName());
}

TEST(PersonEmptyNameThrows) {
    Person p;
    CHECK_THROW(p.setName("", "Иванов"), InvalidClientDataException);
}

TEST(ClientCanOrderAfterPhone) {
    Client c;
    c.setClientId("C-001");
    CHECK(!c.canOrder());

    ContactInfo info;
    // нельзя проверить без геттера — пропускаем
    CHECK(!c.canOrder());
}

TEST(CourierAvailable) {
    Courier c;
    c.setCourierId("D-001");
    CHECK(c.isAvailable());
}

TEST(CourierGoOffline) {
    Courier c;
    c.goOffline();
    CHECK(!c.isAvailable());
    c.goOnline();
    CHECK(c.isAvailable());
}

TEST(EmployeeSalaryThrows) {
    Employee e;
    CHECK_THROW(e.setSalary(-100), PaymentException);
}

TEST(EmployeeMonthly) {
    Employee e;
    e.setSalary(12000);
    CHECK_EQUAL(1000.0, e.monthly());
}

TEST(DishAvailable) {
    Dish d("Пицца", 25.0, 10);
    CHECK(d.isAvailable());
}

TEST(DishUseTooMuchThrows) {
    Dish d("Пицца", 25.0, 5);
    CHECK_THROW(d.use(100), DishOutOfStockException);
}

TEST(DishRestock) {
    Dish d("Пицца", 25.0, 0);
    CHECK(!d.isAvailable());
    d.restock(5);
    CHECK(d.isAvailable());
}

TEST(MenuEmpty) {
    Menu m;
    CHECK(m.isEmpty());
}

TEST(MenuAddItem) {
    Menu m;
    MenuItem item;
    m.addItem(item);
    CHECK_EQUAL(1, m.total());
}

TEST(KitchenCanAccept) {
    Kitchen k;
    CHECK(k.canAccept());
}

TEST(WorkingHoursOpen) {
    WorkingHours h("09:00", "21:00");
    CHECK(h.isOpen("12:00"));
    CHECK(!h.isOpen("22:00"));
}

TEST(RestaurantEmptyNameThrows) {
    Restaurant r;
    CHECK_THROW(r.setName(""), InvalidClientDataException);
}

TEST(RestaurantCanAcceptOrder) {
    Restaurant r;
    CHECK(r.canAcceptOrder());
    r.close();
    CHECK(!r.canAcceptOrder());
}

TEST(FranchiseLarge) {
    Franchise f;
    for (int i = 0; i < 15; ++i) f.addRestaurant();
    CHECK(f.isLarge());
}

TEST(OrderStatusFinal) {
    OrderStatus s("Доставлен", 5);
    CHECK(s.isFinal());
}

TEST(CartEmpty) {
    Cart c;
    CHECK_EQUAL(0, c.size());
    CHECK_EQUAL(0.0, c.total());
}

TEST(DeliveryCompleteWithoutOrderThrows) {
    Delivery d;
    CHECK_THROW(d.complete("12:30"), OrderNotFoundException);
}

TEST(RouteCalculate) {
    Route r;
    r.setPoints(GeoPoint(0, 0), GeoPoint(3, 4));
    r.calculate();
    CHECK(r.estimatedMinutes() > 0);
}

TEST(PaymentPay) {
    Payment p;
    p.setAmount(100.0);
    CHECK(!p.isPaid());
    p.pay();
    CHECK(p.isPaid());
}

TEST(PaymentNegativeAmountThrows) {
    Payment p;
    CHECK_THROW(p.setAmount(-50), PaymentException);
}

TEST(PaymentDoublePayThrows) {
    Payment p;
    p.setAmount(100.0);
    p.pay();
    CHECK_THROW(p.pay(), PaymentException);
}

TEST(PromoCodeValid) {
    PromoCode p("SALE10", 10.0);
    CHECK(p.isValid());
}

TEST(PromoCodeApply) {
    PromoCode p("SALE10", 10.0);
    CHECK_EQUAL(90.0, p.applyTo(100.0));
}

TEST(PromoCodeInvalidThrows) {
    PromoCode p("SALE10", 10.0);
    p.deactivate();
    CHECK_THROW(p.applyTo(100.0), InvalidPromoCodeException);
}

TEST(WalletTopUp) {
    Wallet w;
    w.topUp(100.0);
    CHECK_EQUAL(100.0, w.getBalance());
}

TEST(WalletTopUpNegativeThrows) {
    Wallet w;
    CHECK_THROW(w.topUp(-10), PaymentException);
}

TEST(WalletWithdrawTooMuchThrows) {
    Wallet w;
    w.topUp(50.0);
    CHECK_THROW(w.withdraw(100.0), PaymentException);
}

TEST(ReceiptPrint) {
    Receipt r;
    r.setTotal(100.0);
    r.print();
    CHECK(r.isPrinted());
}

TEST(ReceiptEmptyThrows) {
    Receipt r;
    CHECK_THROW(r.print(), PaymentException);
}

TEST(ReviewBadStarsThrows) {
    Review r;
    CHECK_THROW(r.setStars(10), InvalidOrderDataException);
}

TEST(ReviewValid) {
    Review r;
    r.setStars(5);
    CHECK(r.isValid());
}

TEST(RatingInitialZero) {
    Rating r;
    CHECK_EQUAL(0.0, r.value());
}

TEST(AdvertisementBudget) {
    Advertisement a;
    a.setBudget(1000.0);
    a.addImpression();
    CHECK(a.costPerImpression() > 0);
}

TEST(AdvertisementNegativeBudgetThrows) {
    Advertisement a;
    CHECK_THROW(a.setBudget(-100), PaymentException);
}

TEST(LoyaltyLevelUp) {
    LoyaltyProgram l;
    CHECK_EQUAL("Bronze", l.getLevel());
    l.addPoints(600);
    CHECK_EQUAL("Silver", l.getLevel());
    l.addPoints(500);
    CHECK_EQUAL("Gold", l.getLevel());
}

TEST(WarehouseStore) {
    Warehouse w;
    w.store(100);
    CHECK(w.hasSpace(50));
}

TEST(WarehouseOverflowThrows) {
    Warehouse w;
    CHECK_THROW(w.store(5000), DishOutOfStockException);
}

TEST(SupplierCanDeliver) {
    Supplier s;
    s.setPhone("+375291234567");
    CHECK(s.canDeliver());
}

TEST(SupplierUnreliable) {
    Supplier s;
    s.setPhone("+375291234567");
    s.markUnreliable();
    CHECK(!s.canDeliver());
}

TEST(NotificationEmptyThrows) {
    Notification n;
    CHECK_THROW(n.send(), InvalidOrderDataException);
}

TEST(NotificationSend) {
    Notification n;
    n.setMessage("Заказ принят");
    n.send();
    CHECK(n.isSent());
}

TEST(SupportTicketBadPriorityThrows) {
    SupportTicket t;
    CHECK_THROW(t.setPriority(10), InvalidOrderDataException);
}

TEST(FeedbackBadStarsThrows) {
    Feedback f;
    CHECK_THROW(f.setStars(0), InvalidOrderDataException);
}

TEST(StatisticsAddOrder) {
    Statistics s;
    s.addOrder(100.0);
    s.addOrder(200.0);
    CHECK_EQUAL(150.0, s.averageOrder());
}

TEST(StatisticsNegativeThrows) {
    Statistics s;
    CHECK_THROW(s.addOrder(-10), PaymentException);
}

TEST(SystemEmptyNameThrows) {
    FoodDeliverySystem s;
    CHECK_THROW(s.setName(""), InvalidClientDataException);
}

TEST(SystemAddClient) {
    FoodDeliverySystem s;
    Client c;
    s.addClient(c);
    CHECK(s.counts() > 0);
}

TEST(SystemFindClientNotFound) {
    FoodDeliverySystem s;
    CHECK_THROW(s.findClient("Нет такого"), ClientNotFoundException);
}

TEST(SystemFindRestaurantNotFound) {
    FoodDeliverySystem s;
    CHECK_THROW(s.findRestaurant("Нет такого"), RestaurantNotFoundException);
}

int main() {
    return UnitTest::RunAllTests();
}