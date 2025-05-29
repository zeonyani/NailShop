#pragma once
#include "User.h"
#include <string>

using namespace std;
class Admin : public User {
public:
	Admin() : User() {}  // �⺻ ������ ����, User�� �⺻ �����ڸ� ȣ��
	Admin(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone)
		: User(id, pw, name, phone) {
	}  // �Ű����� ������ ����, User�� �Ű����� �����ڸ� ȣ��
	// Staff Ŭ������ User Ŭ�����κ��� ��ӹ��� ��� �Լ����� ����� �� ����

	// Staff ���� �Լ��� ������ �κ�
	void showTodaySchedule() const; // ���� ���� �����ֱ�
	void searchCustomer(const std::string& customerId) const; // �� �˻�

	// ������ ���� �Լ�
	void manageStaff() const; // ���� ����
	void manageCustomers() const; // �� ����
	void manageReservations() const; // ���� ����
	void removeStaff(const string& staffId); // ���� ���� (���ΰ� �ٲ�Ƿ� const�� ������, ���� ����)
	void removeCustomer(const string& customerId); // �� ����
	void removeReservation(const string& reservationId); // ���� ����

	virtual ~Admin() = default;  // ���� �Ҹ���
};