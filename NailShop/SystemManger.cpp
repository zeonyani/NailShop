// SystemManager.cpp
#include "SystemManager.h"  // SystemManager 클래스
#include <iostream>         // 콘솔 출력
#include <limits>           // numeric_limits (입력 버퍼 비우기)
#include <string>           // std::string, getline
#include <ctime>            // 현재 시간
#include <iomanip>          // 출력 포맷팅
#include <sstream>          // 문자열 스트림

using namespace std;        // std:: 네임스페이스 사용

// SystemManager 생성자
SystemManager::SystemManager()
    : currentLoggedInUserType(UserType::None),
    currentLoggedInUserId(""),
    currentLoggedInUserName(""),
    currentLoggedInUserPhone("")
{
    cout << "네일샵 예약 시스템 시작." << endl;
}

// 시스템 실행 진입점
void SystemManager::run() {
    // 1. 초기 관리자 계정 생성
    createInitialAdminAccount();
    // 2. 초기 서비스 데이터 생성
    createInitialServices();

    // 3. 로그인/회원가입 메뉴
    int entryChoice;
    bool loggedIn = false;
    do {
        displayEntryMenu();
        cout << "메뉴 선택: ";
        if (!(cin >> entryChoice)) {
            cout << "잘못된 입력. 숫자 입력 필요." << endl;
            cin.clear(); // 오류 플래그 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 개행 문자 비우기

        if (entryChoice == 1) { // 로그인
            loggedIn = loginUser();
        }
        else if (entryChoice == 2) { // 회원가입
            registerCustomerAccount();
        }
        else if (entryChoice == 0) { // 종료
            cout << "프로그램 종료." << endl;
            return;
        }
        else {
            cout << "잘못된 입력. 다시 시도." << endl;
        }

        if (!loggedIn && entryChoice != 0) { // 로그인 실패 및 종료 아님
            cout << "\n로그인 또는 다른 작업 다시 시도." << endl;
            cout << "계속하려면 Enter 입력...";
            cin.get();
        }

    } while (!loggedIn); // 로그인 성공 시까지 반복

    // 로그인 성공 후 메인 메뉴 진입
    int mainMenuChoice;
    do {
        displayMainMenu(); // 메인 메뉴 표시
        cout << "메뉴 선택: ";

        // 사용자 입력 및 유효성 검사
        if (!(cin >> mainMenuChoice)) {
            cout << "잘못된 입력. 숫자 입력 필요." << endl;
            cin.clear(); // 오류 플래그 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
            mainMenuChoice = -1; // 잘못된 입력 표시
            continue; // 루프 재시작
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 개행 문자 비우기

        handleMainMenuInput(mainMenuChoice); // 사용자 선택 기능 처리

        // 종료 (0) 선택 아닐 시 Enter 대기
        if (mainMenuChoice != 0) {
            cout << "\n계속하려면 Enter 입력...";
            cin.get();
        }

    } while (mainMenuChoice != 0); // 0 선택 시까지 반복
    cout << "네일샵 예약 시스템 종료." << endl;
}

// 초기 관리자 계정 생성
void SystemManager::createInitialAdminAccount() {
    // "owner" ID 계정 존재 확인
    const User* adminUser = userManager.getUser("owner");
    if (adminUser == nullptr) { // "owner" 계정 없음
        cout << "\n--- 초기 설정: 관리자 계정 생성 ---" << endl;
        cout << "시스템에 등록된 관리자 계정 없음." << endl;
        cout << "초기 관리자 계정(ID: owner, PW: ownerpass, 이름: 김사장) 생성 중..." << endl;
        bool success = userManager.addUser("owner", "ownerpass", UserType::Owner, "김사장", "010-1111-2222"); // 포맷팅된 번호로 입력
        if (success) {
            cout << "초기 관리자 계정 성공적 생성. 이제 owner 계정으로 로그인 가능." << endl;
        }
        else {
            cout << "오류: 초기 관리자 계정 생성 실패." << endl;
        }
    }
}

// 초기 서비스 데이터 생성
void SystemManager::createInitialServices() {
    // ServiceManager에 서비스 없을 시 초기 서비스 추가
    if (serviceManager.getService("SVC1") == nullptr &&
        serviceManager.getService("SVC2") == nullptr &&
        serviceManager.getService("SVC3") == nullptr) {

        cout << "\n--- 초기 설정: 기본 서비스 생성 ---" << endl;
        cout << "등록된 서비스 없음. 기본 서비스 생성 중..." << endl;
        serviceManager.addService("기본 네일", 20000, 60);
        serviceManager.addService("젤 패디", 40000, 90);
        serviceManager.addService("속눈썹 펌", 30000, 45);
        cout << "기본 서비스 생성 완료." << endl;
    }
}

// 프로그램 시작 시 진입 메뉴 출력
void SystemManager::displayEntryMenu() {
    cout << "\n--- 환영합니다! ---" << endl;
    cout << "1. 로그인" << endl;
    cout << "2. 회원가입 (고객 전용)" << endl;
    cout << "0. 프로그램 종료" << endl;
}

// 사용자 로그인 처리
bool SystemManager::loginUser() {
    string userId, password;
    cout << "\n--- 로그인 ---" << endl;
    cout << "사용자 ID: ";
    getline(cin, userId); // 사용자 ID 입력
    cout << "비밀번호: ";
    getline(cin, password); // 비밀번호 입력

    // UserManager를 통한 로그인 시도
    currentLoggedInUserType = userManager.login(userId, password);

    if (currentLoggedInUserType == UserType::None) { // 로그인 실패
        currentLoggedInUserId = ""; // ID 초기화
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
        return false;
    }
    currentLoggedInUserId = userId; // 로그인 성공 시 ID 저장

    // 로그인 사용자 이름/전화번호 가져오기
    const User* loggedInUser = userManager.getUser(userId);
    if (loggedInUser) {
        currentLoggedInUserName = loggedInUser->getName();
        currentLoggedInUserPhone = loggedInUser->getFormattedPhone(); // 포맷팅된 번호로 저장
    }
    else { // 예외 처리 (발생하지 않아야 함)
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
    }
    return true; // 로그인 성공
}

// 고객 회원가입 처리
void SystemManager::registerCustomerAccount() {
    cout << "\n--- 고객 회원가입 ---" << endl;
    string userId, password, name, phone;

    cout << "사용할 ID 입력: ";
    getline(cin, userId);

    // ID 중복 검사
    if (userManager.getUser(userId) != nullptr) {
        cout << "오류: 이미 존재하는 ID. 다른 ID 사용 필요." << endl;
        return;
    }

    cout << "사용할 비밀번호 입력: ";
    getline(cin, password);
    cout << "이름 입력: ";
    getline(cin, name);
    cout << "전화번호 입력 (하이픈 포함 또는 숫자만, 예: 010-1234-5678): "; // 입력 가이드 추가
    getline(cin, phone);

    bool success = userManager.addUser(userId, password, UserType::Customer, name, phone);
    if (success) {
        cout << "회원가입 완료. 이제 로그인 가능!" << endl;
    }
    else {
        // addUser에서 유효성 검사 실패 시 메시지 출력
        // cout << "회원가입 실패 (알 수 없는 오류)." << endl; // UserManager에서 메시지 처리
    }
}

// 메인 메뉴 출력
void SystemManager::displayMainMenu() {
    cout << "\n--- 메인 메뉴 ---" << endl;
    // 현재 로그인 사용자 정보 표시
    cout << "현재 로그인: " << currentLoggedInUserName << " (" << currentLoggedInUserId << ", "
        << currentLoggedInUserPhone << ", " // 이미 포맷팅된 번호 사용
        << (currentLoggedInUserType == UserType::Owner ? "사장" :
            currentLoggedInUserType == UserType::Employee ? "직원" :
            currentLoggedInUserType == UserType::Customer ? "고객" :
            "알 수 없음")
        << ")" << endl;

    cout << "1. 내 예약 조회" << endl;

    // 사용자 유형에 따른 메뉴 분기
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
        cout << "6. 사용자 관리" << endl; // 사용자 관리 하위 메뉴
        cout << "7. 서비스 관리" << endl; // 서비스 관리 하위 메뉴
    }

    cout << "0. 로그아웃 및 종료" << endl;
}

// 메인 메뉴 사용자 입력 처리
void SystemManager::handleMainMenuInput(int choice) {
    switch (choice) {
    case 1: // '내 예약 조회' 또는 '특정 예약 조회'
        if (currentLoggedInUserType == UserType::Customer) {
            viewMyReservations();
        }
        else { // 직원, 사장은 특정 예약 조회
            viewSpecificReservation();
        }
        break;
    case 0: // 로그아웃 및 종료
        break;
    default: // 그 외 메뉴 선택 처리
        if (currentLoggedInUserType == UserType::Customer) {
            switch (choice) {
            case 2: addNewReservation(); break;
            case 3: cancelExistingReservation(); break;
            default: cout << "잘못된 입력. 다시 시도." << endl; break;
            }
        }
        else if (currentLoggedInUserType == UserType::Employee || currentLoggedInUserType == UserType::Owner) {
            switch (choice) {
            case 2: employeeViewTodayReservations(); break; // 오늘 예약 확인
            case 3: viewAllReservations(); break;             // 전체 예약 보기
            case 4: addNewReservation(); break;               // 예약 추가
            case 5: cancelExistingReservation(); break;       // 예약 취소
            case 6: // 사용자 관리 (사장 전용)
                if (currentLoggedInUserType == UserType::Owner) {
                    manageUsers(); // 사용자 관리 하위 메뉴 호출
                }
                else {
                    cout << "해당 기능 권한 없음." << endl;
                }
                break;
            case 7: // 서비스 관리 (사장 전용)
                if (currentLoggedInUserType == UserType::Owner) {
                    manageServices(); // 서비스 관리 하위 메뉴 호출
                }
                else {
                    cout << "해당 기능 권한 없음." << endl;
                }
                break;
            default: cout << "잘못된 입력. 다시 시도." << endl; break;
            }
        }
        else {
            cout << "오류: 로그인 상태 알 수 없음. 다시 로그인 필요." << endl;
        }
        break;
    }
}

// 새 예약 추가
void SystemManager::addNewReservation() {
    string customerId_input, service_name, datetime;
    cout << "\n--- 새 예약 추가 ---" << endl;

    // 고객인 경우 자신의 ID 자동 입력
    if (currentLoggedInUserType == UserType::Customer) {
        customerId_input = currentLoggedInUserId;
        cout << "고객 ID: " << customerId_input << " (자동 입력)" << endl;
    }
    else { // 직원이나 사장인 경우 고객 ID 직접 입력
        cout << "예약할 고객 ID 입력: ";
        getline(cin, customerId_input);
        // 고객 ID 존재 여부 및 유형 확인
        const User* existingCustomer = userManager.getUser(customerId_input);
        if (existingCustomer == nullptr || existingCustomer->getUserType() != UserType::Customer) {
            cout << "오류: 유효한 고객 ID 아님 또는 고객 계정 아님. 예약 취소." << endl;
            return;
        }
    }

    // 서비스 목록 표시 및 선택 유도
    cout << "\n--- 이용 가능 서비스 목록 ---" << endl;
    serviceManager.printAllServices();
    cout << "\n예약할 서비스 이름 정확히 입력: ";
    getline(cin, service_name);

    // 서비스 유효성 확인
    const Service* selectedService = serviceManager.getServiceByName(service_name);
    if (selectedService == nullptr) {
        cout << "오류: '서비스 목록'에 없는 서비스 이름. 예약 취소." << endl;
        return;
    }

    cout << "예약 날짜 및 시간 입력 (예: 2025-06-20 15:00): ";
    getline(cin, datetime);

    reservationManager.addReservation(customerId_input, selectedService->getName(), datetime);
}

// 기존 예약 취소
void SystemManager::cancelExistingReservation() {
    string reservationId;
    cout << "\n--- 예약 취소 ---" << endl;
    // 사장/직원은 전체 목록 표시
    if (currentLoggedInUserType == UserType::Employee || currentLoggedInUserType == UserType::Owner) {
        reservationManager.printAllReservations();
    }
    else { // 고객은 자신의 예약만 표시
        reservationManager.printReservationsByCustomerId(currentLoggedInUserId);
    }

    cout << "취소할 예약 ID 입력: ";
    getline(cin, reservationId);

    // 고객은 자신의 예약만 취소 가능 (추가 검증)
    if (currentLoggedInUserType == UserType::Customer) {
        const Reservation* res = reservationManager.getReservation(reservationId); // 예약 정보 조회

        if (res == nullptr) {
            cout << "오류: 해당 예약 ID 찾을 수 없음." << endl;
            return; // 예약 없음
        }

        if (res->getCustomerId() != currentLoggedInUserId) {
            cout << "오류: 자신의 예약만 취소 가능. 해당 예약은 고객 ID '"
                << res->getCustomerId() << "'의 예약." << endl;
            return; // 자신의 예약 아님
        }
    }

    reservationManager.deleteReservation(reservationId);
}

// 특정 예약 조회
void SystemManager::viewSpecificReservation() {
    string reservationId;
    cout << "\n--- 특정 예약 조회 ---" << endl;
    cout << "조회할 예약 ID 입력: ";
    getline(cin, reservationId);
    reservationManager.printReservation(reservationId);
}

// 모든 예약 조회
void SystemManager::viewAllReservations() {
    reservationManager.printAllReservations();
}

// 내 예약 조회 (고객 전용)
void SystemManager::viewMyReservations() {
    cout << "\n--- 나의 예약 조회 ---" << endl;
    reservationManager.printReservationsByCustomerId(currentLoggedInUserId);
}

// 오늘 예약 확인 (직원/사장)
void SystemManager::employeeViewTodayReservations() {
    cout << "\n--- 오늘 예약 확인 ---" << endl;
    time_t now = time(0); // 현재 시간

    tm ltm_s;
    localtime_s(&ltm_s, &now); // 로컬 시간 변환

    stringstream ss;
    // 오늘 날짜 "YYYY-MM-DD" 형식 포맷팅
    ss << (ltm_s.tm_year + 1900) << "-"
        << setfill('0') << setw(2) << (ltm_s.tm_mon + 1) << "-"
        << setfill('0') << setw(2) << ltm_s.tm_mday;
    string todayDate = ss.str();

    cout << "오늘 날짜: " << todayDate << endl;
    reservationManager.printReservationsForDate(todayDate); // 날짜별 예약 출력
}

// 사용자 관리 메뉴 (사장 전용)
void SystemManager::manageUsers() {
    int userMenuChoice;
    do {
        cout << "\n--- 사용자 관리 (사장 전용) ---" << endl;
        cout << "1. 새 직원/고객 계정 추가" << endl;
        cout << "2. 직원/고객 계정 삭제" << endl;
        cout << "3. 모든 사용자 목록 보기" << endl;
        cout << "4. 사용자 검색 (ID)" << endl;
        cout << "0. 메인 메뉴로 돌아가기" << endl;
        cout << "메뉴 선택: ";

        if (!(cin >> userMenuChoice)) {
            cout << "잘못된 입력. 숫자 입력 필요." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            userMenuChoice = -1;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (userMenuChoice) {
        case 1: addStaffOrCustomerAccount(); break;
        case 2: deleteStaffOrCustomerAccount(); break;
        case 3: viewAllUsers(); break;
        case 4: searchUser(); break;
        case 0: cout << "메인 메뉴로 돌아가기." << endl; break;
        default: cout << "잘못된 입력. 다시 시도." << endl; break;
        }
        if (userMenuChoice != 0) {
            cout << "\n계속하려면 Enter 입력...";
            cin.get();
        }
    } while (userMenuChoice != 0);
}

// 새 직원/고객 계정 추가 (관리자 전용)
void SystemManager::addStaffOrCustomerAccount() {
    cout << "\n--- 새 직원/고객 계정 추가 ---" << endl;
    string userId, password, name, phone, typeStr;
    UserType type = UserType::None;

    cout << "추가할 계정 유형 선택 (1: 고객, 2: 직원): ";
    getline(cin, typeStr);

    if (typeStr == "1") {
        type = UserType::Customer;
    }
    else if (typeStr == "2") {
        type = UserType::Employee;
    }
    else {
        cout << "잘못된 유형 선택. 계정 추가 취소." << endl;
        return;
    }

    cout << "새 계정 ID 입력: ";
    getline(cin, userId);

    // ID 중복 검사
    if (userManager.getUser(userId) != nullptr) {
        cout << "오류: 사용자 ID '" << userId << "' 이미 존재. 다른 ID 사용 필요." << endl;
        return;
    }

    cout << "새 계정 비밀번호 입력: ";
    getline(cin, password);
    cout << "새 계정 이름 입력: ";
    getline(cin, name);
    cout << "새 계정 전화번호 입력 (하이픈 포함 또는 숫자만, 예: 010-1234-5678): "; // 입력 가이드 추가
    getline(cin, phone);

    bool success = userManager.addUser(userId, password, type, name, phone);
    if (success) {
        cout << "새 계정 성공적 추가." << endl;
    }
    else {
        // addUser에서 유효성 검사 실패 시 메시지 출력
        // cout << "계정 추가 실패 (알 수 없는 오류)." << endl;
    }
}

// 직원/고객 계정 삭제 (사장 전용)
void SystemManager::deleteStaffOrCustomerAccount() {
    cout << "\n--- 직원/고객 계정 삭제 ---" << endl;
    userManager.printAllUsers(); // 모든 사용자 목록 표시

    string userIdToDelete;
    cout << "\n삭제할 사용자 ID 입력: ";
    getline(cin, userIdToDelete);

    if (userIdToDelete == currentLoggedInUserId) {
        cout << "오류: 현재 로그인된 자신의 계정 삭제 불가." << endl;
        return;
    }

    userManager.deleteUser(userIdToDelete);
}

// 모든 사용자 목록 보기 (사장 전용)
void SystemManager::viewAllUsers() {
    userManager.printAllUsers();
}

// 사용자 검색 (ID로) (사장/직원 전용)
void SystemManager::searchUser() {
    cout << "\n--- 사용자 검색 (ID) ---" << endl;
    string userIdToSearch;
    cout << "검색할 사용자 ID 입력: ";
    getline(cin, userIdToSearch);

    const User* user = userManager.getUser(userIdToSearch);
    if (user) {
        cout << "\n--- 사용자 정보 ---" << endl;
        cout << "ID: " << user->getUserId() << endl;
        cout << "이름: " << user->getName() << endl;
        cout << "유형: " << (user->getUserType() == UserType::Owner ? "사장" :
            user->getUserType() == UserType::Employee ? "직원" : "고객") << endl;
        cout << "전화번호: " << user->getFormattedPhone() << endl; // 포맷팅된 번호 출력
        cout << "--------------------" << endl;
    }
    else {
        cout << "사용자 ID '" << userIdToSearch << "' 찾을 수 없음." << endl;
    }
}

// 서비스 관리 메뉴 (사장 전용)
void SystemManager::manageServices() {
    int serviceMenuChoice;
    do {
        cout << "\n--- 서비스 관리 ---" << endl;
        cout << "1. 서비스 추가" << endl;
        cout << "2. 서비스 수정" << endl;
        cout << "3. 서비스 삭제" << endl;
        cout << "4. 모든 서비스 목록 보기" << endl;
        cout << "0. 메인 메뉴로 돌아가기" << endl;
        cout << "메뉴 선택: ";

        if (!(cin >> serviceMenuChoice)) {
            cout << "잘못된 입력. 숫자 입력 필요." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            serviceMenuChoice = -1;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (serviceMenuChoice) {
        case 1: addService(); break;
        case 2: updateService(); break;
        case 3: deleteService(); break;
        case 4: viewServices(); break;
        case 0: cout << "메인 메뉴로 돌아가기." << endl; break;
        default: cout << "잘못된 입력. 다시 시도." << endl; break;
        }
        if (serviceMenuChoice != 0) {
            cout << "\n계속하려면 Enter 입력...";
            cin.get();
        }
    } while (serviceMenuChoice != 0);
}

// 서비스 추가
void SystemManager::addService() {
    string name;
    double price;
    int duration;

    cout << "\n--- 서비스 추가 ---" << endl;
    cout << "서비스 이름: ";
    getline(cin, name);

    cout << "가격: ";
    while (!(cin >> price) || price < 0) {
        cout << "잘못된 입력. 유효한 가격(숫자) 입력 필요: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "소요 시간 (분): ";
    while (!(cin >> duration) || duration <= 0) {
        cout << "잘못된 입력. 유효한 시간(양수 숫자) 입력 필요: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 남은 개행 문자 처리

    serviceManager.addService(name, price, duration);
}

// 서비스 수정
void SystemManager::updateService() {
    string serviceId, nameStr, priceStr, durationStr;
    double price;
    int duration;

    cout << "\n--- 서비스 수정 ---" << endl;
    serviceManager.printAllServices(); // 현재 서비스 목록 표시
    cout << "\n수정할 서비스 ID 입력: ";
    getline(cin, serviceId);

    const Service* existingService = serviceManager.getService(serviceId);
    if (!existingService) {
        cout << "오류: 해당 서비스 ID 찾을 수 없음." << endl;
        return;
    }

    cout << "새 서비스 이름 (현재: " << existingService->getName() << ", 변경 없으면 Enter): ";
    getline(cin, nameStr);
    if (nameStr.empty()) nameStr = existingService->getName(); // 입력 없으면 기존 값 유지

    cout << "새 가격 (현재: " << fixed << setprecision(0) << existingService->getPrice() << "원, 변경 없으면 Enter): ";
    getline(cin, priceStr);
    if (priceStr.empty()) {
        price = existingService->getPrice();
    }
    else {
        try {
            price = stod(priceStr);
            if (price < 0) throw invalid_argument("Negative price");
        }
        catch (const invalid_argument& e) {
            cout << "잘못된 가격 입력. 기존 가격 유지." << endl;
            price = existingService->getPrice();
        }
        catch (const out_of_range& e) {
            cout << "가격 범위 초과. 기존 가격 유지." << endl;
            price = existingService->getPrice();
        }
    }

    cout << "새 소요 시간(분) (현재: " << existingService->getDurationMinutes() << "분, 변경 없으면 Enter): ";
    getline(cin, durationStr);
    if (durationStr.empty()) {
        duration = existingService->getDurationMinutes();
    }
    else {
        try {
            duration = stoi(durationStr);
            if (duration <= 0) throw invalid_argument("Non-positive duration");
        }
        catch (const invalid_argument& e) {
            cout << "잘못된 소요 시간 입력. 기존 시간 유지." << endl;
            duration = existingService->getDurationMinutes();
        }
        catch (const out_of_range& e) {
            cout << "소요 시간 범위 초과. 기존 시간 유지." << endl;
            duration = existingService->getDurationMinutes();
        }
    }

    serviceManager.updateService(serviceId, nameStr, price, duration);
}

// 서비스 목록 보기
void SystemManager::viewServices() {
    serviceManager.printAllServices();
}

// 서비스 삭제
void SystemManager::deleteService() {
    string serviceId;
    cout << "\n--- 서비스 삭제 ---" << endl;
    serviceManager.printAllServices(); // 현재 서비스 목록 표시
    cout << "\n삭제할 서비스 ID 입력: ";
    getline(cin, serviceId);

    serviceManager.deleteService(serviceId);
}
