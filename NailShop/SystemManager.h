// SystemManager.h
#pragma once

#include <string>           // std::string
#include "ReservationManager.h" // ReservationManager
#include "UserManager.h"    // UserManager
#include "ServiceManager.h" // ServiceManager
#include "User.h"           // UserType, User

// 전체 시스템 흐름 관리
class SystemManager {
public:
    // SystemManager 생성자
    SystemManager();
    // 시스템 실행 진입점
    void run();

private:
    ReservationManager reservationManager;  // 예약 관리 객체
    UserManager userManager;                // 사용자 관리 객체
    ServiceManager serviceManager;          // 서비스 관리 객체

    UserType currentLoggedInUserType;        // 현재 로그인 사용자 유형
    std::string currentLoggedInUserId;      // 현재 로그인 사용자 ID
    std::string currentLoggedInUserName;    // 현재 로그인 사용자 이름
    std::string currentLoggedInUserPhone;   // 현재 로그인 사용자 전화번호

    // 초기 진입 메뉴 표시
    void displayEntryMenu();
    // 사용자 로그인 처리
    bool loginUser();
    // 고객 회원가입 처리
    void registerCustomerAccount();

    // 초기 관리자 계정 생성
    void createInitialAdminAccount();
    // 초기 서비스 데이터 생성
    void createInitialServices();

    // 메인 메뉴 출력
    void displayMainMenu();
    // 메인 메뉴 입력 처리
    void handleMainMenuInput(int choice);

    // 새 예약 추가
    void addNewReservation();
    // 기존 예약 취소
    void cancelExistingReservation();
    // 특정 예약 조회
    void viewSpecificReservation();
    // 모든 예약 조회
    void viewAllReservations();
    // 내 예약 조회 (고객 전용)
    void viewMyReservations();

    // 오늘 예약 확인 (직원/사장)
    void employeeViewTodayReservations();

    // 사용자 관리 (사장 전용 하위 메뉴)
    void manageUsers();
    // 새 직원/고객 계정 추가
    void addStaffOrCustomerAccount();
    // 직원/고객 계정 삭제
    void deleteStaffOrCustomerAccount();
    // 모든 사용자 목록 보기
    void viewAllUsers();
    // 사용자 검색 (ID)
    void searchUser();


    // 서비스 관리 (사장 전용 하위 메뉴)
    void manageServices();
    // 서비스 추가
    void addService();
    // 서비스 수정
    void updateService();
    // 서비스 삭제
    void deleteService();
    // 서비스 목록 보기
    void viewServices();
};