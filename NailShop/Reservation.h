// Reservation.h
#pragma once

#include <string> // std::string 사용

// 단일 예약 정보
class Reservation {
public:
    // 예약 생성자
    Reservation(const std::string& reservationId, const std::string& customerId, const std::string& service, const std::string& dateTime);

    // 예약 ID 반환
    std::string getReservationId() const;
    // 고객 ID 반환
    std::string getCustomerId() const;
    // 서비스 종류 반환
    std::string getService() const;
    // 예약 날짜 및 시간 반환
    std::string getDateTime() const;

    // CSV 문자열 변환
    std::string toCsvString() const;
    // CSV 문자열로부터 Reservation 객체 생성
    static Reservation fromCsvString(const std::string& csvLine);

private:
    std::string reservationId;  // 예약 고유 ID
    std::string customerId;     // 고객 ID
    std::string service;        // 서비스 종류
    std::string dateTime;       // 예약 날짜/시간
};