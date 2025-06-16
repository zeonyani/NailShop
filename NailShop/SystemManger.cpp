// SystemManager.cpp
#include "SystemManager.h"  // SystemManager Ŭ����
#include <iostream>         // �ܼ� ���
#include <limits>           // numeric_limits (�Է� ���� ����)
#include <string>           // std::string, getline
#include <ctime>            // ���� �ð�
#include <iomanip>          // ��� ������
#include <sstream>          // ���ڿ� ��Ʈ��

using namespace std;        // std:: ���ӽ����̽� ���

// SystemManager ������
SystemManager::SystemManager()
    : currentLoggedInUserType(UserType::None),
    currentLoggedInUserId(""),
    currentLoggedInUserName(""),
    currentLoggedInUserPhone("")
{
    cout << "���ϼ� ���� �ý��� ����." << endl;
}

// �ý��� ���� ������
void SystemManager::run() {
    // 1. �ʱ� ������ ���� ����
    createInitialAdminAccount();
    // 2. �ʱ� ���� ������ ����
    createInitialServices();

    // 3. �α���/ȸ������ �޴�
    int entryChoice;
    bool loggedIn = false;
    do {
        displayEntryMenu();
        cout << "�޴� ����: ";
        if (!(cin >> entryChoice)) {
            cout << "�߸��� �Է�. ���� �Է� �ʿ�." << endl;
            cin.clear(); // ���� �÷��� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ���� ����
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� ���� ����

        if (entryChoice == 1) { // �α���
            loggedIn = loginUser();
        }
        else if (entryChoice == 2) { // ȸ������
            registerCustomerAccount();
        }
        else if (entryChoice == 0) { // ����
            cout << "���α׷� ����." << endl;
            return;
        }
        else {
            cout << "�߸��� �Է�. �ٽ� �õ�." << endl;
        }

        if (!loggedIn && entryChoice != 0) { // �α��� ���� �� ���� �ƴ�
            cout << "\n�α��� �Ǵ� �ٸ� �۾� �ٽ� �õ�." << endl;
            cout << "����Ϸ��� Enter �Է�...";
            cin.get();
        }

    } while (!loggedIn); // �α��� ���� �ñ��� �ݺ�

    // �α��� ���� �� ���� �޴� ����
    int mainMenuChoice;
    do {
        displayMainMenu(); // ���� �޴� ǥ��
        cout << "�޴� ����: ";

        // ����� �Է� �� ��ȿ�� �˻�
        if (!(cin >> mainMenuChoice)) {
            cout << "�߸��� �Է�. ���� �Է� �ʿ�." << endl;
            cin.clear(); // ���� �÷��� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ���� ����
            mainMenuChoice = -1; // �߸��� �Է� ǥ��
            continue; // ���� �����
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� ���� ����

        handleMainMenuInput(mainMenuChoice); // ����� ���� ��� ó��

        // ���� (0) ���� �ƴ� �� Enter ���
        if (mainMenuChoice != 0) {
            cout << "\n����Ϸ��� Enter �Է�...";
            cin.get();
        }

    } while (mainMenuChoice != 0); // 0 ���� �ñ��� �ݺ�
    cout << "���ϼ� ���� �ý��� ����." << endl;
}

// �ʱ� ������ ���� ����
void SystemManager::createInitialAdminAccount() {
    // "owner" ID ���� ���� Ȯ��
    const User* adminUser = userManager.getUser("owner");
    if (adminUser == nullptr) { // "owner" ���� ����
        cout << "\n--- �ʱ� ����: ������ ���� ���� ---" << endl;
        cout << "�ý��ۿ� ��ϵ� ������ ���� ����." << endl;
        cout << "�ʱ� ������ ����(ID: owner, PW: ownerpass, �̸�: �����) ���� ��..." << endl;
        bool success = userManager.addUser("owner", "ownerpass", UserType::Owner, "�����", "010-1111-2222"); // �����õ� ��ȣ�� �Է�
        if (success) {
            cout << "�ʱ� ������ ���� ������ ����. ���� owner �������� �α��� ����." << endl;
        }
        else {
            cout << "����: �ʱ� ������ ���� ���� ����." << endl;
        }
    }
}

// �ʱ� ���� ������ ����
void SystemManager::createInitialServices() {
    // ServiceManager�� ���� ���� �� �ʱ� ���� �߰�
    if (serviceManager.getService("SVC1") == nullptr &&
        serviceManager.getService("SVC2") == nullptr &&
        serviceManager.getService("SVC3") == nullptr) {

        cout << "\n--- �ʱ� ����: �⺻ ���� ���� ---" << endl;
        cout << "��ϵ� ���� ����. �⺻ ���� ���� ��..." << endl;
        serviceManager.addService("�⺻ ����", 20000, 60);
        serviceManager.addService("�� �е�", 40000, 90);
        serviceManager.addService("�Ӵ��� ��", 30000, 45);
        cout << "�⺻ ���� ���� �Ϸ�." << endl;
    }
}

// ���α׷� ���� �� ���� �޴� ���
void SystemManager::displayEntryMenu() {
    cout << "\n--- ȯ���մϴ�! ---" << endl;
    cout << "1. �α���" << endl;
    cout << "2. ȸ������ (�� ����)" << endl;
    cout << "0. ���α׷� ����" << endl;
}

// ����� �α��� ó��
bool SystemManager::loginUser() {
    string userId, password;
    cout << "\n--- �α��� ---" << endl;
    cout << "����� ID: ";
    getline(cin, userId); // ����� ID �Է�
    cout << "��й�ȣ: ";
    getline(cin, password); // ��й�ȣ �Է�

    // UserManager�� ���� �α��� �õ�
    currentLoggedInUserType = userManager.login(userId, password);

    if (currentLoggedInUserType == UserType::None) { // �α��� ����
        currentLoggedInUserId = ""; // ID �ʱ�ȭ
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
        return false;
    }
    currentLoggedInUserId = userId; // �α��� ���� �� ID ����

    // �α��� ����� �̸�/��ȭ��ȣ ��������
    const User* loggedInUser = userManager.getUser(userId);
    if (loggedInUser) {
        currentLoggedInUserName = loggedInUser->getName();
        currentLoggedInUserPhone = loggedInUser->getFormattedPhone(); // �����õ� ��ȣ�� ����
    }
    else { // ���� ó�� (�߻����� �ʾƾ� ��)
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
    }
    return true; // �α��� ����
}

// �� ȸ������ ó��
void SystemManager::registerCustomerAccount() {
    cout << "\n--- �� ȸ������ ---" << endl;
    string userId, password, name, phone;

    cout << "����� ID �Է�: ";
    getline(cin, userId);

    // ID �ߺ� �˻�
    if (userManager.getUser(userId) != nullptr) {
        cout << "����: �̹� �����ϴ� ID. �ٸ� ID ��� �ʿ�." << endl;
        return;
    }

    cout << "����� ��й�ȣ �Է�: ";
    getline(cin, password);
    cout << "�̸� �Է�: ";
    getline(cin, name);
    cout << "��ȭ��ȣ �Է� (������ ���� �Ǵ� ���ڸ�, ��: 010-1234-5678): "; // �Է� ���̵� �߰�
    getline(cin, phone);

    bool success = userManager.addUser(userId, password, UserType::Customer, name, phone);
    if (success) {
        cout << "ȸ������ �Ϸ�. ���� �α��� ����!" << endl;
    }
    else {
        // addUser���� ��ȿ�� �˻� ���� �� �޽��� ���
        // cout << "ȸ������ ���� (�� �� ���� ����)." << endl; // UserManager���� �޽��� ó��
    }
}

// ���� �޴� ���
void SystemManager::displayMainMenu() {
    cout << "\n--- ���� �޴� ---" << endl;
    // ���� �α��� ����� ���� ǥ��
    cout << "���� �α���: " << currentLoggedInUserName << " (" << currentLoggedInUserId << ", "
        << currentLoggedInUserPhone << ", " // �̹� �����õ� ��ȣ ���
        << (currentLoggedInUserType == UserType::Owner ? "����" :
            currentLoggedInUserType == UserType::Employee ? "����" :
            currentLoggedInUserType == UserType::Customer ? "��" :
            "�� �� ����")
        << ")" << endl;

    cout << "1. �� ���� ��ȸ" << endl;

    // ����� ������ ���� �޴� �б�
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
        cout << "6. ����� ����" << endl; // ����� ���� ���� �޴�
        cout << "7. ���� ����" << endl; // ���� ���� ���� �޴�
    }

    cout << "0. �α׾ƿ� �� ����" << endl;
}

// ���� �޴� ����� �Է� ó��
void SystemManager::handleMainMenuInput(int choice) {
    switch (choice) {
    case 1: // '�� ���� ��ȸ' �Ǵ� 'Ư�� ���� ��ȸ'
        if (currentLoggedInUserType == UserType::Customer) {
            viewMyReservations();
        }
        else { // ����, ������ Ư�� ���� ��ȸ
            viewSpecificReservation();
        }
        break;
    case 0: // �α׾ƿ� �� ����
        break;
    default: // �� �� �޴� ���� ó��
        if (currentLoggedInUserType == UserType::Customer) {
            switch (choice) {
            case 2: addNewReservation(); break;
            case 3: cancelExistingReservation(); break;
            default: cout << "�߸��� �Է�. �ٽ� �õ�." << endl; break;
            }
        }
        else if (currentLoggedInUserType == UserType::Employee || currentLoggedInUserType == UserType::Owner) {
            switch (choice) {
            case 2: employeeViewTodayReservations(); break; // ���� ���� Ȯ��
            case 3: viewAllReservations(); break;             // ��ü ���� ����
            case 4: addNewReservation(); break;               // ���� �߰�
            case 5: cancelExistingReservation(); break;       // ���� ���
            case 6: // ����� ���� (���� ����)
                if (currentLoggedInUserType == UserType::Owner) {
                    manageUsers(); // ����� ���� ���� �޴� ȣ��
                }
                else {
                    cout << "�ش� ��� ���� ����." << endl;
                }
                break;
            case 7: // ���� ���� (���� ����)
                if (currentLoggedInUserType == UserType::Owner) {
                    manageServices(); // ���� ���� ���� �޴� ȣ��
                }
                else {
                    cout << "�ش� ��� ���� ����." << endl;
                }
                break;
            default: cout << "�߸��� �Է�. �ٽ� �õ�." << endl; break;
            }
        }
        else {
            cout << "����: �α��� ���� �� �� ����. �ٽ� �α��� �ʿ�." << endl;
        }
        break;
    }
}

// �� ���� �߰�
void SystemManager::addNewReservation() {
    string customerId_input, service_name, datetime;
    cout << "\n--- �� ���� �߰� ---" << endl;

    // ���� ��� �ڽ��� ID �ڵ� �Է�
    if (currentLoggedInUserType == UserType::Customer) {
        customerId_input = currentLoggedInUserId;
        cout << "�� ID: " << customerId_input << " (�ڵ� �Է�)" << endl;
    }
    else { // �����̳� ������ ��� �� ID ���� �Է�
        cout << "������ �� ID �Է�: ";
        getline(cin, customerId_input);
        // �� ID ���� ���� �� ���� Ȯ��
        const User* existingCustomer = userManager.getUser(customerId_input);
        if (existingCustomer == nullptr || existingCustomer->getUserType() != UserType::Customer) {
            cout << "����: ��ȿ�� �� ID �ƴ� �Ǵ� �� ���� �ƴ�. ���� ���." << endl;
            return;
        }
    }

    // ���� ��� ǥ�� �� ���� ����
    cout << "\n--- �̿� ���� ���� ��� ---" << endl;
    serviceManager.printAllServices();
    cout << "\n������ ���� �̸� ��Ȯ�� �Է�: ";
    getline(cin, service_name);

    // ���� ��ȿ�� Ȯ��
    const Service* selectedService = serviceManager.getServiceByName(service_name);
    if (selectedService == nullptr) {
        cout << "����: '���� ���'�� ���� ���� �̸�. ���� ���." << endl;
        return;
    }

    cout << "���� ��¥ �� �ð� �Է� (��: 2025-06-20 15:00): ";
    getline(cin, datetime);

    reservationManager.addReservation(customerId_input, selectedService->getName(), datetime);
}

// ���� ���� ���
void SystemManager::cancelExistingReservation() {
    string reservationId;
    cout << "\n--- ���� ��� ---" << endl;
    // ����/������ ��ü ��� ǥ��
    if (currentLoggedInUserType == UserType::Employee || currentLoggedInUserType == UserType::Owner) {
        reservationManager.printAllReservations();
    }
    else { // ���� �ڽ��� ���ุ ǥ��
        reservationManager.printReservationsByCustomerId(currentLoggedInUserId);
    }

    cout << "����� ���� ID �Է�: ";
    getline(cin, reservationId);

    // ���� �ڽ��� ���ุ ��� ���� (�߰� ����)
    if (currentLoggedInUserType == UserType::Customer) {
        const Reservation* res = reservationManager.getReservation(reservationId); // ���� ���� ��ȸ

        if (res == nullptr) {
            cout << "����: �ش� ���� ID ã�� �� ����." << endl;
            return; // ���� ����
        }

        if (res->getCustomerId() != currentLoggedInUserId) {
            cout << "����: �ڽ��� ���ุ ��� ����. �ش� ������ �� ID '"
                << res->getCustomerId() << "'�� ����." << endl;
            return; // �ڽ��� ���� �ƴ�
        }
    }

    reservationManager.deleteReservation(reservationId);
}

// Ư�� ���� ��ȸ
void SystemManager::viewSpecificReservation() {
    string reservationId;
    cout << "\n--- Ư�� ���� ��ȸ ---" << endl;
    cout << "��ȸ�� ���� ID �Է�: ";
    getline(cin, reservationId);
    reservationManager.printReservation(reservationId);
}

// ��� ���� ��ȸ
void SystemManager::viewAllReservations() {
    reservationManager.printAllReservations();
}

// �� ���� ��ȸ (�� ����)
void SystemManager::viewMyReservations() {
    cout << "\n--- ���� ���� ��ȸ ---" << endl;
    reservationManager.printReservationsByCustomerId(currentLoggedInUserId);
}

// ���� ���� Ȯ�� (����/����)
void SystemManager::employeeViewTodayReservations() {
    cout << "\n--- ���� ���� Ȯ�� ---" << endl;
    time_t now = time(0); // ���� �ð�

    tm ltm_s;
    localtime_s(&ltm_s, &now); // ���� �ð� ��ȯ

    stringstream ss;
    // ���� ��¥ "YYYY-MM-DD" ���� ������
    ss << (ltm_s.tm_year + 1900) << "-"
        << setfill('0') << setw(2) << (ltm_s.tm_mon + 1) << "-"
        << setfill('0') << setw(2) << ltm_s.tm_mday;
    string todayDate = ss.str();

    cout << "���� ��¥: " << todayDate << endl;
    reservationManager.printReservationsForDate(todayDate); // ��¥�� ���� ���
}

// ����� ���� �޴� (���� ����)
void SystemManager::manageUsers() {
    int userMenuChoice;
    do {
        cout << "\n--- ����� ���� (���� ����) ---" << endl;
        cout << "1. �� ����/�� ���� �߰�" << endl;
        cout << "2. ����/�� ���� ����" << endl;
        cout << "3. ��� ����� ��� ����" << endl;
        cout << "4. ����� �˻� (ID)" << endl;
        cout << "0. ���� �޴��� ���ư���" << endl;
        cout << "�޴� ����: ";

        if (!(cin >> userMenuChoice)) {
            cout << "�߸��� �Է�. ���� �Է� �ʿ�." << endl;
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
        case 0: cout << "���� �޴��� ���ư���." << endl; break;
        default: cout << "�߸��� �Է�. �ٽ� �õ�." << endl; break;
        }
        if (userMenuChoice != 0) {
            cout << "\n����Ϸ��� Enter �Է�...";
            cin.get();
        }
    } while (userMenuChoice != 0);
}

// �� ����/�� ���� �߰� (������ ����)
void SystemManager::addStaffOrCustomerAccount() {
    cout << "\n--- �� ����/�� ���� �߰� ---" << endl;
    string userId, password, name, phone, typeStr;
    UserType type = UserType::None;

    cout << "�߰��� ���� ���� ���� (1: ��, 2: ����): ";
    getline(cin, typeStr);

    if (typeStr == "1") {
        type = UserType::Customer;
    }
    else if (typeStr == "2") {
        type = UserType::Employee;
    }
    else {
        cout << "�߸��� ���� ����. ���� �߰� ���." << endl;
        return;
    }

    cout << "�� ���� ID �Է�: ";
    getline(cin, userId);

    // ID �ߺ� �˻�
    if (userManager.getUser(userId) != nullptr) {
        cout << "����: ����� ID '" << userId << "' �̹� ����. �ٸ� ID ��� �ʿ�." << endl;
        return;
    }

    cout << "�� ���� ��й�ȣ �Է�: ";
    getline(cin, password);
    cout << "�� ���� �̸� �Է�: ";
    getline(cin, name);
    cout << "�� ���� ��ȭ��ȣ �Է� (������ ���� �Ǵ� ���ڸ�, ��: 010-1234-5678): "; // �Է� ���̵� �߰�
    getline(cin, phone);

    bool success = userManager.addUser(userId, password, type, name, phone);
    if (success) {
        cout << "�� ���� ������ �߰�." << endl;
    }
    else {
        // addUser���� ��ȿ�� �˻� ���� �� �޽��� ���
        // cout << "���� �߰� ���� (�� �� ���� ����)." << endl;
    }
}

// ����/�� ���� ���� (���� ����)
void SystemManager::deleteStaffOrCustomerAccount() {
    cout << "\n--- ����/�� ���� ���� ---" << endl;
    userManager.printAllUsers(); // ��� ����� ��� ǥ��

    string userIdToDelete;
    cout << "\n������ ����� ID �Է�: ";
    getline(cin, userIdToDelete);

    if (userIdToDelete == currentLoggedInUserId) {
        cout << "����: ���� �α��ε� �ڽ��� ���� ���� �Ұ�." << endl;
        return;
    }

    userManager.deleteUser(userIdToDelete);
}

// ��� ����� ��� ���� (���� ����)
void SystemManager::viewAllUsers() {
    userManager.printAllUsers();
}

// ����� �˻� (ID��) (����/���� ����)
void SystemManager::searchUser() {
    cout << "\n--- ����� �˻� (ID) ---" << endl;
    string userIdToSearch;
    cout << "�˻��� ����� ID �Է�: ";
    getline(cin, userIdToSearch);

    const User* user = userManager.getUser(userIdToSearch);
    if (user) {
        cout << "\n--- ����� ���� ---" << endl;
        cout << "ID: " << user->getUserId() << endl;
        cout << "�̸�: " << user->getName() << endl;
        cout << "����: " << (user->getUserType() == UserType::Owner ? "����" :
            user->getUserType() == UserType::Employee ? "����" : "��") << endl;
        cout << "��ȭ��ȣ: " << user->getFormattedPhone() << endl; // �����õ� ��ȣ ���
        cout << "--------------------" << endl;
    }
    else {
        cout << "����� ID '" << userIdToSearch << "' ã�� �� ����." << endl;
    }
}

// ���� ���� �޴� (���� ����)
void SystemManager::manageServices() {
    int serviceMenuChoice;
    do {
        cout << "\n--- ���� ���� ---" << endl;
        cout << "1. ���� �߰�" << endl;
        cout << "2. ���� ����" << endl;
        cout << "3. ���� ����" << endl;
        cout << "4. ��� ���� ��� ����" << endl;
        cout << "0. ���� �޴��� ���ư���" << endl;
        cout << "�޴� ����: ";

        if (!(cin >> serviceMenuChoice)) {
            cout << "�߸��� �Է�. ���� �Է� �ʿ�." << endl;
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
        case 0: cout << "���� �޴��� ���ư���." << endl; break;
        default: cout << "�߸��� �Է�. �ٽ� �õ�." << endl; break;
        }
        if (serviceMenuChoice != 0) {
            cout << "\n����Ϸ��� Enter �Է�...";
            cin.get();
        }
    } while (serviceMenuChoice != 0);
}

// ���� �߰�
void SystemManager::addService() {
    string name;
    double price;
    int duration;

    cout << "\n--- ���� �߰� ---" << endl;
    cout << "���� �̸�: ";
    getline(cin, name);

    cout << "����: ";
    while (!(cin >> price) || price < 0) {
        cout << "�߸��� �Է�. ��ȿ�� ����(����) �Է� �ʿ�: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "�ҿ� �ð� (��): ";
    while (!(cin >> duration) || duration <= 0) {
        cout << "�߸��� �Է�. ��ȿ�� �ð�(��� ����) �Է� �ʿ�: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� ���� ���� ó��

    serviceManager.addService(name, price, duration);
}

// ���� ����
void SystemManager::updateService() {
    string serviceId, nameStr, priceStr, durationStr;
    double price;
    int duration;

    cout << "\n--- ���� ���� ---" << endl;
    serviceManager.printAllServices(); // ���� ���� ��� ǥ��
    cout << "\n������ ���� ID �Է�: ";
    getline(cin, serviceId);

    const Service* existingService = serviceManager.getService(serviceId);
    if (!existingService) {
        cout << "����: �ش� ���� ID ã�� �� ����." << endl;
        return;
    }

    cout << "�� ���� �̸� (����: " << existingService->getName() << ", ���� ������ Enter): ";
    getline(cin, nameStr);
    if (nameStr.empty()) nameStr = existingService->getName(); // �Է� ������ ���� �� ����

    cout << "�� ���� (����: " << fixed << setprecision(0) << existingService->getPrice() << "��, ���� ������ Enter): ";
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
            cout << "�߸��� ���� �Է�. ���� ���� ����." << endl;
            price = existingService->getPrice();
        }
        catch (const out_of_range& e) {
            cout << "���� ���� �ʰ�. ���� ���� ����." << endl;
            price = existingService->getPrice();
        }
    }

    cout << "�� �ҿ� �ð�(��) (����: " << existingService->getDurationMinutes() << "��, ���� ������ Enter): ";
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
            cout << "�߸��� �ҿ� �ð� �Է�. ���� �ð� ����." << endl;
            duration = existingService->getDurationMinutes();
        }
        catch (const out_of_range& e) {
            cout << "�ҿ� �ð� ���� �ʰ�. ���� �ð� ����." << endl;
            duration = existingService->getDurationMinutes();
        }
    }

    serviceManager.updateService(serviceId, nameStr, price, duration);
}

// ���� ��� ����
void SystemManager::viewServices() {
    serviceManager.printAllServices();
}

// ���� ����
void SystemManager::deleteService() {
    string serviceId;
    cout << "\n--- ���� ���� ---" << endl;
    serviceManager.printAllServices(); // ���� ���� ��� ǥ��
    cout << "\n������ ���� ID �Է�: ";
    getline(cin, serviceId);

    serviceManager.deleteService(serviceId);
}
