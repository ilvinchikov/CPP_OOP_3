#include <QCoreApplication>
#include <Windows.h>
#include "Booking.h"
#include "UsefulFunctions.h"

// ���� �������
void menuRoom(Booking*& room, Hotel*& hotel) { // �������� ����� ��������� ������� (������ ����� - ���������) � ����� ����� (����� - ���������)
    UsefulFunctions us;
    string N;
    us.clearConsole();
    for(;;)
    {
        cout << endl << endl << "\n �������� ������ " << room->getNumber() << ":" << endl;
        cout << "1 - ����� �� ����;" << endl;
        cout << "2 - ���������� � �������;" << endl;
        cout << "3 - �������� ����� �������;" << endl;
        cout << "4 - ������� ���;" << endl;
        cout << "5 - ������� ���������� �����;" << endl;
        cout << "6 - ������� ����;" << endl;
        cout << "7 - ������� ������ (������/��������);" << endl;
        cout << "8 - ������� ����� �����;" << endl;
        cout << "9 - �������� ������;" << endl;
        cout << "10 - ������� ������;" << endl;
        cout << "11 - �������� ������(�����);" << endl;
        cout << "12 - ������� ������(�����);" << endl;
        cout << "������� ����� ��������: ";
        getline(cin,N);
        switch (us.extractLong(N)) {
        case 1: // �����
            us.clearConsole();
            return;
        case 2: // ���� � �������
            room->getDisplayInfo(hotel->getCountBusyRooms(), hotel->getListServices(), hotel->getListBonuses());
            continue;
        case 3: // ������� �����
            cout << endl << "����� ������. ������� ����� ����� (����� �����): ";
            getline(cin,N);
            if (us.extractLong(N) > 0) {
                room->setNumber(us.extractLong(N));
            }
            else cout << "������: ����� ������ ���� �����." << endl;
            continue;
        case 4: // ������� ���
            cout << endl << "����� ���� ������. ������� ����� ��� (������): ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                if (hotel->getListTypesRoom().count(us.trim(N)) > 0) {
                    room->setType(us.trim(N));
                }
                else cout << "������. ������ ���� ������� �� ���������� � ������ ����� ������ �����. ��������� � �������� ���." << endl;
            }
            else {
                cout << "������: ���������� ������ ������." << endl;
                continue;
            }
            continue;
        case 5: // ������� ����� �����
            cout << endl << "����� ���������� �����. ������� ���������� (����� ������������� �����): ";
            getline(cin,N);
            if (us.extractLong(N) > 0) {
                room->setPeriod(us.extractLong(N));
            }
            else cout << "������: ����� ������ ���� ����� � �������������." << endl;
            continue;
        case 6: // ������� ����
            cout << endl << "����� ����. ������� ����� ���� (�����): ";
            getline(cin,N);
            if (us.toDouble(N) > 0) {
                room->setPrice(us.toDouble(N));
            }
            else cout << "������: �������� ������ ���� ������������� ������." << endl;
            continue;
        case 7: // ������� ������
            cout << endl << "����� �������. ������� ����� (0 - �������� / 1 - ������): ";
            getline(cin,N);
            if (us.extractLong(N) == 1) {
                room->setStatus(true);
            }
            else if (us.extractLong(N) == 0) {
                room->setStatus(false);
            }
            else cout << "������: ����� ������ ���� ����� 0 ��� 1." << endl;
            continue;
        case 8: // ������� �����
            cout << endl << "����� ���������� �����. ������� ���������� (����� ������������� �����): ";
            getline(cin,N);
            if (us.extractLong(N) > 0) {
                room->setCount(us.extractLong(N));
            }
            else cout << "������: ����� ������ ���� ����� � �������������." << endl;
            continue;
        case 9: // �������� ������
            cout << endl;
            hotel->displayServices();
            cout << endl << "���������� ������. ������� ��������: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                if (hotel->getListServices().count(us.trim(N)) > 0) {
                    room->addService(us.trim(N));
                }
                else cout << "������. ����� ������ �� ���������� � ������ ����� �����. ��������� � �������� ���." << endl;
            }
            else {
                cout << "������: ���������� ������ ������." << endl;
                continue;
            }
            continue;
        case 10: // ������� ������
            cout << endl;
            hotel->displayServices();
            cout << endl << "�������� ������. ������� ��������: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                room->deleteService(N);
            }
            else {
                cout << "������: ���������� ������ ������." << endl;
                continue;
            }
            continue;
        case 11: // �������� ������
            cout << endl;
            hotel->displayBonuses();
            cout << endl << "���������� ������. ������� ��������: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                if (hotel->getListBonuses().count(us.trim(N)) > 0) {
                    room->addBonus(us.trim(N));
                }
                else cout << "������. ����� ������ �� ���������� � ������ ������ �����. ��������� � �������� �." << endl;
            }
            else {
                cout << "������: ���������� ������ ������." << endl;
                continue;
            }
            continue;
        case 12: // ������� ������
            cout << endl;
            hotel->displayBonuses();
            cout << endl << "�������� ������. ������� ��������: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                room->deleteBonus(N);
            }
            else {
                cout << "������: ���������� ������ ������." << endl;
                continue;
            }
            continue;
        default:
            cout << "\n������. �������� ��������. (����: " << N << ")" <<  endl;
            continue;
        }
    }
}

// ����: ����� "�"
void menuRooms(Hotel*& hotel) { // �������� ����� ���������� ����� (������ ����� - ���������)
    UsefulFunctions us;
    string N;                           // ���������� ��� �����
    vector<string> collectorValuesMain;         // ������� �������� (��������): �����, ���, ���-�� ����� � �.�.
    vector<string> collectorValuesAddition;     // ������� �������� (������, ������������� ����� �������):  �����, ������� � �.�
    us.clearConsole();
    for(;;)
    {
        collectorValuesMain.clear();
        collectorValuesAddition.clear();
        cout << endl << endl << "\n �������� ����� \"" << hotel->getName() << "\": " << endl;
        cout << "1 - ����� �� ����;" << endl;
        cout << "2 - ����� �� �����;" << endl;
        cout << "3 - ����� �� �������;" << endl;
        cout << "4 - ���������� ��������� �������;" << endl;
        cout << "5 - �������� �������;" << endl;
        cout << "6 - �������� �������;" << endl;
        cout << "7 - ������� �������;" << endl;
        cout << "8 - ����������� ������ �������;" << endl;
        cout << "9 - ��������/�������� ����� � ������;" << endl;
        cout << "10 - ������� ����� �� ������;" << endl;
        cout << "11 - ����������� ������ ��������� �����;" << endl;
        cout << "12 - ��������/�������� ������ � ������ �����;" << endl;
        cout << "13 - ������� ������ �� ������ �����;" << endl;
        cout << "14 - ����������� ������ ����� ������;" << endl;
        cout << "15 - ��������/�������� ��� ������� � ������ �����;" << endl;
        cout << "16 - ������� ��� ������� �� ������ �����;" << endl;
        cout << "������� ����� ��������: ";
        getline(cin,N);
        switch (us.extractLong(N)) {
        case 1: // �����
            us.clearConsole();
            return;
        case 2: // ����� �� �����
            us.clearConsole();
            hotel->displayReport();
            continue;
        case 3: // ����� �� ������
            us.clearConsole();
            hotel->displayRooms();
            cout << endl << "����� �� �������. ������� ���������� ����� �������: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= hotel->getRooms().size()) {
                hotel->getRooms()[us.extractLong(N)-1]->getDisplayInfo(hotel->getOccupancy(), hotel->getListServices(), hotel->getListBonuses());
            }
            else cout << "������: ����� ������� �� ����������." << endl;
            continue;
        case 4: // ������� �������� ��������� ������
            us.clearConsole();
            hotel->displayRooms();
            cout << endl << "������� ��������� �������. ������� ���������� ����� �������: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= hotel->getRooms().size()) {
                cout << "�������� ���� � ������ �������� ������ � ���.�����: " << hotel->getRooms()[us.extractLong(N)-1]->calculatePrice(hotel->getOccupancy(), hotel->getListServices(), hotel->getListBonuses()) << endl;
            }
            else cout << "������: ����� ������� �� ����������." << endl;
            continue;
        case 5: // ���������� �������
            us.clearConsole();
            // ����� �������
            cout << "���������� ����� �������:" << endl << "1. ����� ������� (����� �����): ";
            getline(cin,N);
            if (us.extractLong(us.trim(N)) > 0) collectorValuesMain.push_back(us.trim(N));
            else {
                cout << "������. ��������� ����� ������� ����������� (��� ������ ���� ����� �����, ������ ����)." << endl;
                continue;
            }
            // ���
            cout << endl << "2. ��� ������� (������): ";
            getline(cin,N);
            collectorValuesMain.push_back(us.trim(N));
            // ������
            cout << endl << "3. ���������� ����� (����� �����): ";
            getline(cin,N);
            if (us.extractLong(us.trim(N)) > 0) collectorValuesMain.push_back(us.trim(N));
            else {
                cout << "������. ��������� ����� ����� ����������� (��� ������ ���� ����� �����, ������ ����)." << endl;
                continue;
            }
            // ����
            cout << endl << "4. ���� (������������� �����): ";
            getline(cin,N);
            if (us.toDouble(us.trim(N)) > 0) collectorValuesMain.push_back(us.trim(N));
            else {
                cout << "������. ��������� ���� ����������� (��� ������ ���� ������������� �����)." << endl;
                continue;
            }
            // ������ �����
            cout << endl << "5. ����� ����� �����(������������) ��� ���? (��/���): ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).find("��") != string::npos) collectorValuesMain.push_back("true");
            else collectorValuesMain.push_back("false");
            // ����� �������: ��� ���������� ��� ��� ��������
            cout << endl << "6. ���������� ����� (����� �����): ";
            getline(cin,N);
            if (us.toInteger(us.trim(N)) > 0) collectorValuesMain.push_back(us.trim(N));
            else {
                cout << "������. ��������� ���������� ����������� (��� ������ ���� �����, ������ ����)." << endl;
                continue;
            }
            // ������ �� �����
            cout << "\n\n";
            hotel->displayServices();
            cout << "\n\n" << "7. ������ �� �����: (������� ����� ������� �������(�/�) ������, ������� ���� � �����. �������� - \"�������, ����, ����\" ��� �������� ������, ���� ����� �� �����)"
                 << endl << "����: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesAddition.push_back(N);
            }
            else collectorValuesAddition.push_back(" ");
            // ������ �� �����
            cout << "\n\n";
            hotel->displayBonuses();
            cout << "\n\n" << "8. ������ �� �����: (������� ����� ������� �������(�/�) �������, ������� ���� � �����. �������� - \"���������� ������, ���������, �����2024\" ��� �������� ������, ���� ������ �� �����)"
                 << endl << "����: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesAddition.push_back(N);
            }
            else collectorValuesAddition.push_back(" ");

            // ���������� �������
            if (collectorValuesMain.size() == 6 && collectorValuesAddition.size() == 2) {
                // ���������
                hotel->addRoom(us.toInteger(collectorValuesMain[0]), collectorValuesMain[1], us.toInteger(collectorValuesMain[2]), us.toDouble(collectorValuesMain[3]), us.stringToBool(collectorValuesMain[4]), us.toInteger(collectorValuesMain[5]), us.collectValues(collectorValuesAddition[0], ",", true, false), us.collectValues(collectorValuesAddition[1], ",", true, false));
                cout << "���������� ������� ������ �������." << endl;
            }
            else {
                cout << "������. ���-�� ��� ����� ������ �� ���� ��������� ��������. ���������� ��� ���, ������ ����������, ��� ���������� � ������������" << endl;
            }
            // �����
            continue;
        case 6: // �������� �������
            us.clearConsole();
            hotel->displayRooms();
            cout << endl << "��������� �������. ������� ���������� ����� �������: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= hotel->getRooms().size()) {
                menuRoom(hotel->getRooms()[us.extractLong(N)-1], hotel);
            }
            else cout << "������: ����� ������� �� ����������." << endl;
            continue;
        case 7: // ������ �������
            us.clearConsole();
            hotel->displayRooms();
            cout << endl << "��������. ������� ���������� ����� �������: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= hotel->getRooms().size()) {
                hotel->deleteRoomByIndex(us.extractLong(N)-1);
                cout << "�������� ������ �������." << endl;
            }
            else cout << "������: ����� ������� �� ����������." << endl;
            continue;
        case 8: // ������ �������
            hotel->displayBonuses();
            continue;
        case 9: // ��������/�������� �����
            us.clearConsole();
            hotel->displayBonuses();
            // ��������
            cout << endl << "����������/��������� �������. ������� �������� ������: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "������: ���������� ������ ������." << endl;
                continue;
            }
            // ������� ������
            cout << endl << "������� ������ ������ � % (�� 0 �� 100): ";
            getline(cin,N);
            if (us.toDouble(us.trim(N)) >= 0 && us.toDouble(us.trim(N)) <= 100) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "������: ����� ������ ���� �� 0 �� 100." << endl;
                continue;
            }
            // ����
            if (collectorValuesMain.size() == 2) {
                hotel->addOrSetBonus(collectorValuesMain[0], (us.toDouble(collectorValuesMain[1]))/100);
            }
            else {
                cout << "������. ���-�� ��� ����� ������ �� ���� ��������� ��������. ���������� ��� ���, ������ ����������, ��� ���������� � ������������" << endl;
            }
            // �����
            continue;
        case 10: // ������� �����
            us.clearConsole();
            hotel->displayBonuses();
            // ��������
            cout << endl << "�������� �������. ������� �������� ������: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                hotel->deleteBonus(N);
            }
            else cout << "������: ������ � ����� ��������� �� ����������." << endl;
            continue;
        case 11: // ������ �����
            hotel->displayServices();
            continue;
        case 12: // ��������/�������� ������
            us.clearConsole();
            hotel->displayServices();
            // ��������
            cout << endl << "����������/��������� �����. ������� �������� ������: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "������: ���������� ������ ������." << endl;
                continue;
            }
            // ����
            cout << endl << "������� ���� ������ (������������� �����): ";
            getline(cin,N);
            if (us.toDouble(us.trim(N)) >= 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "������: ����� ������ ���� ������������� ��� ����� ����." << endl;
                continue;
            }
            // ����
            if (collectorValuesMain.size() == 2) {
                hotel->addOrSetService(collectorValuesMain[0], us.toDouble(collectorValuesMain[1]));
            }
            else {
                cout << "������. ���-�� ��� ����� ������ �� ���� ��������� ��������. ���������� ��� ���, ������ ����������, ��� ���������� � ������������" << endl;
            }
            // �����
            continue;
        case 13: // ������� ������
            us.clearConsole();
            hotel->displayServices();
            // ��������
            cout << endl << "�������� �����. ������� �������� ������: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                hotel->deleteService(N);
            }
            else cout << "������: ������ � ����� ��������� �� ����������." << endl;
            continue;
        case 14: // ������ ����� ������
            hotel->displayTypesRoom();
            continue;
        case 15: // ��������/�������� ��� �������
            us.clearConsole();
            hotel->displayTypesRoom();
            // ��������
            cout << endl << "����������/��������� ���� �������. ������� �������� ����: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "������: ���������� ������ ������." << endl;
                continue;
            }
            // ����
            cout << endl << "������� ���� �� ����� ���� ������� (������������� �����): ";
            getline(cin,N);
            if (us.toDouble(us.trim(N)) >= 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "������: ����� ������ ���� ������������� ��� ����� ����." << endl;
                continue;
            }
            // ����
            if (collectorValuesMain.size() == 2) {
                hotel->addOrSetTypesRoom(collectorValuesMain[0], us.toDouble(collectorValuesMain[1]));
            }
            else {
                cout << "������. ���-�� ��� ����� ������ �� ���� ��������� ��������. ���������� ��� ���, ������ ����������, ��� ���������� � ������������" << endl;
            }
            // �����
            continue;
        case 16: // ������� ��� �������
            us.clearConsole();
            hotel->displayTypesRoom();
            // ��������
            cout << endl << "�������� ����� ������. ������� ��������: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                hotel->deleteTypesRoom(N);
            }
            else cout << "������: ���� ������� � ����� ��������� �� ����������." << endl;
            continue;
        default:
            cout << "\n������. �������� ��������. (����: " << N << ")" <<  endl;
            continue;
        }
    }
}

// ����: �������� ������
void menuHotels(HotelManager& manager) {
    UsefulFunctions us;
    string N;
    us.clearConsole();
    for(;;)
    {
        cout << endl << endl << "\n �������� ������:" << endl;
        cout << "1 - ����� �� ����;" << endl;
        cout << "2 - ������� �����;" << endl;
        cout << "3 - ������� �����;" << endl;
        cout << "4 - ������� � ���� �����;" << endl;
        cout << "5 - ������ ������;" << endl;
        cout << "������� ����� ��������: ";
        getline(cin, N);
        cout << "(����: " << N << ")" <<  endl;
        switch (us.extractLong(N)) {
        case 1:
            us.clearConsole();
            return;
        case 2:
            manager.addHotel();
            continue;
        case 3:
            manager.displayInfoHotels();
            manager.deleteHotel();
            continue;
        case 4:
            manager.displayInfoHotels();
            cout << endl << "������� � �����. ������� ���������� ����� �����: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= manager.getHotels().size()) {
                menuRooms(manager.getHotels()[us.extractLong(N)-1]);
            }
            else cout << "������: ����� � ��������� ���������� ������� �� ������." << endl;
            continue;
        case 5:
            manager.displayInfoHotels();
            continue;
        default:
            cout << "\n������. �������� ��������. (����: " << N << ")" <<  endl;
            continue;
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SetConsoleCP(1251);             // RUS
    SetConsoleOutputCP(1251);       // RUS
    setlocale(LC_ALL, "Russian");   // RUS
    UsefulFunctions us;
    HotelManager manager;
    string N;

    // ����� ���������
    for (;;) {
        if (manager.getHotels().size() > 0) {
            break;
        }
        else {
            cout << "������� �����? [��/���]: ";
            getline(cin, N);
            if (us.trim(us.toLowerCase(N)).find("��") != string::npos) manager.addHotel();
            else if (us.trim(us.toLowerCase(N)).find("���") != string::npos) return 0;
            cout << "������. (����: " << N << ")" << endl;
        }
    }

    // ���� ���������
    menuHotels(manager);
    // �����
    cout << "����� �� ���������..." << endl;

    return 0;
}
