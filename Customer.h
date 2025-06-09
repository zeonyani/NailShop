#pragma once
#include "User.h"
#include <string>
#include <vector>

using namespace std;
class Customer : public User {
public:
	Customer() : User() {}  // 기본 생성자 정의, User의 기본 생성자를 호출
	Customer(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone)
		: User(id, pw, name, phone) {
	}  // 매개변수 생성자 정의, User의 매개변수 생성자를 호출
	// 추가적인 Customer 전용 함수
	void makeReservation(const std::string& service, const std::string& dateTime); // 예약하기
	void cancelReservation(const std::string& reservationId); // 예약 취소하기
	void viewReservations() const; // 예약 목록 보기
	virtual ~Customer() = default;  // 가상 소멸자
};
