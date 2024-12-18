#ifndef FILE_H
#define FILE_H
#include "UsefulFunctions.h" // доп.файл с необходимыми функциями. | Статус: используется
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class File {
protected:
    string m_name;              // название файла
    string m_dateCreation;      // дата создания      формат: dd.MM.YYYY
    long m_size;              // размер (в Байтах)
    string m_filepath;          // путь к файлу
    bool m_archived;            // архивирован или нет
    vector<string> m_tags;      // теги
public:
    // конструктор
    File (string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): m_name(name), m_dateCreation(dateCreation), m_size(size), m_filepath(filepath), m_archived(archived), m_tags(tags) {}

    // выводим сообщение о попытке открытия файла
    virtual void open() {
        cout << "Открытие файла: " << m_name << endl;
        cout << "Файл " << m_name << " открыт." << endl;
    }

    // получение имени
    string getName() const {
        return m_name;
    }

    // получение даты создания
    string getDateCreation() const {
        return m_dateCreation;
    }

    // получение размера
    long getSize() const {
        return m_size;
    }

    // получение пути к файлу
    string getFilePath() {
        return m_filepath;
    }

    // получение статуса архивации
    bool getStatusArchived() {
        return m_archived;
    }

    // получение тегов
    vector<string> getTags() {
        return m_tags;
    }

    // содержит ли тег
    bool haveTag(string tag){
        for (auto i=0; i<m_tags.size(); i++) if (m_tags[i] == tag) return true;
        return false;
    }

    // архивация файла
    void toArchive() {
        m_archived = true;
    }

    // разархивация файла
    void fromArchive() {
        m_archived = false;
    }
    friend class Explorer;
};

class TextDocument: public File {
public:
    // конструктор
    TextDocument(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // выводим сообщение о попытке открытия файла
    void open() override {
        cout << "Открытие файла: " << m_name << endl;
        cout << "Файл " << m_name << " открыт для редактирования." << endl;
    }
};

class PDFDocument: public File {
public:
    // конструктор
    PDFDocument(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // выводим сообщение о попытке открытия файла
    void open() override {
        cout << "Открытие файла: " << m_name << endl;
        cout << "Файл " << m_name << " открыт для редактирования." << endl;
    }
};

class ImageFile: public File {
public:
    // конструктор
    ImageFile(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // выводим сообщение о попытке открытия файла
    void open() override {
        cout << "Открытие файла: " << m_name << endl;
        cout << "Файл " << m_name << " открыт для просмотра изображения." << endl;
    }
};

class VideoFile: public File {
public:
    // конструктор
    VideoFile(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // выводим сообщение о попытке открытия файла
    void open() override {
        cout << "Открытие файла: " << m_name << endl;
        cout << "Файл " << m_name << " открыт для просмотра видеоконтента." << endl;
    }
};

class AudioFile: public File {
public:
    // конструктор
    AudioFile(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // выводим сообщение о попытке открытия файла
    void open() override {
        cout << "Открытие файла: " << m_name << endl;
       cout << "Файл " << m_name << " открыт для прослушивания аудиозаписи." << endl;
    }
};

class Explorer {
private:
    string m_name;          // название каталога
    vector<File* > files;     // список файлов

public:
    // конструктор с параметрами
    Explorer(string name): m_name(name) {}

    // деструктор
    ~Explorer() {
        // очищаем указатели на файлы
        for (auto i=0; i<files.size(); i++) {
            delete files[i];
        }
        // очищаем вектор
        files.clear();
    }

    // добавление файла (нового)
    void addFile(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags) {
        File* file = new File(name, dateCreation, size, filepath, archived, tags);
        files.emplace_back(file);
    }

    // добавление файла (уже существующего)
    template <typename T>
    void addFile(T* file) {
        files.emplace_back(file);
    }

    // возврат размера папки
    size_t getSize() {
        return files.size();
    }

    // возврат папки
    vector<File*> getFolder() {
        return files;
    }

    // удаление файла (по индексу)
    void deleteFile(long index) {
        string answer;
        UsefulFunctions us;
        if (index >= 0 && index <= files.size()) {
            for (;;) {
                cout << "Вы действительно хотите удалить файл \"" << files[index]->getName() << "\" ? [ДА/НЕТ]: ";
                cin >> answer;
                us.trimSource(answer);  // псевдо-аналог из джавы функции trim
                us.toLowerCaseSource(answer);   // псевдо-аналог из джавы функции toLowerCase
                if (answer == "да") {
                    cout << "Файл " << files[index]->getName() << " был успешно удалён." << endl;
                    files.erase(files.begin() + index);
                    break;
                }
                else if (answer == "нет") break;
                cout << "Ошибка: ваш ответ: \"" << answer << "\" не подходит под ответ. Возможные варианты: \"да\", \"нет\"" << endl;
            }
        }
        else {
            cout << "Ошибка. Некорректно задано искомое значение." << endl;
        }
    }

    // удаление файла (по названию)
    void deleteFile(string Name) {
        string answer;
        UsefulFunctions us;
        bool finded = false;
        for (auto i=0; i<files.size(); i++) {
            if (files[i]->getName() == Name) {
                finded = true;
                for (;;) {
                    cout << "Вы действительно хотите удалить файл \"" << files[i]->getName() << "\" ? [ДА/НЕТ]: ";
                    cin >> answer;
                    us.trimSource(answer);  // псевдо-аналог из джавы функции trim
                    us.toLowerCaseSource(answer);   // псевдо-аналог из джавы функции toLowerCase
                    if (answer == "да") {
                        cout << "Файл " << files[i]->getName() << " был успешно удалён." << endl;
                        files.erase(files.begin() + i);
                        break;
                    }
                    else if (answer == "нет") break;
                    cout << "Ошибка: ваш ответ: \"" << answer << "\" не подходит под ответ. Возможные варианты: \"да\", \"нет\"" << endl;
                }
                break;
            }
        }
        if (!finded) cout << "Ошибка: файл не найден. " << endl;
    }

    // поиск и сортировка
    void searchSort(int typeFilter, string nameObject, vector<string> tagFilters, string sortObject) {
        vector<File* > resFolder;
        UsefulFunctions us;

        // cout << "DEV-начало: " << "typeFilter = " << typeFilter << "; nameObject = " << nameObject << "; sortObject = " << sortObject << endl;
        // for (auto i=0; i<tagFilters.size(); i++) {
        //     cout << "DEV-tags: " << tagFilters[i] << endl;
        // }

        // поиск - фильтрация //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        for (auto i=0; i<files.size(); i++) {
            if (typeFilter > 0 && tagFilters.size() > 0) { // если есть тип фильтра, искомое имя И теги
                switch(typeFilter) {
                case 1: // по названию
                    if (files[i]->getName() == nameObject) {
                        for (auto j=0; j<tagFilters.size(); j++) {
                            if (files[i]->haveTag(tagFilters[j])) resFolder.emplace_back(files[i]);
                        }
                    }
                    break;
                case 2: // по типу
                    if (
                        ((typeid(files[i]) == typeid(TextDocument)) && us.trim(us.toLowerCase(nameObject)) == "txt")
                        || ((typeid(files[i]) == typeid(PDFDocument)) && us.trim(us.toLowerCase(nameObject)) == "pdf")
                        || ((typeid(files[i]) == typeid(ImageFile)) && us.trim(us.toLowerCase(nameObject)) == "jpg")
                        || ((typeid(files[i]) == typeid(VideoFile)) && us.trim(us.toLowerCase(nameObject)) == "mp4")
                        || ((typeid(files[i]) == typeid(AudioFile)) && us.trim(us.toLowerCase(nameObject)) == "mp3")
                        ) {
                        for (auto j=0; j<tagFilters.size(); j++) {
                            if (files[i]->haveTag(tagFilters[j])) resFolder.emplace_back(files[i]);
                        }
                    }
                    break;
                case 3: // по размеру
                    if (files[i]->getSize() == us.toLong(nameObject)) {
                        for (auto j=0; j<tagFilters.size(); j++) {
                            if (files[i]->haveTag(tagFilters[j])) resFolder.emplace_back(files[i]);
                        }
                    }
                    break;
                case 4: // по дате создания
                    if (files[i]->getDateCreation() == nameObject) {
                        for (auto j=0; j<tagFilters.size(); j++) {
                            if (files[i]->haveTag(tagFilters[j])) resFolder.emplace_back(files[i]);
                        }
                    }
                    break;
                default:
                    cout << "Неправильный тип фильтра. Доступные фильтры: 0 - без фильтра, 1 - по названию, 2 - по типу файла, 3 - по размеру файла, 4 - по дате создания" << endl;
                    break;
                }
            }
            else if (typeFilter > 0) {  // если есть только тип фильтра и искомое имя
                switch(typeFilter) {
                case 1: // по названию
                    if (files[i]->getName() == nameObject) {
                        resFolder.emplace_back(files[i]);
                    }
                    break;
                case 2: // по типу
                    if (
                        ((typeid(files[i]) == typeid(TextDocument)) && us.trim(us.toLowerCase(nameObject)) == "txt")
                        || ((typeid(files[i]) == typeid(PDFDocument)) && us.trim(us.toLowerCase(nameObject)) == "pdf")
                        || ((typeid(files[i]) == typeid(ImageFile)) && us.trim(us.toLowerCase(nameObject)) == "jpg")
                        || ((typeid(files[i]) == typeid(VideoFile)) && us.trim(us.toLowerCase(nameObject)) == "mp4")
                        || ((typeid(files[i]) == typeid(AudioFile)) && us.trim(us.toLowerCase(nameObject)) == "mp3")
                        ) {
                        resFolder.emplace_back(files[i]);
                    }
                    break;
                case 3: // по размеру
                    if (files[i]->getSize() == us.toLong(nameObject)) {
                        resFolder.emplace_back(files[i]);
                    }
                    break;
                case 4: // по дате создания
                    if (files[i]->getDateCreation() == nameObject) {
                        resFolder.emplace_back(files[i]);
                    }
                    break;
                default:
                    cout << "Неправильный тип фильтра. Доступные фильтры: 0 - без фильтра, 1 - по названию, 2 - по типу файла, 3 - по размеру файла, 4 - по дате создания" << endl;
                    break;
                }
            }
            else if (tagFilters.size() > 0) { // если есть только теги
                for (auto j=0; j<tagFilters.size(); j++) {
                    if (files[i]->haveTag(tagFilters[j])) resFolder.emplace_back(files[i]);
                }
            }
            else if (typeFilter == 0) {
                resFolder.emplace_back(files[i]);
            }
        }

        // DEV-проверка:
        // for (auto i=0; i<resFolder.size(); i++) {
        //     cout << "[DEV] resFolder[" << i << "] = " << resFolder[i]->getName() << endl;
        // }

        // сортировка //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        us.trimSource(sortObject); // избавляемся от пробелов
        us.toLowerCaseSource(sortObject); // переводим в нижний регистр

        if (sortObject == "name") {
            sort(resFolder.begin(), resFolder.end(), [](const auto& left, const auto& right) {
                return left->getName() < right->getName();
            });
        }
        else if (sortObject == "date creation" || sortObject == "datecreation" || sortObject == "date") {
            sort(resFolder.begin(), resFolder.end(), [](const auto& left, const auto& right) {
                return left->getDateCreation() < right->getDateCreation();
            });
        }
        else if (sortObject == "size") {
            sort(resFolder.begin(), resFolder.end(), [](const auto& left, const auto& right) {
                return left->getSize() < right->getSize();
            });
        }

        // вывод

        cout << " << Результаты поиска: >>" << endl;
        // сначала без архивов
        for (auto i=0; i<resFolder.size(); i++) {
            if (!resFolder[i]->getStatusArchived()) {
                cout << i+1 << ". " << resFolder[i]->getName() << " | " << resFolder[i]->getDateCreation() << " | " << resFolder[i]->getSize() << " | [";
                for (auto j=0; j<resFolder[i]->getTags().size(); j++) {
                    if (j != 0) cout << ", ";
                    cout << resFolder[i]->getTags()[j];
                }
                cout << "]" << endl;
            }
        }

        // архивы
        for (auto i=0; i<resFolder.size(); i++) {
            if (resFolder[i]->getStatusArchived()) {
                cout << "-- Архивы:";
                for (auto j=i; j<resFolder.size(); j++) {
                    if (resFolder[j]->getStatusArchived()) {
                        cout << j << ". " << resFolder[j]->getName() << " | " << resFolder[j]->getDateCreation() << " | " << resFolder[j]->getSize() << " | [";
                        for (auto a=0; a<resFolder[j]->getTags().size(); a++) {
                            if (a != 0) cout << ", ";
                            cout << resFolder[j]->getTags()[a];
                        }
                        cout << "]" << endl;
                    }
                }
                break;
            }
        }

    }

    // отчёт
    void report() {
        // количество файлов
        cout << "Отчёт по каталогу << " << m_name << " >>:" << endl;
        cout << "[ Количество файлов: " << files.size() << " ]" << endl;

        // средний размер
        double folderSize = 0;
        for (auto i=0; i< files.size(); i++) folderSize += files[i]->getSize();
        cout << "[ Средний размер: " << (folderSize/files.size()) << " Байт ]" << endl;

        // последняя дата изменения
        if (files.size() > 0) {
            vector<int> dateCollector;               // формат дат в векторе : YYYYMMdd. Изначально: "dd.MM.YYYY"
            string number;
            string result = "";
            UsefulFunctions us;
            stringstream ss;
            int value;
            for (auto i=0; i<files.size(); i++) {
                // собираем год
                if (us.isCorrectDateFormat(files[i]->getDateCreation())) {
                    ss.clear();
                    ss.str("");
                    number = "";
                    // собираем год
                    number += files[i]->getDateCreation()[6];
                    number += files[i]->getDateCreation()[7];
                    number += files[i]->getDateCreation()[8];
                    number += files[i]->getDateCreation()[9];
                    // собираем месяц
                    number += files[i]->getDateCreation()[3];
                    number += files[i]->getDateCreation()[4];
                    // собираем день
                    number += files[i]->getDateCreation()[0];
                    number += files[i]->getDateCreation()[1];
                    // помещаем в фильтр
                    ss << number;
                    ss >> value;
                    dateCollector.push_back(value);
                }
            }

            // for (auto i=0; i<dateCollector.size(); i++) {
            //     cout << "DEV date: " << dateCollector[i] << endl;
            // }

            // сравнение дат
            value = -1;
            for (auto i=0; i<dateCollector.size(); i++) {
                if (dateCollector[i] > value) value = dateCollector[i];
            }
            // перевод из числа в формат строки
            ss.clear();
            ss.str("");
            ss << value;
            number = "";
            ss >> number;
            // дата
            result = number.substr(6, 2) + "." + number.substr(4, 2) + "." + number.substr(0, 4);
            cout << "[ Последнее изменение: " << result << " ]" << endl;
        }
        else cout << "[ Последнее изменение: нет файлов. ]" << endl;
    }

    // отображение каталога
    void displayInfo() {
        cout << "Каталог << " << m_name << " >>:" << endl;
        for (auto i=0; i<files.size(); i++) {
            cout << i+1 << ". " << files[i]->getName() << " | " << files[i]->getDateCreation() << " | " << files[i]->getSize() << " B | [";
            for (auto j=0; j<files[i]->getTags().size(); j++) {
                if (j != 0) cout << ", ";
                cout << files[i]->getTags()[j];
            }
            cout << "]" << endl;
        }
    }

};



#endif // FILE_H
