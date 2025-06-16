// Reservation.h
#pragma once

#include <string> // std::string ���

// ���� ���� ����
class Reservation {
public:
    // ���� ������
    Reservation(const std::string& reservationId, const std::string& customerId, const std::string& service, const std::string& dateTime);

    // ���� ID ��ȯ
    std::string getReservationId() const;
    // �� ID ��ȯ
    std::string getCustomerId() const;
    // ���� ���� ��ȯ
    std::string getService() const;
    // ���� ��¥ �� �ð� ��ȯ
    std::string getDateTime() const;

    // CSV ���ڿ� ��ȯ
    std::string toCsvString() const;
    // CSV ���ڿ��κ��� Reservation ��ü ����
    static Reservation fromCsvString(const std::string& csvLine);

private:
    std::string reservationId;  // ���� ���� ID
    std::string customerId;     // �� ID
    std::string service;        // ���� ����
    std::string dateTime;       // ���� ��¥/�ð�
};