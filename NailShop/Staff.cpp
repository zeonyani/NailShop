#include "Staff.h"
#include <iostream>
using namespace std;
void Staff::showTodaySchedule() const {
	// ���� ���� �����ֱ� ���� ����
	cout << "������ ���� ����Դϴ�." << endl;
	for (int i = 1; i <= 5; ++i) { // ���÷� 5���� ������ ���
		cout << "���� " << i << ": �� �̸�, �ð�, ����" << endl;
	}
}
void Staff::searchCustomer(const std::string& customerId) const {
	// �� �˻� ���� ����
	cout << "�� ID: " << customerId << "�� ���� ������ �˻��մϴ�." << endl;
}

