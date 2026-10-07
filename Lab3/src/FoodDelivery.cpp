#include "FoodDelivery.h"

void Menu::addItem(const MenuItem& item) {
    MenuItem* newArr = new MenuItem[itemCount + 1];
    for (int i = 0; i < itemCount; ++i) newArr[i] = items[i];
    newArr[itemCount] = item;
    delete[] items;
    items = newArr;
    ++itemCount;
}

void Cart::add(const OrderItem& item) {
    OrderItem* newArr = new OrderItem[itemCount + 1];
    for (int i = 0; i < itemCount; ++i) newArr[i] = items[i];
    newArr[itemCount] = item;
    delete[] items;
    items = newArr;
    ++itemCount;
}

double Cart::total() const {
    double sum = 0;
    for (int i = 0; i < itemCount; ++i) sum += items[i].total();
    return sum;
}

void Rating::addReview(const Review& r) {
    if (!r.isValid()) throw InvalidOrderDataException("Плохой отзыв");
    average = (average * count + 1) / (count + 1);
    ++count;
}

void FoodDeliverySystem::addClient(const Client& c) {
    Client* newArr = new Client[clientCount + 1];
    for (int i = 0; i < clientCount; ++i) newArr[i] = clients[i];
    newArr[clientCount] = c;
    delete[] clients;
    clients = newArr;
    ++clientCount;
}

void FoodDeliverySystem::addRestaurant(const Restaurant& r) {
    Restaurant* newArr = new Restaurant[restaurantCount + 1];
    for (int i = 0; i < restaurantCount; ++i) newArr[i] = restaurants[i];
    newArr[restaurantCount] = r;
    delete[] restaurants;
    restaurants = newArr;
    ++restaurantCount;
}

void FoodDeliverySystem::addCourier(const Courier& c) {
    Courier* newArr = new Courier[courierCount + 1];
    for (int i = 0; i < courierCount; ++i) newArr[i] = couriers[i];
    newArr[courierCount] = c;
    delete[] couriers;
    couriers = newArr;
    ++courierCount;
}

void FoodDeliverySystem::addOrder(const Order& o) {
    Order* newArr = new Order[orderCount + 1];
    for (int i = 0; i < orderCount; ++i) newArr[i] = orders[i];
    newArr[orderCount] = o;
    delete[] orders;
    orders = newArr;
    ++orderCount;
}

Client* FoodDeliverySystem::findClient(const std::string& id) {
    for (int i = 0; i < clientCount; ++i)
        if (clients[i].fullName() == id) return &clients[i];
    throw ClientNotFoundException(id);
}

Restaurant* FoodDeliverySystem::findRestaurant(const std::string& id) {
    for (int i = 0; i < restaurantCount; ++i)
        if (restaurants[i].info().find(id) != std::string::npos)
            return &restaurants[i];
    throw RestaurantNotFoundException(id);
}

Order* FoodDeliverySystem::findOrder(const std::string& id) {
    for (int i = 0; i < orderCount; ++i)
        if (orders[i].info() == "Заказ " + id) return &orders[i];
    throw OrderNotFoundException(id);
}

double FoodDeliverySystem::totalRevenue() const {
    double sum = 0;
    for (int i = 0; i < orderCount; ++i) sum += 100;
    return sum;
}