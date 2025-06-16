//User.h
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <sstream>

// ����� ���� ������
enum class UserType {
    None,       // �ʱⰪ �Ǵ� �� �� ���� ����
    Customer,   // ��
    Employee,   // ����
    Owner       // ����
};

// ����� ������ ��� �⺻ Ŭ����
class User {
private:
    std::string userId;     // ����� ID (���� �ĺ���)
    std::string password;   // ��й�ȣ
    UserType userType;      // ����� ���� (��, ����, ����)
    std::string name;       // �̸�
    std::string phone;      // ��ȭ��ȣ

public:
    // ��ȭ��ȣ ��ȿ�� �˻� �� ����ȭ (static���� ����)
    static std::string normalizePhoneNumber(const std::string& rawPhone);

public:
    // �⺻ ������
    User();
    // �Ű����� ������
    User(const std::string& userId, const std::string& password, UserType userType,
        const std::string& name, const std::string& phone);

    // Getter �޼���
    std::string getUserId() const;
    std::string getPassword() const;
    UserType getUserType() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getFormattedPhone() const;

    // Setter �޼��� (���������� ���������� �߰��ϰų�, update �Լ��� ���)
    void setPassword(const std::string& newPassword) { password = newPassword; }
    void setName(const std::string& newName) { name = newName; }
    void setPhone(const std::string& newPhone) { phone = normalizePhoneNumber(newPhone); }

    // ����� ���� ������Ʈ �޼��� �߰�
    void update(const std::string& newPassword, const std::string& newName, const std::string& newPhone);

    // CSV ���ڿ��� ��ȯ
    std::string toCsvString() const;
    // CSV ���ڿ��κ��� User ��ü ����
    static User fromCsvString(const std::string& csvLine);
};

#endif // USER_H