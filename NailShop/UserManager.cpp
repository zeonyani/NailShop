// UserManager.cpp
#include "UserManager.h"
#include "Admin.h"      // Admin 클래스 포함
#include "Customer.h"   // Customer 클래스 포함
#include "Staff.h"      // Staff 클래스 포함
#include <iostream>     // 콘솔 입출력 기능
#include <algorithm>    // 알고리즘 관련 기능
#include <limits>       // std::numeric_limits 사용
#include <iomanip>      // 입출력 포매팅 기능
#include <regex>        // 정규 표현식 사용

const std::string UserManager::USERS_FILE = "users.csv"; // 사용자 데이터 파일 경로 상수 정의

// UserManager 생성자
UserManager::UserManager() : nextUserId(1) {
    // UserManager 객체 생성 시 사용자 데이터를 로드하는 과정.
    // loadUsers 함수 내부에서 사장 계정의 존재 여부를 확인하고 필요 시 자동 생성.
    loadUsers();
}

// UserManager 소멸자
UserManager::~UserManager() {
    // 프로그램 종료 시 모든 사용자 데이터를 파일에 저장하는 과정.
    saveUsers(true); // 소멸 시에는 사용자에게 메시지 없이 저장 (silent 모드).
}

// 사용자 데이터 로드
void UserManager::loadUsers() {
    std::vector<std::string> lines = CSVHandler::readCsv(USERS_FILE); // CSV 파일에서 모든 사용자 데이터 줄 읽기
    users.clear(); // 기존 메모리의 사용자 데이터 맵 초기화.

    int maxNumericId = 0; // "USR" 접두사를 가진 사용자 ID 중 가장 큰 숫자 부분을 추적하는 변수.
    bool ownerExists = false; // 사장 계정(UserType::Owner)의 존재 여부를 나타내는 플래그.

    for (const std::string& line : lines) {
        User user = User::fromCsvString(line); // 각 줄을 파싱하여 User 객체로 변환.
        if (!user.getUserId().empty()) {
            users[user.getUserId()] = user; // 파싱된 유효한 사용자 정보를 맵에 추가.

            // 현재 사용자가 사장(Owner) 유형인지 확인.
            if (user.getUserType() == UserType::Owner) {
                ownerExists = true; // 사장 계정 발견 시 플래그 설정.
            }

            // 다음 사용자 ID 생성을 위한 최대 숫자 ID 추적.
            // "USR"로 시작하는 ID만 고려하여 nextUserId 계산에 반영.
            if (user.getUserId().rfind("USR", 0) == 0 && user.getUserId().length() > 3) {
                try {
                    // "USR" 다음의 숫자 부분을 정수로 변환.
                    int idNum = std::stoi(user.getUserId().substr(3));
                    if (idNum > maxNumericId) { // 현재까지 찾은 가장 큰 숫자 ID를 업데이트.
                        maxNumericId = idNum;
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "경고: 사용자 ID 숫자 파싱 오류 (invalid_argument): " << e.what() << " - " << user.getUserId() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "경고: 사용자 ID 숫자 파싱 오류 (out_of_range): " << e.what() << " - " << user.getUserId() << std::endl;
                }
            }
        }
    }
    // 모든 사용자 로드 후, 다음으로 할당될 "USR" 기반 ID를 설정.
    // 이는 로드된 모든 "USR" ID 중 가장 큰 숫자 ID에 1을 더한 값.
    // 이렇게 함으로써 USR000, USR001 등이 파일에 있어도 중복되지 않는 다음 ID를 보장.
    nextUserId = maxNumericId + 1;

    // 사장 계정(UserType::Owner)이 존재하지 않을 경우 초기 사장 계정 생성.
    // 이 addOwnerAccount() 함수는 "admin"이라는 고정 ID를 사용.
    // 따라서 CSV 파일에 Owner 타입의 사용자가 하나도 없으면 "admin" 계정 생성 시도.
    if (!ownerExists) {
        addOwnerAccount();
    }
}

// 사용자 데이터 저장
void UserManager::saveUsers(bool silent) {
    std::vector<std::string> lines; // 저장할 사용자 데이터를 담을 벡터.
    for (const auto& pair : users) {
        lines.push_back(pair.second.toCsvString()); // 각 사용자 객체를 CSV 문자열로 변환하여 벡터에 추가.
    }
    if (CSVHandler::writeCsv(USERS_FILE, lines)) { // CSV 파일에 데이터 쓰기 시도.
        if (!silent) {
            std::cout << "사용자 데이터가 성공적으로 저장되었습니다." << std::endl; // 저장 성공 메시지 출력.
        }
    }
    else {
        if (!silent) {
            std::cerr << "오류: 사용자 데이터 저장에 실패했습니다." << std::endl; // 저장 실패 메시지 출력.
        }
    }
}

// owner 계정 생성 (최초 실행 시 'admin' ID로 고정)
void UserManager::addOwnerAccount() {
    // 사장 계정("admin")이 이미 맵에 존재하는지 확인.
    // loadUsers()에서 ownerExists를 통해 대부분 걸러지나, 혹시 모를 경우를 대비.
    if (users.count("admin")) {
        std::cout << "사장 계정 (ID: admin)이 이미 존재합니다." << std::endl; // 이미 존재함 알림.
        return;
    }

    std::cout << "\n--- 초기 사장 계정 설정 ---\n" << std::endl; // 초기 설정 안내.
    std::cout << "시스템을 처음 실행하셨습니다. 사장 계정을 설정합니다." << std::endl; // 시스템 첫 실행 안내.
    std::string ownerId = "admin"; // 사장 계정 ID를 "admin"으로 고정.
    std::string ownerPw; // 사용자로부터 입력받을 비밀번호.
    std::string ownerName = "관리자"; // 사장 계정의 기본 이름.
    std::string ownerPhone; // 사용자로부터 입력받을 전화번호.

    // 비밀번호 설정 규칙 안내 및 유효성 검사 루프.
    std::cout << "기본 사장 ID: " << ownerId << std::endl; // 사장 ID 안내.
    std::cout << "비밀번호는 영문, 숫자, 특수문자를 조합하여 8~15자리로 입력해주세요." << std::endl; // 비밀번호 규칙 안내.

    while (true) {
        std::cout << "사장 계정 비밀번호를 설정해주세요: ";
        std::cin >> ownerPw; // 비밀번호 입력.

        std::string confirmPassword;
        std::cout << "비밀번호 재확인: ";
        std::cin >> confirmPassword; // 비밀번호 재확인 입력.

        if (ownerPw == confirmPassword) { // 비밀번호와 재확인 비밀번호 일치 여부 확인.
            // 비밀번호 유효성 검사 (정규식 사용): 최소 8자, 최대 15자, 영문 대소문자, 숫자, 특수문자 각 1개 이상 포함.
            std::regex password_regex("^(?=.*[a-zA-Z])(?=.*\\d)(?=.*[!@#$%^&*()_+\\-=\\[\\]{};':\"\\\\|,.<>/?]).{8,15}$");
            if (std::regex_match(ownerPw, password_regex)) {
                break; // 비밀번호 일치 및 유효성 통과 시 루프 종료.
            }
            else {
                std::cout << "오류: 비밀번호가 유효성 조건을 충족하지 않습니다. 다시 입력해주세요." << std::endl; // 유효성 실패 메시지.
            }
        }
        else {
            std::cout << "오류: 비밀번호가 일치하지 않습니다. 다시 입력해주세요." << std::endl; // 비밀번호 불일치 메시지.
        }
    }

    // 전화번호 입력 및 정규화.
    std::cout << "사장 계정 전화번호 (예: 01012345678): ";
    std::string rawPhone;
    std::cin >> rawPhone; // 전화번호 입력.
    ownerPhone = User::normalizePhoneNumber(rawPhone); // 입력된 전화번호 정규화.
    if (ownerPhone.empty()) {
        std::cout << "경고: 전화번호 형식이 올바르지 않아 기본값(010-0000-0000)으로 설정됩니다." << std::endl; // 형식 오류 경고.
        ownerPhone = "01000000000"; // 유효하지 않으면 기본값으로 설정.
    }

    // addUser 함수를 통해 사장 계정 추가 시도.
    if (addUser(ownerId, ownerPw, UserType::Owner, ownerName, ownerPhone)) {
        std::cout << "사장 계정 (ID: " << ownerId << ")이 성공적으로 생성되었습니다. 이제 로그인할 수 있습니다." << std::endl; // 생성 성공 메시지.
    }
    else {
        std::cerr << "오류: 사장 계정 생성에 실패했습니다. (내부 오류)" << std::endl; // 생성 실패 메시지 (ID 중복 외의 오류).
    }
}

// 사용자 추가
bool UserManager::addUser(const std::string& userId, const std::string& password, UserType type, const std::string& name, const std::string& phone) {
    if (users.count(userId)) { // 추가하려는 userId가 이미 존재하는지 확인.
        return false; // 이미 존재하는 ID이므로 추가 실패 반환.
    }

    // 각 UserType에 맞는 파생 클래스 객체 생성.
    // 현재 map<string, User>에 값을 직접 저장하는 방식은 C++ 객체 슬라이싱(object slicing)을 발생시킬 수 있습니다.
    // 이는 파생 클래스 고유의 멤버(가상 함수 포함)가 잘려나가 기본 클래스 부분만 저장되는 현상.
    // 본 프로젝트의 현재 기능에서는 User 기본 클래스의 멤버만 사용하고 있어 큰 문제가 없을 수 있으나,
    // 다형적 동작이 필요할 경우 std::map<std::string, std::unique_ptr<User>>와 같이 포인터 기반으로 변경 필요.
    User newUser; // User 객체 선언.
    if (type == UserType::Customer) {
        newUser = Customer(userId, password, name, phone); // Customer 객체로 할당.
    }
    else if (type == UserType::Employee) {
        newUser = Staff(userId, password, name, phone); // Staff 객체로 할당.
    }
    else if (type == UserType::Owner) {
        newUser = Admin(userId, password, name, phone); // Admin 객체로 할당.
    }
    else {
        std::cerr << "오류: 알 수 없는 사용자 유형입니다." << std::endl; // 알 수 없는 유형 오류.
        return false;
    }

    users[userId] = newUser; // 맵에 새 사용자 추가.
    saveUsers(); // 변경 사항을 파일에 저장.
    return true; // 사용자 추가 성공 반환.
}

// 로그인
UserType UserManager::login(const std::string& userId, const std::string& password) {
    auto it = users.find(userId); // 사용자 ID로 맵에서 사용자 찾기.
    if (it != users.end()) { // ID가 존재하는 경우.
        if (it->second.getPassword() == password) { // 비밀번호 일치 여부 확인.
            return it->second.getUserType(); // 로그인 성공, 해당 사용자의 유형 반환.
        }
    }
    return UserType::None; // 로그인 실패 시 None 유형 반환.
}

// 사용자 ID로 사용자 조회 (읽기 전용)
const User* UserManager::getUser(const std::string& userId) const {
    auto it = users.find(userId); // 사용자 ID로 맵에서 사용자 찾기.
    if (it != users.end()) {
        return &(it->second); // 존재하는 사용자 객체의 주소(읽기 전용) 반환.
    }
    return nullptr; // 사용자 없음 시 nullptr 반환.
}

// 사용자 ID로 사용자 조회 (수정 가능)
User* UserManager::getMutableUser(const std::string& userId) {
    auto it = users.find(userId); // 사용자 ID로 맵에서 사용자 찾기.
    if (it != users.end()) {
        return &(it->second); // 존재하는 사용자 객체의 주소(수정 가능) 반환.
    }
    return nullptr; // 사용자 없음 시 nullptr 반환.
}

// 사용자 삭제
bool UserManager::deleteUser(const std::string& userId) {
    auto it = users.find(userId); // 사용자 ID로 맵에서 사용자 찾기.
    if (it != users.end()) {
        users.erase(it); // 맵에서 사용자 제거.
        saveUsers(); // 변경 사항을 파일에 저장.
        return true; // 삭제 성공 반환.
    }
    return false; // 사용자 없음 시 삭제 실패 반환.
}

// 사용자 계정 정보 업데이트
bool UserManager::updateUserAccount(const std::string& userId, const std::string& newPassword, const std::string& newName, const std::string& newPhone) {
    User* userToUpdate = getMutableUser(userId); // 업데이트할 사용자 객체 포인터 가져오기.
    if (userToUpdate) {
        // 새 비밀번호가 비어있지 않고 기존 비밀번호와 다를 경우 업데이트.
        if (!newPassword.empty() && newPassword != userToUpdate->getPassword()) {
            userToUpdate->setPassword(newPassword);
        }
        // 새 이름이 비어있지 않고 기존 이름과 다를 경우 업데이트.
        if (!newName.empty() && newName != userToUpdate->getName()) {
            userToUpdate->setName(newName);
        }
        // 새 전화번호를 정규화하고, 비어있지 않고 기존 전화번호와 다를 경우 업데이트.
        std::string normalizedPhone = User::normalizePhoneNumber(newPhone);
        if (!newPhone.empty() && normalizedPhone != userToUpdate->getPhone()) {
            userToUpdate->setPhone(normalizedPhone);
        }
        saveUsers(); // 변경 사항을 파일에 저장.
        return true; // 업데이트 성공 반환.
    }
    return false; // 사용자 없음 시 업데이트 실패 반환.
}

// 모든 사용자 목록 반환
const std::map<std::string, User>& UserManager::getAllUsers() const {
    return users; // 모든 사용자 정보가 담긴 맵 반환 (읽기 전용).
}

// 모든 사용자 정보 출력 (관리자용)
void UserManager::printAllUsers() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다." << std::endl; // 등록된 사용자 없음 메시지.
        return;
    }
    std::cout << "\n--- 모든 사용자 목록 ---\n" << std::endl; // 목록 제목.
    std::cout << "--------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(10) << "ID"
        << std::setw(15) << "이름"
        << std::setw(10) << "유형"
        << std::setw(15) << "전화번호"
        << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------" << std::endl;

    for (const auto& pair : users) {
        const User& user = pair.second;
        std::string userTypeStr;
        // 사용자 유형에 따라 문자열 변환.
        switch (user.getUserType()) {
        case UserType::Customer: userTypeStr = "고객"; break;
        case UserType::Employee: userTypeStr = "직원"; break;
        case UserType::Owner:    userTypeStr = "사장"; break;
        default:                 userTypeStr = "알 수 없음"; break;
        }
        std::cout << std::left << std::setw(10) << user.getUserId()
            << std::setw(15) << user.getName()
            << std::setw(10) << userTypeStr
            << std::setw(15) << user.getFormattedPhone() // 형식화된 전화번호 출력.
            << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------------------------" << std::endl;
}