#pragma once

#include <string>
#include "ReservationManager.h"
#include "UserManager.h" // UserManager 클래스 사용을 위해 포함하기
#include "User.h"        // UserType을 직접 사용하기 위해 포함하기

class SystemManager {
public:
    SystemManager();
    void run();

private:
    ReservationManager reservationManager;
    UserManager userManager;             // 사용자 관리를 위한 UserManager 객체
    UserType currentLoggedInUserType;    // 현재 로그인된 사용자의 유형
    std::string currentLoggedInUserId;   // 현재 로그인된 사용자의 ID

    // --- 로그인 관련 함수 ---
    bool loginUser();

    // --- 메뉴 관련 함수들 ---
    void displayMainMenu();
    void handleMainMenuInput(int choice);

    // --- 예약 관리 기능 함수들 (ReservationManager의 기능을 활용) ---
    void addNewReservation();
    void cancelExistingReservation();
    void viewSpecificReservation();
    void viewAllReservations();
    void viewMyReservations();        // 현재 로그인된 고객의 예약만 필터링하여 조회하기 (고객 전용)

    // --- 권한별 특화 기능 (미구현 함수는 제외) ---
    void employeeViewTodayReservations();
};