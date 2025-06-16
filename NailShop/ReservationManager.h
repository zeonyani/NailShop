// ReservationManager.h
#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <map>
#include <string>
#include <vector>
#include <chrono>
#include "Reservation.h" // Reservation 필요
#include "ServiceManager.h" // ServiceManager 필요
#include "CSVHandler.h"

class ReservationManager {
private:
    static const std::string RESERVATIONS_FILE;
    std::map<std::string, Reservation> reservations; // 예약 ID -> Reservation 객체
    const ServiceManager& serviceManager; // ServiceManager 참조
    int nextReservationId; // 다음에 할당될 예약 ID 번호

    void loadReservations();
    void saveReservations(bool silent = false); // silent 매개변수 추가

    std::string generateUniqueId(); // 고유 예약 ID 생성 함수 선언

public:
    ReservationManager(const ServiceManager& svcManager); // 생성자
    ~ReservationManager(); // 소멸자

    // 예약 추가
    bool addReservation(const std::string& customerId, const std::string& serviceName,
        const std::chrono::system_clock::time_point& reservationTime);
    // 예약 취소 (이전의 deleteReservation 대신 사용)
    bool cancelReservation(const std::string& reservationId);
    // 예약 ID로 예약 조회
    const Reservation* getReservation(const std::string& reservationId) const;
    // 특정 고객의 모든 예약 조회
    std::vector<const Reservation*> getReservationsByCustomer(const std::string& customerId) const;
    // 특정 날짜의 모든 예약 조회
    std::vector<const Reservation*> getReservationsByDate(const std::string& dateStr) const;
    // 모든 예약 정보 출력
    void printAllReservations() const; // SystemManager에서 이 함수를 활용
    // 시간 겹침 확인
    bool isTimeSlotAvailable(const std::chrono::system_clock::time_point newStartTime, int newDurationMinutes) const;

    // 모든 예약 목록 반환. SystemManager에서 예약 정보 순회에 사용.
    const std::map<std::string, Reservation>& getAllReservations() const;
};

#endif // RESERVATION_MANAGER_H