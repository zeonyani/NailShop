// Staff.cpp
#include "Staff.h"      // Staff 클래스
#include <iostream>     // 콘솔 출력

using namespace std;    // std:: 네임스페이스 사용

// Staff 기본 생성자
Staff::Staff() : User() {
}

// Staff 매개변수 생성자
Staff::Staff(const string& userId, const string& password, const string& name, const string& phone)
    : User(userId, password, UserType::Employee, name, phone) { // 부모 생성자 호출, UserType::Employee 명시
}