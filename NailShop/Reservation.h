//Reservation.h
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>                       // std::string
#include <vector>                       // std::vector
#include <chrono>                       // 시간 처리를 위한 chrono 라이브러리
#include <iomanip>                      // put_time, get_time 등 포맷팅
#include <sstream>                      // stringstream

// 예약 정보를 담는 클래스
class Reservation {
private:
    std::string reservationId;          // 예약 ID (고유 식별자)
    std::string customerId;             // 예약 고객 ID
    std::string serviceName;            // 예약 서비스 이름
    std::chrono::system_clock::time_point reservationTime; // 예약 시간 (std::chrono::time_point 사용)

public:
    // 기본 생성자
    Reservation();
    // 매개변수 생성자
    Reservation(const std::string& reservationId, const std::string& customerId,
        const std::string& serviceName, const std::string& dateTimeStr);

    // 예약 ID 반환
    std::string getReservationId() const;
    // 고객 ID 반환
    std::string getCustomerId() const;
    // 서비스 이름 반환
    std::string getServiceName() const;
    // 예약 시간 반환 (std::chrono::system_clock::time_point)
    std::chrono::system_clock::time_point getReservationTime() const;

    // 예약 시간을 "YYYY-MM-DD HH:MM" 형식의 문자열로 반환 (멤버 함수, 인수를 받지 않음)
    std::string getFormattedDateTime() const;
    // 특정 time_point를 "YYYY-MM-DD HH:MM" 형식의 문자열로 변환 (정적 함수, time_point 인수를 받음)
    static std::string getFormattedDateTime(const std::chrono::system_clock::time_point& time);

    // CSV 문자열로 변환
    std::string toCsvString() const;
    // CSV 문자열로부터 Reservation 객체 생성
    static Reservation fromCsvString(const std::string& csvLine);

    // 문자열을 time_point로 변환 (YYYY-MM-DD HH:MM 형식 예상)
    static std::chrono::system_clock::time_point parseDateTime(const std::string& dateTimeStr);
};

#endif // RESERVATION_H