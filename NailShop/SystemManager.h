//SystemManager.h
#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "UserManager.h"
#include "ServiceManager.h"
#include "ReservationManager.h"
#include "User.h" // UserType 정의를 위해 필요

// SystemManager 클래스
class SystemManager {
private:
    UserManager userManager;
    ServiceManager serviceManager;
    ReservationManager reservationManager; // 생성자에서 serviceManager 참조를 받도록 수정

    UserType currentLoggedInUserType;
    std::string currentLoggedInUserId;
    std::string currentLoggedInUserName;
    std::string currentLoggedInUserPhone; // 현재 로그인한 사용자 전화번호

    // 입력 버퍼 비우기 헬퍼 함수
    void clearInputBuffer();

    // 메뉴 관련 함수들
    void displayMainMenu();
    void processMainMenuInput(int choice);

    void displayOwnerMenu();
    void processOwnerMenuInput(int choice);
    void handleOwnerServiceManagement();
    void handleOwnerUserManagement();
    void handleOwnerReservationManagement(); // 사장 예약 관리 기능
    void handleOwnerAccountInfo(); // 사장 계정 정보 관리 기능

    void displayEmployeeMenu();
    void processEmployeeMenuInput(int choice);
    void handleEmployeeServiceManagement();
    void handleEmployeeReservationManagement(); // 직원 예약 관리 기능
    void handleEmployeeAccountInfo(); // 직원 계정 정보 관리 기능

    void displayCustomerMenu();
    void processCustomerMenuInput(int choice);
    void handleCustomerReservationManagement(); // 고객 예약 관리 기능
    void handleCustomerAccountInfo(); // 고객 계정 정보 관리 기능

    // 추가된 함수 선언
    void handleLogin(); // 로그인 처리 함수

    void addUser();
    void deleteUser();
    // 오버로드된 함수를 사용하여 현재 로그인된 사용자 또는 특정 사용자의 정보를 수정
    void updateUserAccountInfo(const std::string& targetUserId = "");

    void makeReservation(); // 예약 생성 기능
    void cancelReservation(); // 예약 취소 기능 (관리자/직원용)
    void cancelReservation(const std::string& customerId); // 예약 취소 기능 (고객용, 자신의 예약만)
    void viewAllReservations(); // 모든 예약 보기 기능
    void viewReservationsByCustomer(); // 고객별 예약 보기 기능 (관리자/직원용)
    void viewReservationsByCustomer(const std::string& customerId); // 고객별 예약 보기 기능 (고객용, 자신의 예약만)
    void viewReservationsForDate(); // 날짜별 예약 보기 기능

public:
    SystemManager();
    void run();
};

#endif // SYSTEM_MANAGER_H