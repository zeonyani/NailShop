#include "Reservation.h"
#include <string>
using namespace std;
int Reservation::nextReservationId = 1; // 정적 변수 초기화, 예약 ID 생성에 사용
Reservation::Reservation(const string& customerId, const string& serviceType, const string& dateTime)
	: customerId(customerId), serviceType(serviceType), dateTime(dateTime), status(ReservationStatus::Active) {
	reservationId = "R" + to_string(nextReservationId++); // 예약 ID 생성, 고유 ID 증가
} // 매개변수 생성자, 예약 상태는 기본적으로 활성화로 설정
string Reservation::getCustomerId() const {
	return customerId;  // 고객 ID 반환
}
string Reservation::getServiceType() const {
	return serviceType; // 서비스 종류 반환
}
string Reservation::getDateTime() const {
	return dateTime;    // 예약 날짜 및 시간 반환
}
void Reservation::changeReservation(const string& newServiceType, const string& newDateTime) {
	serviceType = newServiceType; // 서비스 종류 변경
	dateTime = newDateTime;       // 예약 날짜 및 시간 변경
}
void Reservation::cancelReservation() {
	status = ReservationStatus::Cancelled; // 예약 상태를 취소로 변경
}
string Reservation::getReservationId() const {
	return reservationId; // 예약 ID 반환
}

// 예약 상태를 반환하는 함수
// 예: Active(예약됨), Cancelled(취소됨)
ReservationStatus Reservation::getStatus() const {
	return status;
}
