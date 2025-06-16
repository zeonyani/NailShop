#include "Reservation.h"
#include "ReservationManager.h"
#include <iostream>
#include <map>
using namespace std;

// ���� �߰� �Լ�
void ReservationManager::addReservation(const string& customerId, const string& service, const string& datetime) {
    // ���ο� ���� ��ü ����
    Reservation newReservation(customerId, service, datetime);
    string reservationId = newReservation.getReservationId();

    // map�� ���� ID�� Ű�� ����
    reservations[reservationId] = newReservation;

    cout << "������ �߰��Ǿ����ϴ�. ���� ID: " << reservationId << endl;
}

// ���� ���� �Լ�
void ReservationManager::deleteReservation(const string& reservationId) {
    // �ش� ������ �����ϴ��� Ȯ��
    if (reservations.find(reservationId) != reservations.end()) {
        reservations[reservationId].cancelReservation();  // ���¸� ���� (������ ���� X)
        cout << "���� ID: " << reservationId << " �� ��ҵǾ����ϴ�." << endl;
    }
    else {
        cout << "�ش� ���� ID�� ã�� �� �����ϴ�." << endl;
    }
}

// Ư�� ���� ��ȸ �Լ�
Reservation ReservationManager::getReservation(const string& reservationId) {
    if (reservations.find(reservationId) != reservations.end()) {
        return reservations[reservationId];
    }
    else {
        cout << "�ش� ���� ID�� ã�� �� �����ϴ�." << endl;
        return Reservation(); // �⺻ ���� ��ü ��ȯ
    }
}

// Ư�� ���� ��� �Լ�
void ReservationManager::printReservation(const string& reservationId) {
    if (reservations.find(reservationId) != reservations.end()) {
        const Reservation& res = reservations[reservationId];
        cout << "==== ���� ���� ====" << endl;
        cout << "���� ID: " << res.getReservationId() << endl;
        cout << "�� ID: " << res.getCustomerId() << endl;
        cout << "����: " << res.getServiceType() << endl;
        cout << "��¥ �� �ð�: " << res.getDateTime() << endl;
        cout << "����: " << (res.getStatus() == ReservationStatus::Active ? "�����" : "��ҵ�") << endl;
    }
    else {
        cout << "�ش� ���� ID�� ã�� �� �����ϴ�." << endl;
    }
}

// ��ü ���� ��� �Լ�
void ReservationManager::printAllReservations() {
    if (reservations.empty()) {
        cout << "��ϵ� ������ �����ϴ�." << endl;
        return;
    }

    cout << "==== ��ü ���� ��� ====" << endl;
    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;
        cout << "[���� ID: " << res.getReservationId()
            << "] �� ID: " << res.getCustomerId()
            << ", ����: " << res.getServiceType()
            << ", ��¥ �� �ð�: " << res.getDateTime()
            << ", ����: " << (res.getStatus() == ReservationStatus::Active ? "�����" : "��ҵ�")
            << endl;
    }
}
