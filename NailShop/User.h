#pragma once
#include <string>

enum class UserType {
    None,
    Customer,
    Employee,
    Owner
};

class User {
public:
    // �� �����ڸ� ����! �⺻ �����ڴ� ����.
    User(const std::string& userId, const std::string& password, UserType type, const std::string& name);
    std::string getUserId() const;
    std::string getPassword() const;
    UserType getUserType() const;
    bool checkPassword(const std::string& inputPassword) const;
    std::string getName() const; // getName �Լ� ����!
private:
    std::string userId;
    std::string password;
    UserType type;
    std::string name; // name ��� ���� ����!
};