// User.h
#pragma once

#include <string> // std::string ���
#include <vector> // std::vector

// ����� ����
enum class UserType {
    None,       // �ʱ�/�α��� ��
    Customer,   // ��
    Employee,   // ����
    Owner       // ����
};

// ����� �⺻ ����
class User {
public:
    // �⺻ ������
    User();

    // �Ű����� ������
    User(const std::string& userId, const std::string& password, UserType type, const std::string& name, const std::string& phone);

    // ����� ID ��ȯ
    std::string getUserId() const;
    // ��й�ȣ ��ȯ
    std::string getPassword() const;
    // ����� ���� ��ȯ
    UserType getUserType() const;
    // ��й�ȣ ��ġ Ȯ��
    bool checkPassword(const std::string& inputPassword) const;
    // ����� �̸� ��ȯ
    std::string getName() const;
    // ����� ��ȭ��ȣ ��ȯ (����� ���� ����)
    std::string getPhone() const;
    // ����� ��ȭ��ȣ ��ȯ (������ ���� ������)
    std::string getFormattedPhone() const; // ���� �߰�: ��¿� ������

    // CSV ���ڿ� ��ȯ
    std::string toCsvString() const;
    // CSV ���ڿ��κ��� User ��ü ����
    static User fromCsvString(const std::string& csvLine);

    // ��ȭ��ȣ ���� (�ܺο��� ���)
    void setPhone(const std::string& newPhone); // ���� �߰�: ��ȭ��ȣ ���� �޼���

private:
    std::string userId;     // ����� ���� ID
    std::string password;   // ����� ��й�ȣ
    UserType type;          // ����� ����
    std::string name;       // ����� �Ǹ�
    std::string phone;      // ����� ��ȭ��ȣ (���ڸ� ����)

    // UserType�� ���ڿ��� ��ȯ
    static std::string userTypeToString(UserType type);
    // ���ڿ��� UserType���� ��ȯ
    static UserType stringToUserType(const std::string& typeStr);

    // ��ȭ��ȣ ������ (���� ��ƿ��Ƽ)
    static std::string formatPhoneNumber(const std::string& phoneNumber); // ���� �߰�: ������
    // ��ȭ��ȣ���� ���ڸ� ���� (���� ��ƿ��Ƽ)
    static std::string extractDigits(const std::string& phoneNumber); // ���� �߰�: ���� ����
    // ��ȭ��ȣ ��ȿ�� �˻� (���� ��ƿ��Ƽ)
    static bool isValidPhoneNumber(const std::string& phoneNumber); // ���� �߰�: ��ȿ�� �˻�
};