#include "SystemManager.h"
#include <iostream>
#include <limits>    // std::numeric_limits ����� ���� �����ϱ�
#include <string>    // std::string, std::getline ����� ���� �����ϱ�
#include <ctime>     // ���� ��¥�� ��� ���� std::time, std::localtime ����ϱ�
#include <iomanip>   // std::put_time, std::setw, std::setfill ����� ���� �����ϱ�
#include <sstream>   // std::stringstream ����� ���� �����ϱ�

// using namespace std; // ����ڴ��� ���� �ڵ� ��Ÿ���� ���� �� ���� ����

SystemManager::SystemManager()
    : currentLoggedInUserType(UserType::None), currentLoggedInUserId("") {
    std::cout << "���ϼ� ���� �ý����� �����մϴ�." << std::endl;
}

void SystemManager::run() {
    if (!loginUser()) {
        std::cout << "�α��ο� �����Ͽ� ���α׷��� �����մϴ�. ���α׷��� �ٽ� �������ּ���." << std::endl;
        return;
    }

    int choice;
    do {
        displayMainMenu();
        std::cout << "�޴��� �����ϼ���: ";

        if (!(std::cin >> choice)) {
            std::cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        handleMainMenuInput(choice);

        if (choice != 0) {
            std::cout << "\n����Ϸ��� Enter�� ��������...";
            std::cin.get();
        }

    } while (choice != 0);
    std::cout << "���ϼ� ���� �ý����� �����մϴ�." << std::endl;
}

bool SystemManager::loginUser() {
    std::string userId, password;
    std::cout << "\n--- �α��� ---" << std::endl;
    std::cout << "����� ID: ";
    std::getline(std::cin, userId);
    std::cout << "��й�ȣ: ";
    std::getline(std::cin, password);

    currentLoggedInUserType = userManager.login(userId, password);

    if (currentLoggedInUserType == UserType::None) {
        return false;
    }
    currentLoggedInUserId = userId;
    return true;
}

void SystemManager::displayMainMenu() {
    std::cout << "\n--- ���� �޴� ---" << std::endl;
    std::cout << "���� �α���: " << currentLoggedInUserId << " ("
        << (currentLoggedInUserType == UserType::Owner ? "����" :
            currentLoggedInUserType == UserType::Employee ? "����" :
            currentLoggedInUserType == UserType::Customer ? "��" :
            "�� �� ����")
        << ")" << std::endl;

    std::cout << "1. �� ���� ��ȸ" << std::endl;

    if (currentLoggedInUserType == UserType::Customer) {
        std::cout << "2. ���ο� ���� �߰�" << std::endl;
        std::cout << "3. ���� ���" << std::endl;
    }
    else if (currentLoggedInUserType == UserType::Employee || currentLoggedInUserType == UserType::Owner) {
        std::cout << "2. ���� ���� Ȯ��" << std::endl;
        std::cout << "3. ��ü ���� ��� ����" << std::endl;
        std::cout << "4. ���� �߰�" << std::endl;
        std::cout << "5. ���� ���" << std::endl;
    }

    if (currentLoggedInUserType == UserType::Owner) {
        std::cout << "6. ����� ���� (�̱���)" << std::endl;
        std::cout << "7. ���� ���� (�̱���)" << std::endl;
    }

    std::cout << "0. �α׾ƿ� �� ����" << std::endl;
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
            default: std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << std::endl; break;
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
                std::cout << "�ش� ����� ���� �������� �ʾҽ��ϴ�." << std::endl;
                break;
            default: std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << std::endl; break;
            }
        }
        else {
            std::cout << "����: �α��� ���¸� �� �� �����ϴ�. �ٽ� �α������ּ���." << std::endl;
        }
        break;
    }
}

// --- ���� ���� ��� �Լ� ���� ---

void SystemManager::addNewReservation() {
    std::string customerId_input, service, datetime;
    std::cout << "���ο� ������ �߰��մϴ�." << std::endl;

    if (currentLoggedInUserType == UserType::Customer) {
        customerId_input = currentLoggedInUserId;
        std::cout << "�� ID: " << customerId_input << " (�ڵ� �Է�)" << std::endl;
    }
    else {
        std::cout << "������ ���� ID�� �Է��ϼ���: ";
        std::getline(std::cin, customerId_input);
    }

    std::cout << "���� ������ �Է��ϼ��� (��: ���Ͼ�Ʈ, �е�ť��): ";
    std::getline(std::cin, service);
    std::cout << "���� ��¥ �� �ð��� �Է��ϼ��� (��: 2025-06-20 15:00): ";
    std::getline(std::cin, datetime);

    reservationManager.addReservation(customerId_input, service, datetime);
}

void SystemManager::cancelExistingReservation() {
    std::string reservationId;
    std::cout << "����� ������ ID�� �Է��ϼ���: ";
    std::getline(std::cin, reservationId);
    reservationManager.deleteReservation(reservationId);
}

void SystemManager::viewSpecificReservation() {
    std::string reservationId;
    std::cout << "��ȸ�� ������ ID�� �Է��ϼ���: ";
    std::getline(std::cin, reservationId);
    reservationManager.printReservation(reservationId);
}

void SystemManager::viewAllReservations() {
    reservationManager.printAllReservations();
}

void SystemManager::viewMyReservations() {
    std::cout << "���� �α��ε� (" << currentLoggedInUserId << ") ���� ���� ����Դϴ�. (��� �̱���)" << std::endl;
    // TODO: ReservationManager�� Ư�� �� ID�� ���ุ ��ȸ�ϴ� �Լ� �߰� �� ȣ���ϱ�
    // ��: reservationManager.printReservationsByCustomerId(currentLoggedInUserId);
}

// --- ���Ѻ� �Լ� (�̱���) ---

void SystemManager::employeeViewTodayReservations() {
    std::cout << "������ ���� Ȯ�� ����Դϴ�." << std::endl;
    std::time_t now = std::time(0);
    std::tm* ltm = std::localtime(&now);

    std::stringstream ss;
    ss << (ltm->tm_year + 1900) << "-"
        << std::setfill('0') << std::setw(2) << (ltm->tm_mon + 1) << "-"
        << std::setfill('0') << std::setw(2) << ltm->tm_mday;
    std::string todayDate = ss.str();

    std::cout << "���� ��¥: " << todayDate << std::endl;
    // TODO: ReservationManager�� Ư�� ��¥�� ���ุ ��ȸ�ϴ� �Լ� �߰� �� ȣ���ϱ�
    // ��: reservationManager.printReservationsForDate(todayDate);
    std::cout << "���� ��¥�� ���� ����� ReservationManager�� ���� ��ȸ�ؾ� �մϴ�. (��� �̱���)" << std::endl;
}