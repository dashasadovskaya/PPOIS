#pragma once
#include <stdexcept>
#include <string>

class FoodDeliveryException : public std::runtime_error {
public:
    explicit FoodDeliveryException(const std::string& m) : std::runtime_error(m) {}
};

class ClientNotFoundException : public FoodDeliveryException {
public:
    explicit ClientNotFoundException(const std::string& id)
        : FoodDeliveryException("Клиент не найден: " + id) {}
};

class RestaurantNotFoundException : public FoodDeliveryException {
public:
    explicit RestaurantNotFoundException(const std::string& id)
        : FoodDeliveryException("Ресторан не найден: " + id) {}
};

class OrderNotFoundException : public FoodDeliveryException {
public:
    explicit OrderNotFoundException(const std::string& id)
        : FoodDeliveryException("Заказ не найден: " + id) {}
};

class InvalidClientDataException : public FoodDeliveryException {
public:
    explicit InvalidClientDataException(const std::string& m)
        : FoodDeliveryException("Некорректные данные клиента: " + m) {}
};

class InvalidOrderDataException : public FoodDeliveryException {
public:
    explicit InvalidOrderDataException(const std::string& m)
        : FoodDeliveryException("Некорректный заказ: " + m) {}
};

class DishNotFoundException : public FoodDeliveryException {
public:
    explicit DishNotFoundException(const std::string& m)
        : FoodDeliveryException("Блюдо не найдено: " + m) {}
};

class DishOutOfStockException : public FoodDeliveryException {
public:
    explicit DishOutOfStockException(const std::string& m)
        : FoodDeliveryException("Блюдо закончилось: " + m) {}
};

class CourierNotAvailableException : public FoodDeliveryException {
public:
    explicit CourierNotAvailableException(const std::string& id)
        : FoodDeliveryException("Курьер недоступен: " + id) {}
};

class PaymentException : public FoodDeliveryException {
public:
    explicit PaymentException(const std::string& m)
        : FoodDeliveryException("Ошибка оплаты: " + m) {}
};

class InvalidPromoCodeException : public FoodDeliveryException {
public:
    explicit InvalidPromoCodeException(const std::string& code)
        : FoodDeliveryException("Промокод недействителен: " + code) {}
};

class DeliveryNotAvailableException : public FoodDeliveryException {
public:
    explicit DeliveryNotAvailableException(const std::string& addr)
        : FoodDeliveryException("Доставка недоступна: " + addr) {}
};