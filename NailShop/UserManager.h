#pragma once

#include <string>
#include <map>
#include "User.h" // User 클래스를 사용하므로 포함하기

class UserManager {
public:
    UserManager();
    // User 생성자에 맞춰 name 파라미터 추가
    bool addUser(const std::string& userId, const std::string& password, UserType type, const std::string& name);
    UserType login(const std::string& userId, const std::string& password);
    const User* getUser(const std::string& userId) const;

private:
    std::map<std::string, User> users;
    void loadInitialUsers();
};