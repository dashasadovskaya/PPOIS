#pragma once
#include <string>
#include <iostream>
#include "Exceptions.h"

class Client; class Restaurant; class Courier; class Order; class Dish;
class Address; class Payment; class PromoCode; class Review; class Rating;
class Menu; class OrderItem; class Delivery;

class Address {
    std::string city;      ///< город
    std::string street;    ///< улица
    std::string house;     ///< дом
    std::string apartment; ///< квартира
public:
    Address() : city(""), street(""), house(""), apartment("") {}
    Address(const std::string& c, const std::string& s,
            const std::string& h, const std::string& a)
        : city(c), street(s), house(h), apartment(a) {}

    bool isValid() const { return !city.empty() && !street.empty(); }
    std::string full() const {
        return city + ", " + street + " " + house + ", кв. " + apartment;
    }
};

class ContactInfo {
    std::string phone;   ///< телефон
    std::string email;   ///< email
public:
    ContactInfo() : phone(""), email("") {}
    bool hasPhone() const { return phone.size() >= 7; }
    void setPhone(const std::string& p) {
        if (p.size() < 7) throw InvalidClientDataException("Короткий телефон");
        phone = p;
    }
    std::string info() const { return phone + " / " + email; }
};

class GeoPoint {
    double latitude;    ///< широта
    double longitude;   ///< долгота
public:
    GeoPoint() : latitude(0), longitude(0) {}
    GeoPoint(double lat, double lon) : latitude(lat), longitude(lon) {}
    bool isValid() const { return latitude != 0 && longitude != 0; }
    double distanceTo(const GeoPoint& other) const {
        double dx = latitude - other.latitude;
        double dy = longitude - other.longitude;
        return dx * dx + dy * dy;
    }
};

class Person {
protected:
    std::string firstName;   ///< имя
    std::string lastName;    ///< фамилия
public:
    Person() : firstName(""), lastName("") {}
    std::string fullName() const { return lastName + " " + firstName; }
    void setName(const std::string& f, const std::string& l) {
        if (f.empty() || l.empty())
            throw InvalidClientDataException("Пустое имя");
        firstName = f; lastName = l;
    }
};

class Client : public Person {
    std::string clientId;      ///< номер клиента
    ContactInfo contacts;      ///< контакты
    Address address;           ///< адрес
    Rating* rating;            ///< рейтинг
    PromoCode* activePromo;    ///< активный промокод
public:
    Client() : clientId(""), rating(nullptr), activePromo(nullptr) {}
    void setClientId(const std::string& id) { clientId = id; }
    bool canOrder() const { return !clientId.empty() && contacts.hasPhone(); }
    void setAddress(const Address& a) { address = a; }
    void applyPromo(PromoCode* p) { activePromo = p; }
    std::string info() const { return fullName() + " (" + clientId + ")"; }
};

class Courier : public Person {
    std::string courierId;     ///< номер курьера
    std::string transport;     ///< транспорт
    bool available;            ///< доступен
    GeoPoint location;         ///< местоположение
    int completedOrders;       ///< выполнено заказов
public:
    Courier() : courierId(""), transport(""), available(true),
                completedOrders(0) {}
    void setCourierId(const std::string& id) { courierId = id; }
    void setTransport(const std::string& t) { transport = t; }
    bool isAvailable() const { return available; }
    void goOffline() { available = false; }
    void goOnline() { available = true; }
    void completeOrder() { ++completedOrders; }
    bool canDeliver(const GeoPoint& to) const {
        return available && location.distanceTo(to) < 100;
    }
};

class Employee : public Person {
    std::string employeeId;    ///< номер
    std::string position;      ///< должность
    double salary;             ///< зарплата
public:
    Employee() : employeeId(""), position(""), salary(0) {}
    void setPosition(const std::string& p) { position = p; }
    void setSalary(double s) {
        if (s < 0) throw PaymentException("Отрицательная зарплата");
        salary = s;
    }
    double monthly() const { return salary / 12.0; }
};

class Category {
    std::string name;   ///< название
    int sortOrder;      ///< порядок
public:
    Category() : name(""), sortOrder(0) {}
    Category(const std::string& n, int o) : name(n), sortOrder(o) {}
    std::string info() const { return name; }
};

class Dish {
    std::string name;      ///< название
    std::string description; ///< описание
    double price;          ///< цена
    int quantity;          ///< остаток
    Category category;     ///< категория
public:
    Dish() : name(""), description(""), price(0), quantity(0) {}
    Dish(const std::string& n, double p, int q)
        : name(n), description(""), price(p), quantity(q) {}

    bool isAvailable() const { return quantity > 0; }
    void use(int n) {
        if (n > quantity) throw DishOutOfStockException(name);
        quantity -= n;
    }
    void restock(int n) { quantity += n; }
    std::string info() const { return name + " — " + std::to_string(price) + " руб."; }
};

class MenuItem {
    Dish dish;             ///< блюдо
    double portionSize;    ///< размер порции
public:
    MenuItem() : portionSize(1.0) {}
    void setDish(const Dish& d) { dish = d; }
    double price() const { return dish.info().empty() ? 0 : 1; }
    bool isAvailable() const { return dish.isAvailable(); }
};

class Menu {
    std::string title;      ///< название меню
    MenuItem* items;        ///< позиции
    int itemCount;          ///< количество
public:
    Menu() : title(""), items(nullptr), itemCount(0) {}
    ~Menu() { delete[] items; }
    void setTitle(const std::string& t) { title = t; }
    void addItem(const MenuItem& item);
    int total() const { return itemCount; }
    bool isEmpty() const { return itemCount == 0; }
};

class OrderItem {
    Dish dish;              ///< блюдо
    int quantity;           ///< количество
    double priceAtOrder;    ///< цена на момент заказа
public:
    OrderItem() : quantity(0), priceAtOrder(0) {}
    OrderItem(const Dish& d, int q)
        : dish(d), quantity(q), priceAtOrder(0) {}
    double total() const { return priceAtOrder * quantity; }
    void setPrice(double p) { priceAtOrder = p; }
};

class Kitchen {
    std::string name;      ///< название
    int capacity;          ///< вместимость
    int activeOrders;      ///< активных заказов
public:
    Kitchen() : name(""), capacity(10), activeOrders(0) {}
    bool canAccept() const { return activeOrders < capacity; }
    void takeOrder() {
        if (!canAccept()) throw InvalidOrderDataException("Кухня перегружена");
        ++activeOrders;
    }
    void finishOrder() { if (activeOrders > 0) --activeOrders; }
};

class WorkingHours {
    std::string open;   ///< открытие
    std::string close;  ///< закрытие
public:
    WorkingHours() : open("09:00"), close("21:00") {}
    WorkingHours(const std::string& o, const std::string& c) : open(o), close(c) {}
    bool isOpen(const std::string& now) const { return now >= open && now < close; }
};

class Restaurant {
    std::string name;      ///< название
    Address address;       ///< адрес
    Kitchen kitchen;       ///< кухня
    WorkingHours hours;    ///< часы работы
    Rating* rating;        ///< рейтинг
    Menu menu;             ///< меню
    bool opened;           ///< открыт
public:
    Restaurant() : name(""), rating(nullptr), opened(true) {}
    void setName(const std::string& n) {
        if (n.empty()) throw InvalidClientDataException("Пустое название");
        name = n;
    }
    bool isOpen() const { return opened; }
    void open() { opened = true; }
    void close() { opened = false; }
    bool canAcceptOrder() const { return opened && kitchen.canAccept(); }
    std::string info() const { return name + " (" + address.full() + ")"; }
};

class Franchise {
    std::string brand;      ///< бренд
    int restaurantCount;    ///< количество ресторанов
    double royalty;         ///< роялти
public:
    Franchise() : brand(""), restaurantCount(0), royalty(0) {}
    bool isLarge() const { return restaurantCount > 10; }
    void addRestaurant() { ++restaurantCount; }
    double monthlyRoyalty() const { return royalty * restaurantCount; }
};

class OrderStatus {
    std::string name;    ///< название
    int code;            ///< код
public:
    OrderStatus() : name(""), code(0) {}
    OrderStatus(const std::string& n, int c) : name(n), code(c) {}
    bool isFinal() const { return code >= 4; }
    std::string info() const { return name; }
};

class Cart {
    OrderItem* items;    ///< позиции
    int itemCount;       ///< количество
public:
    Cart() : items(nullptr), itemCount(0) {}
    ~Cart() { delete[] items; }
    void add(const OrderItem& item);
    void clear() { itemCount = 0; }
    double total() const;
    int size() const { return itemCount; }
};

class Order {
    std::string orderId;      ///< номер
    Client* client;           ///< клиент
    Restaurant* restaurant;   ///< ресторан
    Courier* courier;         ///< курьер
    Cart cart;                ///< корзина
    OrderStatus status;       ///< статус
    Address deliveryAddress;  ///< адрес доставки
    double totalAmount;       ///< итог
    std::string createdAt;    ///< создан
public:
    Order() : client(nullptr), restaurant(nullptr), courier(nullptr),
              totalAmount(0), createdAt("") {}

    void setOrderId(const std::string& id) { orderId = id; }
    void setClient(Client* c) { client = c; }
    void setRestaurant(Restaurant* r) { restaurant = r; }
    void setCourier(Courier* c) { courier = c; }
    void setAddress(const Address& a) { deliveryAddress = a; }
    void calculateTotal() { totalAmount = cart.total(); }
    bool canBeDelivered() const {
        return client && restaurant && courier && totalAmount > 0;
    }
    std::string info() const { return "Заказ " + orderId; }
};

class Delivery {
    Order* order;         ///< заказ
    Courier* courier;     ///< курьер
    std::string startTime; ///< начало
    std::string endTime;   ///< конец
    bool completed;        ///< завершена
public:
    Delivery() : order(nullptr), courier(nullptr), startTime(""),
                 endTime(""), completed(false) {}
    void setOrder(Order* o) { order = o; }
    void setCourier(Courier* c) { courier = c; }
    void start(const std::string& time) { startTime = time; }
    void complete(const std::string& time) {
        if (!order) throw OrderNotFoundException("");
        endTime = time;
        completed = true;
    }
    bool isCompleted() const { return completed; }
};

class Route {
    GeoPoint from;        ///< откуда
    GeoPoint to;          ///< куда
    double distance;      ///< расстояние
public:
    Route() : distance(0) {}
    void setPoints(const GeoPoint& f, const GeoPoint& t) { from = f; to = t; }
    void calculate() { distance = from.distanceTo(to); }
    int estimatedMinutes() const { return static_cast<int>(distance * 2); }
};

class PaymentMethod {
    std::string name;    ///< название
    bool online;         ///< онлайн
public:
    PaymentMethod() : name(""), online(false) {}
    PaymentMethod(const std::string& n, bool o) : name(n), online(o) {}
    std::string info() const { return name; }
};

class Payment {
    std::string id;          ///< номер
    Order* order;            ///< заказ
    PaymentMethod method;    ///< способ
    double amount;           ///< сумма
    bool paid;               ///< оплачен
public:
    Payment() : order(nullptr), amount(0), paid(false) {}
    void setOrder(Order* o) { order = o; }
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

class PromoCode {
    std::string code;      ///< код
    double discount;       ///< скидка в %
    bool active;           ///< активен
public:
    PromoCode() : code(""), discount(0), active(true) {}
    PromoCode(const std::string& c, double d) : code(c), discount(d), active(true) {}
    bool isValid() const {
        if (!active) return false;
        if (discount < 0 || discount > 100) return false;
        return true;
    }
    void deactivate() { active = false; }
    double applyTo(double amount) const {
        if (!isValid()) throw InvalidPromoCodeException(code);
        return amount * (1 - discount / 100.0);
    }
};

class Wallet {
    double balance;       ///< баланс
    std::string currency; ///< валюта
public:
    Wallet() : balance(0), currency("BYN") {}
    void topUp(double amount) {
        if (amount <= 0) throw PaymentException("Сумма пополнения > 0");
        balance += amount;
    }
    bool withdraw(double amount) {
        if (amount > balance) throw PaymentException("Недостаточно средств");
        balance -= amount;
        return true;
    }
    double getBalance() const { return balance; }
};

class Receipt {
    std::string number;   ///< номер
    double total;         ///< итог
    std::string date;     ///< дата
    bool printed;         ///< напечатан
public:
    Receipt() : number(""), total(0), date(""), printed(false) {}
    void setTotal(double t) { total = t; }
    void print() {
        if (total <= 0) throw PaymentException("Пустой чек");
        printed = true;
    }
    bool isPrinted() const { return printed; }
};

class Review {
    Client* client;       ///< клиент
    Restaurant* restaurant; ///< ресторан
    int stars;            ///< оценка 1-5
    std::string text;     ///< текст
public:
    Review() : client(nullptr), restaurant(nullptr), stars(0), text("") {}
    void setClient(Client* c) { client = c; }
    void setRestaurant(Restaurant* r) { restaurant = r; }
    void setStars(int s) {
        if (s < 1 || s > 5) throw InvalidOrderDataException("Оценка 1-5");
        stars = s;
    }
    void setText(const std::string& t) { text = t; }
    bool isValid() const { return stars >= 1 && stars <= 5; }
};

class Rating {
    double average;    ///< средний балл
    int count;         ///< количество
public:
    Rating() : average(0), count(0) {}
    void addReview(const Review& r);
    bool isHigh() const { return average >= 4.5; }
    double value() const { return average; }
};

class Complaint {
    Client* client;      ///< клиент
    Order* order;        ///< заказ
    std::string reason;  ///< причина
    bool resolved;       ///< решена
public:
    Complaint() : client(nullptr), order(nullptr), reason(""), resolved(false) {}
    void setClient(Client* c) { client = c; }
    void setOrder(Order* o) { order = o; }
    void setReason(const std::string& r) { reason = r; }
    void resolve() { resolved = true; }
    bool isResolved() const { return resolved; }
};

class Advertisement {
    std::string title;    ///< заголовок
    double budget;        ///< бюджет
    int impressions;      ///< показов
public:
    Advertisement() : title(""), budget(0), impressions(0) {}
    void setBudget(double b) {
        if (b < 0) throw PaymentException("Отрицательный бюджет");
        budget = b;
    }
    void addImpression() { ++impressions; }
    double costPerImpression() const {
        return impressions == 0 ? 0 : budget / impressions;
    }
};

class Promotion {
    std::string name;     ///< название
    double discount;      ///< скидка
    std::string validUntil; ///< до
public:
    Promotion() : name(""), discount(0), validUntil("") {}

    void setName(const std::string& n) { name = n; }           
    void setDiscount(double d) { discount = d; }               
    void setValidUntil(const std::string& v) { validUntil = v; } 

    bool isActive(const std::string& today) const {
        return !validUntil.empty() && today <= validUntil;
    }
    double apply(double amount) const { return amount * (1 - discount / 100.0); }
};

class LoyaltyProgram {
    int points;          ///< баллы
    std::string level;   ///< уровень
public:
    LoyaltyProgram() : points(0), level("Bronze") {}
    void addPoints(int p) {
        if (p < 0) throw PaymentException("Отрицательные баллы");
        points += p;
        updateLevel();
    }
    void updateLevel() {
        if (points >= 1000) level = "Gold";
        else if (points >= 500) level = "Silver";
    }
    std::string getLevel() const { return level; }
};

class Warehouse {
    std::string name;    ///< название
    int capacity;        ///< вместимость
    int current;         ///< сейчас
public:
    Warehouse() : name(""), capacity(1000), current(0) {}
    bool hasSpace(int n) const { return current + n <= capacity; }
    void store(int n) {
        if (!hasSpace(n)) throw DishOutOfStockException(name);
        current += n;
    }
    void take(int n) { if (n <= current) current -= n; }
};

class Supply {
    Dish dish;           ///< блюдо
    int quantity;        ///< количество
    std::string date;    ///< дата
public:
    Supply() : quantity(0), date("") {}
    void setQuantity(int q) {
        if (q <= 0) throw InvalidOrderDataException("Количество > 0");
        quantity = q;
    }
    bool isReady() const { return quantity > 0 && !date.empty(); }
};

class Supplier {
    std::string name;    ///< название
    std::string phone;   ///< телефон
    bool reliable;       ///< надёжный
public:
    Supplier() : name(""), phone(""), reliable(true) {}

    void setName(const std::string& n) { name = n; }      
    void setPhone(const std::string& p) { phone = p; }    

    void markUnreliable() { reliable = false; }
    bool canDeliver() const { return reliable && phone.size() >= 7; }
};

class Notification {
    Client* client;       ///< клиент
    std::string message;  ///< текст
    bool sent;            ///< отправлено
public:
    Notification() : client(nullptr), message(""), sent(false) {}
    void setClient(Client* c) { client = c; }
    void setMessage(const std::string& m) { message = m; }
    void send() {
        if (message.empty()) throw InvalidOrderDataException("Пустое уведомление");
        sent = true;
    }
    bool isSent() const { return sent; }
};

class SupportChat {
    Client* client;       ///< клиент
    std::string topic;    ///< тема
    bool open;            ///< открыт
public:
    SupportChat() : client(nullptr), topic(""), open(true) {}
    void setClient(Client* c) { client = c; }
    void setTopic(const std::string& t) { topic = t; }
    void close() { open = false; }
    bool isOpen() const { return open; }
};

class SupportTicket {
    std::string id;       ///< номер
    std::string problem;  ///< проблема
    int priority;         ///< приоритет 1-5
    bool resolved;        ///< решён
public:
    SupportTicket() : id(""), problem(""), priority(3), resolved(false) {}
    void setPriority(int p) {
        if (p < 1 || p > 5) throw InvalidOrderDataException("Приоритет 1-5");
        priority = p;
    }
    void resolve() { resolved = true; }
    bool isResolved() const { return resolved; }
};

class Feedback {
    Client* client;       ///< клиент
    int stars;            ///< оценка
    std::string comment;  ///< комментарий
public:
    Feedback() : client(nullptr), stars(0), comment("") {}
    void setStars(int s) {
        if (s < 1 || s > 5) throw InvalidOrderDataException("Оценка 1-5");
        stars = s;
    }
    bool isValid() const { return stars >= 1 && stars <= 5; }
};

class Report {
    std::string title;    ///< заголовок
    std::string period;   ///< период
    std::string content;  ///< содержимое
public:
    Report() : title(""), period(""), content("") {}
    void setTitle(const std::string& t) { title = t; }
    void setPeriod(const std::string& p) { period = p; }
    void append(const std::string& s) { content += s; }
    bool isEmpty() const { return content.empty(); }
};

class Statistics {
    int totalOrders;      ///< всего заказов
    int totalClients;     ///< всего клиентов
    double revenue;       ///< выручка
public:
    Statistics() : totalOrders(0), totalClients(0), revenue(0) {}
    void addOrder(double amount) {
        if (amount < 0) throw PaymentException("Отрицательная сумма");
        ++totalOrders;
        revenue += amount;
    }
    double averageOrder() const {
        return totalOrders == 0 ? 0 : revenue / totalOrders;
    }
};

class Analytics {
    Statistics stats;     ///< статистика
    std::string period;   ///< период
public:
    Analytics() : period("") {}
    void setPeriod(const std::string& p) { period = p; }
    bool isGrowing() const { return stats.averageOrder() > 20; }
    double revenue() const { return stats.averageOrder(); }
};

class AuditLog {
    std::string lastAction; ///< действие
    std::string lastUser;   ///< пользователь
    int count;              ///< количество
public:
    AuditLog() : lastAction(""), lastUser(""), count(0) {}
    void log(const std::string& u, const std::string& a) {
        lastUser = u; lastAction = a; ++count;
    }
    std::string last() const { return lastUser + ": " + lastAction; }
    int total() const { return count; }
};

class DeliveryZone {
    std::string name;     ///< название
    double radius;        ///< радиус
    double deliveryFee;   ///< стоимость доставки
public:
    DeliveryZone() : name(""), radius(0), deliveryFee(0) {}
    bool covers(double distance) const { return distance <= radius; }
    double fee() const { return deliveryFee; }
};

class City {
    std::string name;     ///< название
    int population;       ///< население
public:
    City() : name(""), population(0) {}
    City(const std::string& n, int p) : name(n), population(p) {}
    bool isLarge() const { return population > 500000; }
    std::string info() const { return name; }
};

class District {
    std::string name;     ///< название
    City city;            ///< город
public:
    District() : name("") {}
    void setName(const std::string& n) { name = n; }
    bool isValid() const { return !name.empty(); }
    std::string info() const { return city.info() + ", " + name; }
};

class FoodDeliverySystem {
    std::string name;        ///< название
    Client* clients;         ///< клиенты
    int clientCount;         ///< количество
    Restaurant* restaurants; ///< рестораны
    int restaurantCount;     ///< количество
    Courier* couriers;       ///< курьеры
    int courierCount;        ///< количество
    Order* orders;           ///< заказы
    int orderCount;          ///< количество
public:
    FoodDeliverySystem() : name(""), clients(nullptr), clientCount(0),
                           restaurants(nullptr), restaurantCount(0),
                           couriers(nullptr), courierCount(0),
                           orders(nullptr), orderCount(0) {}
    ~FoodDeliverySystem() {
        delete[] clients;
        delete[] restaurants;
        delete[] couriers;
        delete[] orders;
    }

    void setName(const std::string& n) {
        if (n.empty()) throw InvalidClientDataException("Пустое название");
        name = n;
    }
    void addClient(const Client& c);
    void addRestaurant(const Restaurant& r);
    void addCourier(const Courier& c);
    void addOrder(const Order& o);

    Client* findClient(const std::string& id);
    Restaurant* findRestaurant(const std::string& id);
    Order* findOrder(const std::string& id);

    double totalRevenue() const;
    std::string info() const { return name; }
    int counts() const { return clientCount + restaurantCount + courierCount + orderCount; }
};

class BonusSystem {
    int totalPoints;      ///< всего баллов
    double cashbackRate;  ///< процент кэшбэка
public:
    BonusSystem() : totalPoints(0), cashbackRate(5.0) {}
    void addPoints(int p) { totalPoints += p; }
    double cashback(double amount) const { return amount * cashbackRate / 100.0; }
    int points() const { return totalPoints; }
};