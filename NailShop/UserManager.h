//UserManager.h
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <map>
#include <string>
#include <vector>
#include "User.h"
#include "CSVHandler.h"

class UserManager {
private:
    static const std::string USERS_FILE; // 추가
    std::map<std::string, User> users;
    int nextUserId; // 다음 사용자 ID 번호 (USR001, USR002 등)

    void loadUsers();
    void addOwnerAccount(); // owner 계정 생성 기능

public: // saveUsers는 public에 있어야 SystemManager에서 호출 가능
    void saveUsers(bool silent = false); // silent 매개변수 추가

public:
    UserManager();
    ~UserManager();

    // 사용자 추가
    bool addUser(const std::string& userId, const std::string& password, UserType type, const std::string& name, const std::string& phone);
    // 로그인
    UserType login(const std::string& userId, const std::string& password);
    // 사용자 ID로 사용자 조회 (읽기 전용)
    const User* getUser(const std::string& userId) const;
    // 사용자 ID로 사용자 조회 (수정 가능)
    User* getMutableUser(const std::string& userId);
    // 사용자 삭제
    bool deleteUser(const std::string& userId);
    // 사용자 계정 정보 업데이트
    // newName 매개변수 추가
    bool updateUserAccount(const std::string& userId, const std::string& newPassword, const std::string& newName, const std::string& newPhone);
    // 모든 사용자 정보 출력
    void printAllUsers() const;
    // 모든 사용자 맵 반환 (읽기 전용)
    const std::map<std::string, User>& getAllUsers() const;
};

#endif // USER_MANAGER_H