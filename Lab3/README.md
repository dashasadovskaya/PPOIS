# Система доставки еды

Лабораторная работа №3. Предметная область: **Система доставки еды**.

| Класс | Поля | Методы | Связи |
| Address | 4 | 2 | — |
| ContactInfo | 2 | 3 | — |
| GeoPoint | 2 | 2 | — |
| Person | 2 | 2 | — |
| Client | 5 | 5 | Person, ContactInfo, Address, Rating, PromoCode |
| Courier | 5 | 6 | Person, GeoPoint |
| Employee | 3 | 3 | Person |
| Category | 2 | 1 | — |
| Dish | 5 | 4 | Category |
| MenuItem | 2 | 2 | Dish |
| Menu | 3 | 4 | MenuItem |
| OrderItem | 3 | 2 | Dish |
| Kitchen | 3 | 3 | — |
| WorkingHours | 2 | 1 | — |
| Restaurant | 7 | 6 | Address, Kitchen, WorkingHours, Rating, Menu |
| Franchise | 3 | 3 | — |
| OrderStatus | 2 | 2 | — |
| Cart | 2 | 4 | OrderItem |
| Order | 9 | 7 | Client, Restaurant, Courier, Cart, OrderStatus, Address |
| Delivery | 5 | 4 | Order, Courier |
| Route | 3 | 3 | GeoPoint |
| PaymentMethod | 2 | 1 | — |
| Payment | 5 | 4 | Order, PaymentMethod |
| PromoCode | 3 | 4 | — |
| Wallet | 2 | 3 | — |
| Receipt | 4 | 3 | — |
| Review | 4 | 5 | Client, Restaurant |
| Rating | 2 | 3 | Review |
| Complaint | 4 | 4 | Client, Order |
| Advertisement | 3 | 3 | — |
| Promotion | 3 | 2 | — |
| LoyaltyProgram | 2 | 4 | — |
| Warehouse | 3 | 4 | — |
| Supply | 3 | 2 | Dish |
| Supplier | 3 | 3 | — |
| Notification | 3 | 4 | Client |
| SupportChat | 3 | 4 | Client |
| SupportTicket | 4 | 4 | — |
| Feedback | 3 | 3 | Client |
| Report | 3 | 4 | — |
| Statistics | 3 | 3 | — |
| Analytics | 2 | 3 | Statistics |
| AuditLog | 3 | 3 | — |
| DeliveryZone | 3 | 3 | — |
| City | 2 | 2 | — |
| District | 2 | 3 | City |
| FoodDeliverySystem | 9 | 8 | Client, Restaurant, Courier, Order |
| BonusSystem | 2 | 3 | — |

## Исключения (12)
FoodDeliveryException, ClientNotFoundException, RestaurantNotFoundException,
OrderNotFoundException, InvalidClientDataException, InvalidOrderDataException,
DishNotFoundException, DishOutOfStockException, CourierNotAvailableException,
PaymentException, InvalidPromoCodeException, DeliveryNotAvailableException.

## Итого
- Классы: 50
- Поля: 160
- Поведения: 130
- Ассоциации: 45
- Исключения: 12