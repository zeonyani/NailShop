#include "UserManager.h"
#include <iostream> // 콘솔 입출력을 위해 포함하기

using namespace std;

// UserManager 생성자 구현
// 객체 생성 시 loadInitialUsers 함수를 호출하여 초기 사용자 데이터 로드하기
UserManager::UserManager() {
    loadInitialUsers();
}

// 새 사용자 추가 함수 구현
// userId가 이미 존재하는지 확인 후, 없으면 users 맵에 새 User 객체 추가하기
bool UserManager::addUser(const string& userId, const string& password, UserType type) {
    if (users.find(userId) == users.end()) { // users 맵에서 userId를 찾지 못한 경우 (중복 없음)
        users.emplace(userId, User(userId, password, type)); // 새 User 객체를 생성하여 맵에 삽입하기
        cout << "사용자 " << userId << " 계정이 생성되었습니다. (유형: " << static_cast<int>(type) << ")" << endl;
        return true; // 사용자 추가 성공
    }
    else {
        cout << "오류: 사용자 ID '" << userId << "'는 이미 존재합니다." << endl;
        return false; // 사용자 추가 실패 (ID 중복)
    }
}

// 사용자 로그인 함수 구현
// 입력받은 userId와 password를 확인하여 로그인 인증 수행하기
UserType UserManager::login(const string& userId, const string& password) {
    auto it = users.find(userId); // users 맵에서 해당 userId 검색하기
    if (it != users.end()) { // 사용자 ID를 찾았을 경우
        if (it->second.checkPassword(password)) { // User 객체의 checkPassword 함수로 비밀번호 확인하기
            cout << userId << " 님 환영합니다! (" << (int)it->second.getUserType() << " 권한)" << endl;
            return it->second.getUserType(); // 로그인 성공, 해당 사용자의 UserType 반환하기
        }
        else {
            cout << "로그인 실패: 비밀번호가 올바르지 않습니다." << endl;
            return UserType::None; // 비밀번호 불일치
        }
    }
    else {
        cout << "로그인 실패: 사용자 ID '" << userId << "'를 찾을 수 없습니다." << endl;
        return UserType::None; // 사용자 ID가 맵에 없는 경우
    }
}

// 특정 사용자 가져오기 함수 구현 (const 버전)
// userId에 해당하는 User 객체의 포인터 반환하기
const User* UserManager::getUser(const string& userId) const {
    auto it = users.find(userId); // users 맵에서 userId 검색하기
    if (it != users.end()) {
        return &(it->second); // 찾은 User 객체의 주소 반환하기
    }
    return nullptr; // 사용자 ID를 찾지 못한 경우 nullptr 반환하기
}

// 초기 사용자 데이터를 로드하는 함수 구현
// 프로그램 시작 시 테스트 및 초기 설정을 위한 샘플 계정들 추가하기
void UserManager::loadInitialUsers() {
    // 사장 계정 추가하기
    addUser("owner", "ownerpass", UserType::Owner);
    // 직원 계정 추가하기
    addUser("employee1", "emppass1", UserType::Employee);
    addUser("employee2", "emppass2", UserType::Employee);
    // 고객 계정 추가하기
    addUser("customer1", "custpass1", UserType::Customer);
    addUser("customer2", "custpass2", UserType::Customer);
    cout << "초기 사용자 계정이 로드되었습니다." << endl;
}