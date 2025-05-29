#pragma once
#include <map>
#include <string>
#include "Reservation.h"
using namespace std;

class ReservationManager {
public:
	ReservationManager() = default; // 기본 생성자
	ReservationManager(const ReservationManager&) = delete; // 복사 생성자 삭제
	
private:
	map<string, Reservation> reservations; // 예약 ID를 키로 하는 예약 정보 맵



};