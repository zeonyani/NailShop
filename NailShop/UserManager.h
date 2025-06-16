//UserManager.h
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <map>
#include <string>
#include <vector>
#include "User.h"
#include "CSVHandler.h"

class UserManager {
private:
    static const std::string USERS_FILE; // �߰�
    std::map<std::string, User> users;
    int nextUserId; // ���� ����� ID ��ȣ (USR001, USR002 ��)

    void loadUsers();
    void addOwnerAccount(); // owner ���� ���� ���

public: // saveUsers�� public�� �־�� SystemManager���� ȣ�� ����
    void saveUsers(bool silent = false); // silent �Ű����� �߰�

public:
    UserManager();
    ~UserManager();

    // ����� �߰�
    bool addUser(const std::string& userId, const std::string& password, UserType type, const std::string& name, const std::string& phone);
    // �α���
    UserType login(const std::string& userId, const std::string& password);
    // ����� ID�� ����� ��ȸ (�б� ����)
    const User* getUser(const std::string& userId) const;
    // ����� ID�� ����� ��ȸ (���� ����)
    User* getMutableUser(const std::string& userId);
    // ����� ����
    bool deleteUser(const std::string& userId);
    // ����� ���� ���� ������Ʈ
    // newName �Ű����� �߰�
    bool updateUserAccount(const std::string& userId, const std::string& newPassword, const std::string& newName, const std::string& newPhone);
    // ��� ����� ���� ���
    void printAllUsers() const;
    // ��� ����� �� ��ȯ (�б� ����)
    const std::map<std::string, User>& getAllUsers() const;
};

#endif // USER_MANAGER_H