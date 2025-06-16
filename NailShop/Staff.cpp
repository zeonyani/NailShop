// Staff.cpp
#include "Staff.h"      // Staff Ŭ����
#include <iostream>     // �ܼ� ���

using namespace std;    // std:: ���ӽ����̽� ���

// Staff �⺻ ������
Staff::Staff() : User() {
}

// Staff �Ű����� ������
Staff::Staff(const string& userId, const string& password, const string& name, const string& phone)
    : User(userId, password, UserType::Employee, name, phone) { // �θ� ������ ȣ��, UserType::Employee ���
}