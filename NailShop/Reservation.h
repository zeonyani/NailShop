#pragma once
#include <string>
using namespace std;
enum class ReservationStatus {
	Active,    // 예약됨
	Cancelled, // 취소됨
};

class Reservation {
public:
	// 생성자를 통해 예약 생성
	Reservation() = default; // 기본 생성자
	Reservation(const string& customerId, const string& serviceType, const string& dateTime); // 매개변수 있는 생성자

	// 예약 정보 반환 함수
	string getCustomerId() const;
	string getServiceType() const;
	string getDateTime() const;

	// 예약 변경 함수
	void changeReservation(const string& newServiceType, const string& newDateTime);

	// 예약 취소 함수
	void cancelReservation();

	// 예약 상태 함수(이미 예약이면 추가 못해야 하니까)
	bool isReserved() const;

	// 예약 ID 반환 함수 -> 특정 예약을 찾기 위해 사용(외부에서 특정한 예약을 콕 집으려고)
	string getReservationId() const;

private:
	string reservationId; // 예약 ID -> 효율적으로 특정 예약을 찾도록
	string customerId;  // 고객 ID
	string serviceType; // 서비스 종류
	string dateTime;    // 예약 날짜 및 시간
	ReservationStatus status; // 예약 상태 (예약됨, 취소됨 등)

	static int nextId; // 고유 ID 생성을 위한 정적 변수
};