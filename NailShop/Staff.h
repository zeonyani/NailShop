// Staff.h
#pragma once

#include "User.h"   // User 클래스 상속
#include <string>   // std::string

// 직원 계정 클래스
class Staff : public User {
public:
    // 기본 생성자
    Staff();

    // 매개변수 생성자
    Staff(const std::string& userId, const std::string& password, const std::string& name, const std::string& phone);
};