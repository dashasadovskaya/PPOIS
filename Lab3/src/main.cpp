#include "FoodDelivery.h"
#include <iostream>
#include <limits>

static FoodDeliverySystem system_;
static Client client;
static Courier courier;
static Restaurant restaurant;
static Dish dish("Пицца", 25.0, 50);
static Address address("Минск", "Ленина", "5", "10");
static ContactInfo contact;
static Payment payment;
static PromoCode promo("SALE10", 10.0);
static Review review;
static Rating rating;
static Complaint complaint;
static Notification notification;
static SupportTicket ticket;
static Feedback feedback;
static Statistics stats;
static Report report;
static Analytics analytics;
static AuditLog audit;
static Wallet wallet;
static LoyaltyProgram loyalty;
static BonusSystem bonus;
static Delivery delivery;
static Route route;
static WorkingHours hours;
static Kitchen kitchen;
static Warehouse warehouse;
static Supplier supplier;
static Advertisement ad;
static Promotion promotion;
static DeliveryZone zone;

static void printMenu() {
    std::cout << "\n ДОСТАВКА ЕДЫ \n"
              << " 1. Показать систему\n"
              << " 2. Показать клиента\n"
              << " 3. Показать курьера\n"
              << " 4. Показать ресторан\n"
              << " 5. Показать блюдо\n"
              << " 6. Показать адрес\n"
              << " 7. Показать контакты\n"
              << " 8. Показать оплату\n"
              << " 9. Показать промокод\n"
              << "10. Показать отзыв\n"
              << "11. Показать рейтинг\n"
              << "12. Показать жалобу\n"
              << "13. Показать уведомление\n"
              << "14. Показать тикет\n"
              << "15. Показать обратную связь\n"
              << "16. Показать статистику\n"
              << "17. Показать отчёт\n"
              << "18. Показать аналитику\n"
              << "19. Показать журнал\n"
              << "20. Показать кошелёк\n"
              << "21. Показать бонусы\n"
              << "22. Показать доставку\n"
              << "23. Показать маршрут\n"
              << "24. Показать часы работы\n"
              << "25. Показать кухню\n"
              << "26. Показать склад\n"
              << "27. Показать поставщика\n"
              << "28. Показать рекламу\n"
              << "29. Показать акцию\n"
              << "30. Показать зону доставки\n"
              << " 0. Выход\n"
              << "Выбор: ";
}

static void initData() {
    system_.setName("Еда.Бай");

    client.setName("Иван", "Иванов");
    client.setClientId("C-001");
    client.setAddress(address);

    courier.setName("Пётр", "Петров");
    courier.setCourierId("D-001");
    courier.setTransport("Велосипед");

    restaurant.setName("Вкусно и точка");

    contact.setPhone("+375291234567");

    payment.setAmount(25.0);
    payment.pay();

    review.setStars(5);

    notification.setMessage("Заказ принят");
    notification.send();

    ticket.setPriority(3);

    feedback.setStars(5);

    stats.addOrder(25.0);
    stats.addOrder(30.0);

    report.setTitle("Отчёт за январь");
    report.append("Заказов: 120");

    analytics.setPeriod("Январь");

    audit.log("admin", "Система запущена");

    wallet.topUp(100.0);

    loyalty.addPoints(600);
    bonus.addPoints(600);

    Order order;
    order.setOrderId("O-001");
    order.setClient(&client);
    order.setCourier(&courier);
    order.setAddress(address);
    delivery.setOrder(&order);
    delivery.setCourier(&courier);
    delivery.start("12:00");
    delivery.complete("12:30");

    route.setPoints(GeoPoint(1, 1), GeoPoint(2, 2));
    route.calculate();

    warehouse.store(100);

    supplier.setPhone("+375291234567");

    ad.setBudget(1000.0);
    ad.addImpression();

    promotion.setName("Новогодняя");
    promotion.apply(100.0);


    zone.covers(5);
}

int main() {
     try {
        initData();
    } catch (const FoodDeliveryException& e) {
        std::cout << "Ошибка инициализации: " << e.what() << '\n';
    }
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
                case 1:  std::cout << system_.info() << '\n'; break;
                case 2:  std::cout << client.info() << '\n'; break;
                case 3:  std::cout << courier.fullName() << '\n'; break;
                case 4:  std::cout << restaurant.info() << '\n'; break;
                case 5:  std::cout << dish.info() << '\n'; break;
                case 6:  std::cout << address.full() << '\n'; break;
                case 7:  std::cout << contact.info() << '\n'; break;
                case 8:  std::cout << (payment.isPaid() ? "Оплачено\n" : "Не оплачено\n"); break;
                case 9:  std::cout << (promo.isValid() ? "Промокод активен\n" : "Неактивен\n"); break;
                case 10: std::cout << (review.isValid() ? "Отзыв корректный\n" : "Плохой\n"); break;
                case 11: std::cout << "Рейтинг: " << rating.value() << '\n'; break;
                case 12: std::cout << (complaint.isResolved() ? "Решена\n" : "Не решена\n"); break;
                case 13: std::cout << (notification.isSent() ? "Уведомление отправлено\n" : "Не отправлено\n"); break;
                case 14: std::cout << (ticket.isResolved() ? "Тикет решён\n" : "В работе\n"); break;
                case 15: std::cout << (feedback.isValid() ? "Оценка принята\n" : "Неверная\n"); break;
                case 16: std::cout << "Средний чек: " << stats.averageOrder() << '\n'; break;
                case 17: std::cout << (report.isEmpty() ? "Пусто\n" : "Отчёт есть\n"); break;
                case 18: std::cout << "Выручка: " << analytics.revenue() << '\n'; break;
                case 19: std::cout << audit.last() << '\n'; break;
                case 20: std::cout << "Баланс: " << wallet.getBalance() << '\n'; break;
                case 21: std::cout << "Уровень: " << loyalty.getLevel() << '\n'; break;
                case 22: std::cout << (delivery.isCompleted() ? "Доставлено\n" : "В пути\n"); break;
                case 23: std::cout << "Время в пути: " << route.estimatedMinutes() << " мин\n"; break;
                case 24: std::cout << (hours.isOpen("12:00") ? "Открыто\n" : "Закрыто\n"); break;
                case 25: std::cout << (kitchen.canAccept() ? "Кухня принимает\n" : "Перегружена\n"); break;
                case 26: std::cout << (warehouse.hasSpace(10) ? "Есть место\n" : "Полно\n"); break;
                case 27: std::cout << (supplier.canDeliver() ? "Доставит\n" : "Нет\n"); break;
                case 28: std::cout << "Цена показа: " << ad.costPerImpression() << '\n'; break;
                case 29: std::cout << (promotion.isActive("2025-12-31") ? "Активна\n" : "Неактивна\n"); break;
                case 30: std::cout << (zone.covers(5) ? "Покрывает\n" : "Не покрывает\n"); break;
                case 0:  std::cout << "Пока!\n"; break;
                default: std::cout << "Неверный пункт\n"; break;
            }
        } catch (const FoodDeliveryException& e) {
            std::cout << "Ошибка: " << e.what() << '\n';
        }
    }
    return 0;
}