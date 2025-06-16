// Admin.h
#pragma once
#include "User.h"   // User Ŭ���� ���
#include <string>   // std::string
#include <vector>   // std::vector

// ����(������) ���� Ŭ����
class Admin : public User {
public:
    // �⺻ ������
    Admin();

    // �Ű����� ������
    Admin(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone);

    // ���� �Ҹ���
    virtual ~Admin() = default;
};