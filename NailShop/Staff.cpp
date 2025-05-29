#include "Staff.h"
#include <iostream>
using namespace std;
void Staff::showTodaySchedule() const {
	// 오늘 예약 보여주기 로직 구현
	cout << "오늘의 예약 목록입니다." << endl;
	for (int i = 1; i <= 5; ++i) { // 예시로 5개의 예약을 출력
		cout << "예약 " << i << ": 고객 이름, 시간, 서비스" << endl;
	}
}
void Staff::searchCustomer(const std::string& customerId) const {
	// 고객 검색 로직 구현
	cout << "고객 ID: " << customerId << "에 대한 정보를 검색합니다." << endl;
}

