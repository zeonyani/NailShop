#include "SystemManager.h"
#include <iostream>
#include <limits>    // numeric_limits 사용을 위해 포함하기
#include <string>    // string, getline 사용을 위해 포함하기
#include <ctime>     // 오늘 날짜를 얻기 위해 time, localtime 사용하기
#include <iomanip>   // put_time, setw, setfill 사용을 위해 포함하기
#include <sstream>   // stringstream 사용을 위해 포함하기

using namespace std;

SystemManager::SystemManager()
    : currentLoggedInUserType(UserType::None), currentLoggedInUserId(""), currentLoggedInUserName("") { // name 초기화
    cout << "네일샵 예약 시스템을 시작합니다." << endl;
}

void SystemManager::run() {
    if (!loginUser()) {
        cout << "로그인에 실패하여 프로그램을 종료합니다. 프로그램을 다시 시작해주세요." << endl;
        return;
    }

    int choice;
    do {
        displayMainMenu();
        cout << "메뉴를 선택하세요: ";

        if (!(cin >> choice)) {
            cout << "잘못된 입력입니다. 숫자를 입력해주세요." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        handleMainMenuInput(choice);

        if (choice != 0) {
            cout << "\n계속하려면 Enter를 누르세요...";
            cin.get();
        }

    } while (choice != 0);
    cout << "네일샵 예약 시스템을 종료합니다." << endl;
}

bool SystemManager::loginUser() {
    string userId, password;
    cout << "\n--- 로그인 ---" << endl;
    cout << "사용자 ID: ";
    getline(cin, userId);
    cout << "비밀번호: ";
    getline(cin, password);

    currentLoggedInUserType = userManager.login(userId, password);

    if (currentLoggedInUserType == UserType::None) {
        return false;
    }
    currentLoggedInUserId = userId;
    // 로그인 성공 시 사용자 이름 가져오기
    const User* loggedInUser = userManager.getUser(userId);
    if (loggedInUser) {
        currentLoggedInUserName = loggedInUser->getName();
    }
    else {
        currentLoggedInUserName = ""; // 혹시 모를 상황 대비
    }
    return true;
}

void SystemManager::displayMainMenu() {
    cout << "\n--- 메인 메뉴 ---" << endl;
    // 로그인된 사용자 이름과 ID, 권한 표시
    cout << "현재 로그인: " << currentLoggedInUserName << " (" << currentLoggedInUserId << ", "
        << (currentLoggedInUserType == UserType::Owner ? "사장" :
            currentLoggedInUserType == UserType::Employee ? "직원" :
            currentLoggedInUserType == UserType::Customer ? "고객" :
            "알 수 없음")
        << ")" << endl;

    cout << "1. 내 예약 조회" << endl;

    if (currentLoggedInUserType == UserType::Customer) {
        cout << "2. 새로운 예약 추가" << endl;
        cout << "3. 예약 취소" << endl;
    }
    else if (currentLoggedInUserType == UserType::Employee || currentLoggedInUserType == UserType::Owner) {
        cout << "2. 오늘 예약 확인" << endl;
        cout << "3. 전체 예약 목록 보기" << endl;
        cout << "4. 예약 추가" << endl;
        cout << "5. 예약 취소" << endl;
    }

    if (currentLoggedInUserType == UserType::Owner) {
        cout << "6. 사용자 관리 (미구현)" << endl;
        cout << "7. 서비스 관리 (미구현)" << endl;
    }

    cout << "0. 로그아웃 및 종료" << endl;
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
            default: cout << "잘못된 입력입니다. 다시 시도해주세요." << endl; break;
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
                cout << "해당 기능은 아직 구현되지 않았습니다." << endl;
                break;
            default: cout << "잘못된 입력입니다. 다시 시도해주세요." << endl; break;
            }
        }
        else {
            cout << "오류: 로그인 상태를 알 수 없습니다. 다시 로그인해주세요." << endl;
        }
        break;
    }
}

// --- 예약 관리 기능 함수 구현 ---

void SystemManager::addNewReservation() {
    string customerId_input, service, datetime;
    cout << "새로운 예약을 추가합니다." << endl;

    if (currentLoggedInUserType == UserType::Customer) {
        customerId_input = currentLoggedInUserId;
        cout << "고객 ID: " << customerId_input << " (자동 입력)" << endl;
    }
    else {
        cout << "예약할 고객의 ID를 입력하세요: ";
        getline(cin, customerId_input);
    }

    cout << "서비스 종류를 입력하세요 (예: 네일아트, 패디큐어): ";
    getline(cin, service);
    cout << "예약 날짜 및 시간을 입력하세요 (예: 2025-06-20 15:00): ";
    getline(cin, datetime);

    reservationManager.addReservation(customerId_input, service, datetime);
}

void SystemManager::cancelExistingReservation() {
    string reservationId;
    cout << "취소할 예약의 ID를 입력하세요: ";
    getline(cin, reservationId);
    reservationManager.deleteReservation(reservationId);
}

void SystemManager::viewSpecificReservation() {
    string reservationId;
    cout << "조회할 예약의 ID를 입력하세요: ";
    getline(cin, reservationId);
    reservationManager.printReservation(reservationId);
}

void SystemManager::viewAllReservations() {
    reservationManager.printAllReservations();
}

void SystemManager::viewMyReservations() {
    cout << "현재 로그인된 (" << currentLoggedInUserId << ") 님의 예약 목록입니다. (기능 미구현)" << endl;
    // TODO: ReservationManager에 특정 고객 ID의 예약만 조회하는 함수 추가 후 호출하기
    // 예: reservationManager.printReservationsByCustomerId(currentLoggedInUserId);
}

// --- 권한별 함수 (미구현) ---

void SystemManager::employeeViewTodayReservations() {
    cout << "오늘의 예약 확인 기능입니다." << endl;
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << (ltm->tm_year + 1900) << "-"
        << setfill('0') << setw(2) << (ltm->tm_mon + 1) << "-"
        << setfill('0') << setw(2) << ltm->tm_mday;
    string todayDate = ss.str();

    cout << "오늘 날짜: " << todayDate << endl;
    // TODO: ReservationManager에 특정 날짜의 예약만 조회하는 함수 추가 후 호출하기
    // 예: reservationManager.printReservationsForDate(todayDate);
    cout << "오늘 날짜의 예약 목록을 ReservationManager를 통해 조회해야 합니다. (기능 미구현)" << endl;
}