#include <QCoreApplication>
#include <QFile>
#include <Windows.h>
#include <fstream>
#include "UsefulFunctions.h"
#include "File.h"

void CreateDirectory (Explorer& folder, vector<string>& arrInfoFiles, string& nameFolder) {
    UsefulFunctions us;
    vector <string> valuesObj;
    vector <string> tagsObj;
    string path = "C:\\Users\\user\\" + nameFolder;
    string obj;
    long filesize = 0;

    for (auto i=0; i<arrInfoFiles.size(); i++) {
        // очистка переменных-сборщиков
        valuesObj.clear();
        tagsObj.clear();
        obj = "";
        int x = 0;
        filesize = 0;
        // цикл по собранной информации
        for (auto a=0; a<arrInfoFiles[i].size(); a++) {
            // собираем данные пока не наткнемся на запятую
            if ((arrInfoFiles[i].at(a) != ',' && x < 3) || (arrInfoFiles[i].at(a) != ',' && arrInfoFiles[i].at(a) != '[' && arrInfoFiles[i].at(a) != ']' && x > 2)) obj += arrInfoFiles[i].at(a);
            // название файла и расширение // дата создания
            else if (arrInfoFiles[i].at(a) == ',' && (x == 0 || x == 1)) {
                valuesObj.push_back(us.trim(obj));
                obj = "";
                x++;
            }
            // размер
            else if (arrInfoFiles[i].at(a) == ',' && x == 2) {
                // меняем под целочисленное и сохраняем
                filesize = us.extractLong(us.trim(obj));
                // увеличиваем число, если это KB (КБ), MB (МБ), GB (ГБ)
                if (us.trim(obj).find("KB") != string::npos || us.trim(obj).find("КБ") != string::npos) {
                    filesize *= 1024;
                }
                else if (us.trim(obj).find("MB") != string::npos || us.trim(obj).find("МБ") != string::npos) {
                    filesize *= 1024*1024;
                }
                else if (us.trim(obj).find("GB") != string::npos || us.trim(obj).find("ГБ") != string::npos) {
                    filesize *= 1024*1024*1024;
                }
                obj = "";
                x++;
            }
            // теги
            else if ((arrInfoFiles[i].at(a) == ',' || arrInfoFiles[i].at(a) == ']') && x > 2) {
                tagsObj.push_back(us.trim(obj));
                obj = "";
            }
        }

        if (valuesObj.size() > 1) {
            // добавляем расширение
            if (us.trim(valuesObj[0]).find(".txt") != string::npos) {
                folder.addFile(new TextDocument(valuesObj[0], valuesObj[1], filesize, path, false, tagsObj));
            }
            else if (us.trim(valuesObj[0]).find(".pdf") != string::npos) {
                folder.addFile(new PDFDocument(valuesObj[0], valuesObj[1], filesize, path, false, tagsObj));
            }
            else if (us.trim(valuesObj[0]).find(".jpg") != string::npos) {
                folder.addFile(new ImageFile(valuesObj[0], valuesObj[1], filesize, path, false, tagsObj));
            }
            else if (us.trim(valuesObj[0]).find(".mp4") != string::npos) {
                folder.addFile(new VideoFile (valuesObj[0], valuesObj[1], filesize, path, false, tagsObj));
            }
            else if (us.trim(valuesObj[0]).find(".mp3") != string::npos) {
                folder.addFile(new AudioFile (valuesObj[0], valuesObj[1], filesize, path, false, tagsObj));
            }
            else {
                folder.addFile(new File(valuesObj[0], valuesObj[1], filesize, path, false, tagsObj));
            }
        } 
        else { // иначе добавляем пустышку
            folder.addFile(new File ("corrupted_file", "17.12.2024", filesize, path, false, vector<string>{""}));
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
    string N;
    vector<string> arrInfoFiles; // входящая информация о файлах

    // спрашиваем про импорт
    for (;;) {
        bool IsReaded = false;
        cout << "Вы желаете импортировать файлы с текстового документа? [ДА/НЕТ]: ";
        cin >> N;
        us.trim(N);
        us.toLowerCaseSource(N);
        if (N == "да") {
            for (;;) {
                cout << "Введите название файла с его расширением. Пример: notes.txt" << endl;
                cout << "Напишите \"выйти\", если хотите выйти.\nНазвание: ";
                cin >> N;
                if (us.trim(us.toLowerCase(N)) == "выйти") {
                    break;
                }
                else if (N.size() > 0 && us.trim(N) != "") {
                    ifstream file(N); // окрываем файл для чтения
                    if (file.is_open())
                    {
                        string line;
                        // считаем кол-во строк и записываем их
                        while (getline(file, line)) arrInfoFiles.push_back(line);
                        IsReaded = true;
                        cout << "Файл найден. Данные записаны." << endl;
                    }
                    else {
                        cout << "Ошибка: Файл не найден. Повторите попытку." << endl;
                    }
                    file.close();     // закрываем файл
                    if (IsReaded) break;
                }
            }
        }
        else if (N == "нет") {
            // получаем количество файлов и формируем массив строк
            for (;;) {
                cout << "Введите количество файлов (N): ";
                cin >> N;
                if (us.toLong(N) > 0) break;
                else if (N.size() == 0 || us.trim(us.toLowerCase(N)) == "выйти") return 0;
                cout << "Ошибка. Введите целочисленное положительное число, больше нуля. Пример: 3 \nЕсли хотите выйти из программы, напишите \"выйти\"." << endl;
            }
            string line;
            // записываем описание файлов в массивы строк
            cout << "\nВведите информацию о файлах (формат: имя файла, дата создания, размер, [теги]).\nНапример: Report.pdf, 10.05.2023, 200 KB, [work, project]" << endl;
            for (auto i=0; i<us.toLong(N); i++) {
                cout << i+1 << ". ";
                cin.ignore();
                getline(cin, line);
                arrInfoFiles.push_back(line);
            }
            break;
        }
        else cout << "Ошибка: ваш ответ некорректный (" << N << ")" << endl;
        if (IsReaded) break;
    }

    cout << "Введите название папки (N): ";
    cin >> N;

    // создаем папку с файлами
    Explorer folder(N);
    // заполняем папку
    CreateDirectory(folder, arrInfoFiles, N);
    // переходим к системе
    folder.displayInfo();
    vector <string> collectorStrings;
    vector <string> collectortags;
    string obj;
    for(;;)
    {
        collectorStrings.clear();
        collectortags.clear();
        obj = "";
        N = "";
        cout << endl << endl << "\n Возможные операции над над файлами:" << endl;
        cout << "1 - Открыть файл;" << endl;
        cout << "2 - Поиск и сортировка;" << endl;
        cout << "3 - Архивировать/разархивировать файл;" << endl;
        cout << "4 - Вывести список файлов в папке;" << endl;
        cout << "5 - Вывести отчёт по папке;" << endl;
        cout << "6 - Удалить файл;" << endl;
        cout << "Введите номер операции: ";
        cin >> N;
        cin.ignore();
        switch (us.extractLong(N))
        {
        case 1:
            cout << endl << "Открытие: выберите порядковый номер файла: ";
            cin >> N;
            if (us.toLong(N) > 0 && us.toLong(N) <= folder.getSize()) {
                folder.getFolder()[us.toLong(N)-1]->open();
            }
            else {
                cout << "Ошибка: указан неверный номер." << endl;
            }
            break;
        case 2:
            cout << endl << "Поиск и сортировка: " << endl << endl;
            cout << "Доступные фильтры: 0 - без фильтра, 1 - по названию, 2 - по типу файла, 3 - по размеру файла, 4 - по дате создания" << endl << "1. Введите тип фильтра (число): ";
            cin >> N;
            collectorStrings.push_back(N);

            cout << "2. Введите искомое имя объекта (текст): ";
            cin >> N;
            collectorStrings.push_back(N);

            cout << "3. Искомые теги (текст) вводятся через запятую. Введите \"0\", чтобы пропустить шаг. Ввод: ";
            cin >> N;
            if (N != "0") {
                for (auto a=0; a<N.size(); a++) {
                    // собираем данные пока не наткнемся на запятую
                    if (N.at(a) != ',') obj += N.at(a);
                    // добавляем
                    else if (N.at(a) == ',' || (a+1 == N.size())) {
                        collectortags.push_back(obj);
                        obj = "";
                    }
                }
            }
            cout << "Доступные виды сортировки: name - по имени, date - по дате, size - по размеру, *любое другое слово* - без сортировки." << endl << "4. Введите вид сортировки (текст): ";
            cin >> N;
            collectorStrings.push_back(N);
            // ищем и сортируем
            folder.searchSort(us.toInteger(collectorStrings[0]), collectorStrings[1], collectortags, collectorStrings[2]);
            break;
        case 3:
            cout << endl << "Архивация/разархивация: выберите порядковый номер файла: ";
            cin >> N;
            if (us.toLong(N) > 0 && us.toLong(N) <= folder.getSize()) {
                if (!folder.getFolder()[us.toLong(N)-1]->getStatusArchived()) {
                    folder.getFolder()[us.toLong(N)-1]->toArchive();
                    cout << "Файл помещён в архив." << endl;
                }
                else {
                    folder.getFolder()[us.toLong(N)-1]->fromArchive();
                    cout << "Файл вытащен из архива." << endl;
                }
            }
            else {
                cout << "Ошибка: указан неверный номер." << endl;
            }
            break;
        case 4:
            folder.displayInfo();
            cout << endl;
            break;
        case 5:
            folder.report();
            cout << endl;
            break;
        case 6:
            cout << endl << "Удаление: введите название или порядковый номер файла: ";
            cin >> N;
            if (us.toLong(N) > 0) {
                folder.deleteFile(us.toLong(N)-1);
            }
            else {
                folder.deleteFile(N);
            }
            break;
        default:
            cout << "\nОшибка. Неверная операция." << endl;
            continue;
        }
    }

    return 0;
}

