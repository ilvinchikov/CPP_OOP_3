#ifndef FILE_H
#define FILE_H
#include "UsefulFunctions.h" // ���.���� � ������������ ���������. | ������: ������������
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class File {
protected:
    string m_name;              // �������� �����
    string m_dateCreation;      // ���� ��������      ������: dd.MM.YYYY
    long m_size;              // ������ (� ������)
    string m_filepath;          // ���� � �����
    bool m_archived;            // ����������� ��� ���
    vector<string> m_tags;      // ����
public:
    // �����������
    File (string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): m_name(name), m_dateCreation(dateCreation), m_size(size), m_filepath(filepath), m_archived(archived), m_tags(tags) {}

    // ������� ��������� � ������� �������� �����
    virtual void open() {
        cout << "�������� �����: " << m_name << endl;
        cout << "���� " << m_name << " ������." << endl;
    }

    // ��������� �����
    string getName() const {
        return m_name;
    }

    // ��������� ���� ��������
    string getDateCreation() const {
        return m_dateCreation;
    }

    // ��������� �������
    long getSize() const {
        return m_size;
    }

    // ��������� ���� � �����
    string getFilePath() {
        return m_filepath;
    }

    // ��������� ������� ���������
    bool getStatusArchived() {
        return m_archived;
    }

    // ��������� �����
    vector<string> getTags() {
        return m_tags;
    }

    // �������� �� ���
    bool haveTag(string tag){
        for (auto i=0; i<m_tags.size(); i++) if (m_tags[i] == tag) return true;
        return false;
    }

    // ��������� �����
    void toArchive() {
        m_archived = true;
    }

    // ������������ �����
    void fromArchive() {
        m_archived = false;
    }
    friend class Explorer;
};

class TextDocument: public File {
public:
    // �����������
    TextDocument(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // ������� ��������� � ������� �������� �����
    void open() override {
        cout << "�������� �����: " << m_name << endl;
        cout << "���� " << m_name << " ������ ��� ��������������." << endl;
    }
};

class PDFDocument: public File {
public:
    // �����������
    PDFDocument(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // ������� ��������� � ������� �������� �����
    void open() override {
        cout << "�������� �����: " << m_name << endl;
        cout << "���� " << m_name << " ������ ��� ��������������." << endl;
    }
};

class ImageFile: public File {
public:
    // �����������
    ImageFile(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // ������� ��������� � ������� �������� �����
    void open() override {
        cout << "�������� �����: " << m_name << endl;
        cout << "���� " << m_name << " ������ ��� ��������� �����������." << endl;
    }
};

class VideoFile: public File {
public:
    // �����������
    VideoFile(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // ������� ��������� � ������� �������� �����
    void open() override {
        cout << "�������� �����: " << m_name << endl;
        cout << "���� " << m_name << " ������ ��� ��������� �������������." << endl;
    }
};

class AudioFile: public File {
public:
    // �����������
    AudioFile(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags): File(name, dateCreation, size, filepath, archived, tags) {}
    // ������� ��������� � ������� �������� �����
    void open() override {
        cout << "�������� �����: " << m_name << endl;
       cout << "���� " << m_name << " ������ ��� ������������� �����������." << endl;
    }
};

class Explorer {
private:
    string m_name;          // �������� ��������
    vector<File* > files;     // ������ ������

public:
    // ����������� � �����������
    Explorer(string name): m_name(name) {}

    // ����������
    ~Explorer() {
        // ������� ��������� �� �����
        for (auto i=0; i<files.size(); i++) {
            delete files[i];
        }
        // ������� ������
        files.clear();
    }

    // ���������� ����� (������)
    void addFile(string name, string dateCreation, long size, string filepath, bool archived, vector<string> tags) {
        File* file = new File(name, dateCreation, size, filepath, archived, tags);
        files.emplace_back(file);
    }

    // ���������� ����� (��� �������������)
    template <typename T>
    void addFile(T* file) {
        files.emplace_back(file);
    }

    // ������� ������� �����
    size_t getSize() {
        return files.size();
    }

    // ������� �����
    vector<File*> getFolder() {
        return files;
    }

    // �������� ����� (�� �������)
    void deleteFile(long index) {
        string answer;
        UsefulFunctions us;
        if (index >= 0 && index <= files.size()) {
            for (;;) {
                cout << "�� ������������� ������ ������� ���� \"" << files[index]->getName() << "\" ? [��/���]: ";
                cin >> answer;
                us.trimSource(answer);  // ������-������ �� ����� ������� trim
                us.toLowerCaseSource(answer);   // ������-������ �� ����� ������� toLowerCase
                if (answer == "��") {
                    cout << "���� " << files[index]->getName() << " ��� ������� �����." << endl;
                    files.erase(files.begin() + index);
                    break;
                }
                else if (answer == "���") break;
                cout << "������: ��� �����: \"" << answer << "\" �� �������� ��� �����. ��������� ��������: \"��\", \"���\"" << endl;
            }
        }
        else {
            cout << "������. ����������� ������ ������� ��������." << endl;
        }
    }

    // �������� ����� (�� ��������)
    void deleteFile(string Name) {
        string answer;
        UsefulFunctions us;
        bool finded = false;
        for (auto i=0; i<files.size(); i++) {
            if (files[i]->getName() == Name) {
                finded = true;
                for (;;) {
                    cout << "�� ������������� ������ ������� ���� \"" << files[i]->getName() << "\" ? [��/���]: ";
                    cin >> answer;
                    us.trimSource(answer);  // ������-������ �� ����� ������� trim
                    us.toLowerCaseSource(answer);   // ������-������ �� ����� ������� toLowerCase
                    if (answer == "��") {
                        cout << "���� " << files[i]->getName() << " ��� ������� �����." << endl;
                        files.erase(files.begin() + i);
                        break;
                    }
                    else if (answer == "���") break;
                    cout << "������: ��� �����: \"" << answer << "\" �� �������� ��� �����. ��������� ��������: \"��\", \"���\"" << endl;
                }
                break;
            }
        }
        if (!finded) cout << "������: ���� �� ������. " << endl;
    }

    // ����� � ����������
    void searchSort(int typeFilter, string nameObject, vector<string> tagFilters, string sortObject) {
        vector<File* > resFolder;
        UsefulFunctions us;

        // cout << "DEV-������: " << "typeFilter = " << typeFilter << "; nameObject = " << nameObject << "; sortObject = " << sortObject << endl;
        // for (auto i=0; i<tagFilters.size(); i++) {
        //     cout << "DEV-tags: " << tagFilters[i] << endl;
        // }

        // ����� - ���������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        for (auto i=0; i<files.size(); i++) {
            if (typeFilter > 0 && tagFilters.size() > 0) { // ���� ���� ��� �������, ������� ��� � ����
                switch(typeFilter) {
                case 1: // �� ��������
                    if (files[i]->getName() == nameObject) {
                        for (auto j=0; j<tagFilters.size(); j++) {
                            if (files[i]->haveTag(tagFilters[j])) resFolder.emplace_back(files[i]);
                        }
                    }
                    break;
                case 2: // �� ����
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
                case 3: // �� �������
                    if (files[i]->getSize() == us.toLong(nameObject)) {
                        for (auto j=0; j<tagFilters.size(); j++) {
                            if (files[i]->haveTag(tagFilters[j])) resFolder.emplace_back(files[i]);
                        }
                    }
                    break;
                case 4: // �� ���� ��������
                    if (files[i]->getDateCreation() == nameObject) {
                        for (auto j=0; j<tagFilters.size(); j++) {
                            if (files[i]->haveTag(tagFilters[j])) resFolder.emplace_back(files[i]);
                        }
                    }
                    break;
                default:
                    cout << "������������ ��� �������. ��������� �������: 0 - ��� �������, 1 - �� ��������, 2 - �� ���� �����, 3 - �� ������� �����, 4 - �� ���� ��������" << endl;
                    break;
                }
            }
            else if (typeFilter > 0) {  // ���� ���� ������ ��� ������� � ������� ���
                switch(typeFilter) {
                case 1: // �� ��������
                    if (files[i]->getName() == nameObject) {
                        resFolder.emplace_back(files[i]);
                    }
                    break;
                case 2: // �� ����
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
                case 3: // �� �������
                    if (files[i]->getSize() == us.toLong(nameObject)) {
                        resFolder.emplace_back(files[i]);
                    }
                    break;
                case 4: // �� ���� ��������
                    if (files[i]->getDateCreation() == nameObject) {
                        resFolder.emplace_back(files[i]);
                    }
                    break;
                default:
                    cout << "������������ ��� �������. ��������� �������: 0 - ��� �������, 1 - �� ��������, 2 - �� ���� �����, 3 - �� ������� �����, 4 - �� ���� ��������" << endl;
                    break;
                }
            }
            else if (tagFilters.size() > 0) { // ���� ���� ������ ����
                for (auto j=0; j<tagFilters.size(); j++) {
                    if (files[i]->haveTag(tagFilters[j])) resFolder.emplace_back(files[i]);
                }
            }
            else if (typeFilter == 0) {
                resFolder.emplace_back(files[i]);
            }
        }

        // DEV-��������:
        // for (auto i=0; i<resFolder.size(); i++) {
        //     cout << "[DEV] resFolder[" << i << "] = " << resFolder[i]->getName() << endl;
        // }

        // ���������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        us.trimSource(sortObject); // ����������� �� ��������
        us.toLowerCaseSource(sortObject); // ��������� � ������ �������

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

        // �����

        cout << " << ���������� ������: >>" << endl;
        // ������� ��� �������
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

        // ������
        for (auto i=0; i<resFolder.size(); i++) {
            if (resFolder[i]->getStatusArchived()) {
                cout << "-- ������:";
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

    // �����
    void report() {
        // ���������� ������
        cout << "����� �� �������� << " << m_name << " >>:" << endl;
        cout << "[ ���������� ������: " << files.size() << " ]" << endl;

        // ������� ������
        double folderSize = 0;
        for (auto i=0; i< files.size(); i++) folderSize += files[i]->getSize();
        cout << "[ ������� ������: " << (folderSize/files.size()) << " ���� ]" << endl;

        // ��������� ���� ���������
        if (files.size() > 0) {
            vector<int> dateCollector;               // ������ ��� � ������� : YYYYMMdd. ����������: "dd.MM.YYYY"
            string number;
            string result = "";
            UsefulFunctions us;
            stringstream ss;
            int value;
            for (auto i=0; i<files.size(); i++) {
                // �������� ���
                if (us.isCorrectDateFormat(files[i]->getDateCreation())) {
                    ss.clear();
                    ss.str("");
                    number = "";
                    // �������� ���
                    number += files[i]->getDateCreation()[6];
                    number += files[i]->getDateCreation()[7];
                    number += files[i]->getDateCreation()[8];
                    number += files[i]->getDateCreation()[9];
                    // �������� �����
                    number += files[i]->getDateCreation()[3];
                    number += files[i]->getDateCreation()[4];
                    // �������� ����
                    number += files[i]->getDateCreation()[0];
                    number += files[i]->getDateCreation()[1];
                    // �������� � ������
                    ss << number;
                    ss >> value;
                    dateCollector.push_back(value);
                }
            }

            // for (auto i=0; i<dateCollector.size(); i++) {
            //     cout << "DEV date: " << dateCollector[i] << endl;
            // }

            // ��������� ���
            value = -1;
            for (auto i=0; i<dateCollector.size(); i++) {
                if (dateCollector[i] > value) value = dateCollector[i];
            }
            // ������� �� ����� � ������ ������
            ss.clear();
            ss.str("");
            ss << value;
            number = "";
            ss >> number;
            // ����
            result = number.substr(6, 2) + "." + number.substr(4, 2) + "." + number.substr(0, 4);
            cout << "[ ��������� ���������: " << result << " ]" << endl;
        }
        else cout << "[ ��������� ���������: ��� ������. ]" << endl;
    }

    // ����������� ��������
    void displayInfo() {
        cout << "������� << " << m_name << " >>:" << endl;
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
