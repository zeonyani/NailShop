// Admin.h
#pragma once
#include "User.h"   // User 클래스 상속
#include <string>   // std::string
#include <vector>   // std::vector

// 사장(관리자) 계정 클래스
class Admin : public User {
public:
    // 기본 생성자
    Admin();

    // 매개변수 생성자
    Admin(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone);

    // 가상 소멸자
    virtual ~Admin() = default;
};