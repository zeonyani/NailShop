#pragma once
#include "User.h"
#include <string>

using namespace std;
class Admin : public User {
public:
	Admin() : User() {}  // 기본 생성자 정의, User의 기본 생성자를 호출
	Admin(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone)
		: User(id, pw, name, phone) {
	}  // 매개변수 생성자 정의, User의 매개변수 생성자를 호출
	// Staff 클래스는 User 클래스로부터 상속받은 모든 함수들을 사용할 수 있음

	// Staff 전용 함수와 동일한 부분
	void showTodaySchedule() const; // 오늘 예약 보여주기
	void searchCustomer(const std::string& customerId) const; // 고객 검색

	// 관리자 전용 함수
	void manageStaff() const; // 직원 관리
	void manageCustomers() const; // 고객 관리
	void manageReservations() const; // 예약 관리
	void removeStaff(const string& staffId); // 직원 삭제 (내부가 바뀌므로 const를 빼야함, 이하 동일)
	void removeCustomer(const string& customerId); // 고객 삭제
	void removeReservation(const string& reservationId); // 예약 삭제

	virtual ~Admin() = default;  // 가상 소멸자
};