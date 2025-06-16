// Customer.h
#pragma once

#include "User.h"   // User 클래스 상속
#include <string>   // std::string

// 고객 계정 클래스
class Customer : public User {
public:
    // 기본 생성자
    Customer();

    // 매개변수 생성자
    Customer(const std::string& userId, const std::string& password, const std::string& name, const std::string& phone);
};