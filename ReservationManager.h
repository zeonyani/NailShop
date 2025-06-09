#pragma once
#include <string>
#include "Reservation.h"
using namespace std;

class ReservationManager {
public:
	ReservationManager() = default;
	
	// CRUD 관련 함수
	void addReservation(const string& id, const string& service, const string& datetime); // 예약 추가
	void deleteReservation(string& reservationid); // 예약 삭제
	Reservation getReservation(const string& reservationid); // 예약 반환
	void printReservation(const string& reservationid); // 해당 예약 출력
	void printAllReservations(); // 전체 예약 내역 출력
	
	// 예약 존재 여부 확인 함수
	bool checkReservation(const string& reservationid);

	// 오류메시지 출력 함수
	void showMessage(const string& reservationid);

	~ReservationManager() = default;
};