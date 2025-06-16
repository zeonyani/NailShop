// SystemManager.cpp

#include "SystemManager.h"
#include <iostream>
#include <limits> // std::numeric_limits
#include <algorithm> // std::transform
#include <cctype> // std::tolower
#include <iomanip> // std::put_time, std::get_time
#include <chrono> // �ð� ����
#include <sstream> // std::stringstream

// SystemManager ������
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

// �Է� ���۸� ���� ���� �Լ�
void SystemManager::clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
}

// ���� ���� ���� ���
void SystemManager::handleOwnerServiceManagement() {
    int choice;
    do {
        std::cout << "\n--- ���� ���� ���� ---\n" << std::endl;
        std::cout << "1. ��� ���� ��� ����" << std::endl;
        // 2. ���� �߰� (���������Ƿ� ����)
        // 3. ���� ���� ���� (���������Ƿ� ����)
        // 4. ���� ���� (���������Ƿ� ����)
        std::cout << "0. �ڷΰ���" << std::endl;
        std::cout << "����: ";
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
            serviceManager.printAllServices(); // �� �κ��� ����
            break;
            // case 2: addService(); break;       // ����
            // case 3: updateService(); break;    // ����
            // case 4: deleteService(); break;    // ����
        case 0:
            std::cout << "���� ���� �޴��� �����մϴ�." << std::endl;
            break;
        default:
            std::cout << "��ȿ���� ���� �����Դϴ�. �ٽ� �õ����ּ���." << std::endl;
            break;
        }
    } while (choice != 0);
}

// �ý��� ����
void SystemManager::run() {
    while (true) {
        displayMainMenu();
        int choice;
        std::cout << "����: ";
        std::cin >> choice;
        clearInputBuffer(); // �Է� ���� ����

        processMainMenuInput(choice);
    }
}

// ���� �޴� ���
void SystemManager::displayMainMenu() {
    std::cout << "\n--- ���� �޴� ---\n" << std::endl;
    std::cout << "1. �α���" << std::endl;
    std::cout << "2. ȸ������ (��)" << std::endl;
    std::cout << "3. ����" << std::endl;
}

// ���� �޴� �Է� ó��
void SystemManager::processMainMenuInput(int choice) {
    switch (choice) {
    case 1: // �α���
        handleLogin();
        break;
    case 2: // ȸ������ (��)
        addUser(); // �� ȸ������ ��� ����
        break;
    case 3: // ����
        std::cout << "���α׷��� �����մϴ�." << std::endl;
        exit(0);
    default:
        std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << std::endl;
        break;
    }
}

// �α��� ó��
void SystemManager::handleLogin() {
    std::string userId, password;
    std::cout << "\n--- �α��� ---\n" << std::endl;
    std::cout << "���̵�: ";
    std::cin >> userId;
    std::cout << "��й�ȣ: ";
    std::cin >> password;
    clearInputBuffer();

    currentLoggedInUserType = userManager.login(userId, password);

    if (currentLoggedInUserType != UserType::None) {
        const User* user = userManager.getUser(userId);
        if (user) {
            currentLoggedInUserId = user->getUserId();
            currentLoggedInUserName = user->getName();
            currentLoggedInUserPhone = user->getPhone();
            std::cout << currentLoggedInUserName << "�� ȯ���մϴ�! (" << userId << ")" << std::endl;
        }

        switch (currentLoggedInUserType) {
        case UserType::Owner:
            while (true) {
                displayOwnerMenu();
                int choice;
                std::cout << "����: ";
                std::cin >> choice;
                clearInputBuffer();
                processOwnerMenuInput(choice);
                if (choice == 5) break; // �α׾ƿ�
            }
            break;
        case UserType::Employee:
            while (true) {
                displayEmployeeMenu();
                int choice;
                std::cout << "����: ";
                std::cin >> choice;
                clearInputBuffer();
                processEmployeeMenuInput(choice);
                if (choice == 4) break; // �α׾ƿ�
            }
            break;
        case UserType::Customer:
            while (true) {
                displayCustomerMenu();
                int choice;
                std::cout << "����: ";
                std::cin >> choice;
                clearInputBuffer();
                processCustomerMenuInput(choice);
                if (choice == 3) break; // �α׾ƿ�
            }
            break;
        default:
            // �� ���� �߻����� �ʾƾ� ��
            break;
        }
    }
    else {
        std::cout << "�α��� ����: ���̵� �Ǵ� ��й�ȣ�� �ùٸ��� �ʽ��ϴ�." << std::endl;
    }
}

// ���� �޴� ���
void SystemManager::displayOwnerMenu() {
    std::cout << "\n--- ���� �޴� ---\n" << std::endl;
    std::cout << "1. ���� ����" << std::endl;
    std::cout << "2. ����� ���� ����" << std::endl;
    std::cout << "3. ���� ����" << std::endl;
    std::cout << "4. �� ���� ���� ����" << std::endl;
    std::cout << "5. �α׾ƿ�" << std::endl;
}

// ���� �޴� �Է� ó��
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
        std::cout << "�α׾ƿ� �Ǿ����ϴ�." << std::endl;
        currentLoggedInUserType = UserType::None;
        currentLoggedInUserId = "";
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
        break;
    default:
        std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << std::endl;
        break;
    }
}

// ���� ����� ���� ����
void SystemManager::handleOwnerUserManagement() {
    while (true) {
        std::cout << "\n--- ���� ����� ���� ���� ---\n" << std::endl;
        std::cout << "1. ����� �߰� (����/��)" << std::endl;
        std::cout << "2. ����� ����" << std::endl;
        std::cout << "3. ����� ���� ���� ����" << std::endl; // Ư�� �����
        std::cout << "4. ��� ����� ��� ����" << std::endl;
        std::cout << "5. �ڷ� ����" << std::endl;
        std::cout << "����: ";
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
            std::cout << "������ ������ ����� ID: ";
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
            std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << std::endl;
            break;
        }
    }
}

// ���� ���� ����
void SystemManager::handleOwnerReservationManagement() {
    while (true) {
        std::cout << "\n--- ���� ���� ���� ---\n" << std::endl;
        std::cout << "1. ���� ����" << std::endl;
        std::cout << "2. ���� ���" << std::endl;
        std::cout << "3. ��� ���� ��� ����" << std::endl;
        std::cout << "4. ���� ���� ��� ����" << std::endl;
        std::cout << "5. ��¥�� ���� ��� ����" << std::endl;
        std::cout << "6. �ڷ� ����" << std::endl;
        std::cout << "����: ";
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
            std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << std::endl;
            break;
        }
    }
}

// ���� ���� ���� ����
void SystemManager::handleOwnerAccountInfo() {
    updateUserAccountInfo(currentLoggedInUserId); // ���� �α����� ���� ���� ���� ����
}


// ���� �޴� ���
void SystemManager::displayEmployeeMenu() {
    std::cout << "\n--- ���� �޴� ---\n" << std::endl;
    std::cout << "1. ���� ����" << std::endl; // ����� ������ ���
    std::cout << "2. ���� ����" << std::endl;   // ����� ������ ���
    std::cout << "3. �� ���� ���� ����" << std::endl;
    std::cout << "4. �α׾ƿ�" << std::endl;
}

// ���� �޴� �Է� ó��
void SystemManager::processEmployeeMenuInput(int choice) {
    switch (choice) {
    case 1:
        handleEmployeeServiceManagement(); // �� �Լ��� ȣ��
        break;
    case 2:
        handleEmployeeReservationManagement();
        break;
    case 3:
        handleEmployeeAccountInfo();
        break;
    case 4:
        std::cout << "�α׾ƿ� �Ǿ����ϴ�." << std::endl;
        currentLoggedInUserType = UserType::None;
        currentLoggedInUserId = "";
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
        break;
    default:
        std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << std::endl;
        break;
    }
}

// ���� ���� ���� (���� ���� ������ ����)
void SystemManager::handleEmployeeServiceManagement() {
    handleOwnerServiceManagement(); // ���� ���� ���� �Լ� ����
}

// ���� ���� ���� (���� ���� ������ ����)
void SystemManager::handleEmployeeReservationManagement() {
    handleOwnerReservationManagement(); // ���� ���� ���� �Լ� ����
}

// ���� ���� ���� ����
void SystemManager::handleEmployeeAccountInfo() {
    updateUserAccountInfo(currentLoggedInUserId); // ���� �α����� ���� ���� ���� ����
}


// �� �޴� ���
void SystemManager::displayCustomerMenu() {
    std::cout << "\n--- �� �޴� ---\n" << std::endl;
    std::cout << "1. ���� ����" << std::endl;
    std::cout << "2. �� ���� ���� ����" << std::endl;
    std::cout << "3. �α׾ƿ�" << std::endl;
}

// �� �޴� �Է� ó��
void SystemManager::processCustomerMenuInput(int choice) {
    switch (choice) {
    case 1:
        handleCustomerReservationManagement();
        break;
    case 2:
        handleCustomerAccountInfo();
        break;
    case 3:
        std::cout << "�α׾ƿ� �Ǿ����ϴ�." << std::endl;
        currentLoggedInUserType = UserType::None;
        currentLoggedInUserId = "";
        currentLoggedInUserName = "";
        currentLoggedInUserPhone = "";
        break;
    default:
        std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << std::endl;
        break;
    }
}

// �� ���� ����
void SystemManager::handleCustomerReservationManagement() {
    while (true) {
        std::cout << "\n--- �� ���� ���� ---\n" << std::endl;
        std::cout << "1. ���� ����" << std::endl;
        std::cout << "2. �� ���� ���" << std::endl;
        std::cout << "3. �� ���� ��� ����" << std::endl;
        std::cout << "4. �ڷ� ����" << std::endl;
        std::cout << "����: ";
        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
            makeReservation();
            break;
        case 2:
            cancelReservation(currentLoggedInUserId); // �ڽ��� ���ุ ���
            break;
        case 3:
            viewReservationsByCustomer(currentLoggedInUserId); // �ڽ��� ���ุ ����
            break;
        case 4:
            return;
        default:
            std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << std::endl;
            break;
        }
    }
}

// �� ���� ���� ����
void SystemManager::handleCustomerAccountInfo() {
    updateUserAccountInfo(currentLoggedInUserId); // ���� �α����� �� ���� ���� ����
}

// ====================================================================================================
// ����� ���� ��� ����
// ====================================================================================================

// ����� �߰� (ȸ������ ����)
void SystemManager::addUser() {
    std::string userId, password, name, phone;
    int typeChoice;
    UserType userType = UserType::None;

    std::cout << "\n--- ����� �߰� ---\n" << std::endl;
    if (currentLoggedInUserType == UserType::Owner) { // ���常 ����/�� ���� ����
        std::cout << "�߰��� ����� ���� ����:\n";
        std::cout << "1. ��\n";
        std::cout << "2. ����\n";
        std::cout << "����: ";
        while (!(std::cin >> typeChoice) || (typeChoice != 1 && typeChoice != 2)) {
            std::cout << "�߸��� �Է��Դϴ�. 1(��) �Ǵ� 2(����)�� �Է����ּ���: ";
            clearInputBuffer();
        }
        clearInputBuffer();
        userType = (typeChoice == 1) ? UserType::Customer : UserType::Employee;
    }
    else { // ���� �޴����� �� ȸ������ ��
        userType = UserType::Customer;
    }

    std::cout << "���̵� (����, ���� 5~12��): ";
    std::cin >> userId;
    clearInputBuffer();
    // TODO: ���̵� ��ȿ�� �˻� (���Խ� ���) �� �ߺ� Ȯ�� �߰� �ʿ�

    // ���̵� �ߺ� Ȯ��
    if (userManager.getUser(userId) != nullptr) {
        std::cout << "����: �̹� ��� ���� ���̵��Դϴ�. �ٸ� ���̵� �Է����ּ���." << std::endl;
        return;
    }


    std::cout << "��й�ȣ (����, ����, Ư������ ���� 8~15��): ";
    std::cin >> password;
    clearInputBuffer();
    // TODO: ��й�ȣ ��ȿ�� �˻� (���Խ� ���) �߰� �ʿ�

    std::cout << "�̸�: ";
    std::getline(std::cin, name);
    // TODO: �̸� ��ȿ�� �˻� �߰� �ʿ�

    std::cout << "��ȭ��ȣ (���ڸ�, 10~11�ڸ�, ��: 01012345678): ";
    std::cin >> phone;
    clearInputBuffer();
    // ��ȭ��ȣ ��ȿ�� �˻�� User::normalizePhoneNumber ���� ó��

    // ��ȭ��ȣ ����ȭ �� ��ȿ�� �˻�
    std::string normalizedPhone = User::normalizePhoneNumber(phone);
    if (normalizedPhone.empty()) {
        std::cout << "����: ��ȿ���� ���� ��ȭ��ȣ �����Դϴ�." << std::endl;
        return;
    }

    if (userManager.addUser(userId, password, userType, name, normalizedPhone)) {
        std::cout << "����� '" << name << "'(" << userId << ")��(��) ���������� �߰��Ǿ����ϴ�." << std::endl;
    }
    else {
        std::cout << "����� �߰��� �����߽��ϴ�. (���̵� �ߺ� �Ǵ� ��Ÿ ����)" << std::endl;
    }
}

// ����� ����
void SystemManager::deleteUser() {
    std::string userIdToDelete;
    std::cout << "\n--- ����� ���� ---\n" << std::endl;
    std::cout << "������ ����� ID: ";
    std::cin >> userIdToDelete;
    clearInputBuffer();

    // ������ �ڽ��� ������ ������ �� ���� ��
    if (userIdToDelete == currentLoggedInUserId) {
        std::cout << "����: �ڽ��� ������ ������ �� �����ϴ�." << std::endl;
        return;
    }
    // ������ �ٸ� ���� ������ ������ �� ���� ��
    const User* userToDelete = userManager.getUser(userIdToDelete);
    if (userToDelete && userToDelete->getUserType() == UserType::Owner) {
        std::cout << "����: �ٸ� ���� ������ ������ �� �����ϴ�." << std::endl;
        return;
    }

    if (userManager.deleteUser(userIdToDelete)) {
        std::cout << "����� ID '" << userIdToDelete << "'��(��) ���������� �����Ǿ����ϴ�." << std::endl;
    }
    else {
        std::cout << "����� ������ �����߽��ϴ�. (����� ID�� ã�� �� ���ų� ��Ÿ ����)" << std::endl;
    }
}

// ����� ���� ���� ���� (�����ε�� �Լ�)
void SystemManager::updateUserAccountInfo(const std::string& targetUserId) {
    std::string userIdToUpdate = targetUserId;

    // targetUserId�� ��������� ���� �α��ε� ������� ������ ����
    if (userIdToUpdate.empty()) {
        userIdToUpdate = currentLoggedInUserId;
    }

    User* userToUpdate = userManager.getMutableUser(userIdToUpdate);
    if (!userToUpdate) {
        std::cout << "����: �ش� ����� ID�� ã�� �� �����ϴ�." << std::endl;
        return;
    }

    std::string newPassword, newName, newPhone;

    std::cout << "\n--- ���� ���� ���� (" << userToUpdate->getUserId() << ") ---\n" << std::endl;

    std::cout << "�� ��й�ȣ (����: " << userToUpdate->getPassword() << ", �������� �������� Enter): ";
    std::getline(std::cin, newPassword);
    // TODO: �� ��й�ȣ ��ȿ�� �˻� �߰� (���� �Է��� �ִٸ�)

    std::cout << "�� �̸� (����: " << userToUpdate->getName() << ", �������� �������� Enter): ";
    std::getline(std::cin, newName);
    // TODO: �� �̸� ��ȿ�� �˻� �߰� (���� �Է��� �ִٸ�)

    std::cout << "�� ��ȭ��ȣ (����: " << userToUpdate->getFormattedPhone() << ", �������� �������� Enter): ";
    std::getline(std::cin, newPhone);
    // ��ȭ��ȣ ��ȿ�� �˻� �� ����ȭ
    std::string normalizedNewPhone = newPhone.empty() ? "" : User::normalizePhoneNumber(newPhone);
    if (!newPhone.empty() && normalizedNewPhone.empty()) {
        std::cout << "���: ��ȿ���� ���� ��ȭ��ȣ �����Դϴ�. ��ȭ��ȣ�� ������� �ʽ��ϴ�." << std::endl;
        // ��ȿ���� ������ ���� ��ȭ��ȣ ����
        normalizedNewPhone = userToUpdate->getPhone();
    }
    else if (newPhone.empty()) {
        normalizedNewPhone = userToUpdate->getPhone(); // �Է��� ������ ���� ��ȭ��ȣ ����
    }

    // ������ ���� ���� ���� ������Ʈ �Լ� ȣ��
    if (!newPassword.empty() || !newName.empty() || !newPhone.empty()) {
        if (userManager.updateUserAccount(userIdToUpdate,
            newPassword.empty() ? userToUpdate->getPassword() : newPassword,
            newName.empty() ? userToUpdate->getName() : newName,
            normalizedNewPhone)) {
            std::cout << "���� ������ ���������� ������Ʈ�Ǿ����ϴ�." << std::endl;
            // ���� �α��ε� ������� ������ ����Ǿ��ٸ� �ý��� �� ������ ������Ʈ
            if (userIdToUpdate == currentLoggedInUserId) {
                if (!newName.empty()) currentLoggedInUserName = newName;
                if (!newPhone.empty()) currentLoggedInUserPhone = normalizedNewPhone;
            }
        }
        else {
            std::cout << "���� ���� ������Ʈ�� �����߽��ϴ�." << std::endl;
        }
    }
    else {
        std::cout << "������ ������ �����ϴ�." << std::endl;
    }
}


// ====================================================================================================
// ���� ���� ��� ����
// ====================================================================================================

// ���� ����
void SystemManager::makeReservation() {
    std::string customerId;
    std::string serviceName;
    std::string dateTimeStr;

    // �����ڳ� ������ ������ �����ϴ� ��� �� ID�� �Է¹���
    if (currentLoggedInUserType == UserType::Owner || currentLoggedInUserType == UserType::Employee) {
        std::cout << "\n--- ���� ���� (������/������) ---\n" << std::endl;
        std::cout << "������ ���� ID: ";
        std::cin >> customerId;
        clearInputBuffer();
        if (userManager.getUser(customerId) == nullptr || userManager.getUser(customerId)->getUserType() != UserType::Customer) {
            std::cout << "����: ��ȿ�� �� ID�� �ƴմϴ�." << std::endl;
            return;
        }
    }
    else { // ���� �ڽ��� ������ �����ϴ� ���
        customerId = currentLoggedInUserId;
        std::cout << "\n--- ���� ���� ---\n" << std::endl;
    }

    serviceManager.printAllServices(); // ��� ������ ���� ��� ǥ��

    std::cout << "������ ���� �̸�: ";
    std::getline(std::cin, serviceName);

    const Service* service = serviceManager.getServiceByName(serviceName);
    if (service == nullptr) {
        std::cout << "����: �������� �ʴ� ���� �̸��Դϴ�." << std::endl;
        return;
    }

    std::cout << "���� �ð� (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, dateTimeStr);

    std::chrono::system_clock::time_point reservationTime = Reservation::parseDateTime(dateTimeStr);
    if (reservationTime == std::chrono::system_clock::time_point()) {
        std::cout << "����: ��¥/�ð� ������ �ùٸ��� �ʰų� ��ȿ���� ���� �ð��Դϴ�." << std::endl;
        return;
    }

    // ���� �ð����� ���� �ð����� ���� �õ� �� �ź�
    if (reservationTime < std::chrono::system_clock::now()) {
        std::cout << "����: ���� �ð����� ���� �ð����δ� ������ �� �����ϴ�." << std::endl;
        return;
    }


    if (reservationManager.addReservation(customerId, serviceName, reservationTime)) {
        std::cout << "������ ���������� �����Ǿ����ϴ�." << std::endl;
    }
    else {
        std::cout << "���� ������ �����߽��ϴ�. (�ð� �ߺ� �Ǵ� ��Ÿ ����)" << std::endl;
    }
}

// ���� ��� (������/������ - ��� ���� ��� ����)
void SystemManager::cancelReservation() {
    std::string reservationId;
    std::cout << "\n--- ���� ��� (������/������) ---\n" << std::endl;
    std::cout << "����� ���� ID: ";
    std::cin >> reservationId;
    clearInputBuffer();

    if (reservationManager.cancelReservation(reservationId)) {
        std::cout << "���� ID '" << reservationId << "'��(��) ���������� ��ҵǾ����ϴ�." << std::endl;
    }
    else {
        std::cout << "���� ��ҿ� �����߽��ϴ�. (���� ID�� ã�� �� ���ų� ��Ÿ ����)" << std::endl;
    }
}

// ���� ��� (���� - �ڽ��� ���ุ ��� ����)
void SystemManager::cancelReservation(const std::string& customerId) {
    std::string reservationId;
    std::cout << "\n--- �� ���� ��� ---\n" << std::endl;
    std::cout << "����� ���� ID: ";
    std::cin >> reservationId;
    clearInputBuffer();

    const Reservation* reservation = reservationManager.getReservation(reservationId);
    if (reservation == nullptr) {
        std::cout << "����: �ش� ���� ID�� ã�� �� �����ϴ�." << std::endl;
        return;
    }

    // �ش� ������ ���� �α����� ���� �������� Ȯ��
    if (reservation->getCustomerId() != customerId) {
        std::cout << "����: �ٸ� ���� ������ ����� �� �����ϴ�." << std::endl;
        return;
    }

    if (reservationManager.cancelReservation(reservationId)) {
        std::cout << "���� ID '" << reservationId << "'��(��) ���������� ��ҵǾ����ϴ�." << std::endl;
    }
    else {
        std::cout << "���� ��ҿ� �����߽��ϴ�." << std::endl;
    }
}

// ��� ���� ���� ���
void SystemManager::viewAllReservations() {
    reservationManager.printAllReservations();
}

// ���� ���� ���� (������/������)
void SystemManager::viewReservationsByCustomer() {
    std::string customerId;
    std::cout << "\n--- ���� ���� ���� (������/������) ---\n" << std::endl;
    std::cout << "��ȸ�� �� ID: ";
    std::cin >> customerId;
    clearInputBuffer();

    std::vector<const Reservation*> reservations = reservationManager.getReservationsByCustomer(customerId);
    if (reservations.empty()) {
        std::cout << "�� ID '" << customerId << "'�� ������ �����ϴ�." << std::endl;
    }
    else {
        std::cout << "\n--- �� ID '" << customerId << "'�� ���� ��� ---\n" << std::endl;
        std::cout << std::left << std::setw(15) << "���� ID"
            << std::setw(15) << "�� ID"
            << std::setw(25) << "���� �̸�"
            << std::setw(20) << "���� �ð�" << std::endl;
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

// ���� ���� ���� (���� - �ڽ��� ���ุ)
void SystemManager::viewReservationsByCustomer(const std::string& customerId) {
    std::cout << "\n--- �� ���� ��� ---\n" << std::endl;
    std::vector<const Reservation*> reservations = reservationManager.getReservationsByCustomer(customerId);
    if (reservations.empty()) {
        std::cout << "���� ������ �����ϴ�." << std::endl;
    }
    else {
        std::cout << std::left << std::setw(15) << "���� ID"
            << std::setw(25) << "���� �̸�"
            << std::setw(20) << "���� �ð�" << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        for (const auto& res : reservations) {
            std::cout << std::left << std::setw(15) << res->getReservationId()
                << std::setw(25) << res->getServiceName()
                << std::setw(20) << res->getFormattedDateTime() << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
    }
}

// ��¥�� ���� ����
void SystemManager::viewReservationsForDate() {
    std::string dateStr;
    std::cout << "\n--- ��¥�� ���� ���� ---\n" << std::endl;
    std::cout << "��ȸ�� ��¥ (YYYY-MM-DD): ";
    std::cin >> dateStr;
    clearInputBuffer();

    std::vector<const Reservation*> reservations = reservationManager.getReservationsByDate(dateStr);
    if (reservations.empty()) {
        std::cout << "��¥ '" << dateStr << "'�� ������ �����ϴ�." << std::endl;
    }
    else {
        std::cout << "\n--- ��¥ '" << dateStr << "'�� ���� ��� ---\n" << std::endl;
        std::cout << std::left << std::setw(15) << "���� ID"
            << std::setw(15) << "�� ID"
            << std::setw(25) << "���� �̸�"
            << std::setw(20) << "���� �ð�" << std::endl;
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