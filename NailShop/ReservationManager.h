// ReservationManager.h
#pragma once

#include <string>   // std::string
#include <map>      // std::map
#include <vector>   // std::vector
#include "Reservation.h" // Reservation 클래스
#include "CSVHandler.h" // CSVHandler

// 예약 관리
class ReservationManager {
public:
    // ReservationManager 생성자
    ReservationManager();
    // ReservationManager 소멸자
    ~ReservationManager();

    // 새 예약 추가
    bool addReservation(const std::string& customerId, const std::string& service, const std::string& dateTime);

    // 기존 예약 삭제
    bool deleteReservation(const std::string& reservationId);

    // 특정 예약 정보 출력
    void printReservation(const std::string& reservationId) const;

    // 특정 예약 정보 조회 (객체 반환)
    const Reservation* getReservation(const std::string& reservationId) const;

    // 모든 예약 정보 출력
    void printAllReservations() const;

    // 특정 고객의 예약 출력
    void printReservationsByCustomerId(const std::string& customerId) const;

    // 특정 날짜의 예약 출력
    void printReservationsForDate(const std::string& date) const;

private:
    std::map<std::string, Reservation> reservations; // 예약 ID-Reservation 맵
    int nextReservationId; // 다음 예약 ID 카운터
    const std::string RESERVATIONS_FILE = "reservations.csv"; // 예약 데이터 파일 경로

    // 고유 예약 ID 생성
    std::string generateUniqueId();
    // CSV 파일로부터 예약 데이터 로드
    void loadReservations();
    // CSV 파일에 예약 데이터 저장
    void saveReservations();
};