#include "Reservation.h"
#include "ReservationManager.h"
#include <iostream>
#include <map>

void ReservationManager::addReservation(const string& id, const string& service, const string& datetime){
	// ������ �̹� �����ϴ��� Ȯ��
	if (reservations.find(id) != reservations.end()) {
		cout << "�̹� ������ �����մϴ�." << endl; // ������ �̹� ������ ���
		return;
	}

	// ���ο� ���� ����
	Reservation newReservation(id, service, datetime);
	reservations[id] = newReservation; // ���� �߰�
	cout << "������ �߰��Ǿ����ϴ�." << endl;
}

void ReservationManager::deleteReservation(const string& reservationid) {
	// ������ �����ϴ��� Ȯ��
	if (reservations.find(reservationid) != reservations.end()) {
		reservations.erase(reservationid); // ���� ����
		cout << "������ �����Ǿ����ϴ�." << endl;
	}
	else {
		cout << "������ �������� �ʽ��ϴ�." << endl; // ������ �������� ���� ���
	}
}
Reservation ReservationManager::getReservation(const string& reservationid) {
	// ������ �����ϴ��� Ȯ��
	if (reservations.find(reservationid) != reservations.end()) {
		return reservations[reservationid]; // ���� ��ȯ
	}
	else {
		cout << "������ �������� �ʽ��ϴ�." << endl; // ������ �������� ���� ���
		return Reservation(); // �� Reservation ��ü ��ȯ
	}
}
void ReservationManager::printReservation(const string& reservationid) {
	// ������ �����ϴ��� Ȯ��
	if (reservations.find(reservationid) != reservations.end()) {
		Reservation res = reservations[reservationid];
		cout << "���� ID: " << res.getId() << endl;
		cout << "����: " << res.getService() << endl;
		cout << "��¥ �� �ð�: " << res.getDatetime() << endl;
	}
	else {
		cout << "������ �������� �ʽ��ϴ�." << endl; // ������ �������� ���� ���
	}
}
void ReservationManager::printAllReservation(const string& reservationid) {
	// ��� ������ ���
	for (const auto& pair : reservations) {
		const Reservation& res = pair.second;
		cout << "���� ID: " << res.getId() << ", ����: " << res.getService() << ", ��¥ �� �ð�: " << res.getDatetime() << endl;
	}
}