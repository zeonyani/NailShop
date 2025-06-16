#include "SystemManager.h"
#include <iostream>
#include <limits> // numeric_limits를 위해 필요
#include <string> // getline을 위해 필요

// !!! 주의: using namespace std; 사용으로 인한 이름 충돌 가능성을 인지하고 사용하십시오. !!!
using namespace std;

// 생성자 구현
SystemManager::SystemManager() {
    cout << "네일샵 예약 시스템을 시작합니다." << endl;
}

// 시스템 메인 루프
void SystemManager::run() {
    int choice;
    do {
        displayMainMenu();
        cout << "메뉴를 선택하세요: ";
        cin >> choice;

        // 입력 버퍼 비우기 (cin 다음에 getline 사용 시 필수)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        handleMainMenuInput(choice);

        // 프로그램 종료 (0번)이 아닌 경우에만 잠시 멈춤
        if (choice != 0) {
            cout << "\n계속하려면 Enter를 누르세요...";
            cin.get(); // Enter 입력 대기
        }

    } while (choice != 0); // 0을 입력하면 종료
    cout << "네일샵 예약 시스템을 종료합니다." << endl;
}

// 메인 메뉴 출력
void SystemManager::displayMainMenu() {
    cout << "\n--- 메인 메뉴 ---" << endl;
    cout << "1. 예약 관리" << endl;
    cout << "0. 프로그램 종료" << endl;
}

// 메인 메뉴 입력 처리
void SystemManager::handleMainMenuInput(int choice) {
    switch (choice) {
    case 1:
        reservationMenu(); // 예약 관리 서브 메뉴 호출
        break;
    case 0:
        // 종료 메시지는 run() 함수에서 처리
        break;
    default:
        cout << "잘못된 입력입니다. 다시 시도해주세요." << endl;
        break;
    }
}

// 예약 관리 서브 메뉴 출력
void SystemManager::reservationMenu() {
    int choice;
    do {
        cout << "\n--- 예약 관리 메뉴 ---" << endl;
        cout << "1. 새 예약 추가" << endl;
        cout << "2. 예약 취소 (삭제)" << endl;
        cout << "3. 특정 예약 조회" << endl;
        cout << "4. 전체 예약 목록 보기" << endl;
        cout << "0. 뒤로가기 (메인 메뉴)" << endl;
        cout << "메뉴를 선택하세요: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기

        handleReservationMenuInput(choice);

        // 뒤로가기(0번)이 아닌 경우에만 잠시 멈춤
        if (choice != 0) {
            cout << "\n계속하려면 Enter를 누르세요...";
            cin.get();
        }

    } while (choice != 0);
}

// 예약 관리 메뉴 입력 처리
void SystemManager::handleReservationMenuInput(int choice) {
    switch (choice) {
    case 1:
        addNewReservation();
        break;
    case 2:
        cancelExistingReservation();
        break;
    case 3:
        viewSpecificReservation();
        break;
    case 4:
        viewAllReservations();
        break;
    case 0:
        // 뒤로가기 (상위 메뉴로 돌아감)
        break;
    default:
        cout << "잘못된 입력입니다. 다시 시도해주세요." << endl;
        break;
    }
}

// --- 예약 관리 기능 함수 구현 ---

void SystemManager::addNewReservation() {
    string customerId, service, datetime;
    cout << "새로운 예약을 추가합니다." << endl;
    cout << "고객 ID를 입력하세요: ";
    getline(cin, customerId);
    cout << "서비스 종류를 입력하세요 (예: 네일아트, 패디큐어): ";
    getline(cin, service);
    cout << "예약 날짜 및 시간을 입력하세요 (예: 2025-06-20 15:00): ";
    getline(cin, datetime);

    reservationManager.addReservation(customerId, service, datetime);
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