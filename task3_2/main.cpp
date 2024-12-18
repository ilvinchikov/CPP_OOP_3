#include <QCoreApplication>
#include <Windows.h>
#include "Booking.h"
#include "UsefulFunctions.h"

// МЕНЮ комнаты
void menuRoom(Booking*& room, Hotel*& hotel) { // получаем адрес выбранной комнаты (каждый номер - указатель) и адрес отеля (отель - указатель)
    UsefulFunctions us;
    string N;
    us.clearConsole();
    for(;;)
    {
        cout << endl << endl << "\n МЕНЕДЖЕР НОМЕРА " << room->getNumber() << ":" << endl;
        cout << "1 - Выйти из меню;" << endl;
        cout << "2 - Информация о комнате;" << endl;
        cout << "3 - Поменять номер комнаты;" << endl;
        cout << "4 - Сменить тип;" << endl;
        cout << "5 - Сменить количество ночей;" << endl;
        cout << "6 - Сменить цену;" << endl;
        cout << "7 - Сменить статус (занято/свободно);" << endl;
        cout << "8 - Сменить число людей;" << endl;
        cout << "9 - Добавить услугу;" << endl;
        cout << "10 - Удалить услугу;" << endl;
        cout << "11 - Добавить скидку(бонус);" << endl;
        cout << "12 - Удалить скидку(бонус);" << endl;
        cout << "Введите номер операции: ";
        getline(cin,N);
        switch (us.extractLong(N)) {
        case 1: // выход
            us.clearConsole();
            return;
        case 2: // инфо о комнате
            room->getDisplayInfo(hotel->getCountBusyRooms(), hotel->getListServices(), hotel->getListBonuses());
            continue;
        case 3: // сменить номер
            cout << endl << "Смена номера. Введите новый номер (целое число): ";
            getline(cin,N);
            if (us.extractLong(N) > 0) {
                room->setNumber(us.extractLong(N));
            }
            else cout << "Ошибка: число должно быть целым." << endl;
            continue;
        case 4: // сменить тип
            cout << endl << "Смена типа номера. Введите новый тип (строка): ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                if (hotel->getListTypesRoom().count(us.trim(N)) > 0) {
                    room->setType(us.trim(N));
                }
                else cout << "Ошибка. Такого типа комнаты не существует в списке типов комнат отеля. Вернитесь и добавьте его." << endl;
            }
            else {
                cout << "Ошибка: обнаружена пустая строка." << endl;
                continue;
            }
            continue;
        case 5: // сменить колво ночей
            cout << endl << "Смена количества ночей. Введите количество (целое положительное число): ";
            getline(cin,N);
            if (us.extractLong(N) > 0) {
                room->setPeriod(us.extractLong(N));
            }
            else cout << "Ошибка: число должно быть целым и положительным." << endl;
            continue;
        case 6: // сменить цену
            cout << endl << "Смена цены. Введите новую цену (число): ";
            getline(cin,N);
            if (us.toDouble(N) > 0) {
                room->setPrice(us.toDouble(N));
            }
            else cout << "Ошибка: значение должно быть положительным числом." << endl;
            continue;
        case 7: // сменить статус
            cout << endl << "Смена статуса. Введите число (0 - свободно / 1 - занято): ";
            getline(cin,N);
            if (us.extractLong(N) == 1) {
                room->setStatus(true);
            }
            else if (us.extractLong(N) == 0) {
                room->setStatus(false);
            }
            else cout << "Ошибка: число должно быть равно 0 или 1." << endl;
            continue;
        case 8: // сменить число
            cout << endl << "Смена количества людей. Введите количество (целое положительное число): ";
            getline(cin,N);
            if (us.extractLong(N) > 0) {
                room->setCount(us.extractLong(N));
            }
            else cout << "Ошибка: число должно быть целым и положительным." << endl;
            continue;
        case 9: // добавить услугу
            cout << endl;
            hotel->displayServices();
            cout << endl << "Добавление услуги. Введите название: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                if (hotel->getListServices().count(us.trim(N)) > 0) {
                    room->addService(us.trim(N));
                }
                else cout << "Ошибка. Такой услуги не существует в списке услуг отеля. Вернитесь и добавьте его." << endl;
            }
            else {
                cout << "Ошибка: обнаружена пустая строка." << endl;
                continue;
            }
            continue;
        case 10: // удалить услугу
            cout << endl;
            hotel->displayServices();
            cout << endl << "Удаление услуги. Введите название: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                room->deleteService(N);
            }
            else {
                cout << "Ошибка: обнаружена пустая строка." << endl;
                continue;
            }
            continue;
        case 11: // добавить скидку
            cout << endl;
            hotel->displayBonuses();
            cout << endl << "Добавление скидки. Введите название: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                if (hotel->getListBonuses().count(us.trim(N)) > 0) {
                    room->addBonus(us.trim(N));
                }
                else cout << "Ошибка. Такой скидки не существует в списке скидок отеля. Вернитесь и добавьте её." << endl;
            }
            else {
                cout << "Ошибка: обнаружена пустая строка." << endl;
                continue;
            }
            continue;
        case 12: // удалить скидку
            cout << endl;
            hotel->displayBonuses();
            cout << endl << "Удаление скидки. Введите название: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                room->deleteBonus(N);
            }
            else {
                cout << "Ошибка: обнаружена пустая строка." << endl;
                continue;
            }
            continue;
        default:
            cout << "\nОшибка. Неверная операция. (Ввод: " << N << ")" <<  endl;
            continue;
        }
    }
}

// МЕНЮ: отеля "Х"
void menuRooms(Hotel*& hotel) { // получаем адрес выбранного отеля (каждый отель - указатель)
    UsefulFunctions us;
    string N;                           // переменная для ввода
    vector<string> collectorValuesMain;         // сборщик значений (основных): номер, тип, кол-во ночей и т.д.
    vector<string> collectorValuesAddition;     // сборщик значений (обычно, перечисленных через запятую):  услуг, бонусов и т.д
    us.clearConsole();
    for(;;)
    {
        collectorValuesMain.clear();
        collectorValuesAddition.clear();
        cout << endl << endl << "\n МЕНЕДЖЕР ОТЕЛЯ \"" << hotel->getName() << "\": " << endl;
        cout << "1 - Выйти из меню;" << endl;
        cout << "2 - Отчёт по отелю;" << endl;
        cout << "3 - Отчёт по комнате;" << endl;
        cout << "4 - Рассчитать стоимость комнаты;" << endl;
        cout << "5 - Добавить комнату;" << endl;
        cout << "6 - Изменить комнату;" << endl;
        cout << "7 - Удалить комнату;" << endl;
        cout << "8 - Просмотреть список бонусов;" << endl;
        cout << "9 - Добавить/изменить бонус в список;" << endl;
        cout << "10 - Удалить бонус из списка;" << endl;
        cout << "11 - Просмотреть список доступных услуг;" << endl;
        cout << "12 - Добавить/изменить услугу в список отеля;" << endl;
        cout << "13 - Удалить услугу из списка отеля;" << endl;
        cout << "14 - Просмотреть список типов комнат;" << endl;
        cout << "15 - Добавить/изменить тип комнаты в список отеля;" << endl;
        cout << "16 - Удалить тип комнаты из списка отеля;" << endl;
        cout << "Введите номер операции: ";
        getline(cin,N);
        switch (us.extractLong(N)) {
        case 1: // выход
            us.clearConsole();
            return;
        case 2: // отчёт по отелю
            us.clearConsole();
            hotel->displayReport();
            continue;
        case 3: // отчёт по номеру
            us.clearConsole();
            hotel->displayRooms();
            cout << endl << "Отчёт по комнате. Введите порядковый номер комнаты: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= hotel->getRooms().size()) {
                hotel->getRooms()[us.extractLong(N)-1]->getDisplayInfo(hotel->getOccupancy(), hotel->getListServices(), hotel->getListBonuses());
            }
            else cout << "Ошибка: такой комнаты не существует." << endl;
            continue;
        case 4: // рассчет итоговой стоимости номера
            us.clearConsole();
            hotel->displayRooms();
            cout << endl << "Рассчёт стоимости комнаты. Введите порядковый номер комнаты: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= hotel->getRooms().size()) {
                cout << "Конечная цена с учетом бонусных скидок и доп.услуг: " << hotel->getRooms()[us.extractLong(N)-1]->calculatePrice(hotel->getOccupancy(), hotel->getListServices(), hotel->getListBonuses()) << endl;
            }
            else cout << "Ошибка: такой комнаты не существует." << endl;
            continue;
        case 5: // добавление комнаты
            us.clearConsole();
            // номер комнаты
            cout << "Добавление новой комнаты:" << endl << "1. Номер комнаты (целое число): ";
            getline(cin,N);
            if (us.extractLong(us.trim(N)) > 0) collectorValuesMain.push_back(us.trim(N));
            else {
                cout << "Ошибка. Указанный номер комнаты некорректен (это должно быть целое число, больше нуля)." << endl;
                continue;
            }
            // тип
            cout << endl << "2. Тип комнаты (строка): ";
            getline(cin,N);
            collectorValuesMain.push_back(us.trim(N));
            // период
            cout << endl << "3. Количество ночей (целое число): ";
            getline(cin,N);
            if (us.extractLong(us.trim(N)) > 0) collectorValuesMain.push_back(us.trim(N));
            else {
                cout << "Ошибка. Указанное число ночей некорректно (это должно быть целое число, больше нуля)." << endl;
                continue;
            }
            // цена
            cout << endl << "4. Цена (положительное число): ";
            getline(cin,N);
            if (us.toDouble(us.trim(N)) > 0) collectorValuesMain.push_back(us.trim(N));
            else {
                cout << "Ошибка. Указанная цена некорректна (это должно быть положительное число)." << endl;
                continue;
            }
            // статус брони
            cout << endl << "5. Номер будет занят(забронирован) или нет? (ДА/НЕТ): ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).find("да") != string::npos) collectorValuesMain.push_back("true");
            else collectorValuesMain.push_back("false");
            // число номеров: для группового или для одиночки
            cout << endl << "6. Количество людей (целое число): ";
            getline(cin,N);
            if (us.toInteger(us.trim(N)) > 0) collectorValuesMain.push_back(us.trim(N));
            else {
                cout << "Ошибка. Указанное количество некорректно (это должно быть число, больше нуля)." << endl;
                continue;
            }
            // услуги от отеля
            cout << "\n\n";
            hotel->displayServices();
            cout << "\n\n" << "7. Услуги от отеля: (введите через запятую названи(е/я) услуги, которые ЕСТЬ у отеля. Например - \"завтрак, обед, ужин\" ИЛИ оставьте пустым, если услуг не будет)"
                 << endl << "Ввод: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesAddition.push_back(N);
            }
            else collectorValuesAddition.push_back(" ");
            // бонусы от отеля
            cout << "\n\n";
            hotel->displayBonuses();
            cout << "\n\n" << "8. Скидки от отеля: (введите через запятую названи(е/я) бонусов, которые ЕСТЬ у отеля. Например - \"постоянный клиент, уголовник, Семья2024\" ИЛИ оставьте пустым, если скидок не будет)"
                 << endl << "Ввод: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesAddition.push_back(N);
            }
            else collectorValuesAddition.push_back(" ");

            // добавление комнаты
            if (collectorValuesMain.size() == 6 && collectorValuesAddition.size() == 2) {
                // добавляем
                hotel->addRoom(us.toInteger(collectorValuesMain[0]), collectorValuesMain[1], us.toInteger(collectorValuesMain[2]), us.toDouble(collectorValuesMain[3]), us.stringToBool(collectorValuesMain[4]), us.toInteger(collectorValuesMain[5]), us.collectValues(collectorValuesAddition[0], ",", true, false), us.collectValues(collectorValuesAddition[1], ",", true, false));
                cout << "Добавление комнаты прошло успешно." << endl;
            }
            else {
                cout << "Ошибка. Где-то при вводе данных не было сохранено значение. Попробуйте ещё раз, следуя регламенту, или обратитесь к разработчику" << endl;
            }
            // конец
            continue;
        case 6: // изменить комнату
            us.clearConsole();
            hotel->displayRooms();
            cout << endl << "Изменение комнаты. Введите порядковый номер комнаты: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= hotel->getRooms().size()) {
                menuRoom(hotel->getRooms()[us.extractLong(N)-1], hotel);
            }
            else cout << "Ошибка: такой комнаты не существует." << endl;
            continue;
        case 7: // удалит комнату
            us.clearConsole();
            hotel->displayRooms();
            cout << endl << "Удаление. Введите порядковый номер комнаты: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= hotel->getRooms().size()) {
                hotel->deleteRoomByIndex(us.extractLong(N)-1);
                cout << "Удаление прошло успешно." << endl;
            }
            else cout << "Ошибка: такой комнаты не существует." << endl;
            continue;
        case 8: // список бонусов
            hotel->displayBonuses();
            continue;
        case 9: // добавить/изменить бонус
            us.clearConsole();
            hotel->displayBonuses();
            // название
            cout << endl << "Добавление/Изменение бонусов. Введите название бонуса: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "Ошибка: обнаружено пустая строка." << endl;
                continue;
            }
            // процент скидки
            cout << endl << "Введите скидку бонуса в % (от 0 до 100): ";
            getline(cin,N);
            if (us.toDouble(us.trim(N)) >= 0 && us.toDouble(us.trim(N)) <= 100) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "Ошибка: число должно быть от 0 до 100." << endl;
                continue;
            }
            // итог
            if (collectorValuesMain.size() == 2) {
                hotel->addOrSetBonus(collectorValuesMain[0], (us.toDouble(collectorValuesMain[1]))/100);
            }
            else {
                cout << "Ошибка. Где-то при вводе данных не было сохранено значение. Попробуйте ещё раз, следуя регламенту, или обратитесь к разработчику" << endl;
            }
            // конец
            continue;
        case 10: // удалить бонус
            us.clearConsole();
            hotel->displayBonuses();
            // название
            cout << endl << "Удаление бонусов. Введите название бонуса: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                hotel->deleteBonus(N);
            }
            else cout << "Ошибка: бонуса с таким названием не существует." << endl;
            continue;
        case 11: // список услуг
            hotel->displayServices();
            continue;
        case 12: // добавить/изменить услугу
            us.clearConsole();
            hotel->displayServices();
            // название
            cout << endl << "Добавление/Изменение услуг. Введите название услуги: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "Ошибка: обнаружена пустая строка." << endl;
                continue;
            }
            // цена
            cout << endl << "Введите цену услуги (положительное число): ";
            getline(cin,N);
            if (us.toDouble(us.trim(N)) >= 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "Ошибка: число должно быть положительным или равно нулю." << endl;
                continue;
            }
            // итог
            if (collectorValuesMain.size() == 2) {
                hotel->addOrSetService(collectorValuesMain[0], us.toDouble(collectorValuesMain[1]));
            }
            else {
                cout << "Ошибка. Где-то при вводе данных не было сохранено значение. Попробуйте ещё раз, следуя регламенту, или обратитесь к разработчику" << endl;
            }
            // конец
            continue;
        case 13: // удалить услугу
            us.clearConsole();
            hotel->displayServices();
            // название
            cout << endl << "Удаление услуг. Введите название услуги: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                hotel->deleteService(N);
            }
            else cout << "Ошибка: услуги с таким названием не существует." << endl;
            continue;
        case 14: // список типов комнат
            hotel->displayTypesRoom();
            continue;
        case 15: // добавить/изменить тип комнаты
            us.clearConsole();
            hotel->displayTypesRoom();
            // название
            cout << endl << "Добавление/Изменение типа комнаты. Введите название типа: ";
            getline(cin,N);
            if (us.trim(us.toLowerCase(N)).size() > 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "Ошибка: обнаружена пустая строка." << endl;
                continue;
            }
            // цена
            cout << endl << "Введите цену по этому типу комнаты (положительное число): ";
            getline(cin,N);
            if (us.toDouble(us.trim(N)) >= 0) {
                collectorValuesMain.push_back(us.trim(N));
            }
            else {
                cout << "Ошибка: число должно быть положительным или равно нулю." << endl;
                continue;
            }
            // итог
            if (collectorValuesMain.size() == 2) {
                hotel->addOrSetTypesRoom(collectorValuesMain[0], us.toDouble(collectorValuesMain[1]));
            }
            else {
                cout << "Ошибка. Где-то при вводе данных не было сохранено значение. Попробуйте ещё раз, следуя регламенту, или обратитесь к разработчику" << endl;
            }
            // конец
            continue;
        case 16: // удалить тип комнаты
            us.clearConsole();
            hotel->displayTypesRoom();
            // название
            cout << endl << "Удаление типов комнат. Введите название: ";
            getline(cin,N);
            if (us.trim(N).size() > 0) {
                hotel->deleteTypesRoom(N);
            }
            else cout << "Ошибка: типа комнаты с таким названием не существует." << endl;
            continue;
        default:
            cout << "\nОшибка. Неверная операция. (Ввод: " << N << ")" <<  endl;
            continue;
        }
    }
}

// МЕНЮ: менеджер отелей
void menuHotels(HotelManager& manager) {
    UsefulFunctions us;
    string N;
    us.clearConsole();
    for(;;)
    {
        cout << endl << endl << "\n МЕНЕДЖЕР ОТЕЛЕЙ:" << endl;
        cout << "1 - Выйти из меню;" << endl;
        cout << "2 - Создать отель;" << endl;
        cout << "3 - Удалить отель;" << endl;
        cout << "4 - Перейти в меню отеля;" << endl;
        cout << "5 - Список отелей;" << endl;
        cout << "Введите номер операции: ";
        getline(cin, N);
        cout << "(Ввод: " << N << ")" <<  endl;
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
            cout << endl << "Переход к отелю. Введите порядковый номер отеля: ";
            getline(cin,N);
            if (us.extractLong(N) > 0 && us.extractLong(N) <= manager.getHotels().size()) {
                menuRooms(manager.getHotels()[us.extractLong(N)-1]);
            }
            else cout << "Ошибка: отель с указанным порядковым номером не найден." << endl;
            continue;
        case 5:
            manager.displayInfoHotels();
            continue;
        default:
            cout << "\nОшибка. Неверная операция. (Ввод: " << N << ")" <<  endl;
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

    // старт программы
    for (;;) {
        if (manager.getHotels().size() > 0) {
            break;
        }
        else {
            cout << "Создать отель? [ДА/НЕТ]: ";
            getline(cin, N);
            if (us.trim(us.toLowerCase(N)).find("да") != string::npos) manager.addHotel();
            else if (us.trim(us.toLowerCase(N)).find("нет") != string::npos) return 0;
            cout << "Ошибка. (Ввод: " << N << ")" << endl;
        }
    }

    // меню программы
    menuHotels(manager);
    // выход
    cout << "Выход из программы..." << endl;

    return 0;
}
