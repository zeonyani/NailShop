#include "Customer.h"
#include <iostream>
using namespace std;
void Customer::makeReservation(const std::string& service, const std::string& dateTime) {
	// 예약하기 로직 구현
	cout << "고객 " << getName() << " 님이 " << service << " 서비스를 " << dateTime << "에 예약했습니다." << endl;
}
void Customer::cancelReservation(const std::string& reservationId) {
	// 예약 취소하기 로직 구현
	cout << "고객 " <<  getName() << " 님이 예약 ID: " << reservationId << "의 예약을 취소했습니다." << endl;
}
void Customer::viewReservations() const {
	// 예약 목록 보기 로직 구현
	cout << "고객 " << getName() << " 님의 예약 목록입니다." << endl;
	for (int i = 1; i <= 3; ++i) { // 예시로 3개의 예약을 출력
		cout << "예약 " << i << ": 서비스, 날짜 및 시간" << endl;
	}
}
