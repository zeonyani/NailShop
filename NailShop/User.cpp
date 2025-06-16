// User.cpp
#include "User.h"       // User Ŭ����
#include "CSVHandler.h" // CSVHandler
#include <iostream>     // �ܼ� ���
#include <vector>       // std::vector
#include <regex>        // ���� ǥ���� (��ȭ��ȣ ��ȿ�� �˻�/������)

using namespace std;    // std:: ���ӽ����̽� ���

// UserType ���ڿ� ��ȯ
string User::userTypeToString(UserType type) {
    switch (type) {
    case UserType::Customer: return "Customer";
    case UserType::Employee: return "Employee";
    case UserType::Owner:    return "Owner";
    default:                 return "None";
    }
}

// ���ڿ� UserType ��ȯ
UserType User::stringToUserType(const string& typeStr) {
    if (typeStr == "Customer") return UserType::Customer;
    if (typeStr == "Employee") return UserType::Employee;
    if (typeStr == "Owner")    return UserType::Owner;
    return UserType::None;
}

// ��ȭ��ȣ���� ���ڸ� ����
string User::extractDigits(const string& phoneNumber) {
    string digits;
    for (char c : phoneNumber) {
        if (isdigit(c)) {
            digits += c;
        }
    }
    return digits;
}

// ��ȭ��ȣ ��ȿ�� �˻� (������ ���� 10-11�ڸ� ����)
bool User::isValidPhoneNumber(const string& phoneNumber) {
    // 10�ڸ� �Ǵ� 11�ڸ� �������� Ȯ�� (������ ���� ���� ���� ����, extractDigits�� ���ڸ� ���� �� �˻�)
    string digits = extractDigits(phoneNumber);
    return digits.length() >= 10 && digits.length() <= 11 &&
        (digits.substr(0, 3) == "010" || digits.substr(0, 2) == "02" || digits.substr(0, 3) == "031" || // �⺻���� ��ȣ�� Ȯ�� (���� ����)
            digits.substr(0, 3) == "032" || digits.substr(0, 3) == "033" || digits.substr(0, 3) == "041" ||
            digits.substr(0, 3) == "042" || digits.substr(0, 3) == "043" || digits.substr(0, 3) == "044" ||
            digits.substr(0, 3) == "051" || digits.substr(0, 3) == "052" || digits.substr(0, 3) == "053" ||
            digits.substr(0, 3) == "054" || digits.substr(0, 3) == "055" || digits.substr(0, 3) == "061" ||
            digits.substr(0, 3) == "062" || digits.substr(0, 3) == "063" || digits.substr(0, 3) == "064");
}

// ��ȭ��ȣ ������ (������ �߰�)
string User::formatPhoneNumber(const string& phoneNumber) {
    string digits = extractDigits(phoneNumber); // ���ڸ� ����

    if (digits.length() == 10) { // 000-000-0000 �Ǵ� 00-000-0000
        if (digits.rfind("02", 0) == 0) { // 02�� �����ϴ� 10�ڸ� (����)
            return digits.substr(0, 2) + "-" + digits.substr(2, 4) + "-" + digits.substr(6);
        }
        else { // 01X�� �����ϴ� 10�ڸ� (�Ϲ� �޴���) �Ǵ� �ٸ� ������ȣ
            return digits.substr(0, 3) + "-" + digits.substr(3, 3) + "-" + digits.substr(6);
        }
    }
    else if (digits.length() == 11) { // 000-0000-0000 (�Ϲ� �޴���)
        return digits.substr(0, 3) + "-" + digits.substr(3, 4) + "-" + digits.substr(7);
    }
    return phoneNumber; // �� �� ������ ���� ��ȯ
}

// User �⺻ ������
User::User() : userId(""), password(""), type(UserType::None), name(""), phone("") {}

// User �Ű����� ������
User::User(const string& userId, const string& password, UserType type, const string& name, const string& phone)
    : userId(userId), password(password), type(type), name(name) {
    // �����ڿ����� ��ȭ��ȣ ��ȿ�� �˻� �� ���ڸ� ����
    if (isValidPhoneNumber(phone)) {
        this->phone = extractDigits(phone);
    }
    else {
        this->phone = ""; // ��ȿ���� ������ �� ���ڿ� �Ǵ� ���� ó��
        cerr << "���: ��ȿ���� ���� ��ȭ��ȣ: " << phone << ". �� ������ �����." << endl;
    }
}

// ����� ID ��ȯ
string User::getUserId() const {
    return userId;
}

// ��й�ȣ ��ȯ
string User::getPassword() const {
    return password;
}

// ����� ���� ��ȯ
UserType User::getUserType() const {
    return type;
}

// ��й�ȣ ��ġ Ȯ��
bool User::checkPassword(const string& inputPassword) const {
    return password == inputPassword;
}

// ����� �̸� ��ȯ
string User::getName() const {
    return name;
}

// ����� ��ȭ��ȣ ��ȯ (����� ���� - ���ڸ�)
string User::getPhone() const {
    return phone;
}

// ����� ��ȭ��ȣ ��ȯ (������ ���� ������)
string User::getFormattedPhone() const {
    return formatPhoneNumber(phone); // ����� ���ڸ� �ִ� ��ȣ�� �������Ͽ� ��ȯ
}

// ����� ���� CSV ���ڿ� ��ȯ
string User::toCsvString() const {
    vector<string> fields;
    fields.push_back(userId);
    fields.push_back(password);
    fields.push_back(userTypeToString(type)); // UserType ���ڿ� ��ȯ
    fields.push_back(name);
    fields.push_back(phone); // CSV���� ���ڸ� �ִ� ���·� ����
    return CSVHandler::formatCsvLine(fields);
}

// CSV ���ڿ��κ��� User ��ü ����
User User::fromCsvString(const string& csvLine) {
    vector<string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 5) {
        UserType parsedType = stringToUserType(fields[2]);
        // CSV���� �о�� ���� ��ȿ�� �˻縦 ������, �̹� ����� �������̹Ƿ� �ַ� ���� ���⸸
        string loadedPhone = extractDigits(fields[4]); // CSV���� �о�� ��ȭ��ȣ ���ڸ� ����
        if (!isValidPhoneNumber(loadedPhone)) { // �ٽ� �ѹ� ��ȿ�� �˻�
            cerr << "���: CSV���� �о�� ��ȭ��ȣ�� ��ȿ���� ����: " << fields[4] << ". �� ������ �ε��." << endl;
            loadedPhone = "";
        }
        return User(fields[0], fields[1], parsedType, fields[3], loadedPhone);
    }
    return User(); // �߸��� ���� �� �⺻ User ��ü ��ȯ
}

// ��ȭ��ȣ ���� (��ȿ�� �˻� �� ���ڸ� ����)
void User::setPhone(const string& newPhone) {
    if (isValidPhoneNumber(newPhone)) {
        this->phone = extractDigits(newPhone);
    }
    else {
        // ��ȿ���� ���� ���, ���� �� ���� �Ǵ� ���� ó��
        cout << "����: ��ȿ���� ���� ��ȭ��ȣ ����. ��ȭ��ȣ ���� ����." << endl;
    }
}