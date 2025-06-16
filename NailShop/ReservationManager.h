// ReservationManager.h
#pragma once

#include <string>   // std::string
#include <map>      // std::map
#include <vector>   // std::vector
#include "Reservation.h" // Reservation Ŭ����
#include "CSVHandler.h" // CSVHandler

// ���� ����
class ReservationManager {
public:
    // ReservationManager ������
    ReservationManager();
    // ReservationManager �Ҹ���
    ~ReservationManager();

    // �� ���� �߰�
    bool addReservation(const std::string& customerId, const std::string& service, const std::string& dateTime);

    // ���� ���� ����
    bool deleteReservation(const std::string& reservationId);

    // Ư�� ���� ���� ���
    void printReservation(const std::string& reservationId) const;

    // Ư�� ���� ���� ��ȸ (��ü ��ȯ)
    const Reservation* getReservation(const std::string& reservationId) const;

    // ��� ���� ���� ���
    void printAllReservations() const;

    // Ư�� ���� ���� ���
    void printReservationsByCustomerId(const std::string& customerId) const;

    // Ư�� ��¥�� ���� ���
    void printReservationsForDate(const std::string& date) const;

private:
    std::map<std::string, Reservation> reservations; // ���� ID-Reservation ��
    int nextReservationId; // ���� ���� ID ī����
    const std::string RESERVATIONS_FILE = "reservations.csv"; // ���� ������ ���� ���

    // ���� ���� ID ����
    std::string generateUniqueId();
    // CSV ���Ϸκ��� ���� ������ �ε�
    void loadReservations();
    // CSV ���Ͽ� ���� ������ ����
    void saveReservations();
};