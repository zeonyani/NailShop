#pragma once
#include <string>
#include "Reservation.h"
using namespace std;

class ReservationManager {
public:
	ReservationManager() = default;
	
	// CRUD ���� �Լ�
	void addReservation(const string& id, const string& service, const string& datetime); // ���� �߰�
	void deleteReservation(string& reservationid); // ���� ����
	Reservation getReservation(const string& reservationid); // ���� ��ȯ
	void printReservation(const string& reservationid); // �ش� ���� ���
	void printAllReservations(); // ��ü ���� ���� ���
	
	// ���� ���� ���� Ȯ�� �Լ�
	bool checkReservation(const string& reservationid);

	// �����޽��� ��� �Լ�
	void showMessage(const string& reservationid);

	~ReservationManager() = default;
};