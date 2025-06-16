#include "SystemManager.h"
#include <iostream>
#include <limits>    // numeric_limits ����� ���� �����ϱ�
#include <string>    // string, getline ����� ���� �����ϱ�
#include <ctime>     // ���� ��¥�� ��� ���� time, localtime ����ϱ�
#include <iomanip>   // put_time, setw, setfill ����� ���� �����ϱ�
#include <sstream>   // stringstream ����� ���� �����ϱ�

using namespace std;

SystemManager::SystemManager()
    : currentLoggedInUserType(UserType::None), currentLoggedInUserId(""), currentLoggedInUserName("") { // name �ʱ�ȭ
    cout << "���ϼ� ���� �ý����� �����մϴ�." << endl;
}

void SystemManager::run() {
    if (!loginUser()) {
        cout << "�α��ο� �����Ͽ� ���α׷��� �����մϴ�. ���α׷��� �ٽ� �������ּ���." << endl;
        return;
    }

    int choice;
    do {
        displayMainMenu();
        cout << "�޴��� �����ϼ���: ";

        if (!(cin >> choice)) {
            cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        handleMainMenuInput(choice);

        if (choice != 0) {
            cout << "\n����Ϸ��� Enter�� ��������...";
            cin.get();
        }

    } while (choice != 0);
    cout << "���ϼ� ���� �ý����� �����մϴ�." << endl;
}

bool SystemManager::loginUser() {
    string userId, password;
    cout << "\n--- �α��� ---" << endl;
    cout << "����� ID: ";
    getline(cin, userId);
    cout << "��й�ȣ: ";
    getline(cin, password);

    currentLoggedInUserType = userManager.login(userId, password);

    if (currentLoggedInUserType == UserType::None) {
        return false;
    }
    currentLoggedInUserId = userId;
    // �α��� ���� �� ����� �̸� ��������
    const User* loggedInUser = userManager.getUser(userId);
    if (loggedInUser) {
        currentLoggedInUserName = loggedInUser->getName();
    }
    else {
        currentLoggedInUserName = ""; // Ȥ�� �� ��Ȳ ���
    }
    return true;
}

void SystemManager::displayMainMenu() {
    cout << "\n--- ���� �޴� ---" << endl;
    // �α��ε� ����� �̸��� ID, ���� ǥ��
    cout << "���� �α���: " << currentLoggedInUserName << " (" << currentLoggedInUserId << ", "
        << (currentLoggedInUserType == UserType::Owner ? "����" :
            currentLoggedInUserType == UserType::Employee ? "����" :
            currentLoggedInUserType == UserType::Customer ? "��" :
            "�� �� ����")
        << ")" << endl;

    cout << "1. �� ���� ��ȸ" << endl;

    if (currentLoggedInUserType == UserType::Customer) {
        cout << "2. ���ο� ���� �߰�" << endl;
        cout << "3. ���� ���" << endl;
    }
    else if (currentLoggedInUserType == UserType::Employee || currentLoggedInUserType == UserType::Owner) {
        cout << "2. ���� ���� Ȯ��" << endl;
        cout << "3. ��ü ���� ��� ����" << endl;
        cout << "4. ���� �߰�" << endl;
        cout << "5. ���� ���" << endl;
    }

    if (currentLoggedInUserType == UserType::Owner) {
        cout << "6. ����� ���� (�̱���)" << endl;
        cout << "7. ���� ���� (�̱���)" << endl;
    }

    cout << "0. �α׾ƿ� �� ����" << endl;
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
            default: cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << endl; break;
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
                cout << "�ش� ����� ���� �������� �ʾҽ��ϴ�." << endl;
                break;
            default: cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << endl; break;
            }
        }
        else {
            cout << "����: �α��� ���¸� �� �� �����ϴ�. �ٽ� �α������ּ���." << endl;
        }
        break;
    }
}

// --- ���� ���� ��� �Լ� ���� ---

void SystemManager::addNewReservation() {
    string customerId_input, service, datetime;
    cout << "���ο� ������ �߰��մϴ�." << endl;

    if (currentLoggedInUserType == UserType::Customer) {
        customerId_input = currentLoggedInUserId;
        cout << "�� ID: " << customerId_input << " (�ڵ� �Է�)" << endl;
    }
    else {
        cout << "������ ���� ID�� �Է��ϼ���: ";
        getline(cin, customerId_input);
    }

    cout << "���� ������ �Է��ϼ��� (��: ���Ͼ�Ʈ, �е�ť��): ";
    getline(cin, service);
    cout << "���� ��¥ �� �ð��� �Է��ϼ��� (��: 2025-06-20 15:00): ";
    getline(cin, datetime);

    reservationManager.addReservation(customerId_input, service, datetime);
}

void SystemManager::cancelExistingReservation() {
    string reservationId;
    cout << "����� ������ ID�� �Է��ϼ���: ";
    getline(cin, reservationId);
    reservationManager.deleteReservation(reservationId);
}

void SystemManager::viewSpecificReservation() {
    string reservationId;
    cout << "��ȸ�� ������ ID�� �Է��ϼ���: ";
    getline(cin, reservationId);
    reservationManager.printReservation(reservationId);
}

void SystemManager::viewAllReservations() {
    reservationManager.printAllReservations();
}

void SystemManager::viewMyReservations() {
    cout << "���� �α��ε� (" << currentLoggedInUserId << ") ���� ���� ����Դϴ�. (��� �̱���)" << endl;
    // TODO: ReservationManager�� Ư�� �� ID�� ���ุ ��ȸ�ϴ� �Լ� �߰� �� ȣ���ϱ�
    // ��: reservationManager.printReservationsByCustomerId(currentLoggedInUserId);
}

// --- ���Ѻ� �Լ� (�̱���) ---

void SystemManager::employeeViewTodayReservations() {
    cout << "������ ���� Ȯ�� ����Դϴ�." << endl;
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << (ltm->tm_year + 1900) << "-"
        << setfill('0') << setw(2) << (ltm->tm_mon + 1) << "-"
        << setfill('0') << setw(2) << ltm->tm_mday;
    string todayDate = ss.str();

    cout << "���� ��¥: " << todayDate << endl;
    // TODO: ReservationManager�� Ư�� ��¥�� ���ุ ��ȸ�ϴ� �Լ� �߰� �� ȣ���ϱ�
    // ��: reservationManager.printReservationsForDate(todayDate);
    cout << "���� ��¥�� ���� ����� ReservationManager�� ���� ��ȸ�ؾ� �մϴ�. (��� �̱���)" << endl;
}