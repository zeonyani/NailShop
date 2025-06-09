#pragma once
#include "User.h"
#include <string>
#include <vector>

using namespace std;
class Customer : public User {
public:
	Customer() : User() {}  // �⺻ ������ ����, User�� �⺻ �����ڸ� ȣ��
	Customer(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone)
		: User(id, pw, name, phone) {
	}  // �Ű����� ������ ����, User�� �Ű����� �����ڸ� ȣ��
	// �߰����� Customer ���� �Լ�
	void makeReservation(const std::string& service, const std::string& dateTime); // �����ϱ�
	void cancelReservation(const std::string& reservationId); // ���� ����ϱ�
	void viewReservations() const; // ���� ��� ����
	virtual ~Customer() = default;  // ���� �Ҹ���
};
