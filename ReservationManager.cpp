#include "Reservation.h"
#include "ReservationManager.h"
#include <iostream>
#include <map>

void ReservationManager::addReservation(const string& id, const string& service, const string& datetime){
	// 예약이 이미 존재하는지 확인
	if (reservations.find(id) != reservations.end()) {
		cout << "이미 예약이 존재합니다." << endl; // 예약이 이미 존재할 경우
		return;
	}

	// 새로운 예약 생성
	Reservation newReservation(id, service, datetime);
	reservations[id] = newReservation; // 예약 추가
	cout << "예약이 추가되었습니다." << endl;
}

void ReservationManager::deleteReservation(const string& reservationid) {
	// 예약이 존재하는지 확인
	if (reservations.find(reservationid) != reservations.end()) {
		reservations.erase(reservationid); // 예약 삭제
		cout << "예약이 삭제되었습니다." << endl;
	}
	else {
		cout << "예약이 존재하지 않습니다." << endl; // 예약이 존재하지 않을 경우
	}
}
Reservation ReservationManager::getReservation(const string& reservationid) {
	// 예약이 존재하는지 확인
	if (reservations.find(reservationid) != reservations.end()) {
		return reservations[reservationid]; // 예약 반환
	}
	else {
		cout << "예약이 존재하지 않습니다." << endl; // 예약이 존재하지 않을 경우
		return Reservation(); // 빈 Reservation 객체 반환
	}
}
void ReservationManager::printReservation(const string& reservationid) {
	// 예약이 존재하는지 확인
	if (reservations.find(reservationid) != reservations.end()) {
		Reservation res = reservations[reservationid];
		cout << "예약 ID: " << res.getId() << endl;
		cout << "서비스: " << res.getService() << endl;
		cout << "날짜 및 시간: " << res.getDatetime() << endl;
	}
	else {
		cout << "예약이 존재하지 않습니다." << endl; // 예약이 존재하지 않을 경우
	}
}
void ReservationManager::printAllReservation(const string& reservationid) {
	// 모든 예약을 출력
	for (const auto& pair : reservations) {
		const Reservation& res = pair.second;
		cout << "예약 ID: " << res.getId() << ", 서비스: " << res.getService() << ", 날짜 및 시간: " << res.getDatetime() << endl;
	}
}