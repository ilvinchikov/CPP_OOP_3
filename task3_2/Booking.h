#ifndef BOOKING_H
#define BOOKING_H
#include "UsefulFunctions.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// ����������� �������
class Booking {
private:
    int m_number;       // ����� �������
    string m_type;      // ��� �������
    int m_period;       // ���������� �����
    double m_price;     // ��������� ���� �� 1 ����
    bool m_status;      // ������: ������������� ��� ���
    int m_count;        // 1 ������� ��� ��������� ������������
    vector<string> m_services;  // ���.������ - ������������ �� ������� ����� m_hotelServices
    vector<string> m_bonuses;  // ������ - ������������ �� ������� ����� m_hotelBonuses
public:
    // ����������� � �����������
    Booking(int number, string type, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses): m_number(number), m_type(type), m_period(period), m_price(price), m_status(status), m_count(count), m_services(services), m_bonuses(bonuses) {}

    // ����� ���������� � ������
    void getDisplayInfo(const double& hotelOccupancy, const map<string, double>& hotelServices, const map<string, double>& hotelBonuses){
        cout << "<< ����� " << m_number << " (" << m_type << ") >>";
        if (m_count > 1 && m_status) {
            cout << " - ��������� ������������" << endl;
            cout << "���������� �������: " << m_count << endl;
        }
        else {
            cout << endl;
        }
        cout << "���������� �����: " << m_period << endl
             << "��������� ���� �� 1 ����: " << m_price << endl
             << "�������������� ������: ";
        if (m_services.size() > 0) {
            for (auto i=0; i<m_services.size(); i++) {
                if (i != 0) cout << ", ";
                cout << m_services[i];
            }
            cout << endl;
        }
        else {
            cout << "���" << endl;
        }
        cout << "������(������): ";
        if (m_bonuses.size() > 0) {
            for (auto i=0; i<m_bonuses.size(); i++) {
                if (i != 0) cout << ", ";
                cout << m_bonuses[i];
            }
            cout << endl;
        }
        else {
            cout << "���" << endl;
        }
        cout << endl << "����� ���������: " << calculatePrice(hotelOccupancy, hotelServices, hotelBonuses);
        if (m_bonuses.size() > 0) {
            cout << " (� ������ ������)";
        }
        cout << endl;
    }

    // ������ ���� ������
    double calculatePrice(const double& hotelOccupancy, const map<string, double>& hotelServices, const map<string, double>& hotelBonuses) {
        UsefulFunctions us;
        double resultPrice = m_price;
        // ���-�� �����
        resultPrice *= m_period;
        // ������������� (+��������)
        if (hotelOccupancy > 0 && hotelOccupancy <= 1) {
            if (hotelOccupancy >= 0.5) resultPrice *= (0.6 + hotelOccupancy);
            else resultPrice *= (1 - (0.6 - hotelOccupancy));
        }
        // �������� ������:
        for (auto i=0; i<m_bonuses.size(); i++) {
            if (hotelBonuses.count(m_bonuses[i]) > 0) resultPrice *= (1 - hotelBonuses.at(m_bonuses[i]));
        }
        // ���.������:
        for (auto i=0; i<m_services.size(); i++) {
            if (hotelServices.count(m_services[i]) > 0) resultPrice += hotelServices.at(m_services[i]);
        }
        return resultPrice;
    }

    // ������� ���� �������
    string getType(){
        return m_type;
    }

    // ��������� ���� �������
    void setType(string type){
        m_type = type;
    }

    // ������� ��������� ����
    double getPrice() {
        return m_price;
    }

    // ��������� ��������� ����
    void setPrice(double price) {
        m_price = price;
    }

    // ������� ������ �������
    int getNumber(){
        return m_number;
    }

    // ��������� ������
    void setNumber(int number) {
        m_number = number;
    }

    // ������� �����
    int getCount(){
        return m_count;
    }

    // ��������� �����
    void setCount(int count) {
        m_count = count;
    }

    // ������� ���������� �����
    int getPeriod(){
        return m_period;
    }

    // ��������� ���������� �����
    void setPeriod(int period){
        m_period = period;
    }

    // ��������� ������� (�����/��������)
    bool getStatus() {
        return m_status;
    }

    // ��������� ������� (�����/��������)
    void setStatus(bool status) {
        m_status = status;
    }

    // ������� ����������� �����
    vector<string> getServices(){
        return m_services;
    }

    // ���������� ������ (� ������)
    void addService(string name){
        m_services.push_back(name);
    }


    // �������� ������ (�� ������)
    void deleteService(size_t index){
        m_services.erase(m_services.begin() + index);
    }

    // �������� ������ (�� ��������)
    void deleteService(string name){
        UsefulFunctions us;
        for (auto i=0; i< m_services.size(); i++) {
            if (us.trim(us.toLowerCase(name)) == us.trim(us.toLowerCase(m_services[i]))) {
                m_services.erase(m_services.begin() + i);
                return;
            }
        }
        cout << "������ ��������: ������ � ����� ��������� �� �������." << endl;
    }

    // ������� ����������� �������
    vector<string> getBonuses(){
        return m_bonuses;
    }

    // ���������� ������� (� ������)
    void addBonus(string name){
        m_bonuses.push_back(name);
    }

    // �������� ������� (�� ������)
    void deleteBonus(size_t index){
        m_bonuses.erase(m_bonuses.begin() + index);
    }

    // �������� ������� (�� ��������)
    void deleteBonus(string name){
        UsefulFunctions us;
        for (auto i=0; i< m_bonuses.size(); i++) {
            if (us.trim(us.toLowerCase(name)) == us.trim(us.toLowerCase(m_bonuses[i]))) {
                m_bonuses.erase(m_bonuses.begin() + i);
                return;
            }
        }
        cout << "������ ��������: ������ � ����� ��������� �� �������." << endl;
    }



    // ����������� ����� Hotels
    friend class Hotels;
};

// ����������� �����
class SingleRoom: public Booking {
public:
    // ����������� � �����������
    SingleRoom(int number, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses): Booking(number, "Single Room", period, price, status, count, services, bonuses) {}
};

// ����������� �����
class DoubleRoom: public Booking {
public:
    // ����������� � �����������
    DoubleRoom(int number, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses): Booking(number, "Double Room", period, price, status, count, services, bonuses) {}

};

// ����� ����
class Suite: public Booking {
public:
    // ����������� � �����������
    Suite(int number, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses): Booking(number, "Suite", period, price, status, count, services, bonuses) {}
};

// �����
class Hotel {
private:
    string m_name;
    double m_hotelOccupancy;                    // ����. ������������� (0 <= x <= 1)
    map<string, double> m_hotelServices;        // ������� �����: ������ - ����
    map<string, double> m_hotelBonuses;         // ������� �������: ����� - ������(0 <= x <= 1)
    map<string, double> m_hotelTypesRoom;       // ������� ������: ������� - ���� (��� ������� ����� ���� ����)
    vector<Booking*> m_rooms;                   // �������
public:
    // ����������� � �����������
    Hotel(string name): m_name(name), m_hotelOccupancy(0) {
        // ���������� ����.�������������
        updateOccupancy();
    }

    // ����������
    ~Hotel() {
        // ������� ��������� �� �������
        for (auto i=0; i<m_rooms.size(); i++) {
            delete m_rooms[i];
        }
        // ������� ������
        m_rooms.clear();
    }

    // ��������� ����� �����
    void setName(string name) {
        m_name = name;
    }

    // ������� ����� �����
    string getName() {
        return m_name;
    }

    // ������� ������ ������
    vector<Booking*> getRooms() {
        return m_rooms;
    }

    // ������� ������ �����
    map<string, double> getListServices() {
        return m_hotelServices;
    }

    // ������� ������ ����� ������
    map<string, double> getListTypesRoom() {
        return m_hotelTypesRoom;
    }

    // ������� ������ �������
    map<string, double> getListBonuses() {
        return m_hotelBonuses;
    }

    // ���������� ���� ������� � ������ �����
    void addOrSetTypesRoom(string name, double price) {
        m_hotelTypesRoom[name] = price;
    }

    // �������� ���� ������� �� ������ �����
    void deleteTypesRoom(string name) {
        m_hotelTypesRoom.erase(name);
    }

    // ����������� ����� ������
    void displayTypesRoom() {
        cout << "��������� ���� ������ ����� \"" << m_name << "\":" << endl;
        for (const auto& [type, price] : m_hotelTypesRoom) cout << "��� �������: " << type << " - ����: " << price << endl;
    }

    // ���������� ����� � ������ �����
    void addOrSetService(string name, double price) {
        m_hotelServices[name] = price;
    }

    // �������� ����� � ������ �����
    void deleteService(string name) {
        m_hotelServices.erase(name);
    }

    // ����������� ������ �����
    void displayServices() {
        cout << "�������������� ������ ����� \"" << m_name << "\":" << endl;
        for (const auto& [service, price] : m_hotelServices) cout << "������: " << service << " - ����: " << price << endl;
    }

    // ���������� ������� � ������ �����
    void addOrSetBonus(string name, double discount) {
        if (discount >= 0 && discount <= 1) m_hotelBonuses[name] = discount;
        else m_hotelBonuses[name] = 0;

    }

    // �������� ������� �� ������ �����
    void deleteBonus(string name) {
        m_hotelBonuses.erase(name);
    }

    // ����������� ������ �������
    void displayBonuses() {
        cout << "�������� ������ ����� \"" << m_name << "\":" << endl;
        for (const auto& [bonus, discount] : m_hotelBonuses) cout << "�����: " << bonus << " - ������: " << discount*100 << "%" << endl;
    }

    // ������� �������������
    double getOccupancy() {
        updateOccupancy();
        return m_hotelOccupancy;
    }

    // ���������� ������������� (����������� ���� ������)
    void updateOccupancy() {
        if (m_rooms.size() > 0) m_hotelOccupancy = (getCountBusyRooms()/m_rooms.size());
        else m_hotelOccupancy = 0;
    }

    // ������� �������/��������������� ������
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

    // ����������� ������ ������
    void displayRooms() {
        if (m_rooms.size() > 0) {
            for(auto i=0; i<m_rooms.size(); i++) {
                cout << i+1 << ". �����: " << m_rooms[i]->getNumber()
                     << ", ��� �������: " << m_rooms[i]->getType()
                     << ", ��������� ����: " << m_rooms[i]->getPrice()
                     << ", ��������/������: " << m_rooms[i]->getStatus();
                if (m_rooms[i]->getCount() > 1 && m_rooms[i]->getStatus()) cout << ", ��������� ������������ (" << m_rooms[i]->getCount() << " ������)";
                cout << ", �����: " << m_rooms[i]->getPeriod();
                // ������
                if (m_rooms[i]->getServices().size() > 0) {
                    cout << ", ������: ";
                    for (auto j=0; j<m_rooms[i]->getServices().size(); j++) {
                        if (j != 0) cout << ", ";
                        cout << m_rooms[i]->getServices()[j];
                    }
                }
                // ������
                if (m_rooms[i]->getBonuses().size() > 0) {
                    cout << ", ������: ";
                    for (auto j=0; j<m_rooms[i]->getBonuses().size(); j++) {
                        if (j != 0) cout << ", ";
                        cout << m_rooms[i]->getBonuses()[j];
                    }
                }
                cout << endl;
            }
        }
        else {
            cout << "<< ������ ��� >>" << endl;
        }
    }

    // �������� ������� (�����) � ������ �����
    void addRoom(int number, string type, int period, double price, bool status, int count, vector<string> services, vector<string> bonuses) {
        UsefulFunctions us;
        // ��������: ���� ���� ����� ������ � �����
        for (auto i=0; i<bonuses.size(); i++) {
            if (m_hotelBonuses.count(bonuses[i]) == 0) {
                cout << "������. �������� ������, ������� �� ������ �������� � ������, ����������� � ������ ������ ������ �����." << endl;
                return;
            }
        }
        // �������� : ���� ���� ����� ������ � �����
        for (auto i=0; i<services.size(); i++) {
            if (m_hotelServices.count(services[i]) == 0) {
                cout << "������. �������������� ������, ������� �� ������ �������� � ������, ����������� � ������ ����� ������ �����." << endl;
                return;
            }
        }
        // ����� ������ � ������� �����

        // ��������� �����
        if (us.trim(us.toLowerCase(type)).find("single room") && (m_hotelTypesRoom.count("Single Room") > 0)) {
            m_rooms.emplace_back(new SingleRoom(number, period, m_hotelTypesRoom["Single Room"], status, count, services, bonuses));
        }
        // ����������� �����
        else if (us.trim(us.toLowerCase(type)).find("double room") && (m_hotelTypesRoom.count("Double Room") > 0)) {
            m_rooms.emplace_back(new DoubleRoom(number, period, m_hotelTypesRoom["Double Room"], status, count, services, bonuses));
        }
        // ���� �����
        else if (us.trim(us.toLowerCase(type)).find("suite") && (m_hotelTypesRoom.count("Suite") > 0)) {
            m_rooms.emplace_back(new Suite(number, period, m_hotelTypesRoom["Suite"], status, count, services, bonuses));
        }
        // ����� ������ �����, ������������ � ������� m_hotelTypesRoom
        else if (m_hotelTypesRoom.count(type) > 0) {
            m_rooms.emplace_back(new Booking(number, type, period, m_hotelTypesRoom[type], status, count, services, bonuses));
        }
        // ���� � ������� ������ ���� (type) ������� ���� ��� ��� "������ �������"
        else {
            m_rooms.emplace_back(new Booking(number, type, period, price, status, count, services, bonuses));
            // ����� ���� �� � �������� ����� ����� ��� �������, ������� ��� �� ���������� � �������, �� ����� ���� ������ �������, ������� �����
        }
        updateOccupancy();
    }

    // �������� ������� (�������) � ������ �����
    template<typename T>
    void addRoom(T* room) {
        m_rooms.emplace_back(room);
        updateOccupancy();
    }


    // �������� ������� (�� ����������� ������)
    void deleteRoomByIndex(size_t index){
        delete m_rooms[index];
        m_rooms.erase(m_rooms.begin() + index);
    }

    // �������� ������� (�� ������ �������)
    void deleteRoomByNumber(int number){
        for (auto i=0; i< m_rooms.size(); i++) {
            if (number == m_rooms[i]->getNumber()) {
                delete m_rooms[i];
                m_rooms.erase(m_rooms.begin() + i);
                break;
            }
        }
    }

    // ����� �� �����
    void displayReport() {
        cout << "<< ����� �� ����� \"" << m_name << "\": >>" << endl;
        displayServices();
        displayBonuses();
        cout << "������������� �����: " << getOccupancy()*100 << "%" << endl;
        cout << "���������� ������������ (������� ������): ";
        if (m_rooms.size() > 0) {
            cout << getCountBusyRooms() << " �� " << m_rooms.size() << endl << endl;
            // ������� ������� ���������
            cout << "��������� ������: " << endl;
            bool isExists = false;
            for (auto i=0; i<m_rooms.size(); i++) {
                if (!m_rooms[i]->getStatus()) {
                    isExists = true;
                    cout << i+1 << ". ����� " << m_rooms[i]->getNumber();
                    if (m_rooms[i]->getCount() > 1) cout << ", ��������� ������������ (" << m_rooms[i]->getCount() << " ������)";
                    cout << ", �����: " << m_rooms[i]->getPeriod();
                    if (m_rooms[i]->getServices().size() > 0) {
                        cout << ", ������: ";
                        for (auto j=0; j<m_rooms[i]->getServices().size(); j++) {
                            if (j != 0) cout << ", ";
                            cout << m_rooms[i]->getServices()[j];
                        }
                    }
                    cout << endl;
                }
            }
            if (!isExists) cout << "<�����������>" << endl;
            // ������� ���������������
            isExists = false;
            cout << "������� ��� ��������������� ������: " << endl;
            for (auto i=0; i<m_rooms.size(); i++) {
                if (m_rooms[i]->getStatus()) {
                    isExists = true;
                    cout << i+1 << ". ����� " << m_rooms[i]->getNumber();
                    if (m_rooms[i]->getCount() > 1) cout << ", ��������� ������������ (" << m_rooms[i]->getCount() << " ������)";
                    cout << ", �����: " << m_rooms[i]->getPeriod();
                    if (m_rooms[i]->getServices().size() > 0) {
                        cout << ", ������: ";
                        for (auto j=0; j<m_rooms[i]->getServices().size(); j++) {
                            if (j != 0) cout << ", ";
                            cout << m_rooms[i]->getServices()[j];
                        }
                    }
                    cout << endl;
                }
            }
            if (!isExists) cout << "<�����������>" << endl;
        }
        else cout << "� ����� ��� ������." << endl;
    }
};

class HotelManager {
private:
    vector<Hotel*> hotels; // ������ ������
public:

    // ����������
    ~HotelManager() {
        // ������� ��������� �� �����
        for (auto i=0; i<hotels.size(); i++) {
            delete hotels[i];
        }
        // ������� ������
        hotels.clear();
    }

    // ������� ������ ������
    vector<Hotel*> getHotels() {
        return hotels;
    }

    // ���������� ����� (� ������)
    void addHotel() {
        string N;
        Hotel* main = new Hotel("�� �������");

        // ��������� ��������
        cout << "������� �������� �����: ";
        getline(cin, N);
        if (N.size() > 0) main->setName(N);
        hotels.emplace_back(main);
    }

    // �������� ����� (� ������)
    void deleteHotel() {
        UsefulFunctions us;
        string N;

        cout << "������� �������� �����: ";
        getline(cin, N);
        if (N.size() > 0) {
            for (auto i=0; i<hotels.size(); i++) {
                if (us.trim(N) == hotels[i]->getName()) {
                    hotels.erase(hotels.begin() + i);
                    break;
                }
            }
        }
        else cout << "������. ������� ���������� ��������." << endl;
    }

    // ����������� ������ ������
    void displayInfoHotels() {
        cout << "<< ������ ������: >>" << endl;
        if (hotels.size() > 0) {
            for(auto i=0; i<hotels.size(); i++) {
                cout << i+1 << ". " << hotels[i]->getName() << endl;
            }
        }
        else {
            cout << "<< ������ ��� >>" << endl;
        }
    }
};

#endif // BOOKING_H
