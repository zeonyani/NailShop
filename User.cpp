#include "User.h"
using namespace std;
string User::getId() const {
	return id;  // ���̵� ��ȯ
}
string User::getName() const {
	return name;  // �̸� ��ȯ
}
string User::getPhone() const {
	return phone;  // ��ȭ��ȣ ��ȯ
}
bool User::checkPw(const std::string& password) const {
	return pw == password;  // ��й�ȣ ��
}
void User::setPhone(const std::string& phoneNumber) {
	phone = phoneNumber;  // ��ȭ��ȣ ����
}