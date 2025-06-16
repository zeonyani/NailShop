// Customer.cpp
#include "Customer.h"   // Customer Ŭ����
#include <iostream>     // �ܼ� ���

using namespace std;    // std:: ���ӽ����̽� ���

// Customer �⺻ ������
Customer::Customer() : User() {
}

// Customer �Ű����� ������
Customer::Customer(const string& userId, const string& password, const string& name, const string& phone)
    : User(userId, password, UserType::Customer, name, phone) { // �θ� ������ ȣ��, UserType::Customer ���
}