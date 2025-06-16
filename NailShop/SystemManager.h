//SystemManager.h
#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "UserManager.h"
#include "ServiceManager.h"
#include "ReservationManager.h"
#include "User.h" // UserType ���Ǹ� ���� �ʿ�

// SystemManager Ŭ����
class SystemManager {
private:
    UserManager userManager;
    ServiceManager serviceManager;
    ReservationManager reservationManager; // �����ڿ��� serviceManager ������ �޵��� ����

    UserType currentLoggedInUserType;
    std::string currentLoggedInUserId;
    std::string currentLoggedInUserName;
    std::string currentLoggedInUserPhone; // ���� �α����� ����� ��ȭ��ȣ

    // �Է� ���� ���� ���� �Լ�
    void clearInputBuffer();

    // �޴� ���� �Լ���
    void displayMainMenu();
    void processMainMenuInput(int choice);

    void displayOwnerMenu();
    void processOwnerMenuInput(int choice);
    void handleOwnerServiceManagement();
    void handleOwnerUserManagement();
    void handleOwnerReservationManagement(); // ���� ���� ���� ���
    void handleOwnerAccountInfo(); // ���� ���� ���� ���� ���

    void displayEmployeeMenu();
    void processEmployeeMenuInput(int choice);
    void handleEmployeeServiceManagement();
    void handleEmployeeReservationManagement(); // ���� ���� ���� ���
    void handleEmployeeAccountInfo(); // ���� ���� ���� ���� ���

    void displayCustomerMenu();
    void processCustomerMenuInput(int choice);
    void handleCustomerReservationManagement(); // �� ���� ���� ���
    void handleCustomerAccountInfo(); // �� ���� ���� ���� ���

    // �߰��� �Լ� ����
    void handleLogin(); // �α��� ó�� �Լ�

    void addUser();
    void deleteUser();
    // �����ε�� �Լ��� ����Ͽ� ���� �α��ε� ����� �Ǵ� Ư�� ������� ������ ����
    void updateUserAccountInfo(const std::string& targetUserId = "");

    void makeReservation(); // ���� ���� ���
    void cancelReservation(); // ���� ��� ��� (������/������)
    void cancelReservation(const std::string& customerId); // ���� ��� ��� (����, �ڽ��� ���ุ)
    void viewAllReservations(); // ��� ���� ���� ���
    void viewReservationsByCustomer(); // ���� ���� ���� ��� (������/������)
    void viewReservationsByCustomer(const std::string& customerId); // ���� ���� ���� ��� (����, �ڽ��� ���ุ)
    void viewReservationsForDate(); // ��¥�� ���� ���� ���

public:
    SystemManager();
    void run();
};

#endif // SYSTEM_MANAGER_H