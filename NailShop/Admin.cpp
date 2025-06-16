// Admin.cpp
#include "Admin.h"      // Admin Ŭ����
#include <iostream>     // �ܼ� ���

using namespace std;    // std:: ���ӽ����̽� ���

// Admin �⺻ ������
Admin::Admin() : User() {
}

// Admin �Ű����� ������
Admin::Admin(const string& id, const string& pw, const string& name, const string& phone)
    : User(id, pw, UserType::Owner, name, phone) { // �θ� ������ ȣ��, UserType::Owner ���
}