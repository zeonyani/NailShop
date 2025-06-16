// UserManager.h
#pragma once

#include <string>   // std::string
#include <map>      // std::map
#include <vector>   // std::vector
#include "User.h"   // User Ŭ����
#include "CSVHandler.h" // CSVHandler

// ����� ���� ����
class UserManager {
public:
    // UserManager ������
    UserManager();
    // UserManager �Ҹ���
    ~UserManager();

    // ����� ���� �߰�
    bool addUser(const std::string& userId, const std::string& password, UserType type, const std::string& name, const std::string& phone);

    // ����� �α��� ó��
    UserType login(const std::string& userId, const std::string& password);

    // ����� ��ü ��ȸ (�б� ����)
    const User* getUser(const std::string& userId) const;

    // ����� ��ü ��ȸ (���� ����)
    User* getMutableUser(const std::string& userId);

    // ����� ���� ����
    bool deleteUser(const std::string& userId);

    // ��� ����� ���� ��ȯ
    const std::map<std::string, User>& getAllUsers() const;

    // ��� ����� ���� ���
    void printAllUsers() const;

private:
    std::map<std::string, User> users; // ����� ID-User ��
    const std::string USERS_FILE = "users.csv"; // ����� ������ ���� ���

    // CSV ���Ϸκ��� ����� ������ �ε�
    void loadUsers();
    // CSV ���Ͽ� ����� ������ ����
    void saveUsers();
};