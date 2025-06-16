// UserManager.cpp
#include "UserManager.h"    // UserManager Ŭ����
#include <iostream>         // �ܼ� ���
#include <fstream>          // ���� �����
#include <iomanip>          // ��� ������

using namespace std;        // std:: ���ӽ����̽� ���

// UserManager ������
UserManager::UserManager() {
    cout << "UserManager �ʱ�ȭ. ����� ������ �ε� ��..." << endl;
    loadUsers(); // ����� ������ �ε�
}

// UserManager �Ҹ���
UserManager::~UserManager() {
    cout << "UserManager ����. ����� ������ ���� ��..." << endl;
    saveUsers(); // ����� ������ ����
}

// CSV ���Ϸκ��� ����� ������ �ε�
void UserManager::loadUsers() {
    vector<string> userLines = CSVHandler::readCsv(USERS_FILE);
    if (userLines.empty()) {
        cout << "����� ������ ���� ����/�������. �� ���� ���� ����." << endl;
        return;
    }

    for (const string& line : userLines) {
        User user = User::fromCsvString(line);
        if (user.getUserId() != "") { // ��ȿ�� ����� ���� �߰�
            users.emplace(user.getUserId(), user);
        }
    }
    cout << "�� " << users.size() << "�� ����� ������ �ε� �Ϸ�." << endl;
}

// CSV ���Ͽ� ����� ������ ����
void UserManager::saveUsers() {
    vector<string> dataToSave;
    for (const auto& pair : users) {
        dataToSave.push_back(pair.second.toCsvString());
    }
    CSVHandler::writeCsv(USERS_FILE, dataToSave);
    cout << "�� " << users.size() << "�� ����� ������ ���� �Ϸ�." << endl;
}

// ����� �߰�
bool UserManager::addUser(const string& userId, const string& password, UserType type, const string& name, const string& phone) {
    // ID �ߺ� Ȯ��
    if (users.find(userId) == users.end()) {
        // User �����ڿ��� ��ȭ��ȣ ��ȿ�� �˻� �� ���ڸ� ���� ó��
        User newUser(userId, password, type, name, phone);
        if (newUser.getPhone().empty() && !phone.empty()) { // ��ȿ���� ���� ��ȭ��ȣ�� �ԷµǾ��� ���
            cout << "����: �Էµ� ��ȭ��ȣ�� ��ȿ���� �ʾ� ����� �߰� ����." << endl;
            return false;
        }
        users.emplace(userId, newUser);
        saveUsers(); // ���Ͽ� ����
        return true;
    }
    else {
        cout << "����: ����� ID '" << userId << "' �̹� ����." << endl;
        return false;
    }
}

// �α���
UserType UserManager::login(const string& userId, const string& password) {
    auto it = users.find(userId); // ����� ID �˻�
    if (it != users.end()) { // ����� ID ����
        if (it->second.checkPassword(password)) { // ��й�ȣ ��ġ
            cout << it->second.getName() << "�� ȯ���մϴ�! (" <<
                (it->second.getUserType() == UserType::Owner ? "����" :
                    it->second.getUserType() == UserType::Employee ? "����" : "��")
                << " ����)" << endl;
            return it->second.getUserType(); // ����� ���� ��ȯ
        }
        else {
            cout << "�α��� ����: ��й�ȣ ����ġ." << endl;
            return UserType::None; // ��й�ȣ ����ġ
        }
    }
    else {
        cout << "�α��� ����: ����� ID '" << userId << "' ����." << endl;
        return UserType::None; // ����� ID ����
    }
}

// User ��ü ��ȸ (���)
const User* UserManager::getUser(const string& userId) const {
    auto it = users.find(userId); // ����� ID �˻�
    if (it != users.end()) { // ����� ID ����
        return &(it->second); // User ��ü �ּ� ��ȯ
    }
    return nullptr; // ����� ID ����
}

// User ��ü ��ȸ (���� ����)
User* UserManager::getMutableUser(const std::string& userId) {
    auto it = users.find(userId);
    if (it != users.end()) {
        return &(it->second);
    }
    return nullptr;
}

// ����� ����
bool UserManager::deleteUser(const std::string& userId) {
    if (userId == "owner") { // "owner" ���� ���� ����
        cout << "����: 'owner' ���� ���� �Ұ�." << endl;
        return false;
    }
    if (users.erase(userId)) { // ����� ���� �õ�
        saveUsers(); // ���Ͽ� ����
        cout << "����� ID '" << userId << "' ���� �Ϸ�." << endl;
        return true; // ���� ����
    }
    else {
        cout << "����: ����� ID '" << userId << "' ã�� �� ����. ���� ����." << endl;
        return false; // ���� ����
    }
}

// ��� ����� ���� ��ȯ
const map<string, User>& UserManager::getAllUsers() const {
    return users;
}

// ��� ����� ���� ���
void UserManager::printAllUsers() const {
    if (users.empty()) {
        cout << "��ϵ� ����� ����." << endl;
        return;
    }

    cout << "\n--- ��ü ����� ��� ---" << endl;
    cout << left << setw(15) << "ID"
        << setw(10) << "����"
        << setw(15) << "�̸�"
        << setw(18) << "��ȭ��ȣ" << endl; // ��ȭ��ȣ �� Ȯ��
    cout << "---------------------------------------------------------" << endl;

    for (const auto& pair : users) {
        const User& user = pair.second;
        string userTypeStr;
        switch (user.getUserType()) {
        case UserType::Customer: userTypeStr = "��"; break;
        case UserType::Employee: userTypeStr = "����"; break;
        case UserType::Owner:    userTypeStr = "����"; break;
        default:                 userTypeStr = "�� �� ����"; break;
        }
        cout << left << setw(15) << user.getUserId()
            << setw(10) << userTypeStr
            << setw(15) << user.getName()
            << setw(18) << user.getFormattedPhone() << endl; // getFormattedPhone ���
    }
    cout << "---------------------------------------------------------" << endl;
}