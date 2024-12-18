#ifndef USEFULFUNCTIONS_H
#define USEFULFUNCTIONS_H

#include <sstream>
#include <string>
#include <iostream>
using namespace std;

class UsefulFunctions {
public:
    // проверка правильности даты
    bool isCorrectDateFormat(string str) {
        // если у нас равное количество символов по формату: dd.MM.YYYY И на месте числа стоит только цифра
        if (str.size() == 10 && (isdigit(str[0]) && isdigit(str[1]) && isdigit(str[3]) && isdigit(str[4]) && isdigit(str[6]) && isdigit(str[7]) && isdigit(str[8]) && isdigit(str[9]))) {
            return true;
        }
        else return false;
    }

    // возврат копии строки, переведённый в низкий регистр
    string toLowerCase(string str) {
        for (auto i=0; i<str.size(); i++) {
            str[i] = tolower(str[i]);
        }
        return str;
    }

    // передаваемую строку переводим в низкий регистр
    void toLowerCaseSource(string& str) {
        for (auto i=0; i<str.size(); i++) {
            str[i] = tolower(str[i]);
        }
    }

    // возврат очищенной строки от пробелов в начале и конце
    string trim(string str) {
        size_t x = 0;
        // ищем входящий первый символ, который не является пробелом или \t
        for (auto i=0; str[i] != '\0'; i++) {
            if (!isblank(str[i])) {
                x += i;
                break;
            }
        }
        // ищем с конца по начало первый символ, не являющийся пробелом
        for (auto i=str.size()-1; i >= 0; i--) {
            if (!isblank(str[i])) {
                return str.substr(x, (i-x)+1);
            }
        }
        return "";
    }

    // очищаем пердаваемую строку от пробелов в начале и конце
    void trimSource(string& str) {
        size_t x = 0;
        // ищем входящий первый символ, который не является пробелом или \t
        for (auto i=0; str[i] != '\0'; i++) {
            if (!isblank(str[i])) {
                x += i;
                break;
            }
        }
        // ищем с конца по начало первый символ, не являющийся пробелом
        for (auto i=str.size()-1; i >= 0; i--) {
            if (!isblank(str[i])) {
                str = str.substr(x, (i-x)+1);
                return;
            }
        }
        str = "";
    }

    // возврат числа int из строки
    int toInteger(string str) {
        int value = 0;
        bool oneMinusHave = false;
        stringstream ss;
        // проверка на посторонние знаки
        for (auto i=0; i<str.size(); i++) {
            if ((!isdigit(str[i]) && str[i] != '-') || ((str[i] == '-') && oneMinusHave)) return value;
            if (str[i] == '-') oneMinusHave = true;
        }
        // перевод из строки в число
        ss << str;
        ss >> value;
        return value;
    }

    // возврат числа long из строки
    long toLong(string str) {
        long value = 0;
        bool oneMinusHave = false;
        stringstream ss;
        // проверка на посторонние знаки
        for (auto i=0; i<str.size(); i++) {
            if ((!isdigit(str[i]) && str[i] != '-') || ((str[i] == '-') && oneMinusHave)) return value;
            if (str[i] == '-') oneMinusHave = true;
        }
        // перевод из строки в число
        ss << str;
        ss >> value;
        return value;
    }

    // экстракт числа из строки, содержащей не только цифры
    long extractLong(string str) {
        string line = "";
        long value = 0;
        bool oneMinusHave = false;
        stringstream ss;
        // сборка числа
        for (auto i=0; i<str.size(); i++) {
            if ((isdigit(str[i]) && str[i] == '-')  && !oneMinusHave || (isdigit(str[i]))) line += str[i];
            if (str[i] == '-') oneMinusHave = true;
        }
        // перевод из строки в число
        ss << line;
        ss >> value;
        return value;
    }

    // возврат строки
    template <typename T>
    string toString(T obj) {
        string str;
        stringstream ss;
        ss << obj;
        ss >> str;
        return str;
    }

};
#endif // USEFULFUNCTIONS_H
