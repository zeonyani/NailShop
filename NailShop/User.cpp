//User.cpp
#include "User.h"
#include "CSVHandler.h"
#include <iostream>
#include <regex>
#include <algorithm>

// User 기본 생성자
User::User()
    : userId(""), password(""), userType(UserType::None), name(""), phone("") {
}

// User 매개변수 생성자
User::User(const std::string& userId, const std::string& password, UserType userType,
    const std::string& name, const std::string& phone)
    : userId(userId), password(password), userType(userType), name(name) {
    this->phone = normalizePhoneNumber(phone); // 전화번호 정규화하여 저장
}

// Getter 메서드 구현
std::string User::getUserId() const {
    return userId;
}

std::string User::getPassword() const {
    return password;
}

UserType User::getUserType() const {
    return userType;
}

std::string User::getName() const {
    return name;
}

std::string User::getPhone() const {
    return phone;
}

// 형식화된 전화번호 반환 (하이픈 추가)
std::string User::getFormattedPhone() const {
    if (phone.length() == 11) { // 010-XXXX-XXXX
        return phone.substr(0, 3) + "-" + phone.substr(3, 4) + "-" + phone.substr(7, 4);
    }
    else if (phone.length() == 10) { // 0X-XXX-XXXX (서울 02), 0XX-XXX-XXXX (그 외 지역)
        if (phone.rfind("02", 0) == 0) { // 02로 시작하는 경우
            return phone.substr(0, 2) + "-" + phone.substr(2, 4) + "-" + phone.substr(6, 4);
        }
        else { // 그 외 0X로 시작 (세 자리 지역번호)
            return phone.substr(0, 3) + "-" + phone.substr(3, 3) + "-" + phone.substr(6, 4);
        }
    }
    else if (phone.length() == 9) { // 0X-XXXX-XXXX (서울 02)
        if (phone.rfind("02", 0) == 0) {
            return phone.substr(0, 2) + "-" + phone.substr(2, 3) + "-" + phone.substr(5, 4);
        }
    }
    return phone; // 정규화 실패 시 원본 반환
}

// 전화번호 유효성 검사 및 정규화 (하이픈 제거)
std::string User::normalizePhoneNumber(const std::string& rawPhone) {
    std::string digitsOnly;
    for (char c : rawPhone) {
        if (isdigit(c)) {
            digitsOnly += c;
        }
    }

    // 대한민국 전화번호 형식에 대한 간단한 유효성 검사
    // 010-xxxx-xxxx (11자리), 지역번호 포함 일반 전화번호 (9-11자리)
    if ((digitsOnly.length() == 11 && digitsOnly.rfind("010", 0) == 0) ||
        (digitsOnly.length() >= 9 && digitsOnly.length() <= 11)) { // 지역번호 포함 일반 전화번호 (최소 9자리)
        return digitsOnly;
    }
    return ""; // 유효하지 않으면 빈 문자열 반환
}

// CSV 문자열로 변환
std::string User::toCsvString() const {
    std::vector<std::string> fields;
    fields.push_back(userId);
    fields.push_back(password);
    fields.push_back(std::to_string(static_cast<int>(userType))); // UserType을 int로 변환하여 저장
    fields.push_back(name);
    fields.push_back(phone); // 정규화된 전화번호 저장
    return CSVHandler::formatCsvLine(fields);
}

// CSV 문자열로부터 User 객체 생성
User User::fromCsvString(const std::string& csvLine) {
    std::vector<std::string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 5) {
        try {
            std::string userId = fields[0];
            std::string password = fields[1];
            UserType userType = static_cast<UserType>(std::stoi(fields[2])); // int를 UserType으로 변환
            std::string name = fields[3];
            std::string phone = fields[4];
            return User(userId, password, userType, name, phone);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "User::fromCsvString - 숫자 파싱 오류 (Invalid Argument): " << e.what() << " in line: " << csvLine << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "User::fromCsvString - 숫자 범위 오류 (Out of Range): " << e.what() << " in line: " << csvLine << std::endl;
        }
    }
    return User(); // 잘못된 형식 시 기본 User 객체 반환
}

// User::update 메서드 정의 추가
void User::update(const std::string& newPassword, const std::string& newName, const std::string& newPhone) {
    password = newPassword;
    name = newName;
    phone = normalizePhoneNumber(newPhone);
}