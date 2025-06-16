#pragma once
#include <string>
#include <map>
#include "Reservation.h"

class ReservationManager {
public:
    // ���� �߰�
    void addReservation(const std::string& customerId, const std::string& service, const std::string& datetime);

    // ���� ���� (���)
    void deleteReservation(const std::string& reservationId);

    // Ư�� ���� ��ȯ
    Reservation getReservation(const std::string& reservationId);

    // Ư�� ���� ���
    void printReservation(const std::string& reservationId);

    // ��ü ���� ���
    void printAllReservations();

private:
    // ���� ID �� Reservation ��ü ����
    std::map<std::string, Reservation> reservations;
};
