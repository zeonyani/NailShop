// UserManager.h
#pragma once

#include <string>   // std::string
#include <map>      // std::map
#include <vector>   // std::vector
#include "User.h"   // User 클래스
#include "CSVHandler.h" // CSVHandler

// 사용자 계정 관리
class UserManager {
public:
    // UserManager 생성자
    UserManager();
    // UserManager 소멸자
    ~UserManager();

    // 사용자 계정 추가
    bool addUser(const std::string& userId, const std::string& password, UserType type, const std::string& name, const std::string& phone);

    // 사용자 로그인 처리
    UserType login(const std::string& userId, const std::string& password);

    // 사용자 객체 조회 (읽기 전용)
    const User* getUser(const std::string& userId) const;

    // 사용자 객체 조회 (수정 가능)
    User* getMutableUser(const std::string& userId);

    // 사용자 계정 삭제
    bool deleteUser(const std::string& userId);

    // 모든 사용자 정보 반환
    const std::map<std::string, User>& getAllUsers() const;

    // 모든 사용자 정보 출력
    void printAllUsers() const;

private:
    std::map<std::string, User> users; // 사용자 ID-User 맵
    const std::string USERS_FILE = "users.csv"; // 사용자 데이터 파일 경로

    // CSV 파일로부터 사용자 데이터 로드
    void loadUsers();
    // CSV 파일에 사용자 데이터 저장
    void saveUsers();
};