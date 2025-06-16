#include "Reservation.h"
#include "ReservationManager.h"
#include <iostream>
#include <map>
using namespace std;

// 예약 추가 함수
void ReservationManager::addReservation(const string& customerId, const string& service, const string& datetime) {
    // 새로운 예약 객체 생성
    Reservation newReservation(customerId, service, datetime);
    string reservationId = newReservation.getReservationId();

    // map에 예약 ID를 키로 저장
    reservations[reservationId] = newReservation;

    cout << "예약이 추가되었습니다. 예약 ID: " << reservationId << endl;
}

// 예약 삭제 함수
void ReservationManager::deleteReservation(const string& reservationId) {
    // 해당 예약이 존재하는지 확인
    if (reservations.find(reservationId) != reservations.end()) {
        reservations[reservationId].cancelReservation();  // 상태만 변경 (물리적 삭제 X)
        cout << "예약 ID: " << reservationId << " 가 취소되었습니다." << endl;
    }
    else {
        cout << "해당 예약 ID를 찾을 수 없습니다." << endl;
    }
}

// 특정 예약 조회 함수
Reservation ReservationManager::getReservation(const string& reservationId) {
    if (reservations.find(reservationId) != reservations.end()) {
        return reservations[reservationId];
    }
    else {
        cout << "해당 예약 ID를 찾을 수 없습니다." << endl;
        return Reservation(); // 기본 예약 객체 반환
    }
}

// 특정 예약 출력 함수
void ReservationManager::printReservation(const string& reservationId) {
    if (reservations.find(reservationId) != reservations.end()) {
        const Reservation& res = reservations[reservationId];
        cout << "==== 예약 정보 ====" << endl;
        cout << "예약 ID: " << res.getReservationId() << endl;
        cout << "고객 ID: " << res.getCustomerId() << endl;
        cout << "서비스: " << res.getServiceType() << endl;
        cout << "날짜 및 시간: " << res.getDateTime() << endl;
        cout << "상태: " << (res.getStatus() == ReservationStatus::Active ? "예약됨" : "취소됨") << endl;
    }
    else {
        cout << "해당 예약 ID를 찾을 수 없습니다." << endl;
    }
}

// 전체 예약 출력 함수
void ReservationManager::printAllReservations() {
    if (reservations.empty()) {
        cout << "등록된 예약이 없습니다." << endl;
        return;
    }

    cout << "==== 전체 예약 목록 ====" << endl;
    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;
        cout << "[예약 ID: " << res.getReservationId()
            << "] 고객 ID: " << res.getCustomerId()
            << ", 서비스: " << res.getServiceType()
            << ", 날짜 및 시간: " << res.getDateTime()
            << ", 상태: " << (res.getStatus() == ReservationStatus::Active ? "예약됨" : "취소됨")
            << endl;
    }
}
