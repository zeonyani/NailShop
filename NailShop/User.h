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
    // 이 생성자만 존재! 기본 생성자는 없음.
    User(const std::string& userId, const std::string& password, UserType type, const std::string& name);
    std::string getUserId() const;
    std::string getPassword() const;
    UserType getUserType() const;
    bool checkPassword(const std::string& inputPassword) const;
    std::string getName() const; // getName 함수 존재!
private:
    std::string userId;
    std::string password;
    UserType type;
    std::string name; // name 멤버 변수 존재!
};