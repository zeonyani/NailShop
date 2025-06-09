#pragma once
#include <string>

using namespace std;
class User {
public:
	User() = default;  // 기본 생성자
	User(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone)
		: id(id), pw(pw), name(name), phone(phone) {
	}  // 매개변수 생성자
    // 아이디, 이름, 폰번호를 가져오는 함수들
    string getId() const;
    string getName() const;
    string getPhone() const;

	// 비밀번호 외부에서 가져갈 수 없는 것이 타당(보안상) -> 비교만 거칠 수 있도록!
    bool checkPw(const std::string& password) const;
    
    // 전화번호 설정 함수는 유저가 바꿀 수 있도록 해야함(전화번호는 자주 바뀌니)
    void setPhone(const std::string& phoneNumber);

    virtual ~User() = default;  // 가상 소멸자

private:
    std::string id;
    std::string pw;
    std::string name;
    std::string phone;
};
