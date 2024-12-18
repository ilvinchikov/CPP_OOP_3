#ifndef USEFULFUNCTIONS_H
#define USEFULFUNCTIONS_H

#include <sstream>
#include <string>
#include <iostream>
using namespace std;

class UsefulFunctions {
public:
    // �������� ������������ ����
    bool isCorrectDateFormat(string str) {
        // ���� � ��� ������ ���������� �������� �� �������: dd.MM.YYYY � �� ����� ����� ����� ������ �����
        if (str.size() == 10 && (isdigit(str[0]) && isdigit(str[1]) && isdigit(str[3]) && isdigit(str[4]) && isdigit(str[6]) && isdigit(str[7]) && isdigit(str[8]) && isdigit(str[9]))) {
            return true;
        }
        else return false;
    }

    // ������� ����� ������, ����������� � ������ �������
    string toLowerCase(string str) {
        for (auto i=0; i<str.size(); i++) {
            str[i] = tolower(str[i]);
        }
        return str;
    }

    // ������������ ������ ��������� � ������ �������
    void toLowerCaseSource(string& str) {
        for (auto i=0; i<str.size(); i++) {
            str[i] = tolower(str[i]);
        }
    }

    // ������� ��������� ������ �� �������� � ������ � �����
    string trim(string str) {
        size_t x = 0;
        // ���� �������� ������ ������, ������� �� �������� �������� ��� \t
        for (auto i=0; str[i] != '\0'; i++) {
            if (!isblank(str[i])) {
                x += i;
                break;
            }
        }
        // ���� � ����� �� ������ ������ ������, �� ���������� ��������
        for (auto i=str.size()-1; i >= 0; i--) {
            if (!isblank(str[i])) {
                return str.substr(x, (i-x)+1);
            }
        }
        return "";
    }

    // ������� ����������� ������ �� �������� � ������ � �����
    void trimSource(string& str) {
        size_t x = 0;
        // ���� �������� ������ ������, ������� �� �������� �������� ��� \t
        for (auto i=0; str[i] != '\0'; i++) {
            if (!isblank(str[i])) {
                x += i;
                break;
            }
        }
        // ���� � ����� �� ������ ������ ������, �� ���������� ��������
        for (auto i=str.size()-1; i >= 0; i--) {
            if (!isblank(str[i])) {
                str = str.substr(x, (i-x)+1);
                return;
            }
        }
        str = "";
    }

    // ������� ����� int �� ������
    int toInteger(string str) {
        int value = 0;
        bool oneMinusHave = false;
        stringstream ss;
        // �������� �� ����������� �����
        for (auto i=0; i<str.size(); i++) {
            if ((!isdigit(str[i]) && str[i] != '-') || ((str[i] == '-') && oneMinusHave)) return value;
            if (str[i] == '-') oneMinusHave = true;
        }
        // ������� �� ������ � �����
        ss << str;
        ss >> value;
        return value;
    }

    // ������� ����� long �� ������
    long toLong(string str) {
        long value = 0;
        bool oneMinusHave = false;
        stringstream ss;
        // �������� �� ����������� �����
        for (auto i=0; i<str.size(); i++) {
            if ((!isdigit(str[i]) && str[i] != '-') || ((str[i] == '-') && oneMinusHave)) return value;
            if (str[i] == '-') oneMinusHave = true;
        }
        // ������� �� ������ � �����
        ss << str;
        ss >> value;
        return value;
    }

    // �������� ����� �� ������, ���������� �� ������ �����
    long extractLong(string str) {
        string line = "";
        long value = 0;
        bool oneMinusHave = false;
        stringstream ss;
        // ������ �����
        for (auto i=0; i<str.size(); i++) {
            if ((isdigit(str[i]) && str[i] == '-')  && !oneMinusHave || (isdigit(str[i]))) line += str[i];
            if (str[i] == '-') oneMinusHave = true;
        }
        // ������� �� ������ � �����
        ss << line;
        ss >> value;
        return value;
    }

    // ������� ������
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
