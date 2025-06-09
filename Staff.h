#pragma once
#include "User.h"
#include <string>

class Staff : public User {
public:
	Staff() : User() {}  // 기본 생성자 정의, User의 기본 생성자를 호출
	Staff(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone)
		: User(id, pw, name, phone) {
	}  // 매개변수 생성자 정의, User의 매개변수 생성자를 호출
// Staff 클래스는 User 클래스로부터 상속받은 모든 함수들을 사용할 수 있음

// 추가적인 Staff 전용 함수
	void showTodaySchedule() const; // 오늘 예약 보여주기
	void searchCustomer(const std::string& customerId) const; // 고객 검색

	virtual ~Staff() = default;  // 가상 소멸자
};