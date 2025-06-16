// Customer.h
#pragma once

#include "User.h"   // User Ŭ���� ���
#include <string>   // std::string

// �� ���� Ŭ����
class Customer : public User {
public:
    // �⺻ ������
    Customer();

    // �Ű����� ������
    Customer(const std::string& userId, const std::string& password, const std::string& name, const std::string& phone);
};