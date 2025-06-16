// Reservation.cpp
#include "Reservation.h"    // Reservation Ŭ����
#include "CSVHandler.h"     // CSVHandler
#include <iostream>         // �ܼ� ���
#include <vector>           // std::vector

using namespace std;        // std:: ���ӽ����̽� ���

// Reservation ������
Reservation::Reservation(const string& reservationId, const string& customerId, const string& service, const string& dateTime)
    : reservationId(reservationId), customerId(customerId), service(service), dateTime(dateTime) {
}

// ���� ID ��ȯ
string Reservation::getReservationId() const {
    return reservationId;
}

// �� ID ��ȯ
string Reservation::getCustomerId() const {
    return customerId;
}

// ���� ���� ��ȯ
string Reservation::getService() const {
    return service;
}

// ���� ��¥ �� �ð� ��ȯ
string Reservation::getDateTime() const {
    return dateTime;
}

// ���� ���� CSV ���ڿ� ��ȯ
string Reservation::toCsvString() const {
    vector<string> fields;
    fields.push_back(reservationId);
    fields.push_back(customerId);
    fields.push_back(service);
    fields.push_back(dateTime);
    return CSVHandler::formatCsvLine(fields);
}

// CSV ���ڿ��κ��� Reservation ��ü ����
Reservation Reservation::fromCsvString(const string& csvLine) {
    vector<string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 4) { // ���� ���� �ʵ� �� (4��)
        return Reservation(fields[0], fields[1], fields[2], fields[3]);
    }
    return Reservation("", "", "", ""); // �߸��� ���� �� �� Reservation ��ü ��ȯ
}