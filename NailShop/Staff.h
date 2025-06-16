// Staff.h
#pragma once

#include "User.h"   // User Ŭ���� ���
#include <string>   // std::string

// ���� ���� Ŭ����
class Staff : public User {
public:
    // �⺻ ������
    Staff();

    // �Ű����� ������
    Staff(const std::string& userId, const std::string& password, const std::string& name, const std::string& phone);
};