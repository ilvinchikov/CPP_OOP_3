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
        // ������� ����������-���������
        valuesObj.clear();
        tagsObj.clear();
        obj = "";
        int x = 0;
        filesize = 0;
        // ���� �� ��������� ����������
        for (auto a=0; a<arrInfoFiles[i].size(); a++) {
            // �������� ������ ���� �� ��������� �� �������
            if ((arrInfoFiles[i].at(a) != ',' && x < 3) || (arrInfoFiles[i].at(a) != ',' && arrInfoFiles[i].at(a) != '[' && arrInfoFiles[i].at(a) != ']' && x > 2)) obj += arrInfoFiles[i].at(a);
            // �������� ����� � ���������� // ���� ��������
            else if (arrInfoFiles[i].at(a) == ',' && (x == 0 || x == 1)) {
                valuesObj.push_back(us.trim(obj));
                obj = "";
                x++;
            }
            // ������
            else if (arrInfoFiles[i].at(a) == ',' && x == 2) {
                // ������ ��� ������������� � ���������
                filesize = us.extractLong(us.trim(obj));
                // ����������� �����, ���� ��� KB (��), MB (��), GB (��)
                if (us.trim(obj).find("KB") != string::npos || us.trim(obj).find("��") != string::npos) {
                    filesize *= 1024;
                }
                else if (us.trim(obj).find("MB") != string::npos || us.trim(obj).find("��") != string::npos) {
                    filesize *= 1024*1024;
                }
                else if (us.trim(obj).find("GB") != string::npos || us.trim(obj).find("��") != string::npos) {
                    filesize *= 1024*1024*1024;
                }
                obj = "";
                x++;
            }
            // ����
            else if ((arrInfoFiles[i].at(a) == ',' || arrInfoFiles[i].at(a) == ']') && x > 2) {
                tagsObj.push_back(us.trim(obj));
                obj = "";
            }
        }

        if (valuesObj.size() > 1) {
            // ��������� ����������
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
        else { // ����� ��������� ��������
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
    vector<string> arrInfoFiles; // �������� ���������� � ������

    // ���������� ��� ������
    for (;;) {
        bool IsReaded = false;
        cout << "�� ������� ������������� ����� � ���������� ���������? [��/���]: ";
        cin >> N;
        us.trim(N);
        us.toLowerCaseSource(N);
        if (N == "��") {
            for (;;) {
                cout << "������� �������� ����� � ��� �����������. ������: notes.txt" << endl;
                cout << "�������� \"�����\", ���� ������ �����.\n��������: ";
                cin >> N;
                if (us.trim(us.toLowerCase(N)) == "�����") {
                    break;
                }
                else if (N.size() > 0 && us.trim(N) != "") {
                    ifstream file(N); // �������� ���� ��� ������
                    if (file.is_open())
                    {
                        string line;
                        // ������� ���-�� ����� � ���������� ��
                        while (getline(file, line)) arrInfoFiles.push_back(line);
                        IsReaded = true;
                        cout << "���� ������. ������ ��������." << endl;
                    }
                    else {
                        cout << "������: ���� �� ������. ��������� �������." << endl;
                    }
                    file.close();     // ��������� ����
                    if (IsReaded) break;
                }
            }
        }
        else if (N == "���") {
            // �������� ���������� ������ � ��������� ������ �����
            for (;;) {
                cout << "������� ���������� ������ (N): ";
                cin >> N;
                if (us.toLong(N) > 0) break;
                else if (N.size() == 0 || us.trim(us.toLowerCase(N)) == "�����") return 0;
                cout << "������. ������� ������������� ������������� �����, ������ ����. ������: 3 \n���� ������ ����� �� ���������, �������� \"�����\"." << endl;
            }
            string line;
            // ���������� �������� ������ � ������� �����
            cout << "\n������� ���������� � ������ (������: ��� �����, ���� ��������, ������, [����]).\n��������: Report.pdf, 10.05.2023, 200 KB, [work, project]" << endl;
            for (auto i=0; i<us.toLong(N); i++) {
                cout << i+1 << ". ";
                cin.ignore();
                getline(cin, line);
                arrInfoFiles.push_back(line);
            }
            break;
        }
        else cout << "������: ��� ����� ������������ (" << N << ")" << endl;
        if (IsReaded) break;
    }

    cout << "������� �������� ����� (N): ";
    cin >> N;

    // ������� ����� � �������
    Explorer folder(N);
    // ��������� �����
    CreateDirectory(folder, arrInfoFiles, N);
    // ��������� � �������
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
        cout << endl << endl << "\n ��������� �������� ��� ��� �������:" << endl;
        cout << "1 - ������� ����;" << endl;
        cout << "2 - ����� � ����������;" << endl;
        cout << "3 - ������������/��������������� ����;" << endl;
        cout << "4 - ������� ������ ������ � �����;" << endl;
        cout << "5 - ������� ����� �� �����;" << endl;
        cout << "6 - ������� ����;" << endl;
        cout << "������� ����� ��������: ";
        cin >> N;
        cin.ignore();
        switch (us.extractLong(N))
        {
        case 1:
            cout << endl << "��������: �������� ���������� ����� �����: ";
            cin >> N;
            if (us.toLong(N) > 0 && us.toLong(N) <= folder.getSize()) {
                folder.getFolder()[us.toLong(N)-1]->open();
            }
            else {
                cout << "������: ������ �������� �����." << endl;
            }
            break;
        case 2:
            cout << endl << "����� � ����������: " << endl << endl;
            cout << "��������� �������: 0 - ��� �������, 1 - �� ��������, 2 - �� ���� �����, 3 - �� ������� �����, 4 - �� ���� ��������" << endl << "1. ������� ��� ������� (�����): ";
            cin >> N;
            collectorStrings.push_back(N);

            cout << "2. ������� ������� ��� ������� (�����): ";
            cin >> N;
            collectorStrings.push_back(N);

            cout << "3. ������� ���� (�����) �������� ����� �������. ������� \"0\", ����� ���������� ���. ����: ";
            cin >> N;
            if (N != "0") {
                for (auto a=0; a<N.size(); a++) {
                    // �������� ������ ���� �� ��������� �� �������
                    if (N.at(a) != ',') obj += N.at(a);
                    // ���������
                    else if (N.at(a) == ',' || (a+1 == N.size())) {
                        collectortags.push_back(obj);
                        obj = "";
                    }
                }
            }
            cout << "��������� ���� ����������: name - �� �����, date - �� ����, size - �� �������, *����� ������ �����* - ��� ����������." << endl << "4. ������� ��� ���������� (�����): ";
            cin >> N;
            collectorStrings.push_back(N);
            // ���� � ���������
            folder.searchSort(us.toInteger(collectorStrings[0]), collectorStrings[1], collectortags, collectorStrings[2]);
            break;
        case 3:
            cout << endl << "���������/������������: �������� ���������� ����� �����: ";
            cin >> N;
            if (us.toLong(N) > 0 && us.toLong(N) <= folder.getSize()) {
                if (!folder.getFolder()[us.toLong(N)-1]->getStatusArchived()) {
                    folder.getFolder()[us.toLong(N)-1]->toArchive();
                    cout << "���� ������� � �����." << endl;
                }
                else {
                    folder.getFolder()[us.toLong(N)-1]->fromArchive();
                    cout << "���� ������� �� ������." << endl;
                }
            }
            else {
                cout << "������: ������ �������� �����." << endl;
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
            cout << endl << "��������: ������� �������� ��� ���������� ����� �����: ";
            cin >> N;
            if (us.toLong(N) > 0) {
                folder.deleteFile(us.toLong(N)-1);
            }
            else {
                folder.deleteFile(N);
            }
            break;
        default:
            cout << "\n������. �������� ��������." << endl;
            continue;
        }
    }

    return 0;
}

