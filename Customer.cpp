#include "Customer.h"
#include <iostream>
using namespace std;
void Customer::makeReservation(const std::string& service, const std::string& dateTime) {
	// �����ϱ� ���� ����
	cout << "�� " << getName() << " ���� " << service << " ���񽺸� " << dateTime << "�� �����߽��ϴ�." << endl;
}
void Customer::cancelReservation(const std::string& reservationId) {
	// ���� ����ϱ� ���� ����
	cout << "�� " <<  getName() << " ���� ���� ID: " << reservationId << "�� ������ ����߽��ϴ�." << endl;
}
void Customer::viewReservations() const {
	// ���� ��� ���� ���� ����
	cout << "�� " << getName() << " ���� ���� ����Դϴ�." << endl;
	for (int i = 1; i <= 3; ++i) { // ���÷� 3���� ������ ���
		cout << "���� " << i << ": ����, ��¥ �� �ð�" << endl;
	}
}
