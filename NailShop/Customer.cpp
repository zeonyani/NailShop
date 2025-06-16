// Customer.cpp
#include "Customer.h"   // Customer 클래스
#include <iostream>     // 콘솔 출력

using namespace std;    // std:: 네임스페이스 사용

// Customer 기본 생성자
Customer::Customer() : User() {
}

// Customer 매개변수 생성자
Customer::Customer(const string& userId, const string& password, const string& name, const string& phone)
    : User(userId, password, UserType::Customer, name, phone) { // 부모 생성자 호출, UserType::Customer 명시
}