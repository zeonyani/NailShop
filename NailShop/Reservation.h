//Reservation.h
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>                       // std::string
#include <vector>                       // std::vector
#include <chrono>                       // �ð� ó���� ���� chrono ���̺귯��
#include <iomanip>                      // put_time, get_time �� ������
#include <sstream>                      // stringstream

// ���� ������ ��� Ŭ����
class Reservation {
private:
    std::string reservationId;          // ���� ID (���� �ĺ���)
    std::string customerId;             // ���� �� ID
    std::string serviceName;            // ���� ���� �̸�
    std::chrono::system_clock::time_point reservationTime; // ���� �ð� (std::chrono::time_point ���)

public:
    // �⺻ ������
    Reservation();
    // �Ű����� ������
    Reservation(const std::string& reservationId, const std::string& customerId,
        const std::string& serviceName, const std::string& dateTimeStr);

    // ���� ID ��ȯ
    std::string getReservationId() const;
    // �� ID ��ȯ
    std::string getCustomerId() const;
    // ���� �̸� ��ȯ
    std::string getServiceName() const;
    // ���� �ð� ��ȯ (std::chrono::system_clock::time_point)
    std::chrono::system_clock::time_point getReservationTime() const;

    // ���� �ð��� "YYYY-MM-DD HH:MM" ������ ���ڿ��� ��ȯ (��� �Լ�, �μ��� ���� ����)
    std::string getFormattedDateTime() const;
    // Ư�� time_point�� "YYYY-MM-DD HH:MM" ������ ���ڿ��� ��ȯ (���� �Լ�, time_point �μ��� ����)
    static std::string getFormattedDateTime(const std::chrono::system_clock::time_point& time);

    // CSV ���ڿ��� ��ȯ
    std::string toCsvString() const;
    // CSV ���ڿ��κ��� Reservation ��ü ����
    static Reservation fromCsvString(const std::string& csvLine);

    // ���ڿ��� time_point�� ��ȯ (YYYY-MM-DD HH:MM ���� ����)
    static std::chrono::system_clock::time_point parseDateTime(const std::string& dateTimeStr);
};

#endif // RESERVATION_H