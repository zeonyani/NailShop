#pragma once

#include <string>
#include <map>
#include "User.h" // User Ŭ������ ����ϹǷ� �����ϱ�

class UserManager {
public:
    UserManager();
    // User �����ڿ� ���� name �Ķ���� �߰�
    bool addUser(const std::string& userId, const std::string& password, UserType type, const std::string& name);
    UserType login(const std::string& userId, const std::string& password);
    const User* getUser(const std::string& userId) const;

private:
    std::map<std::string, User> users;
    void loadInitialUsers();
};