#include "UserManager.h"
#include <iostream>

using namespace std;

UserManager::UserManager() {
    loadInitialUsers();
}

// 이 함수는 이미 지난 답변에서 name 파라미터를 받도록 수정됨
bool UserManager::addUser(const string& userId, const string& password, UserType type, const string& name) {
    if (users.find(userId) == users.end()) {
        users.emplace(userId, User(userId, password, type, name)); // User 객체 생성 시 name 전달!
        cout << "사용자 " << userId << " 계정(" << name << ")이 생성되었습니다. (유형: " << static_cast<int>(type) << ")" << endl;
        return true;
    }
    else {
        cout << "오류: 사용자 ID '" << userId << "'는 이미 존재합니다." << endl;
        return false;
    }
}

UserType UserManager::login(const string& userId, const string& password) {
    auto it = users.find(userId);
    if (it != users.end()) {
        if (it->second.checkPassword(password)) {
            cout << it->second.getName() << " 님 환영합니다! (" << (int)it->second.getUserType() << " 권한)" << endl;
            return it->second.getUserType();
        }
        else {
            cout << "로그인 실패: 비밀번호가 올바르지 않습니다." << endl;
            return UserType::None;
        }
    }
    else {
        cout << "로그인 실패: 사용자 ID '" << userId << "'를 찾을 수 없습니다." << endl;
        return UserType::None;
    }
}

const User* UserManager::getUser(const string& userId) const {
    auto it = users.find(userId);
    if (it != users.end()) {
        return &(it->second);
    }
    return nullptr;
}

// 이 함수가 문제의 핵심! addUser 호출 시 name 인자 추가
void UserManager::loadInitialUsers() {
    // name 파라미터 추가하여 addUser 호출하기
    // 예시: addUser("아이디", "비밀번호", UserType::유형, "이름");
    addUser("owner", "ownerpass", UserType::Owner, "김사장");       // 사장 계정
    addUser("employee1", "emppass1", UserType::Employee, "이직원"); // 직원 계정
    addUser("employee2", "emppass2", UserType::Employee, "박직원"); // 직원 계정
    addUser("customer1", "custpass1", UserType::Customer, "최고객"); // 고객 계정
    addUser("customer2", "custpass2", UserType::Customer, "정고객"); // 고객 계정
    cout << "초기 사용자 계정이 로드되었습니다." << endl;
}