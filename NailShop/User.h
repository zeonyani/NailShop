//User.h
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <sstream>

// 사용자 유형 열거형
enum class UserType {
    None,       // 초기값 또는 알 수 없는 유형
    Customer,   // 고객
    Employee,   // 직원
    Owner       // 사장
};

// 사용자 정보를 담는 기본 클래스
class User {
private:
    std::string userId;     // 사용자 ID (고유 식별자)
    std::string password;   // 비밀번호
    UserType userType;      // 사용자 유형 (고객, 직원, 사장)
    std::string name;       // 이름
    std::string phone;      // 전화번호

public:
    // 전화번호 유효성 검사 및 정규화 (static으로 변경)
    static std::string normalizePhoneNumber(const std::string& rawPhone);

public:
    // 기본 생성자
    User();
    // 매개변수 생성자
    User(const std::string& userId, const std::string& password, UserType userType,
        const std::string& name, const std::string& phone);

    // Getter 메서드
    std::string getUserId() const;
    std::string getPassword() const;
    UserType getUserType() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getFormattedPhone() const;

    // Setter 메서드 (선택적으로 개별적으로 추가하거나, update 함수를 사용)
    void setPassword(const std::string& newPassword) { password = newPassword; }
    void setName(const std::string& newName) { name = newName; }
    void setPhone(const std::string& newPhone) { phone = normalizePhoneNumber(newPhone); }

    // 사용자 정보 업데이트 메서드 추가
    void update(const std::string& newPassword, const std::string& newName, const std::string& newPhone);

    // CSV 문자열로 변환
    std::string toCsvString() const;
    // CSV 문자열로부터 User 객체 생성
    static User fromCsvString(const std::string& csvLine);
};

#endif // USER_H