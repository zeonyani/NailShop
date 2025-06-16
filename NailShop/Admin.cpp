// Admin.cpp
#include "Admin.h"      // Admin 클래스
#include <iostream>     // 콘솔 출력

using namespace std;    // std:: 네임스페이스 사용

// Admin 기본 생성자
Admin::Admin() : User() {
}

// Admin 매개변수 생성자
Admin::Admin(const string& id, const string& pw, const string& name, const string& phone)
    : User(id, pw, UserType::Owner, name, phone) { // 부모 생성자 호출, UserType::Owner 명시
}