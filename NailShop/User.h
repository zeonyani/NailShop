// User.h
#pragma once

#include <string> // std::string 사용
#include <vector> // std::vector

// 사용자 유형
enum class UserType {
    None,       // 초기/로그인 전
    Customer,   // 고객
    Employee,   // 직원
    Owner       // 사장
};

// 사용자 기본 정보
class User {
public:
    // 기본 생성자
    User();

    // 매개변수 생성자
    User(const std::string& userId, const std::string& password, UserType type, const std::string& name, const std::string& phone);

    // 사용자 ID 반환
    std::string getUserId() const;
    // 비밀번호 반환
    std::string getPassword() const;
    // 사용자 유형 반환
    UserType getUserType() const;
    // 비밀번호 일치 확인
    bool checkPassword(const std::string& inputPassword) const;
    // 사용자 이름 반환
    std::string getName() const;
    // 사용자 전화번호 반환 (저장된 원본 형식)
    std::string getPhone() const;
    // 사용자 전화번호 반환 (하이픈 포함 포맷팅)
    std::string getFormattedPhone() const; // 새로 추가: 출력용 포맷팅

    // CSV 문자열 변환
    std::string toCsvString() const;
    // CSV 문자열로부터 User 객체 생성
    static User fromCsvString(const std::string& csvLine);

    // 전화번호 설정 (외부에서 사용)
    void setPhone(const std::string& newPhone); // 새로 추가: 전화번호 설정 메서드

private:
    std::string userId;     // 사용자 고유 ID
    std::string password;   // 사용자 비밀번호
    UserType type;          // 사용자 유형
    std::string name;       // 사용자 실명
    std::string phone;      // 사용자 전화번호 (숫자만 저장)

    // UserType을 문자열로 변환
    static std::string userTypeToString(UserType type);
    // 문자열을 UserType으로 변환
    static UserType stringToUserType(const std::string& typeStr);

    // 전화번호 포맷팅 (내부 유틸리티)
    static std::string formatPhoneNumber(const std::string& phoneNumber); // 새로 추가: 포맷팅
    // 전화번호에서 숫자만 추출 (내부 유틸리티)
    static std::string extractDigits(const std::string& phoneNumber); // 새로 추가: 숫자 추출
    // 전화번호 유효성 검사 (내부 유틸리티)
    static bool isValidPhoneNumber(const std::string& phoneNumber); // 새로 추가: 유효성 검사
};