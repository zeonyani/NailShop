//Resrevation.cpp
#include "Reservation.h"    // Reservation Ŭ����
#include "CSVHandler.h"     // CSVHandler
#include <iostream>         // �ܼ� ��� (������)
#include <ctime>            // std::tm, mktime
#include <limits>           // numeric_limits
#include <iomanip>          // std::put_time, std::get_time
#include <sstream>          // std::stringstream

// Reservation �⺻ ������
Reservation::Reservation()
    : reservationId(""), customerId(""), serviceName(""), reservationTime(std::chrono::system_clock::time_point()) {
}

// Reservation �Ű����� ������
Reservation::Reservation(const std::string& reservationId, const std::string& customerId,
    const std::string& serviceName, const std::string& dateTimeStr)
    : reservationId(reservationId), customerId(customerId), serviceName(serviceName) {
    reservationTime = parseDateTime(dateTimeStr);
}

// ���� ID ��ȯ
std::string Reservation::getReservationId() const {
    return reservationId;
}

// �� ID ��ȯ
std::string Reservation::getCustomerId() const {
    return customerId;
}

// ���� �̸� ��ȯ
std::string Reservation::getServiceName() const {
    return serviceName;
}

// ���� �ð� ��ȯ (std::chrono::system_clock::time_point)
std::chrono::system_clock::time_point Reservation::getReservationTime() const {
    return reservationTime;
}

// ���� �ð��� "YYYY-MM-DD HH:MM" ������ ���ڿ��� ��ȯ (��� �Լ�)
std::string Reservation::getFormattedDateTime() const {
    return getFormattedDateTime(reservationTime); // ���� ���� �Լ� ȣ��
}

// Ư�� time_point�� "YYYY-MM-DD HH:MM" ������ ���ڿ��� ��ȯ (���� �Լ�)
std::string Reservation::getFormattedDateTime(const std::chrono::system_clock::time_point& time) {
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm t = {};
    localtime_s(&t, &tt); // ������ ������ localtime_s ��� (Windows)
    // ������/macOS�� ���: localtime_r(&tt, &t);
    std::stringstream ss;
    ss << std::put_time(&t, "%Y-%m-%d %H:%M");
    return ss.str();
}

// CSV ���ڿ��� ��ȯ
std::string Reservation::toCsvString() const {
    std::vector<std::string> fields;
    fields.push_back(reservationId);
    fields.push_back(customerId);
    fields.push_back(serviceName);
    fields.push_back(getFormattedDateTime(reservationTime)); // ���� �Լ� ���
    return CSVHandler::formatCsvLine(fields);
}

// CSV ���ڿ��κ��� Reservation ��ü ����
Reservation Reservation::fromCsvString(const std::string& csvLine) {
    std::vector<std::string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 4) {
        return Reservation(fields[0], fields[1], fields[2], fields[3]);
    }
    return Reservation(); // �߸��� ���� �� �⺻ Reservation ��ü ��ȯ
}

// ���ڿ��� time_point�� ��ȯ (YYYY-MM-DD HH:MM ���� ����) - ���� �Լ�
std::chrono::system_clock::time_point Reservation::parseDateTime(const std::string& dateTimeStr) {
    std::tm t = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M"); // YYYY-MM-DD HH:MM �������� �Ľ�

    if (ss.fail()) {
        // std::cerr << "���: ��¥/�ð� �Ľ� ����: " << dateTimeStr << std::endl; // �ּ� ó��
        return std::chrono::system_clock::time_point(); // ��ȿ���� ���� �ð� ��ȯ
    }

    t.tm_isdst = -1; // �ϱ� ���� �ð� (DST) �ڵ� ����
    std::time_t tt = std::mktime(&t); // tm ����ü�� time_t�� ��ȯ
    if (tt == -1) {
        // std::cerr << "���: time_t ��ȯ ���� (��ȿ���� ���� ��¥/�ð�): " << dateTimeStr << std::endl; // �ּ� ó��
        return std::chrono::system_clock::time_point();
    }
    return std::chrono::system_clock::from_time_t(tt); // time_t�� time_point�� ��ȯ
}