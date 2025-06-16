#include "SystemManager.h"
#include <iostream>
#include <limits>    // std::numeric_limits 사용을 위해 포함하기
#include <string>    // std::string, std::getline 사용을 위해 포함하기
#include <ctime>     // 오늘 날짜를 얻기 위해 std::time, std::localtime 사용하기
#include <iomanip>   // std::put_time, std::setw, std::setfill 사용을 위해 포함하기
#include <sstream>   // std::stringstream 사용을 위해 포함하기

// using namespace std; // 사용자님의 기존 코드 스타일을 위해 이 라인 제거

SystemManager::SystemManager()
    : currentLoggedInUserType(UserType::None), currentLoggedInUserId("") {
    std::cout << "네일샵 예약 시스템을 시작합니다." << std::endl;
}

void SystemManager::run() {
    if (!loginUser()) {
        std::cout << "로그인에 실패하여 프로그램을 종료합니다. 프로그램을 다시 시작해주세요." << std::endl;
        return;
    }

    int choice;
    do {
        displayMainMenu();
        std::cout << "메뉴를 선택하세요: ";

        if (!(std::cin >> choice)) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        handleMainMenuInput(choice);

        if (choice != 0) {
            std::cout << "\n계속하려면 Enter를 누르세요...";
            std::cin.get();
        }

    } while (choice != 0);
    std::cout << "네일샵 예약 시스템을 종료합니다." << std::endl;
}

bool SystemManager::loginUser() {
    std::string userId, password;
    std::cout << "\n--- 로그인 ---" << std::endl;
    std::cout << "사용자 ID: ";
    std::getline(std::cin, userId);
    std::cout << "비밀번호: ";
    std::getline(std::cin, password);

    currentLoggedInUserType = userManager.login(userId, password);

    if (currentLoggedInUserType == UserType::None) {
        return false;
    }
    currentLoggedInUserId = userId;
    return true;
}

void SystemManager::displayMainMenu() {
    std::cout << "\n--- 메인 메뉴 ---" << std::endl;
    std::cout << "현재 로그인: " << currentLoggedInUserId << " ("
        << (currentLoggedInUserType == UserType::Owner ? "사장" :
            currentLoggedInUserType == UserType::Employee ? "직원" :
            currentLoggedInUserType == UserType::Customer ? "고객" :
            "알 수 없음")
        << ")" << std::endl;

    std::cout << "1. 내 예약 조회" << std::endl;

    if (currentLoggedInUserType == UserType::Customer) {
        std::cout << "2. 새로운 예약 추가" << std::endl;
        std::cout << "3. 예약 취소" << std::endl;
    }
    else if (currentLoggedInUserType == UserType::Employee || currentLoggedInUserType == UserType::Owner) {
        std::cout << "2. 오늘 예약 확인" << std::endl;
        std::cout << "3. 전체 예약 목록 보기" << std::endl;
        std::cout << "4. 예약 추가" << std::endl;
        std::cout << "5. 예약 취소" << std::endl;
    }

    if (currentLoggedInUserType == UserType::Owner) {
        std::cout << "6. 사용자 관리 (미구현)" << std::endl;
        std::cout << "7. 서비스 관리 (미구현)" << std::endl;
    }

    std::cout << "0. 로그아웃 및 종료" << std::endl;
}

void SystemManager::handleMainMenuInput(int choice) {
    switch (choice) {
    case 1:
        if (currentLoggedInUserType == UserType::Customer) {
            viewMyReservations();
        }
        else {
            viewSpecificReservation();
        }
        break;
    case 0:
        break;
    default:
        if (currentLoggedInUserType == UserType::Customer) {
            switch (choice) {
            case 2: addNewReservation(); break;
            case 3: cancelExistingReservation(); break;
            default: std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl; break;
            }
        }
        else if (currentLoggedInUserType == UserType::Employee || currentLoggedInUserType == UserType::Owner) {
            switch (choice) {
            case 2: employeeViewTodayReservations(); break;
            case 3: viewAllReservations(); break;
            case 4: addNewReservation(); break;
            case 5: cancelExistingReservation(); break;
            case 6:
            case 7:
                std::cout << "해당 기능은 아직 구현되지 않았습니다." << std::endl;
                break;
            default: std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl; break;
            }
        }
        else {
            std::cout << "오류: 로그인 상태를 알 수 없습니다. 다시 로그인해주세요." << std::endl;
        }
        break;
    }
}

// --- 예약 관리 기능 함수 구현 ---

void SystemManager::addNewReservation() {
    std::string customerId_input, service, datetime;
    std::cout << "새로운 예약을 추가합니다." << std::endl;

    if (currentLoggedInUserType == UserType::Customer) {
        customerId_input = currentLoggedInUserId;
        std::cout << "고객 ID: " << customerId_input << " (자동 입력)" << std::endl;
    }
    else {
        std::cout << "예약할 고객의 ID를 입력하세요: ";
        std::getline(std::cin, customerId_input);
    }

    std::cout << "서비스 종류를 입력하세요 (예: 네일아트, 패디큐어): ";
    std::getline(std::cin, service);
    std::cout << "예약 날짜 및 시간을 입력하세요 (예: 2025-06-20 15:00): ";
    std::getline(std::cin, datetime);

    reservationManager.addReservation(customerId_input, service, datetime);
}

void SystemManager::cancelExistingReservation() {
    std::string reservationId;
    std::cout << "취소할 예약의 ID를 입력하세요: ";
    std::getline(std::cin, reservationId);
    reservationManager.deleteReservation(reservationId);
}

void SystemManager::viewSpecificReservation() {
    std::string reservationId;
    std::cout << "조회할 예약의 ID를 입력하세요: ";
    std::getline(std::cin, reservationId);
    reservationManager.printReservation(reservationId);
}

void SystemManager::viewAllReservations() {
    reservationManager.printAllReservations();
}

void SystemManager::viewMyReservations() {
    std::cout << "현재 로그인된 (" << currentLoggedInUserId << ") 님의 예약 목록입니다. (기능 미구현)" << std::endl;
    // TODO: ReservationManager에 특정 고객 ID의 예약만 조회하는 함수 추가 후 호출하기
    // 예: reservationManager.printReservationsByCustomerId(currentLoggedInUserId);
}

// --- 권한별 함수 (미구현) ---

void SystemManager::employeeViewTodayReservations() {
    std::cout << "오늘의 예약 확인 기능입니다." << std::endl;
    std::time_t now = std::time(0);
    std::tm* ltm = std::localtime(&now);

    std::stringstream ss;
    ss << (ltm->tm_year + 1900) << "-"
        << std::setfill('0') << std::setw(2) << (ltm->tm_mon + 1) << "-"
        << std::setfill('0') << std::setw(2) << ltm->tm_mday;
    std::string todayDate = ss.str();

    std::cout << "오늘 날짜: " << todayDate << std::endl;
    // TODO: ReservationManager에 특정 날짜의 예약만 조회하는 함수 추가 후 호출하기
    // 예: reservationManager.printReservationsForDate(todayDate);
    std::cout << "오늘 날짜의 예약 목록을 ReservationManager를 통해 조회해야 합니다. (기능 미구현)" << std::endl;
}