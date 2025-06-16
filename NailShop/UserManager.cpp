#include "UserManager.h"
#include <iostream>

using namespace std;

UserManager::UserManager() {
    loadInitialUsers();
}

// �� �Լ��� �̹� ���� �亯���� name �Ķ���͸� �޵��� ������
bool UserManager::addUser(const string& userId, const string& password, UserType type, const string& name) {
    if (users.find(userId) == users.end()) {
        users.emplace(userId, User(userId, password, type, name)); // User ��ü ���� �� name ����!
        cout << "����� " << userId << " ����(" << name << ")�� �����Ǿ����ϴ�. (����: " << static_cast<int>(type) << ")" << endl;
        return true;
    }
    else {
        cout << "����: ����� ID '" << userId << "'�� �̹� �����մϴ�." << endl;
        return false;
    }
}

UserType UserManager::login(const string& userId, const string& password) {
    auto it = users.find(userId);
    if (it != users.end()) {
        if (it->second.checkPassword(password)) {
            cout << it->second.getName() << " �� ȯ���մϴ�! (" << (int)it->second.getUserType() << " ����)" << endl;
            return it->second.getUserType();
        }
        else {
            cout << "�α��� ����: ��й�ȣ�� �ùٸ��� �ʽ��ϴ�." << endl;
            return UserType::None;
        }
    }
    else {
        cout << "�α��� ����: ����� ID '" << userId << "'�� ã�� �� �����ϴ�." << endl;
        return UserType::None;
    }
}

const User* UserManager::getUser(const string& userId) const {
    auto it = users.find(userId);
    if (it != users.end()) {
        return &(it->second);
    }
    return nullptr;
}

// �� �Լ��� ������ �ٽ�! addUser ȣ�� �� name ���� �߰�
void UserManager::loadInitialUsers() {
    // name �Ķ���� �߰��Ͽ� addUser ȣ���ϱ�
    // ����: addUser("���̵�", "��й�ȣ", UserType::����, "�̸�");
    addUser("owner", "ownerpass", UserType::Owner, "�����");       // ���� ����
    addUser("employee1", "emppass1", UserType::Employee, "������"); // ���� ����
    addUser("employee2", "emppass2", UserType::Employee, "������"); // ���� ����
    addUser("customer1", "custpass1", UserType::Customer, "�ְ�"); // �� ����
    addUser("customer2", "custpass2", UserType::Customer, "����"); // �� ����
    cout << "�ʱ� ����� ������ �ε�Ǿ����ϴ�." << endl;
}