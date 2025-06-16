// User.cpp
#include "User.h"       // User 클래스
#include "CSVHandler.h" // CSVHandler
#include <iostream>     // 콘솔 출력
#include <vector>       // std::vector
#include <regex>        // 정규 표현식 (전화번호 유효성 검사/포맷팅)

using namespace std;    // std:: 네임스페이스 사용

// UserType 문자열 변환
string User::userTypeToString(UserType type) {
    switch (type) {
    case UserType::Customer: return "Customer";
    case UserType::Employee: return "Employee";
    case UserType::Owner:    return "Owner";
    default:                 return "None";
    }
}

// 문자열 UserType 변환
UserType User::stringToUserType(const string& typeStr) {
    if (typeStr == "Customer") return UserType::Customer;
    if (typeStr == "Employee") return UserType::Employee;
    if (typeStr == "Owner")    return UserType::Owner;
    return UserType::None;
}

// 전화번호에서 숫자만 추출
string User::extractDigits(const string& phoneNumber) {
    string digits;
    for (char c : phoneNumber) {
        if (isdigit(c)) {
            digits += c;
        }
    }
    return digits;
}

// 전화번호 유효성 검사 (하이픈 없이 10-11자리 숫자)
bool User::isValidPhoneNumber(const string& phoneNumber) {
    // 10자리 또는 11자리 숫자인지 확인 (하이픈 포함 여부 관계 없음, extractDigits로 숫자만 추출 후 검사)
    string digits = extractDigits(phoneNumber);
    return digits.length() >= 10 && digits.length() <= 11 &&
        (digits.substr(0, 3) == "010" || digits.substr(0, 2) == "02" || digits.substr(0, 3) == "031" || // 기본적인 번호대 확인 (선택 사항)
            digits.substr(0, 3) == "032" || digits.substr(0, 3) == "033" || digits.substr(0, 3) == "041" ||
            digits.substr(0, 3) == "042" || digits.substr(0, 3) == "043" || digits.substr(0, 3) == "044" ||
            digits.substr(0, 3) == "051" || digits.substr(0, 3) == "052" || digits.substr(0, 3) == "053" ||
            digits.substr(0, 3) == "054" || digits.substr(0, 3) == "055" || digits.substr(0, 3) == "061" ||
            digits.substr(0, 3) == "062" || digits.substr(0, 3) == "063" || digits.substr(0, 3) == "064");
}

// 전화번호 포맷팅 (하이픈 추가)
string User::formatPhoneNumber(const string& phoneNumber) {
    string digits = extractDigits(phoneNumber); // 숫자만 추출

    if (digits.length() == 10) { // 000-000-0000 또는 00-000-0000
        if (digits.rfind("02", 0) == 0) { // 02로 시작하는 10자리 (서울)
            return digits.substr(0, 2) + "-" + digits.substr(2, 4) + "-" + digits.substr(6);
        }
        else { // 01X로 시작하는 10자리 (일반 휴대폰) 또는 다른 지역번호
            return digits.substr(0, 3) + "-" + digits.substr(3, 3) + "-" + digits.substr(6);
        }
    }
    else if (digits.length() == 11) { // 000-0000-0000 (일반 휴대폰)
        return digits.substr(0, 3) + "-" + digits.substr(3, 4) + "-" + digits.substr(7);
    }
    return phoneNumber; // 그 외 형식은 원본 반환
}

// User 기본 생성자
User::User() : userId(""), password(""), type(UserType::None), name(""), phone("") {}

// User 매개변수 생성자
User::User(const string& userId, const string& password, UserType type, const string& name, const string& phone)
    : userId(userId), password(password), type(type), name(name) {
    // 생성자에서도 전화번호 유효성 검사 및 숫자만 저장
    if (isValidPhoneNumber(phone)) {
        this->phone = extractDigits(phone);
    }
    else {
        this->phone = ""; // 유효하지 않으면 빈 문자열 또는 오류 처리
        cerr << "경고: 유효하지 않은 전화번호: " << phone << ". 빈 값으로 저장됨." << endl;
    }
}

// 사용자 ID 반환
string User::getUserId() const {
    return userId;
}

// 비밀번호 반환
string User::getPassword() const {
    return password;
}

// 사용자 유형 반환
UserType User::getUserType() const {
    return type;
}

// 비밀번호 일치 확인
bool User::checkPassword(const string& inputPassword) const {
    return password == inputPassword;
}

// 사용자 이름 반환
string User::getName() const {
    return name;
}

// 사용자 전화번호 반환 (저장된 원본 - 숫자만)
string User::getPhone() const {
    return phone;
}

// 사용자 전화번호 반환 (하이픈 포함 포맷팅)
string User::getFormattedPhone() const {
    return formatPhoneNumber(phone); // 저장된 숫자만 있는 번호를 포맷팅하여 반환
}

// 사용자 정보 CSV 문자열 변환
string User::toCsvString() const {
    vector<string> fields;
    fields.push_back(userId);
    fields.push_back(password);
    fields.push_back(userTypeToString(type)); // UserType 문자열 변환
    fields.push_back(name);
    fields.push_back(phone); // CSV에는 숫자만 있는 형태로 저장
    return CSVHandler::formatCsvLine(fields);
}

// CSV 문자열로부터 User 객체 생성
User User::fromCsvString(const string& csvLine) {
    vector<string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 5) {
        UserType parsedType = stringToUserType(fields[2]);
        // CSV에서 읽어올 때도 유효성 검사를 하지만, 이미 저장된 데이터이므로 주로 숫자 추출만
        string loadedPhone = extractDigits(fields[4]); // CSV에서 읽어온 전화번호 숫자만 추출
        if (!isValidPhoneNumber(loadedPhone)) { // 다시 한번 유효성 검사
            cerr << "경고: CSV에서 읽어온 전화번호가 유효하지 않음: " << fields[4] << ". 빈 값으로 로드됨." << endl;
            loadedPhone = "";
        }
        return User(fields[0], fields[1], parsedType, fields[3], loadedPhone);
    }
    return User(); // 잘못된 형식 시 기본 User 객체 반환
}

// 전화번호 설정 (유효성 검사 후 숫자만 저장)
void User::setPhone(const string& newPhone) {
    if (isValidPhoneNumber(newPhone)) {
        this->phone = extractDigits(newPhone);
    }
    else {
        // 유효하지 않은 경우, 기존 값 유지 또는 오류 처리
        cout << "오류: 유효하지 않은 전화번호 형식. 전화번호 변경 실패." << endl;
    }
}