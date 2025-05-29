#pragma once
#include "User.h"
#include <string>

class Staff : public User {
public:
	Staff() : User() {}  // �⺻ ������ ����, User�� �⺻ �����ڸ� ȣ��
	Staff(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone)
		: User(id, pw, name, phone) {
	}  // �Ű����� ������ ����, User�� �Ű����� �����ڸ� ȣ��
// Staff Ŭ������ User Ŭ�����κ��� ��ӹ��� ��� �Լ����� ����� �� ����

// �߰����� Staff ���� �Լ�
	void showTodaySchedule() const; // ���� ���� �����ֱ�
	void searchCustomer(const std::string& customerId) const; // �� �˻�

	virtual ~Staff() = default;  // ���� �Ҹ���
};