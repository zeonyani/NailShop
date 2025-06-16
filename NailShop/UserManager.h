#pragma once
#include <string> // std::string 사용하기
#include <map>    // std::map 사용하기
#include "User.h" // User 클래스 사용을 위해 포함하기

// UserManager 클래스는 사용자 계정을 관리하는 역할을 함
// 사용자 추가, 로그인 인증 등의 기능 제공하기
class UserManager {
public:
    // 생성자: UserManager 객체 생성 시 호출되기
    UserManager();

    // 새 사용자 계정을 추가하는 함수
    // userId: 추가할 사용자의 ID
    // password: 사용자의 비밀번호
    // type: 사용자의 유형 (고객, 직원, 사장)
    // 반환값: 사용자 추가 성공 시 true, 실패 시 (예: ID 중복) false
    bool addUser(const std::string& userId, const std::string& password, UserType type);

    // 사용자 로그인 인증을 시도하는 함수
    // userId: 로그인 시도할 사용자의 ID
    // password: 사용자가 입력한 비밀번호
    // 반환값: 로그인 성공 시 해당 사용자의 UserType, 실패 시 UserType::None
    UserType login(const std::string& userId, const std::string& password);

    // 특정 사용자 ID로 User 객체를 가져오는 함수
    // userId: 조회할 사용자의 ID
    // 반환값: 해당 User 객체의 포인터 (const), 찾지 못하면 nullptr
    const User* getUser(const std::string& userId) const;

private:
    // 사용자 ID(std::string)를 키로 User 객체를 저장하는 맵
    // 이를 통해 빠른 사용자 조회 및 관리 가능하기
    std::map<std::string, User> users;

    // 프로그램 시작 시 미리 정의된 초기 사용자 데이터를 로드하는 함수
    // 실제 운영에서는 파일 등에서 데이터를 로드하도록 변경될 수 있기
    void loadInitialUsers();
};