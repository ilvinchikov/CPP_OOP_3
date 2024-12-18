#ifndef BOOKING_H
#define BOOKING_H
#include "UsefulFunctions.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// стандартная комната
class Booking {
private:
    int m_number;       // номер комнаты
    string m_type;      // тип комнаты
    int m_period;       // количество ночей
    double m_price;     // начальная цена за 1 ночь
    bool m_status;      // статус: забронирована или нет
    int m_count;        // 1 человек или групповое бронирование
    vector<string> m_services;  // доп.услуги - записываются из словаря отеля m_hotelServices
    vector<string> m_bonuses;  // бонусы - записываются из словаря отеля m_hotelBonuses
public:
    // конструктор с параметрами
    Booking(int number, string type, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses): m_number(number), m_type(type), m_period(period), m_price(price), m_status(status), m_count(count), m_services(services), m_bonuses(bonuses) {}

    // показ информации о номере
    void getDisplayInfo(const double& hotelOccupancy, const map<string, double>& hotelServices, const map<string, double>& hotelBonuses){
        cout << "<< Номер " << m_number << " (" << m_type << ") >>";
        if (m_count > 1 && m_status) {
            cout << " - Групповое бронирование" << endl;
            cout << "Количество номеров: " << m_count << endl;
        }
        else {
            cout << endl;
        }
        cout << "Количество ночей: " << m_period << endl
             << "Начальная цена за 1 ночь: " << m_price << endl
             << "Дополнительные услуги: ";
        if (m_services.size() > 0) {
            for (auto i=0; i<m_services.size(); i++) {
                if (i != 0) cout << ", ";
                cout << m_services[i];
            }
            cout << endl;
        }
        else {
            cout << "нет" << endl;
        }
        cout << "Скидки(бонусы): ";
        if (m_bonuses.size() > 0) {
            for (auto i=0; i<m_bonuses.size(); i++) {
                if (i != 0) cout << ", ";
                cout << m_bonuses[i];
            }
            cout << endl;
        }
        else {
            cout << "нет" << endl;
        }
        cout << endl << "Общая стоимость: " << calculatePrice(hotelOccupancy, hotelServices, hotelBonuses);
        if (m_bonuses.size() > 0) {
            cout << " (с учётом скидок)";
        }
        cout << endl;
    }

    // расчет цены номера
    double calculatePrice(const double& hotelOccupancy, const map<string, double>& hotelServices, const map<string, double>& hotelBonuses) {
        UsefulFunctions us;
        double resultPrice = m_price;
        // кол-во ночей
        resultPrice *= m_period;
        // загруженность (+проверка)
        if (hotelOccupancy > 0 && hotelOccupancy <= 1) {
            if (hotelOccupancy >= 0.5) resultPrice *= (0.6 + hotelOccupancy);
            else resultPrice *= (1 - (0.6 - hotelOccupancy));
        }
        // бонусные скидки:
        for (auto i=0; i<m_bonuses.size(); i++) {
            if (hotelBonuses.count(m_bonuses[i]) > 0) resultPrice *= (1 - hotelBonuses.at(m_bonuses[i]));
        }
        // доп.услуги:
        for (auto i=0; i<m_services.size(); i++) {
            if (hotelServices.count(m_services[i]) > 0) resultPrice += hotelServices.at(m_services[i]);
        }
        return resultPrice;
    }

    // возврат типа комнаты
    string getType(){
        return m_type;
    }

    // установка типа комнаты
    void setType(string type){
        m_type = type;
    }

    // возврат начальной цены
    double getPrice() {
        return m_price;
    }

    // установка начальной цены
    void setPrice(double price) {
        m_price = price;
    }

    // возврат номера комнаты
    int getNumber(){
        return m_number;
    }

    // установка номера
    void setNumber(int number) {
        m_number = number;
    }

    // возврат числа
    int getCount(){
        return m_count;
    }

    // установка числа
    void setCount(int count) {
        m_count = count;
    }

    // возврат количества ночей
    int getPeriod(){
        return m_period;
    }

    // установка количества ночей
    void setPeriod(int period){
        m_period = period;
    }

    // получение статуса (занят/свободен)
    bool getStatus() {
        return m_status;
    }

    // установка статуса (занят/свободен)
    void setStatus(bool status) {
        m_status = status;
    }

    // возврат назначенных услуг
    vector<string> getServices(){
        return m_services;
    }

    // добавление услуги (к заказу)
    void addService(string name){
        m_services.push_back(name);
    }


    // удаление услуги (по номеру)
    void deleteService(size_t index){
        m_services.erase(m_services.begin() + index);
    }

    // удаление услуги (по названию)
    void deleteService(string name){
        UsefulFunctions us;
        for (auto i=0; i< m_services.size(); i++) {
            if (us.trim(us.toLowerCase(name)) == us.trim(us.toLowerCase(m_services[i]))) {
                m_services.erase(m_services.begin() + i);
                return;
            }
        }
        cout << "Ошибка удаления: услуги с таким названием не найдено." << endl;
    }

    // возврат начисленных бонусов
    vector<string> getBonuses(){
        return m_bonuses;
    }

    // добавление бонусов (к заказу)
    void addBonus(string name){
        m_bonuses.push_back(name);
    }

    // удаление бонусов (по номеру)
    void deleteBonus(size_t index){
        m_bonuses.erase(m_bonuses.begin() + index);
    }

    // удаление бонусов (по названию)
    void deleteBonus(string name){
        UsefulFunctions us;
        for (auto i=0; i< m_bonuses.size(); i++) {
            if (us.trim(us.toLowerCase(name)) == us.trim(us.toLowerCase(m_bonuses[i]))) {
                m_bonuses.erase(m_bonuses.begin() + i);
                return;
            }
        }
        cout << "Ошибка удаления: бонуса с таким названием не найдено." << endl;
    }



    // дружелюбный класс Hotels
    friend class Hotels;
};

// одноместный номер
class SingleRoom: public Booking {
public:
    // конструктор с параметрами
    SingleRoom(int number, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses): Booking(number, "Single Room", period, price, status, count, services, bonuses) {}
};

// двухместный номер
class DoubleRoom: public Booking {
public:
    // конструктор с параметрами
    DoubleRoom(int number, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses): Booking(number, "Double Room", period, price, status, count, services, bonuses) {}

};

// номер люкс
class Suite: public Booking {
public:
    // конструктор с параметрами
    Suite(int number, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses): Booking(number, "Suite", period, price, status, count, services, bonuses) {}
};

// отель
class Hotel {
private:
    string m_name;
    double m_hotelOccupancy;                    // коэф. загруженности (0 <= x <= 1)
    map<string, double> m_hotelServices;        // словарь услуг: услуга - цена
    map<string, double> m_hotelBonuses;         // словарь бонусов: бонус - скидка(0 <= x <= 1)
    map<string, double> m_hotelTypesRoom;       // словарь комнат: комната - цена (для каждого отеля свои цены)
    vector<Booking*> m_rooms;                   // комнаты
public:
    // конструктор с параметрами
    Hotel(string name): m_name(name), m_hotelOccupancy(0) {
        // вычисление коэф.загруженности
        updateOccupancy();
    }

    // деструктор
    ~Hotel() {
        // очищаем указатели на комнаты
        for (auto i=0; i<m_rooms.size(); i++) {
            delete m_rooms[i];
        }
        // очищаем вектор
        m_rooms.clear();
    }

    // установка имени отеля
    void setName(string name) {
        m_name = name;
    }

    // возврат имени отеля
    string getName() {
        return m_name;
    }

    // возврат списка комнат
    vector<Booking*> getRooms() {
        return m_rooms;
    }

    // возврат списка услуг
    map<string, double> getListServices() {
        return m_hotelServices;
    }

    // возврат списка типов комнат
    map<string, double> getListTypesRoom() {
        return m_hotelTypesRoom;
    }

    // возврат списка бонусов
    map<string, double> getListBonuses() {
        return m_hotelBonuses;
    }

    // добавление типа комнаты в список отеля
    void addOrSetTypesRoom(string name, double price) {
        m_hotelTypesRoom[name] = price;
    }

    // удаление типа комнаты из списка отеля
    void deleteTypesRoom(string name) {
        m_hotelTypesRoom.erase(name);
    }

    // отображение видов комнат
    void displayTypesRoom() {
        cout << "Доступные типы комнат отеля \"" << m_name << "\":" << endl;
        for (const auto& [type, price] : m_hotelTypesRoom) cout << "Тип комнаты: " << type << " - Цена: " << price << endl;
    }

    // добавление услуг в список отеля
    void addOrSetService(string name, double price) {
        m_hotelServices[name] = price;
    }

    // удаление услуг у списка отеля
    void deleteService(string name) {
        m_hotelServices.erase(name);
    }

    // отображение списка услуг
    void displayServices() {
        cout << "Дополнительные услуги отеля \"" << m_name << "\":" << endl;
        for (const auto& [service, price] : m_hotelServices) cout << "Услуга: " << service << " - Цена: " << price << endl;
    }

    // добавление бонусов в список отеля
    void addOrSetBonus(string name, double discount) {
        if (discount >= 0 && discount <= 1) m_hotelBonuses[name] = discount;
        else m_hotelBonuses[name] = 0;

    }

    // удаление бонусов из списка отеля
    void deleteBonus(string name) {
        m_hotelBonuses.erase(name);
    }

    // отображение списка бонусов
    void displayBonuses() {
        cout << "Бонусные скидки отеля \"" << m_name << "\":" << endl;
        for (const auto& [bonus, discount] : m_hotelBonuses) cout << "Бонус: " << bonus << " - Скидка: " << discount*100 << "%" << endl;
    }

    // возврат загруженности
    double getOccupancy() {
        updateOccupancy();
        return m_hotelOccupancy;
    }

    // обновление загруженности (обновляется член класса)
    void updateOccupancy() {
        if (m_rooms.size() > 0) m_hotelOccupancy = (getCountBusyRooms()/m_rooms.size());
        else m_hotelOccupancy = 0;
    }

    // возврат занятых/забронированных комнат
    long getCountBusyRooms(){
        if (m_rooms.size() > 0) {
            long busyRooms = 0;
            for (auto i=0; i<m_rooms.size(); i++) {
                if (m_rooms[i]->getStatus()) busyRooms++;
            }
            return busyRooms;
        }
        return 0;
    }

    // отображение списка комнат
    void displayRooms() {
        if (m_rooms.size() > 0) {
            for(auto i=0; i<m_rooms.size(); i++) {
                cout << i+1 << ". Номер: " << m_rooms[i]->getNumber()
                     << ", тип комнаты: " << m_rooms[i]->getType()
                     << ", начальная цена: " << m_rooms[i]->getPrice()
                     << ", свободна/занята: " << m_rooms[i]->getStatus();
                if (m_rooms[i]->getCount() > 1 && m_rooms[i]->getStatus()) cout << ", групповое бронирование (" << m_rooms[i]->getCount() << " номера)";
                cout << ", ночей: " << m_rooms[i]->getPeriod();
                // услуги
                if (m_rooms[i]->getServices().size() > 0) {
                    cout << ", услуги: ";
                    for (auto j=0; j<m_rooms[i]->getServices().size(); j++) {
                        if (j != 0) cout << ", ";
                        cout << m_rooms[i]->getServices()[j];
                    }
                }
                // бонусы
                if (m_rooms[i]->getBonuses().size() > 0) {
                    cout << ", бонусы: ";
                    for (auto j=0; j<m_rooms[i]->getBonuses().size(); j++) {
                        if (j != 0) cout << ", ";
                        cout << m_rooms[i]->getBonuses()[j];
                    }
                }
                cout << endl;
            }
        }
        else {
            cout << "<< Комнат нет >>" << endl;
        }
    }

    // добавить комнату (новую) в список отеля
    void addRoom(int number, string type, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses) {
        UsefulFunctions us;
        // проверка: если есть такие бонусы у отеля
        for (auto i=0; i<bonuses.size(); i++) {
            if (m_hotelBonuses.count(bonuses[i]) == 0) {
                cout << "Ошибка. Бонусные скидки, которые вы хотите добавить к номеру, отсутствуют в списке скидок вашего отеля." << endl;
                return;
            }
        }
        // проверка : если есть такие услуги у отеля
        for (auto i=0; i<services.size(); i++) {
            if (m_hotelServices.count(services[i]) == 0) {
                cout << "Ошибка. Дополнительные услуги, которые вы хотите добавить к номеру, отсутствуют в списке услуг вашего отеля." << endl;
                return;
            }
        }
        // тогда доступ к нижнему блоку

        // одиночный номер
        if (us.trim(us.toLowerCase(type)).find("single room") && (m_hotelTypesRoom.count("Single Room") > 0)) {
            m_rooms.emplace_back(new SingleRoom(number, period, m_hotelTypesRoom["Single Room"], status, count, services, bonuses));
        }
        // двухместный номер
        else if (us.trim(us.toLowerCase(type)).find("double room") && (m_hotelTypesRoom.count("Double Room") > 0)) {
            m_rooms.emplace_back(new DoubleRoom(number, period, m_hotelTypesRoom["Double Room"], status, count, services, bonuses));
        }
        // люкс номер
        else if (us.trim(us.toLowerCase(type)).find("suite") && (m_hotelTypesRoom.count("Suite") > 0)) {
            m_rooms.emplace_back(new Suite(number, period, m_hotelTypesRoom["Suite"], status, count, services, bonuses));
        }
        // любой другой номер, содержащийся в словаре m_hotelTypesRoom
        else if (m_hotelTypesRoom.count(type) > 0) {
            m_rooms.emplace_back(new Booking(number, type, period, m_hotelTypesRoom[type], status, count, services, bonuses));
        }
        // если в словаре такого типа (type) комнаты нету ещё ИЛИ "особые условия"
        else {
            m_rooms.emplace_back(new Booking(number, type, period, price, status, count, services, bonuses));
            // можно было бы и добавить здесь новый тип комнаты, который еще не существует в словаре, НО могут быть особые условия, поэтому игнор
        }
        updateOccupancy();
    }

    // добавить комнату (готовую) в список отеля
    template<typename T>
    void addRoom(T* room) {
        m_rooms.emplace_back(room);
        updateOccupancy();
    }


    // удаление комнаты (по порядковому номеру)
    void deleteRoomByIndex(size_t index){
        delete m_rooms[index];
        m_rooms.erase(m_rooms.begin() + index);
    }

    // удаление комнаты (по номеру комнаты)
    void deleteRoomByNumber(int number){
        for (auto i=0; i< m_rooms.size(); i++) {
            if (number == m_rooms[i]->getNumber()) {
                delete m_rooms[i];
                m_rooms.erase(m_rooms.begin() + i);
                break;
            }
        }
    }

    // отчёт по отелю
    void displayReport() {
        cout << "<< Отчёт по отелю \"" << m_name << "\": >>" << endl;
        displayServices();
        displayBonuses();
        cout << "Загруженность отеля: " << getOccupancy()*100 << "%" << endl;
        cout << "Количество бронирований (занятых комнат): ";
        if (m_rooms.size() > 0) {
            cout << getCountBusyRooms() << " из " << m_rooms.size() << endl << endl;
            // выводим сначала доступные
            cout << "Доступные номера: " << endl;
            bool isExists = false;
            for (auto i=0; i<m_rooms.size(); i++) {
                if (!m_rooms[i]->getStatus()) {
                    isExists = true;
                    cout << i+1 << ". Номер " << m_rooms[i]->getNumber();
                    if (m_rooms[i]->getCount() > 1) cout << ", групповое бронирование (" << m_rooms[i]->getCount() << " номера)";
                    cout << ", ночей: " << m_rooms[i]->getPeriod();
                    if (m_rooms[i]->getServices().size() > 0) {
                        cout << ", услуги: ";
                        for (auto j=0; j<m_rooms[i]->getServices().size(); j++) {
                            if (j != 0) cout << ", ";
                            cout << m_rooms[i]->getServices()[j];
                        }
                    }
                    cout << endl;
                }
            }
            if (!isExists) cout << "<отсутствуют>" << endl;
            // выводим забронированные
            isExists = false;
            cout << "Занятые или забронированные номера: " << endl;
            for (auto i=0; i<m_rooms.size(); i++) {
                if (m_rooms[i]->getStatus()) {
                    isExists = true;
                    cout << i+1 << ". Номер " << m_rooms[i]->getNumber();
                    if (m_rooms[i]->getCount() > 1) cout << ", групповое бронирование (" << m_rooms[i]->getCount() << " номера)";
                    cout << ", ночей: " << m_rooms[i]->getPeriod();
                    if (m_rooms[i]->getServices().size() > 0) {
                        cout << ", услуги: ";
                        for (auto j=0; j<m_rooms[i]->getServices().size(); j++) {
                            if (j != 0) cout << ", ";
                            cout << m_rooms[i]->getServices()[j];
                        }
                    }
                    cout << endl;
                }
            }
            if (!isExists) cout << "<отсутствуют>" << endl;
        }
        else cout << "в отеле нет комнат." << endl;
    }
};

class HotelManager {
private:
    vector<Hotel*> hotels; // список отелей
public:

    // деструктор
    ~HotelManager() {
        // очищаем указатели на отели
        for (auto i=0; i<hotels.size(); i++) {
            delete hotels[i];
        }
        // очищаем вектор
        hotels.clear();
    }

    // возврат списка отелей
    vector<Hotel*> getHotels() {
        return hotels;
    }

    // добавление отеля (с вводом)
    void addHotel() {
        string N;
        Hotel* main = new Hotel("не указано");

        // добавляем название
        cout << "Введите название отеля: ";
        getline(cin, N);
        if (N.size() > 0) main->setName(N);
        hotels.emplace_back(main);
    }

    // удаление отеля (с вводом)
    void deleteHotel() {
        UsefulFunctions us;
        string N;

        cout << "Введите название отеля: ";
        getline(cin, N);
        if (N.size() > 0) {
            for (auto i=0; i<hotels.size(); i++) {
                if (us.trim(N) == hotels[i]->getName()) {
                    hotels.erase(hotels.begin() + i);
                    break;
                }
            }
        }
        else cout << "Ошибка. Введите корректное значение." << endl;
    }

    // отображение списка отелей
    void displayInfoHotels() {
        cout << "<< Список отелей: >>" << endl;
        if (hotels.size() > 0) {
            for(auto i=0; i<hotels.size(); i++) {
                cout << i+1 << ". " << hotels[i]->getName() << endl;
            }
        }
        else {
            cout << "<< Отелей нет >>" << endl;
        }
    }
};

#endif // BOOKING_H
