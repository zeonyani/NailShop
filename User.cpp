#include "User.h"
using namespace std;
string User::getId() const {
	return id;  // 아이디 반환
}
string User::getName() const {
	return name;  // 이름 반환
}
string User::getPhone() const {
	return phone;  // 전화번호 반환
}
bool User::checkPw(const std::string& password) const {
	return pw == password;  // 비밀번호 비교
}
void User::setPhone(const std::string& phoneNumber) {
	phone = phoneNumber;  // 전화번호 설정
}