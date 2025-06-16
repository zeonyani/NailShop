#pragma once
#include <string>
// #include <map> // 현재 SystemManager.h에서 map을 직접 사용하지 않으므로 주석 처리 또는 제거 가능
#include "ReservationManager.h" // ReservationManager 객체를 사용하므로 포함

// 시스템 관리자 클래스
class SystemManager {
public:
    // 생성자: 필요한 경우 ReservationManager 객체를 초기화합니다.
    SystemManager();

    // 시스템을 시작하고 메인 메뉴 루프를 실행하는 함수
    void run();

private:
    // 예약 관리를 위한 ReservationManager 객체
    ReservationManager reservationManager;

    // --- 메뉴 관련 함수들 ---
    void displayMainMenu(); // 메인 메뉴를 출력하는 함수
    void handleMainMenuInput(int choice); // 메인 메뉴 선택을 처리하는 함수

    // --- 예약 관리 서브 메뉴 관련 함수들 ---
    void reservationMenu(); // 예약 관리 서브 메뉴를 출력하는 함수
    void handleReservationMenuInput(int choice); // 예약 관리 메뉴 선택을 처리하는 함수

    // --- 예약 관리 기능 함수들 (ReservationManager의 래퍼) ---
    void addNewReservation(); // 새로운 예약 추가를 위한 사용자 입력 처리
    void cancelExistingReservation(); // 기존 예약 취소를 위한 사용자 입력 처리
    void viewSpecificReservation(); // 특정 예약 조회를 위한 사용자 입력 처리
    void viewAllReservations(); // 전체 예약 목록 조회
};