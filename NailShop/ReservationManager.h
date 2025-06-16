// ReservationManager.h
#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <map>
#include <string>
#include <vector>
#include <chrono>
#include "Reservation.h" // Reservation �ʿ�
#include "ServiceManager.h" // ServiceManager �ʿ�
#include "CSVHandler.h"

class ReservationManager {
private:
    static const std::string RESERVATIONS_FILE;
    std::map<std::string, Reservation> reservations; // ���� ID -> Reservation ��ü
    const ServiceManager& serviceManager; // ServiceManager ����
    int nextReservationId; // ������ �Ҵ�� ���� ID ��ȣ

    void loadReservations();
    void saveReservations(bool silent = false); // silent �Ű����� �߰�

    std::string generateUniqueId(); // ���� ���� ID ���� �Լ� ����

public:
    ReservationManager(const ServiceManager& svcManager); // ������
    ~ReservationManager(); // �Ҹ���

    // ���� �߰�
    bool addReservation(const std::string& customerId, const std::string& serviceName,
        const std::chrono::system_clock::time_point& reservationTime);
    // ���� ��� (������ deleteReservation ��� ���)
    bool cancelReservation(const std::string& reservationId);
    // ���� ID�� ���� ��ȸ
    const Reservation* getReservation(const std::string& reservationId) const;
    // Ư�� ���� ��� ���� ��ȸ
    std::vector<const Reservation*> getReservationsByCustomer(const std::string& customerId) const;
    // Ư�� ��¥�� ��� ���� ��ȸ
    std::vector<const Reservation*> getReservationsByDate(const std::string& dateStr) const;
    // ��� ���� ���� ���
    void printAllReservations() const; // SystemManager���� �� �Լ��� Ȱ��
    // �ð� ��ħ Ȯ��
    bool isTimeSlotAvailable(const std::chrono::system_clock::time_point newStartTime, int newDurationMinutes) const;

    // ��� ���� ��� ��ȯ. SystemManager���� ���� ���� ��ȸ�� ���.
    const std::map<std::string, Reservation>& getAllReservations() const;
};

#endif // RESERVATION_MANAGER_H