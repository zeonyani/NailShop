#pragma once
#include <string> // std::string ����ϱ�
#include <map>    // std::map ����ϱ�
#include "User.h" // User Ŭ���� ����� ���� �����ϱ�

// UserManager Ŭ������ ����� ������ �����ϴ� ������ ��
// ����� �߰�, �α��� ���� ���� ��� �����ϱ�
class UserManager {
public:
    // ������: UserManager ��ü ���� �� ȣ��Ǳ�
    UserManager();

    // �� ����� ������ �߰��ϴ� �Լ�
    // userId: �߰��� ������� ID
    // password: ������� ��й�ȣ
    // type: ������� ���� (��, ����, ����)
    // ��ȯ��: ����� �߰� ���� �� true, ���� �� (��: ID �ߺ�) false
    bool addUser(const std::string& userId, const std::string& password, UserType type);

    // ����� �α��� ������ �õ��ϴ� �Լ�
    // userId: �α��� �õ��� ������� ID
    // password: ����ڰ� �Է��� ��й�ȣ
    // ��ȯ��: �α��� ���� �� �ش� ������� UserType, ���� �� UserType::None
    UserType login(const std::string& userId, const std::string& password);

    // Ư�� ����� ID�� User ��ü�� �������� �Լ�
    // userId: ��ȸ�� ������� ID
    // ��ȯ��: �ش� User ��ü�� ������ (const), ã�� ���ϸ� nullptr
    const User* getUser(const std::string& userId) const;

private:
    // ����� ID(std::string)�� Ű�� User ��ü�� �����ϴ� ��
    // �̸� ���� ���� ����� ��ȸ �� ���� �����ϱ�
    std::map<std::string, User> users;

    // ���α׷� ���� �� �̸� ���ǵ� �ʱ� ����� �����͸� �ε��ϴ� �Լ�
    // ���� ������� ���� ��� �����͸� �ε��ϵ��� ����� �� �ֱ�
    void loadInitialUsers();
};