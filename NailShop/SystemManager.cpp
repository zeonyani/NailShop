// SystemManager.cpp

#include "SystemManager.h"
#include <iostream>
#include <limits> // std::numeric_limits
#include <algorithm> // std::transform
#include <cctype> // std::tolower
#include <iomanip> // std::put_time, std::get_time
#include <chrono> // 시간 관련
#include <sstream> // std::stringstream

// SystemManager 생성자
SystemManager::SystemManager()
    : userManager(),
    serviceManager(),
    reservationManager(serviceManager),
    currentLoggedInUserType(UserType::None),
    currentLoggedInUserId(""),
    currentLoggedInUserName(""),
    currentLoggedInUserPhone("")
{

}

// 입력 버퍼를 비우는 헬퍼 함수
void SystemManager::clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
}

// 사장 서비스 관리 기능
void SystemManager::handleOwnerServiceManagement() {
    int choice;
    do {
        std::cout << "\n--- 사장 서비스 관리 ---\n" << std::endl;
        std::cout << "1. 모든 서비스 목록 보기" << std::endl;
        // 2. 서비스 추가 (삭제했으므로 제거)
        // 3. 서비스 정보 수정 (삭제했으므로 제거)
        // 4. 서비스 삭제 (삭제했으므로 제거)
        std::cout << "0. 뒤로가기" << std::endl;
        std::cout << "선택: ";
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
            serviceManager.printAllServices(); // 이 부분은 유지
            break;
            // case 2: addService(); break;       // 삭제
            // case 3: updateService(); break;    // 삭제
            // case 4: deleteService(); break;    // 삭제
        case 0:
            std::cout << "서비스 관리 메뉴를 종료합니다." << std::endl;
            break;
        default:
            std::cout << "유효하지 않은 선택입니다. 다시 시도해주세요." << std::endl;
            break;
        }
    } while (choice != 0);
}

// 시스템 실행
void SystemManager::run() {
    while (true) {
        displayMainMenu();
        int choice;
        std::cout << "선택: ";
        std::cin >> choice;
        clearInputBuffer(); // 입력 버퍼 비우기

        processMainMenuInput(choice);
    }
}

// 메인 메뉴 출력
void SystemManager::displayMainMenu() {
    std::cout << "\n--- 메인 메뉴 ---\n" << std::endl;
    std::cout << "1. 로그인" << std::endl;
    std::cout << "2. 회원가입 (고객)" << std::endl;
    std::cout << "3. 종료" << std::endl;
}

// 메인 메뉴 입력 처리
void SystemManager::processMainMenuInput(int choice) {
    switch (choice) {
    case 1: // 로그인
        handleLogin();
        break;
    case 2: // 회원가입 (고객)
        addUser(); // 고객 회원가입 기능 재사용
        break;
    case 3: // 종료
        std::cout << "프로그램을 종료합니다." << std::endl;
        exit(0);
    default:
        std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl;
        break;
    }
}

// 로그인 처리
void SystemManager::handleLogin() {
    std::string userId, password;
    std::cout << "\n--- 로그인 ---\n" << std::endl;
    std::cout << "아이디: ";
    std::cin >> userId;
    std::cout << "비밀번호: ";
    std::cin >> password;
    clearInputBuffer();

    currentLoggedInUserType = userManager.login(userId, password);

    if (currentLoggedInUserType != UserType::None) {
        const User* user = userManager.getUser(userId);
        if (user) {
            currentLoggedInUserId = user->getUserId();
            currentLoggedInUserName = user->getName();
            currentLoggedInUserPhone = user->getPhone();
            std::cout << currentLoggedInUserName << "님 환영합니다! (" << userId << ")" << std::endl;
        }

        switch (currentLoggedInUserType) {
        case UserType::Owner:
            while (true) {
                displayOwnerMenu();
                int choice;
                std::cout << "선택: ";
                std::cin >> choice;
                clearInputBuffer();
                processOwnerMenuInput(choice);
                if (choice == 5) break; // 로그아웃
            }
            break;
        case UserType::Employee:
            while (true) {
                displayEmployeeMenu();
                int choice;
                std::cout << "선택: ";
                std::cin >> choice;
                clearInputBuffer();
                processEmployeeMenuInput(choice);
                if (choice == 4) break; // 로그아웃
            }
            break;
        case UserType::Customer:
            while (true) {
                displayCustomerMenu();
                int choice;
                std::cout << "선택: ";
                std::cin >> choice;
                clearInputBuffer();
                processCustomerMenuInput(choice);
                if (choice == 3) break; // 로그아웃
            }
            break;
        default:
            // 이 경우는 발생하지 않아야 함
            break;
        }
    }
    else {
        std::cout << "로그인 실패: 아이디 또는 비밀번호가 올바르지 않습니다." << std::endl;
    }
}

// 사장 메뉴 출력
void SystemManager::displayOwnerMenu() {
    std::cout << "\n--- 사장 메뉴 ---\n" << std::endl;
    std::cout << "1. 서비스 관리" << std::endl;
    std::cout << "2. 사용자 계정 관리" << std::endl;
    std::cout << "3. 예약 관리" << std::endl;
    std::cout << "4. 내 계정 정보 관리" << std::endl;
    std::cout << "5. 로그아웃" << std::endl;
}

// 사장 메뉴 입력 처리
void SystemManager::processOwnerMenuInput(int choice) {
    switch (choice) {
    case 1:
        handleOwnerServiceManagement();
        break;
    case 2:
        handleOwnerUserManagement();
        break;
    case 3:
        handleOwnerReservationManagement();
        break;
    case 4:
        handleOwnerAccountInfo();
        break;
    case 5:
        std::cout << "로그아웃 되었습니다." << std::endl;
        currentLoggedInUserType = UserType::None;
        currentLoggedInUserId = "";
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
        break;
    default:
        std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl;
        break;
    }
}

// 사장 사용자 계정 관리
void SystemManager::handleOwnerUserManagement() {
    while (true) {
        std::cout << "\n--- 사장 사용자 계정 관리 ---\n" << std::endl;
        std::cout << "1. 사용자 추가 (직원/고객)" << std::endl;
        std::cout << "2. 사용자 삭제" << std::endl;
        std::cout << "3. 사용자 계정 정보 수정" << std::endl; // 특정 사용자
        std::cout << "4. 모든 사용자 목록 보기" << std::endl;
        std::cout << "5. 뒤로 가기" << std::endl;
        std::cout << "선택: ";
        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
            addUser();
            break;
        case 2:
            deleteUser();
            break;
        case 3: {
            std::string targetUserId;
            std::cout << "정보를 수정할 사용자 ID: ";
            std::cin >> targetUserId;
            clearInputBuffer();
            updateUserAccountInfo(targetUserId);
            break;
        }
        case 4:
            userManager.printAllUsers();
            break;
        case 5:
            return;
        default:
            std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl;
            break;
        }
    }
}

// 사장 예약 관리
void SystemManager::handleOwnerReservationManagement() {
    while (true) {
        std::cout << "\n--- 사장 예약 관리 ---\n" << std::endl;
        std::cout << "1. 예약 생성" << std::endl;
        std::cout << "2. 예약 취소" << std::endl;
        std::cout << "3. 모든 예약 목록 보기" << std::endl;
        std::cout << "4. 고객별 예약 목록 보기" << std::endl;
        std::cout << "5. 날짜별 예약 목록 보기" << std::endl;
        std::cout << "6. 뒤로 가기" << std::endl;
        std::cout << "선택: ";
        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
            makeReservation();
            break;
        case 2:
            cancelReservation();
            break;
        case 3:
            viewAllReservations();
            break;
        case 4:
            viewReservationsByCustomer();
            break;
        case 5:
            viewReservationsForDate();
            break;
        case 6:
            return;
        default:
            std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl;
            break;
        }
    }
}

// 사장 계정 정보 관리
void SystemManager::handleOwnerAccountInfo() {
    updateUserAccountInfo(currentLoggedInUserId); // 현재 로그인한 사장 계정 정보 수정
}


// 직원 메뉴 출력
void SystemManager::displayEmployeeMenu() {
    std::cout << "\n--- 직원 메뉴 ---\n" << std::endl;
    std::cout << "1. 서비스 관리" << std::endl; // 사장과 동일한 기능
    std::cout << "2. 예약 관리" << std::endl;   // 사장과 동일한 기능
    std::cout << "3. 내 계정 정보 관리" << std::endl;
    std::cout << "4. 로그아웃" << std::endl;
}

// 직원 메뉴 입력 처리
void SystemManager::processEmployeeMenuInput(int choice) {
    switch (choice) {
    case 1:
        handleEmployeeServiceManagement(); // 이 함수를 호출
        break;
    case 2:
        handleEmployeeReservationManagement();
        break;
    case 3:
        handleEmployeeAccountInfo();
        break;
    case 4:
        std::cout << "로그아웃 되었습니다." << std::endl;
        currentLoggedInUserType = UserType::None;
        currentLoggedInUserId = "";
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
        break;
    default:
        std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl;
        break;
    }
}

// 직원 서비스 관리 (사장 서비스 관리와 동일)
void SystemManager::handleEmployeeServiceManagement() {
    handleOwnerServiceManagement(); // 사장 서비스 관리 함수 재사용
}

// 직원 예약 관리 (사장 예약 관리와 동일)
void SystemManager::handleEmployeeReservationManagement() {
    handleOwnerReservationManagement(); // 사장 예약 관리 함수 재사용
}

// 직원 계정 정보 관리
void SystemManager::handleEmployeeAccountInfo() {
    updateUserAccountInfo(currentLoggedInUserId); // 현재 로그인한 직원 계정 정보 수정
}


// 고객 메뉴 출력
void SystemManager::displayCustomerMenu() {
    std::cout << "\n--- 고객 메뉴 ---\n" << std::endl;
    std::cout << "1. 예약 관리" << std::endl;
    std::cout << "2. 내 계정 정보 관리" << std::endl;
    std::cout << "3. 로그아웃" << std::endl;
}

// 고객 메뉴 입력 처리
void SystemManager::processCustomerMenuInput(int choice) {
    switch (choice) {
    case 1:
        handleCustomerReservationManagement();
        break;
    case 2:
        handleCustomerAccountInfo();
        break;
    case 3:
        std::cout << "로그아웃 되었습니다." << std::endl;
        currentLoggedInUserType = UserType::None;
        currentLoggedInUserId = "";
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
        break;
    default:
        std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl;
        break;
    }
}

// 고객 예약 관리
void SystemManager::handleCustomerReservationManagement() {
    while (true) {
        std::cout << "\n--- 고객 예약 관리 ---\n" << std::endl;
        std::cout << "1. 예약 생성" << std::endl;
        std::cout << "2. 내 예약 취소" << std::endl;
        std::cout << "3. 내 예약 목록 보기" << std::endl;
        std::cout << "4. 뒤로 가기" << std::endl;
        std::cout << "선택: ";
        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
            makeReservation();
            break;
        case 2:
            cancelReservation(currentLoggedInUserId); // 자신의 예약만 취소
            break;
        case 3:
            viewReservationsByCustomer(currentLoggedInUserId); // 자신의 예약만 보기
            break;
        case 4:
            return;
        default:
            std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl;
            break;
        }
    }
}

// 고객 계정 정보 관리
void SystemManager::handleCustomerAccountInfo() {
    updateUserAccountInfo(currentLoggedInUserId); // 현재 로그인한 고객 계정 정보 수정
}

// ====================================================================================================
// 사용자 관리 기능 구현
// ====================================================================================================

// 사용자 추가 (회원가입 포함)
void SystemManager::addUser() {
    std::string userId, password, name, phone;
    int typeChoice;
    UserType userType = UserType::None;

    std::cout << "\n--- 사용자 추가 ---\n" << std::endl;
    if (currentLoggedInUserType == UserType::Owner) { // 사장만 직원/고객 선택 가능
        std::cout << "추가할 사용자 유형 선택:\n";
        std::cout << "1. 고객\n";
        std::cout << "2. 직원\n";
        std::cout << "선택: ";
        while (!(std::cin >> typeChoice) || (typeChoice != 1 && typeChoice != 2)) {
            std::cout << "잘못된 입력입니다. 1(고객) 또는 2(직원)를 입력해주세요: ";
            clearInputBuffer();
        }
        clearInputBuffer();
        userType = (typeChoice == 1) ? UserType::Customer : UserType::Employee;
    }
    else { // 메인 메뉴에서 고객 회원가입 시
        userType = UserType::Customer;
    }

    std::cout << "아이디 (영문, 숫자 5~12자): ";
    std::cin >> userId;
    clearInputBuffer();
    // TODO: 아이디 유효성 검사 (정규식 사용) 및 중복 확인 추가 필요

    // 아이디 중복 확인
    if (userManager.getUser(userId) != nullptr) {
        std::cout << "오류: 이미 사용 중인 아이디입니다. 다른 아이디를 입력해주세요." << std::endl;
        return;
    }


    std::cout << "비밀번호 (영문, 숫자, 특수문자 조합 8~15자): ";
    std::cin >> password;
    clearInputBuffer();
    // TODO: 비밀번호 유효성 검사 (정규식 사용) 추가 필요

    std::cout << "이름: ";
    std::getline(std::cin, name);
    // TODO: 이름 유효성 검사 추가 필요

    std::cout << "전화번호 (숫자만, 10~11자리, 예: 01012345678): ";
    std::cin >> phone;
    clearInputBuffer();
    // 전화번호 유효성 검사는 User::normalizePhoneNumber 에서 처리

    // 전화번호 정규화 및 유효성 검사
    std::string normalizedPhone = User::normalizePhoneNumber(phone);
    if (normalizedPhone.empty()) {
        std::cout << "오류: 유효하지 않은 전화번호 형식입니다." << std::endl;
        return;
    }

    if (userManager.addUser(userId, password, userType, name, normalizedPhone)) {
        std::cout << "사용자 '" << name << "'(" << userId << ")이(가) 성공적으로 추가되었습니다." << std::endl;
    }
    else {
        std::cout << "사용자 추가에 실패했습니다. (아이디 중복 또는 기타 오류)" << std::endl;
    }
}

// 사용자 삭제
void SystemManager::deleteUser() {
    std::string userIdToDelete;
    std::cout << "\n--- 사용자 삭제 ---\n" << std::endl;
    std::cout << "삭제할 사용자 ID: ";
    std::cin >> userIdToDelete;
    clearInputBuffer();

    // 사장은 자신의 계정을 삭제할 수 없게 함
    if (userIdToDelete == currentLoggedInUserId) {
        std::cout << "오류: 자신의 계정은 삭제할 수 없습니다." << std::endl;
        return;
    }
    // 사장은 다른 사장 계정을 삭제할 수 없게 함
    const User* userToDelete = userManager.getUser(userIdToDelete);
    if (userToDelete && userToDelete->getUserType() == UserType::Owner) {
        std::cout << "오류: 다른 사장 계정은 삭제할 수 없습니다." << std::endl;
        return;
    }

    if (userManager.deleteUser(userIdToDelete)) {
        std::cout << "사용자 ID '" << userIdToDelete << "'이(가) 성공적으로 삭제되었습니다." << std::endl;
    }
    else {
        std::cout << "사용자 삭제에 실패했습니다. (사용자 ID를 찾을 수 없거나 기타 오류)" << std::endl;
    }
}

// 사용자 계정 정보 수정 (오버로드된 함수)
void SystemManager::updateUserAccountInfo(const std::string& targetUserId) {
    std::string userIdToUpdate = targetUserId;

    // targetUserId가 비어있으면 현재 로그인된 사용자의 정보를 수정
    if (userIdToUpdate.empty()) {
        userIdToUpdate = currentLoggedInUserId;
    }

    User* userToUpdate = userManager.getMutableUser(userIdToUpdate);
    if (!userToUpdate) {
        std::cout << "오류: 해당 사용자 ID를 찾을 수 없습니다." << std::endl;
        return;
    }

    std::string newPassword, newName, newPhone;

    std::cout << "\n--- 계정 정보 수정 (" << userToUpdate->getUserId() << ") ---\n" << std::endl;

    std::cout << "새 비밀번호 (현재: " << userToUpdate->getPassword() << ", 변경하지 않으려면 Enter): ";
    std::getline(std::cin, newPassword);
    // TODO: 새 비밀번호 유효성 검사 추가 (만약 입력이 있다면)

    std::cout << "새 이름 (현재: " << userToUpdate->getName() << ", 변경하지 않으려면 Enter): ";
    std::getline(std::cin, newName);
    // TODO: 새 이름 유효성 검사 추가 (만약 입력이 있다면)

    std::cout << "새 전화번호 (현재: " << userToUpdate->getFormattedPhone() << ", 변경하지 않으려면 Enter): ";
    std::getline(std::cin, newPhone);
    // 전화번호 유효성 검사 및 정규화
    std::string normalizedNewPhone = newPhone.empty() ? "" : User::normalizePhoneNumber(newPhone);
    if (!newPhone.empty() && normalizedNewPhone.empty()) {
        std::cout << "경고: 유효하지 않은 전화번호 형식입니다. 전화번호는 변경되지 않습니다." << std::endl;
        // 유효하지 않으면 기존 전화번호 유지
        normalizedNewPhone = userToUpdate->getPhone();
    }
    else if (newPhone.empty()) {
        normalizedNewPhone = userToUpdate->getPhone(); // 입력이 없으면 기존 전화번호 유지
    }

    // 변경할 값이 있을 때만 업데이트 함수 호출
    if (!newPassword.empty() || !newName.empty() || !newPhone.empty()) {
        if (userManager.updateUserAccount(userIdToUpdate,
            newPassword.empty() ? userToUpdate->getPassword() : newPassword,
            newName.empty() ? userToUpdate->getName() : newName,
            normalizedNewPhone)) {
            std::cout << "계정 정보가 성공적으로 업데이트되었습니다." << std::endl;
            // 현재 로그인된 사용자의 정보가 변경되었다면 시스템 내 정보도 업데이트
            if (userIdToUpdate == currentLoggedInUserId) {
                if (!newName.empty()) currentLoggedInUserName = newName;
                if (!newPhone.empty()) currentLoggedInUserPhone = normalizedNewPhone;
            }
        }
        else {
            std::cout << "계정 정보 업데이트에 실패했습니다." << std::endl;
        }
    }
    else {
        std::cout << "변경할 정보가 없습니다." << std::endl;
    }
}


// ====================================================================================================
// 예약 관리 기능 구현
// ====================================================================================================

// 예약 생성
void SystemManager::makeReservation() {
    std::string customerId;
    std::string serviceName;
    std::string dateTimeStr;

    // 관리자나 직원이 예약을 생성하는 경우 고객 ID를 입력받음
    if (currentLoggedInUserType == UserType::Owner || currentLoggedInUserType == UserType::Employee) {
        std::cout << "\n--- 예약 생성 (관리자/직원용) ---\n" << std::endl;
        std::cout << "예약할 고객의 ID: ";
        std::cin >> customerId;
        clearInputBuffer();
        if (userManager.getUser(customerId) == nullptr || userManager.getUser(customerId)->getUserType() != UserType::Customer) {
            std::cout << "오류: 유효한 고객 ID가 아닙니다." << std::endl;
            return;
        }
    }
    else { // 고객이 자신의 예약을 생성하는 경우
        customerId = currentLoggedInUserId;
        std::cout << "\n--- 예약 생성 ---\n" << std::endl;
    }

    serviceManager.printAllServices(); // 사용 가능한 서비스 목록 표시

    std::cout << "예약할 서비스 이름: ";
    std::getline(std::cin, serviceName);

    const Service* service = serviceManager.getServiceByName(serviceName);
    if (service == nullptr) {
        std::cout << "오류: 존재하지 않는 서비스 이름입니다." << std::endl;
        return;
    }

    std::cout << "예약 시간 (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, dateTimeStr);

    std::chrono::system_clock::time_point reservationTime = Reservation::parseDateTime(dateTimeStr);
    if (reservationTime == std::chrono::system_clock::time_point()) {
        std::cout << "오류: 날짜/시간 형식이 올바르지 않거나 유효하지 않은 시간입니다." << std::endl;
        return;
    }

    // 현재 시간보다 이전 시간으로 예약 시도 시 거부
    if (reservationTime < std::chrono::system_clock::now()) {
        std::cout << "오류: 현재 시간보다 이전 시간으로는 예약할 수 없습니다." << std::endl;
        return;
    }


    if (reservationManager.addReservation(customerId, serviceName, reservationTime)) {
        std::cout << "예약이 성공적으로 생성되었습니다." << std::endl;
    }
    else {
        std::cout << "예약 생성에 실패했습니다. (시간 중복 또는 기타 오류)" << std::endl;
    }
}

// 예약 취소 (관리자/직원용 - 모든 예약 취소 가능)
void SystemManager::cancelReservation() {
    std::string reservationId;
    std::cout << "\n--- 예약 취소 (관리자/직원용) ---\n" << std::endl;
    std::cout << "취소할 예약 ID: ";
    std::cin >> reservationId;
    clearInputBuffer();

    if (reservationManager.cancelReservation(reservationId)) {
        std::cout << "예약 ID '" << reservationId << "'이(가) 성공적으로 취소되었습니다." << std::endl;
    }
    else {
        std::cout << "예약 취소에 실패했습니다. (예약 ID를 찾을 수 없거나 기타 오류)" << std::endl;
    }
}

// 예약 취소 (고객용 - 자신의 예약만 취소 가능)
void SystemManager::cancelReservation(const std::string& customerId) {
    std::string reservationId;
    std::cout << "\n--- 내 예약 취소 ---\n" << std::endl;
    std::cout << "취소할 예약 ID: ";
    std::cin >> reservationId;
    clearInputBuffer();

    const Reservation* reservation = reservationManager.getReservation(reservationId);
    if (reservation == nullptr) {
        std::cout << "오류: 해당 예약 ID를 찾을 수 없습니다." << std::endl;
        return;
    }

    // 해당 예약이 현재 로그인한 고객의 예약인지 확인
    if (reservation->getCustomerId() != customerId) {
        std::cout << "오류: 다른 고객의 예약은 취소할 수 없습니다." << std::endl;
        return;
    }

    if (reservationManager.cancelReservation(reservationId)) {
        std::cout << "예약 ID '" << reservationId << "'이(가) 성공적으로 취소되었습니다." << std::endl;
    }
    else {
        std::cout << "예약 취소에 실패했습니다." << std::endl;
    }
}

// 모든 예약 정보 출력
void SystemManager::viewAllReservations() {
    reservationManager.printAllReservations();
}

// 고객별 예약 보기 (관리자/직원용)
void SystemManager::viewReservationsByCustomer() {
    std::string customerId;
    std::cout << "\n--- 고객별 예약 보기 (관리자/직원용) ---\n" << std::endl;
    std::cout << "조회할 고객 ID: ";
    std::cin >> customerId;
    clearInputBuffer();

    std::vector<const Reservation*> reservations = reservationManager.getReservationsByCustomer(customerId);
    if (reservations.empty()) {
        std::cout << "고객 ID '" << customerId << "'의 예약이 없습니다." << std::endl;
    }
    else {
        std::cout << "\n--- 고객 ID '" << customerId << "'의 예약 목록 ---\n" << std::endl;
        std::cout << std::left << std::setw(15) << "예약 ID"
            << std::setw(15) << "고객 ID"
            << std::setw(25) << "서비스 이름"
            << std::setw(20) << "예약 시간" << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        for (const auto& res : reservations) {
            std::cout << std::left << std::setw(15) << res->getReservationId()
                << std::setw(15) << res->getCustomerId()
                << std::setw(25) << res->getServiceName()
                << std::setw(20) << res->getFormattedDateTime() << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
    }
}

// 고객별 예약 보기 (고객용 - 자신의 예약만)
void SystemManager::viewReservationsByCustomer(const std::string& customerId) {
    std::cout << "\n--- 내 예약 목록 ---\n" << std::endl;
    std::vector<const Reservation*> reservations = reservationManager.getReservationsByCustomer(customerId);
    if (reservations.empty()) {
        std::cout << "현재 예약이 없습니다." << std::endl;
    }
    else {
        std::cout << std::left << std::setw(15) << "예약 ID"
            << std::setw(25) << "서비스 이름"
            << std::setw(20) << "예약 시간" << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        for (const auto& res : reservations) {
            std::cout << std::left << std::setw(15) << res->getReservationId()
                << std::setw(25) << res->getServiceName()
                << std::setw(20) << res->getFormattedDateTime() << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
    }
}

// 날짜별 예약 보기
void SystemManager::viewReservationsForDate() {
    std::string dateStr;
    std::cout << "\n--- 날짜별 예약 보기 ---\n" << std::endl;
    std::cout << "조회할 날짜 (YYYY-MM-DD): ";
    std::cin >> dateStr;
    clearInputBuffer();

    std::vector<const Reservation*> reservations = reservationManager.getReservationsByDate(dateStr);
    if (reservations.empty()) {
        std::cout << "날짜 '" << dateStr << "'에 예약이 없습니다." << std::endl;
    }
    else {
        std::cout << "\n--- 날짜 '" << dateStr << "'의 예약 목록 ---\n" << std::endl;
        std::cout << std::left << std::setw(15) << "예약 ID"
            << std::setw(15) << "고객 ID"
            << std::setw(25) << "서비스 이름"
            << std::setw(20) << "예약 시간" << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        for (const auto& res : reservations) {
            std::cout << std::left << std::setw(15) << res->getReservationId()
                << std::setw(15) << res->getCustomerId()
                << std::setw(25) << res->getServiceName()
                << std::setw(20) << res->getFormattedDateTime() << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
    }
}