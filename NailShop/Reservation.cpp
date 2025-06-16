// Reservation.cpp
#include "Reservation.h"    // Reservation 클래스
#include "CSVHandler.h"     // CSVHandler
#include <iostream>         // 콘솔 출력
#include <vector>           // std::vector

using namespace std;        // std:: 네임스페이스 사용

// Reservation 생성자
Reservation::Reservation(const string& reservationId, const string& customerId, const string& service, const string& dateTime)
    : reservationId(reservationId), customerId(customerId), service(service), dateTime(dateTime) {
}

// 예약 ID 반환
string Reservation::getReservationId() const {
    return reservationId;
}

// 고객 ID 반환
string Reservation::getCustomerId() const {
    return customerId;
}

// 서비스 종류 반환
string Reservation::getService() const {
    return service;
}

// 예약 날짜 및 시간 반환
string Reservation::getDateTime() const {
    return dateTime;
}

// 예약 정보 CSV 문자열 변환
string Reservation::toCsvString() const {
    vector<string> fields;
    fields.push_back(reservationId);
    fields.push_back(customerId);
    fields.push_back(service);
    fields.push_back(dateTime);
    return CSVHandler::formatCsvLine(fields);
}

// CSV 문자열로부터 Reservation 객체 생성
Reservation Reservation::fromCsvString(const string& csvLine) {
    vector<string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 4) { // 예약 정보 필드 수 (4개)
        return Reservation(fields[0], fields[1], fields[2], fields[3]);
    }
    return Reservation("", "", "", ""); // 잘못된 형식 시 빈 Reservation 객체 반환
}