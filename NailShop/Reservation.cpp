#include "Reservation.h"
#include <string>
using namespace std;
int Reservation::nextReservationId = 1; // ���� ���� �ʱ�ȭ, ���� ID ������ ���
Reservation::Reservation(const string& customerId, const string& serviceType, const string& dateTime)
	: customerId(customerId), serviceType(serviceType), dateTime(dateTime), status(ReservationStatus::Active) {
	reservationId = "R" + to_string(nextReservationId++); // ���� ID ����, ���� ID ����
} // �Ű����� ������, ���� ���´� �⺻������ Ȱ��ȭ�� ����
string Reservation::getCustomerId() const {
	return customerId;  // �� ID ��ȯ
}
string Reservation::getServiceType() const {
	return serviceType; // ���� ���� ��ȯ
}
string Reservation::getDateTime() const {
	return dateTime;    // ���� ��¥ �� �ð� ��ȯ
}
void Reservation::changeReservation(const string& newServiceType, const string& newDateTime) {
	serviceType = newServiceType; // ���� ���� ����
	dateTime = newDateTime;       // ���� ��¥ �� �ð� ����
}
void Reservation::cancelReservation() {
	status = ReservationStatus::Cancelled; // ���� ���¸� ��ҷ� ����
}
string Reservation::getReservationId() const {
	return reservationId; // ���� ID ��ȯ
}

// ���� ���¸� ��ȯ�ϴ� �Լ�
// ��: Active(�����), Cancelled(��ҵ�)
ReservationStatus Reservation::getStatus() const {
	return status;
}
