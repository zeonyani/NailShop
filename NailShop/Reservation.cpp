//Resrevation.cpp
#include "Reservation.h"    // Reservation 클래스
#include "CSVHandler.h"     // CSVHandler
#include <iostream>         // 콘솔 출력 (디버깅용)
#include <ctime>            // std::tm, mktime
#include <limits>           // numeric_limits
#include <iomanip>          // std::put_time, std::get_time
#include <sstream>          // std::stringstream

// Reservation 기본 생성자
Reservation::Reservation()
    : reservationId(""), customerId(""), serviceName(""), reservationTime(std::chrono::system_clock::time_point()) {
}

// Reservation 매개변수 생성자
Reservation::Reservation(const std::string& reservationId, const std::string& customerId,
    const std::string& serviceName, const std::string& dateTimeStr)
    : reservationId(reservationId), customerId(customerId), serviceName(serviceName) {
    reservationTime = parseDateTime(dateTimeStr);
}

// 예약 ID 반환
std::string Reservation::getReservationId() const {
    return reservationId;
}

// 고객 ID 반환
std::string Reservation::getCustomerId() const {
    return customerId;
}

// 서비스 이름 반환
std::string Reservation::getServiceName() const {
    return serviceName;
}

// 예약 시간 반환 (std::chrono::system_clock::time_point)
std::chrono::system_clock::time_point Reservation::getReservationTime() const {
    return reservationTime;
}

// 예약 시간을 "YYYY-MM-DD HH:MM" 형식의 문자열로 반환 (멤버 함수)
std::string Reservation::getFormattedDateTime() const {
    return getFormattedDateTime(reservationTime); // 정적 헬퍼 함수 호출
}

// 특정 time_point를 "YYYY-MM-DD HH:MM" 형식의 문자열로 변환 (정적 함수)
std::string Reservation::getFormattedDateTime(const std::chrono::system_clock::time_point& time) {
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm t = {};
    localtime_s(&t, &tt); // 스레드 안전한 localtime_s 사용 (Windows)
    // 리눅스/macOS의 경우: localtime_r(&tt, &t);
    std::stringstream ss;
    ss << std::put_time(&t, "%Y-%m-%d %H:%M");
    return ss.str();
}

// CSV 문자열로 변환
std::string Reservation::toCsvString() const {
    std::vector<std::string> fields;
    fields.push_back(reservationId);
    fields.push_back(customerId);
    fields.push_back(serviceName);
    fields.push_back(getFormattedDateTime(reservationTime)); // 정적 함수 사용
    return CSVHandler::formatCsvLine(fields);
}

// CSV 문자열로부터 Reservation 객체 생성
Reservation Reservation::fromCsvString(const std::string& csvLine) {
    std::vector<std::string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 4) {
        return Reservation(fields[0], fields[1], fields[2], fields[3]);
    }
    return Reservation(); // 잘못된 형식 시 기본 Reservation 객체 반환
}

// 문자열을 time_point로 변환 (YYYY-MM-DD HH:MM 형식 예상) - 정적 함수
std::chrono::system_clock::time_point Reservation::parseDateTime(const std::string& dateTimeStr) {
    std::tm t = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M"); // YYYY-MM-DD HH:MM 형식으로 파싱

    if (ss.fail()) {
        // std::cerr << "경고: 날짜/시간 파싱 실패: " << dateTimeStr << std::endl; // 주석 처리
        return std::chrono::system_clock::time_point(); // 유효하지 않은 시간 반환
    }

    t.tm_isdst = -1; // 일광 절약 시간 (DST) 자동 결정
    std::time_t tt = std::mktime(&t); // tm 구조체를 time_t로 변환
    if (tt == -1) {
        // std::cerr << "경고: time_t 변환 실패 (유효하지 않은 날짜/시간): " << dateTimeStr << std::endl; // 주석 처리
        return std::chrono::system_clock::time_point();
    }
    return std::chrono::system_clock::from_time_t(tt); // time_t를 time_point로 변환
}