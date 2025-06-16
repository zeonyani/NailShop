#pragma once
#include <string>
#include <map>
#include "Reservation.h"

class ReservationManager {
public:
    // 예약 추가
    void addReservation(const std::string& customerId, const std::string& service, const std::string& datetime);

    // 예약 삭제 (취소)
    void deleteReservation(const std::string& reservationId);

    // 특정 예약 반환
    Reservation getReservation(const std::string& reservationId);

    // 특정 예약 출력
    void printReservation(const std::string& reservationId);

    // 전체 예약 출력
    void printAllReservations();

private:
    // 예약 ID → Reservation 객체 매핑
    std::map<std::string, Reservation> reservations;
};
