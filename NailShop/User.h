#pragma once // 헤더 파일이 한 번만 포함되도록 하기

#include <string> // std::string 사용하기

// --- 여기에 UserType enum class 정의 추가하기 ---
// UserType enum class는 사용자 계정의 유형을 정의함
// None: 로그인되지 않거나 알 수 없는 유형
// Customer: 고객 유형
// Employee: 직원 유형
// Owner: 사장 유형
enum class UserType {
    None,       // 초기 상태 또는 로그인되지 않은 상태
    Customer,   // 고객
    Employee,   // 직원
    Owner       // 사장
};
// --- UserType 정의 끝 ---


// User 클래스는 개별 사용자 계정의 정보(ID, 비밀번호, 유형)를 저장함
class User {
public:
    // 생성자: User 객체 생성 시 호출되기
    User(const std::string& userId, const std::string& password, UserType type);

    // 사용자 ID를 반환하는 함수
    std::string getUserId() const;
    // 비밀번호를 반환하는 함수 (보안상 외부 노출 지양, 테스트용)
    std::string getPassword() const;
    // 사용자 유형을 반환하는 함수
    UserType getUserType() const;

    // 입력된 비밀번호가 저장된 비밀번호와 일치하는지 확인하는 함수
    // 반환값: 일치하면 true, 불일치하면 false
    bool checkPassword(const std::string& inputPassword) const;

private:
    // 사용자 ID
    std::string userId;
    // 사용자 비밀번호
    std::string password;
    // 사용자 유형 (UserType enum class 사용)
    UserType type;
};