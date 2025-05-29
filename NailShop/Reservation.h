#pragma once
#include <string>
using namespace std;
enum class ReservationStatus {
	Active,    // �����
	Cancelled, // ��ҵ�
};

class Reservation {
public:
	// �����ڸ� ���� ���� ����
	Reservation() = default; // �⺻ ������
	Reservation(const string& customerId, const string& serviceType, const string& dateTime); // �Ű����� �ִ� ������

	// ���� ���� ��ȯ �Լ�
	string getCustomerId() const;
	string getServiceType() const;
	string getDateTime() const;

	// ���� ���� �Լ�
	void changeReservation(const string& newServiceType, const string& newDateTime);

	// ���� ��� �Լ�
	void cancelReservation();

	// ���� ���� �Լ�(�̹� �����̸� �߰� ���ؾ� �ϴϱ�)
	bool isReserved() const;

	// ���� ID ��ȯ �Լ� -> Ư�� ������ ã�� ���� ���(�ܺο��� Ư���� ������ �� ��������)
	string getReservationId() const;

private:
	string reservationId; // ���� ID -> ȿ�������� Ư�� ������ ã����
	string customerId;  // �� ID
	string serviceType; // ���� ����
	string dateTime;    // ���� ��¥ �� �ð�
	ReservationStatus status; // ���� ���� (�����, ��ҵ� ��)

	static int nextId; // ���� ID ������ ���� ���� ����
};