#include "UserManager.h"
#include <iostream> // �ܼ� ������� ���� �����ϱ�

using namespace std;

// UserManager ������ ����
// ��ü ���� �� loadInitialUsers �Լ��� ȣ���Ͽ� �ʱ� ����� ������ �ε��ϱ�
UserManager::UserManager() {
    loadInitialUsers();
}

// �� ����� �߰� �Լ� ����
// userId�� �̹� �����ϴ��� Ȯ�� ��, ������ users �ʿ� �� User ��ü �߰��ϱ�
bool UserManager::addUser(const string& userId, const string& password, UserType type) {
    if (users.find(userId) == users.end()) { // users �ʿ��� userId�� ã�� ���� ��� (�ߺ� ����)
        users.emplace(userId, User(userId, password, type)); // �� User ��ü�� �����Ͽ� �ʿ� �����ϱ�
        cout << "����� " << userId << " ������ �����Ǿ����ϴ�. (����: " << static_cast<int>(type) << ")" << endl;
        return true; // ����� �߰� ����
    }
    else {
        cout << "����: ����� ID '" << userId << "'�� �̹� �����մϴ�." << endl;
        return false; // ����� �߰� ���� (ID �ߺ�)
    }
}

// ����� �α��� �Լ� ����
// �Է¹��� userId�� password�� Ȯ���Ͽ� �α��� ���� �����ϱ�
UserType UserManager::login(const string& userId, const string& password) {
    auto it = users.find(userId); // users �ʿ��� �ش� userId �˻��ϱ�
    if (it != users.end()) { // ����� ID�� ã���� ���
        if (it->second.checkPassword(password)) { // User ��ü�� checkPassword �Լ��� ��й�ȣ Ȯ���ϱ�
            cout << userId << " �� ȯ���մϴ�! (" << (int)it->second.getUserType() << " ����)" << endl;
            return it->second.getUserType(); // �α��� ����, �ش� ������� UserType ��ȯ�ϱ�
        }
        else {
            cout << "�α��� ����: ��й�ȣ�� �ùٸ��� �ʽ��ϴ�." << endl;
            return UserType::None; // ��й�ȣ ����ġ
        }
    }
    else {
        cout << "�α��� ����: ����� ID '" << userId << "'�� ã�� �� �����ϴ�." << endl;
        return UserType::None; // ����� ID�� �ʿ� ���� ���
    }
}

// Ư�� ����� �������� �Լ� ���� (const ����)
// userId�� �ش��ϴ� User ��ü�� ������ ��ȯ�ϱ�
const User* UserManager::getUser(const string& userId) const {
    auto it = users.find(userId); // users �ʿ��� userId �˻��ϱ�
    if (it != users.end()) {
        return &(it->second); // ã�� User ��ü�� �ּ� ��ȯ�ϱ�
    }
    return nullptr; // ����� ID�� ã�� ���� ��� nullptr ��ȯ�ϱ�
}

// �ʱ� ����� �����͸� �ε��ϴ� �Լ� ����
// ���α׷� ���� �� �׽�Ʈ �� �ʱ� ������ ���� ���� ������ �߰��ϱ�
void UserManager::loadInitialUsers() {
    // ���� ���� �߰��ϱ�
    addUser("owner", "ownerpass", UserType::Owner);
    // ���� ���� �߰��ϱ�
    addUser("employee1", "emppass1", UserType::Employee);
    addUser("employee2", "emppass2", UserType::Employee);
    // �� ���� �߰��ϱ�
    addUser("customer1", "custpass1", UserType::Customer);
    addUser("customer2", "custpass2", UserType::Customer);
    cout << "�ʱ� ����� ������ �ε�Ǿ����ϴ�." << endl;
}