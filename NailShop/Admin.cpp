#include "Admin.h"
#include <iostream>
#include <string>
using namespace std;

void Admin::showTodaySchedule() const {
	// ���� ���� �����ֱ� ���� ����
	cout << "������ ���� ����Դϴ�." << endl;
	for (int i = 1; i <= 5; ++i) { // ���÷� 5���� ������ ���
		cout << "���� " << i << ": �� �̸�, �ð�, ����" << endl;
	}
}
void Admin::searchCustomer(const std::string& customerId) const {
	// �� �˻� ���� ����
	cout << "�� ID: " << customerId << "�� ���� ������ �˻��մϴ�." << endl;
}
void Admin::manageStaff() const {
	// ���� ���� ���� ����
	cout << "���� ���� �޴��Դϴ�." << endl;
	// ���÷� ���� ��� ���
	cout << "���� ���:" << endl;
	cout << "1. ���� A" << endl;
	cout << "2. ���� B" << endl;
}
void Admin::manageCustomers() const {
	// �� ���� ���� ����
	cout << "�� ���� �޴��Դϴ�." << endl;
	// ���÷� �� ��� ���
	cout << "�� ���:" << endl;
	cout << "1. �� A" << endl;
	cout << "2. �� B" << endl;
}
void Admin::manageReservations() const {
	// ���� ���� ���� ����
	cout << "���� ���� �޴��Դϴ�." << endl;
	// ���÷� ���� ��� ���
	cout << "���� ���:" << endl;
	cout << "1. ���� A" << endl;
	cout << "2. ���� B" << endl;
}
void Admin::removeStaff(const string& staffId) {
	// ���� ���� ���� ����
	cout << "���� ID: " << staffId << "��(��) �����մϴ�." << endl;
}
void Admin::removeCustomer(const string& customerId) {
	// �� ���� ���� ����
	cout << "�� ID: " << customerId << "��(��) �����մϴ�." << endl;
}
void Admin::removeReservation(const string& reservationId) {
	// ���� ���� ���� ����
	cout << "���� ID: " << reservationId << "��(��) �����մϴ�." << endl;
}