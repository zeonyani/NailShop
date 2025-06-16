// UserManager.cpp
#include "UserManager.h"
#include "Admin.h"      // Admin Ŭ���� ����
#include "Customer.h"   // Customer Ŭ���� ����
#include "Staff.h"      // Staff Ŭ���� ����
#include <iostream>     // �ܼ� ����� ���
#include <algorithm>    // �˰��� ���� ���
#include <limits>       // std::numeric_limits ���
#include <iomanip>      // ����� ������ ���
#include <regex>        // ���� ǥ���� ���

const std::string UserManager::USERS_FILE = "users.csv"; // ����� ������ ���� ��� ��� ����

// UserManager ������
UserManager::UserManager() : nextUserId(1) {
    // UserManager ��ü ���� �� ����� �����͸� �ε��ϴ� ����.
    // loadUsers �Լ� ���ο��� ���� ������ ���� ���θ� Ȯ���ϰ� �ʿ� �� �ڵ� ����.
    loadUsers();
}

// UserManager �Ҹ���
UserManager::~UserManager() {
    // ���α׷� ���� �� ��� ����� �����͸� ���Ͽ� �����ϴ� ����.
    saveUsers(true); // �Ҹ� �ÿ��� ����ڿ��� �޽��� ���� ���� (silent ���).
}

// ����� ������ �ε�
void UserManager::loadUsers() {
    std::vector<std::string> lines = CSVHandler::readCsv(USERS_FILE); // CSV ���Ͽ��� ��� ����� ������ �� �б�
    users.clear(); // ���� �޸��� ����� ������ �� �ʱ�ȭ.

    int maxNumericId = 0; // "USR" ���λ縦 ���� ����� ID �� ���� ū ���� �κ��� �����ϴ� ����.
    bool ownerExists = false; // ���� ����(UserType::Owner)�� ���� ���θ� ��Ÿ���� �÷���.

    for (const std::string& line : lines) {
        User user = User::fromCsvString(line); // �� ���� �Ľ��Ͽ� User ��ü�� ��ȯ.
        if (!user.getUserId().empty()) {
            users[user.getUserId()] = user; // �Ľ̵� ��ȿ�� ����� ������ �ʿ� �߰�.

            // ���� ����ڰ� ����(Owner) �������� Ȯ��.
            if (user.getUserType() == UserType::Owner) {
                ownerExists = true; // ���� ���� �߰� �� �÷��� ����.
            }

            // ���� ����� ID ������ ���� �ִ� ���� ID ����.
            // "USR"�� �����ϴ� ID�� ����Ͽ� nextUserId ��꿡 �ݿ�.
            if (user.getUserId().rfind("USR", 0) == 0 && user.getUserId().length() > 3) {
                try {
                    // "USR" ������ ���� �κ��� ������ ��ȯ.
                    int idNum = std::stoi(user.getUserId().substr(3));
                    if (idNum > maxNumericId) { // ������� ã�� ���� ū ���� ID�� ������Ʈ.
                        maxNumericId = idNum;
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "���: ����� ID ���� �Ľ� ���� (invalid_argument): " << e.what() << " - " << user.getUserId() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "���: ����� ID ���� �Ľ� ���� (out_of_range): " << e.what() << " - " << user.getUserId() << std::endl;
                }
            }
        }
    }
    // ��� ����� �ε� ��, �������� �Ҵ�� "USR" ��� ID�� ����.
    // �̴� �ε�� ��� "USR" ID �� ���� ū ���� ID�� 1�� ���� ��.
    // �̷��� �����ν� USR000, USR001 ���� ���Ͽ� �־ �ߺ����� �ʴ� ���� ID�� ����.
    nextUserId = maxNumericId + 1;

    // ���� ����(UserType::Owner)�� �������� ���� ��� �ʱ� ���� ���� ����.
    // �� addOwnerAccount() �Լ��� "admin"�̶�� ���� ID�� ���.
    // ���� CSV ���Ͽ� Owner Ÿ���� ����ڰ� �ϳ��� ������ "admin" ���� ���� �õ�.
    if (!ownerExists) {
        addOwnerAccount();
    }
}

// ����� ������ ����
void UserManager::saveUsers(bool silent) {
    std::vector<std::string> lines; // ������ ����� �����͸� ���� ����.
    for (const auto& pair : users) {
        lines.push_back(pair.second.toCsvString()); // �� ����� ��ü�� CSV ���ڿ��� ��ȯ�Ͽ� ���Ϳ� �߰�.
    }
    if (CSVHandler::writeCsv(USERS_FILE, lines)) { // CSV ���Ͽ� ������ ���� �õ�.
        if (!silent) {
            std::cout << "����� �����Ͱ� ���������� ����Ǿ����ϴ�." << std::endl; // ���� ���� �޽��� ���.
        }
    }
    else {
        if (!silent) {
            std::cerr << "����: ����� ������ ���忡 �����߽��ϴ�." << std::endl; // ���� ���� �޽��� ���.
        }
    }
}

// owner ���� ���� (���� ���� �� 'admin' ID�� ����)
void UserManager::addOwnerAccount() {
    // ���� ����("admin")�� �̹� �ʿ� �����ϴ��� Ȯ��.
    // loadUsers()���� ownerExists�� ���� ��κ� �ɷ�����, Ȥ�� �� ��츦 ���.
    if (users.count("admin")) {
        std::cout << "���� ���� (ID: admin)�� �̹� �����մϴ�." << std::endl; // �̹� ������ �˸�.
        return;
    }

    std::cout << "\n--- �ʱ� ���� ���� ���� ---\n" << std::endl; // �ʱ� ���� �ȳ�.
    std::cout << "�ý����� ó�� �����ϼ̽��ϴ�. ���� ������ �����մϴ�." << std::endl; // �ý��� ù ���� �ȳ�.
    std::string ownerId = "admin"; // ���� ���� ID�� "admin"���� ����.
    std::string ownerPw; // ����ڷκ��� �Է¹��� ��й�ȣ.
    std::string ownerName = "������"; // ���� ������ �⺻ �̸�.
    std::string ownerPhone; // ����ڷκ��� �Է¹��� ��ȭ��ȣ.

    // ��й�ȣ ���� ��Ģ �ȳ� �� ��ȿ�� �˻� ����.
    std::cout << "�⺻ ���� ID: " << ownerId << std::endl; // ���� ID �ȳ�.
    std::cout << "��й�ȣ�� ����, ����, Ư�����ڸ� �����Ͽ� 8~15�ڸ��� �Է����ּ���." << std::endl; // ��й�ȣ ��Ģ �ȳ�.

    while (true) {
        std::cout << "���� ���� ��й�ȣ�� �������ּ���: ";
        std::cin >> ownerPw; // ��й�ȣ �Է�.

        std::string confirmPassword;
        std::cout << "��й�ȣ ��Ȯ��: ";
        std::cin >> confirmPassword; // ��й�ȣ ��Ȯ�� �Է�.

        if (ownerPw == confirmPassword) { // ��й�ȣ�� ��Ȯ�� ��й�ȣ ��ġ ���� Ȯ��.
            // ��й�ȣ ��ȿ�� �˻� (���Խ� ���): �ּ� 8��, �ִ� 15��, ���� ��ҹ���, ����, Ư������ �� 1�� �̻� ����.
            std::regex password_regex("^(?=.*[a-zA-Z])(?=.*\\d)(?=.*[!@#$%^&*()_+\\-=\\[\\]{};':\"\\\\|,.<>/?]).{8,15}$");
            if (std::regex_match(ownerPw, password_regex)) {
                break; // ��й�ȣ ��ġ �� ��ȿ�� ��� �� ���� ����.
            }
            else {
                std::cout << "����: ��й�ȣ�� ��ȿ�� ������ �������� �ʽ��ϴ�. �ٽ� �Է����ּ���." << std::endl; // ��ȿ�� ���� �޽���.
            }
        }
        else {
            std::cout << "����: ��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���." << std::endl; // ��й�ȣ ����ġ �޽���.
        }
    }

    // ��ȭ��ȣ �Է� �� ����ȭ.
    std::cout << "���� ���� ��ȭ��ȣ (��: 01012345678): ";
    std::string rawPhone;
    std::cin >> rawPhone; // ��ȭ��ȣ �Է�.
    ownerPhone = User::normalizePhoneNumber(rawPhone); // �Էµ� ��ȭ��ȣ ����ȭ.
    if (ownerPhone.empty()) {
        std::cout << "���: ��ȭ��ȣ ������ �ùٸ��� �ʾ� �⺻��(010-0000-0000)���� �����˴ϴ�." << std::endl; // ���� ���� ���.
        ownerPhone = "01000000000"; // ��ȿ���� ������ �⺻������ ����.
    }

    // addUser �Լ��� ���� ���� ���� �߰� �õ�.
    if (addUser(ownerId, ownerPw, UserType::Owner, ownerName, ownerPhone)) {
        std::cout << "���� ���� (ID: " << ownerId << ")�� ���������� �����Ǿ����ϴ�. ���� �α����� �� �ֽ��ϴ�." << std::endl; // ���� ���� �޽���.
    }
    else {
        std::cerr << "����: ���� ���� ������ �����߽��ϴ�. (���� ����)" << std::endl; // ���� ���� �޽��� (ID �ߺ� ���� ����).
    }
}

// ����� �߰�
bool UserManager::addUser(const std::string& userId, const std::string& password, UserType type, const std::string& name, const std::string& phone) {
    if (users.count(userId)) { // �߰��Ϸ��� userId�� �̹� �����ϴ��� Ȯ��.
        return false; // �̹� �����ϴ� ID�̹Ƿ� �߰� ���� ��ȯ.
    }

    // �� UserType�� �´� �Ļ� Ŭ���� ��ü ����.
    // ���� map<string, User>�� ���� ���� �����ϴ� ����� C++ ��ü �����̽�(object slicing)�� �߻���ų �� �ֽ��ϴ�.
    // �̴� �Ļ� Ŭ���� ������ ���(���� �Լ� ����)�� �߷����� �⺻ Ŭ���� �κи� ����Ǵ� ����.
    // �� ������Ʈ�� ���� ��ɿ����� User �⺻ Ŭ������ ����� ����ϰ� �־� ū ������ ���� �� ������,
    // ������ ������ �ʿ��� ��� std::map<std::string, std::unique_ptr<User>>�� ���� ������ ������� ���� �ʿ�.
    User newUser; // User ��ü ����.
    if (type == UserType::Customer) {
        newUser = Customer(userId, password, name, phone); // Customer ��ü�� �Ҵ�.
    }
    else if (type == UserType::Employee) {
        newUser = Staff(userId, password, name, phone); // Staff ��ü�� �Ҵ�.
    }
    else if (type == UserType::Owner) {
        newUser = Admin(userId, password, name, phone); // Admin ��ü�� �Ҵ�.
    }
    else {
        std::cerr << "����: �� �� ���� ����� �����Դϴ�." << std::endl; // �� �� ���� ���� ����.
        return false;
    }

    users[userId] = newUser; // �ʿ� �� ����� �߰�.
    saveUsers(); // ���� ������ ���Ͽ� ����.
    return true; // ����� �߰� ���� ��ȯ.
}

// �α���
UserType UserManager::login(const std::string& userId, const std::string& password) {
    auto it = users.find(userId); // ����� ID�� �ʿ��� ����� ã��.
    if (it != users.end()) { // ID�� �����ϴ� ���.
        if (it->second.getPassword() == password) { // ��й�ȣ ��ġ ���� Ȯ��.
            return it->second.getUserType(); // �α��� ����, �ش� ������� ���� ��ȯ.
        }
    }
    return UserType::None; // �α��� ���� �� None ���� ��ȯ.
}

// ����� ID�� ����� ��ȸ (�б� ����)
const User* UserManager::getUser(const std::string& userId) const {
    auto it = users.find(userId); // ����� ID�� �ʿ��� ����� ã��.
    if (it != users.end()) {
        return &(it->second); // �����ϴ� ����� ��ü�� �ּ�(�б� ����) ��ȯ.
    }
    return nullptr; // ����� ���� �� nullptr ��ȯ.
}

// ����� ID�� ����� ��ȸ (���� ����)
User* UserManager::getMutableUser(const std::string& userId) {
    auto it = users.find(userId); // ����� ID�� �ʿ��� ����� ã��.
    if (it != users.end()) {
        return &(it->second); // �����ϴ� ����� ��ü�� �ּ�(���� ����) ��ȯ.
    }
    return nullptr; // ����� ���� �� nullptr ��ȯ.
}

// ����� ����
bool UserManager::deleteUser(const std::string& userId) {
    auto it = users.find(userId); // ����� ID�� �ʿ��� ����� ã��.
    if (it != users.end()) {
        users.erase(it); // �ʿ��� ����� ����.
        saveUsers(); // ���� ������ ���Ͽ� ����.
        return true; // ���� ���� ��ȯ.
    }
    return false; // ����� ���� �� ���� ���� ��ȯ.
}

// ����� ���� ���� ������Ʈ
bool UserManager::updateUserAccount(const std::string& userId, const std::string& newPassword, const std::string& newName, const std::string& newPhone) {
    User* userToUpdate = getMutableUser(userId); // ������Ʈ�� ����� ��ü ������ ��������.
    if (userToUpdate) {
        // �� ��й�ȣ�� ������� �ʰ� ���� ��й�ȣ�� �ٸ� ��� ������Ʈ.
        if (!newPassword.empty() && newPassword != userToUpdate->getPassword()) {
            userToUpdate->setPassword(newPassword);
        }
        // �� �̸��� ������� �ʰ� ���� �̸��� �ٸ� ��� ������Ʈ.
        if (!newName.empty() && newName != userToUpdate->getName()) {
            userToUpdate->setName(newName);
        }
        // �� ��ȭ��ȣ�� ����ȭ�ϰ�, ������� �ʰ� ���� ��ȭ��ȣ�� �ٸ� ��� ������Ʈ.
        std::string normalizedPhone = User::normalizePhoneNumber(newPhone);
        if (!newPhone.empty() && normalizedPhone != userToUpdate->getPhone()) {
            userToUpdate->setPhone(normalizedPhone);
        }
        saveUsers(); // ���� ������ ���Ͽ� ����.
        return true; // ������Ʈ ���� ��ȯ.
    }
    return false; // ����� ���� �� ������Ʈ ���� ��ȯ.
}

// ��� ����� ��� ��ȯ
const std::map<std::string, User>& UserManager::getAllUsers() const {
    return users; // ��� ����� ������ ��� �� ��ȯ (�б� ����).
}

// ��� ����� ���� ��� (�����ڿ�)
void UserManager::printAllUsers() const {
    if (users.empty()) {
        std::cout << "��ϵ� ����ڰ� �����ϴ�." << std::endl; // ��ϵ� ����� ���� �޽���.
        return;
    }
    std::cout << "\n--- ��� ����� ��� ---\n" << std::endl; // ��� ����.
    std::cout << "--------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(10) << "ID"
        << std::setw(15) << "�̸�"
        << std::setw(10) << "����"
        << std::setw(15) << "��ȭ��ȣ"
        << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------" << std::endl;

    for (const auto& pair : users) {
        const User& user = pair.second;
        std::string userTypeStr;
        // ����� ������ ���� ���ڿ� ��ȯ.
        switch (user.getUserType()) {
        case UserType::Customer: userTypeStr = "��"; break;
        case UserType::Employee: userTypeStr = "����"; break;
        case UserType::Owner:    userTypeStr = "����"; break;
        default:                 userTypeStr = "�� �� ����"; break;
        }
        std::cout << std::left << std::setw(10) << user.getUserId()
            << std::setw(15) << user.getName()
            << std::setw(10) << userTypeStr
            << std::setw(15) << user.getFormattedPhone() // ����ȭ�� ��ȭ��ȣ ���.
            << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------------------------" << std::endl;
}