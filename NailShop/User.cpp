//User.cpp
#include "User.h"
#include "CSVHandler.h"
#include <iostream>
#include <regex>
#include <algorithm>

// User �⺻ ������
User::User()
    : userId(""), password(""), userType(UserType::None), name(""), phone("") {
}

// User �Ű����� ������
User::User(const std::string& userId, const std::string& password, UserType userType,
    const std::string& name, const std::string& phone)
    : userId(userId), password(password), userType(userType), name(name) {
    this->phone = normalizePhoneNumber(phone); // ��ȭ��ȣ ����ȭ�Ͽ� ����
}

// Getter �޼��� ����
std::string User::getUserId() const {
    return userId;
}

std::string User::getPassword() const {
    return password;
}

UserType User::getUserType() const {
    return userType;
}

std::string User::getName() const {
    return name;
}

std::string User::getPhone() const {
    return phone;
}

// ����ȭ�� ��ȭ��ȣ ��ȯ (������ �߰�)
std::string User::getFormattedPhone() const {
    if (phone.length() == 11) { // 010-XXXX-XXXX
        return phone.substr(0, 3) + "-" + phone.substr(3, 4) + "-" + phone.substr(7, 4);
    }
    else if (phone.length() == 10) { // 0X-XXX-XXXX (���� 02), 0XX-XXX-XXXX (�� �� ����)
        if (phone.rfind("02", 0) == 0) { // 02�� �����ϴ� ���
            return phone.substr(0, 2) + "-" + phone.substr(2, 4) + "-" + phone.substr(6, 4);
        }
        else { // �� �� 0X�� ���� (�� �ڸ� ������ȣ)
            return phone.substr(0, 3) + "-" + phone.substr(3, 3) + "-" + phone.substr(6, 4);
        }
    }
    else if (phone.length() == 9) { // 0X-XXXX-XXXX (���� 02)
        if (phone.rfind("02", 0) == 0) {
            return phone.substr(0, 2) + "-" + phone.substr(2, 3) + "-" + phone.substr(5, 4);
        }
    }
    return phone; // ����ȭ ���� �� ���� ��ȯ
}

// ��ȭ��ȣ ��ȿ�� �˻� �� ����ȭ (������ ����)
std::string User::normalizePhoneNumber(const std::string& rawPhone) {
    std::string digitsOnly;
    for (char c : rawPhone) {
        if (isdigit(c)) {
            digitsOnly += c;
        }
    }

    // ���ѹα� ��ȭ��ȣ ���Ŀ� ���� ������ ��ȿ�� �˻�
    // 010-xxxx-xxxx (11�ڸ�), ������ȣ ���� �Ϲ� ��ȭ��ȣ (9-11�ڸ�)
    if ((digitsOnly.length() == 11 && digitsOnly.rfind("010", 0) == 0) ||
        (digitsOnly.length() >= 9 && digitsOnly.length() <= 11)) { // ������ȣ ���� �Ϲ� ��ȭ��ȣ (�ּ� 9�ڸ�)
        return digitsOnly;
    }
    return ""; // ��ȿ���� ������ �� ���ڿ� ��ȯ
}

// CSV ���ڿ��� ��ȯ
std::string User::toCsvString() const {
    std::vector<std::string> fields;
    fields.push_back(userId);
    fields.push_back(password);
    fields.push_back(std::to_string(static_cast<int>(userType))); // UserType�� int�� ��ȯ�Ͽ� ����
    fields.push_back(name);
    fields.push_back(phone); // ����ȭ�� ��ȭ��ȣ ����
    return CSVHandler::formatCsvLine(fields);
}

// CSV ���ڿ��κ��� User ��ü ����
User User::fromCsvString(const std::string& csvLine) {
    std::vector<std::string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 5) {
        try {
            std::string userId = fields[0];
            std::string password = fields[1];
            UserType userType = static_cast<UserType>(std::stoi(fields[2])); // int�� UserType���� ��ȯ
            std::string name = fields[3];
            std::string phone = fields[4];
            return User(userId, password, userType, name, phone);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "User::fromCsvString - ���� �Ľ� ���� (Invalid Argument): " << e.what() << " in line: " << csvLine << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "User::fromCsvString - ���� ���� ���� (Out of Range): " << e.what() << " in line: " << csvLine << std::endl;
        }
    }
    return User(); // �߸��� ���� �� �⺻ User ��ü ��ȯ
}

// User::update �޼��� ���� �߰�
void User::update(const std::string& newPassword, const std::string& newName, const std::string& newPhone) {
    password = newPassword;
    name = newName;
    phone = normalizePhoneNumber(newPhone);
}