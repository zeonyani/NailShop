// UserManager.cpp
#include "UserManager.h"    // UserManager 클래스
#include <iostream>         // 콘솔 출력
#include <fstream>          // 파일 입출력
#include <iomanip>          // 출력 포맷팅

using namespace std;        // std:: 네임스페이스 사용

// UserManager 생성자
UserManager::UserManager() {
    cout << "UserManager 초기화. 사용자 데이터 로드 중..." << endl;
    loadUsers(); // 사용자 데이터 로드
}

// UserManager 소멸자
UserManager::~UserManager() {
    cout << "UserManager 종료. 사용자 데이터 저장 중..." << endl;
    saveUsers(); // 사용자 데이터 저장
}

// CSV 파일로부터 사용자 데이터 로드
void UserManager::loadUsers() {
    vector<string> userLines = CSVHandler::readCsv(USERS_FILE);
    if (userLines.empty()) {
        cout << "사용자 데이터 파일 없음/비어있음. 새 파일 생성 가능." << endl;
        return;
    }

    for (const string& line : userLines) {
        User user = User::fromCsvString(line);
        if (user.getUserId() != "") { // 유효한 사용자 정보 추가
            users.emplace(user.getUserId(), user);
        }
    }
    cout << "총 " << users.size() << "명 사용자 데이터 로드 완료." << endl;
}

// CSV 파일에 사용자 데이터 저장
void UserManager::saveUsers() {
    vector<string> dataToSave;
    for (const auto& pair : users) {
        dataToSave.push_back(pair.second.toCsvString());
    }
    CSVHandler::writeCsv(USERS_FILE, dataToSave);
    cout << "총 " << users.size() << "명 사용자 데이터 저장 완료." << endl;
}

// 사용자 추가
bool UserManager::addUser(const string& userId, const string& password, UserType type, const string& name, const string& phone) {
    // ID 중복 확인
    if (users.find(userId) == users.end()) {
        // User 생성자에서 전화번호 유효성 검사 및 숫자만 저장 처리
        User newUser(userId, password, type, name, phone);
        if (newUser.getPhone().empty() && !phone.empty()) { // 유효하지 않은 전화번호가 입력되었을 경우
            cout << "오류: 입력된 전화번호가 유효하지 않아 사용자 추가 실패." << endl;
            return false;
        }
        users.emplace(userId, newUser);
        saveUsers(); // 파일에 저장
        return true;
    }
    else {
        cout << "오류: 사용자 ID '" << userId << "' 이미 존재." << endl;
        return false;
    }
}

// 로그인
UserType UserManager::login(const string& userId, const string& password) {
    auto it = users.find(userId); // 사용자 ID 검색
    if (it != users.end()) { // 사용자 ID 존재
        if (it->second.checkPassword(password)) { // 비밀번호 일치
            cout << it->second.getName() << "님 환영합니다! (" <<
                (it->second.getUserType() == UserType::Owner ? "사장" :
                    it->second.getUserType() == UserType::Employee ? "직원" : "고객")
                << " 권한)" << endl;
            return it->second.getUserType(); // 사용자 유형 반환
        }
        else {
            cout << "로그인 실패: 비밀번호 불일치." << endl;
            return UserType::None; // 비밀번호 불일치
        }
    }
    else {
        cout << "로그인 실패: 사용자 ID '" << userId << "' 없음." << endl;
        return UserType::None; // 사용자 ID 없음
    }
}

// User 객체 조회 (상수)
const User* UserManager::getUser(const string& userId) const {
    auto it = users.find(userId); // 사용자 ID 검색
    if (it != users.end()) { // 사용자 ID 존재
        return &(it->second); // User 객체 주소 반환
    }
    return nullptr; // 사용자 ID 없음
}

// User 객체 조회 (수정 가능)
User* UserManager::getMutableUser(const std::string& userId) {
    auto it = users.find(userId);
    if (it != users.end()) {
        return &(it->second);
    }
    return nullptr;
}

// 사용자 삭제
bool UserManager::deleteUser(const std::string& userId) {
    if (userId == "owner") { // "owner" 계정 삭제 방지
        cout << "오류: 'owner' 계정 삭제 불가." << endl;
        return false;
    }
    if (users.erase(userId)) { // 사용자 삭제 시도
        saveUsers(); // 파일에 저장
        cout << "사용자 ID '" << userId << "' 삭제 완료." << endl;
        return true; // 삭제 성공
    }
    else {
        cout << "오류: 사용자 ID '" << userId << "' 찾을 수 없음. 삭제 실패." << endl;
        return false; // 삭제 실패
    }
}

// 모든 사용자 정보 반환
const map<string, User>& UserManager::getAllUsers() const {
    return users;
}

// 모든 사용자 정보 출력
void UserManager::printAllUsers() const {
    if (users.empty()) {
        cout << "등록된 사용자 없음." << endl;
        return;
    }

    cout << "\n--- 전체 사용자 목록 ---" << endl;
    cout << left << setw(15) << "ID"
        << setw(10) << "유형"
        << setw(15) << "이름"
        << setw(18) << "전화번호" << endl; // 전화번호 폭 확장
    cout << "---------------------------------------------------------" << endl;

    for (const auto& pair : users) {
        const User& user = pair.second;
        string userTypeStr;
        switch (user.getUserType()) {
        case UserType::Customer: userTypeStr = "고객"; break;
        case UserType::Employee: userTypeStr = "직원"; break;
        case UserType::Owner:    userTypeStr = "사장"; break;
        default:                 userTypeStr = "알 수 없음"; break;
        }
        cout << left << setw(15) << user.getUserId()
            << setw(10) << userTypeStr
            << setw(15) << user.getName()
            << setw(18) << user.getFormattedPhone() << endl; // getFormattedPhone 사용
    }
    cout << "---------------------------------------------------------" << endl;
}