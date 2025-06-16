// SystemManager.h
#pragma once

#include <string>           // std::string
#include "ReservationManager.h" // ReservationManager
#include "UserManager.h"    // UserManager
#include "ServiceManager.h" // ServiceManager
#include "User.h"           // UserType, User

// ��ü �ý��� �帧 ����
class SystemManager {
public:
    // SystemManager ������
    SystemManager();
    // �ý��� ���� ������
    void run();

private:
    ReservationManager reservationManager;  // ���� ���� ��ü
    UserManager userManager;                // ����� ���� ��ü
    ServiceManager serviceManager;          // ���� ���� ��ü

    UserType currentLoggedInUserType;        // ���� �α��� ����� ����
    std::string currentLoggedInUserId;      // ���� �α��� ����� ID
    std::string currentLoggedInUserName;    // ���� �α��� ����� �̸�
    std::string currentLoggedInUserPhone;   // ���� �α��� ����� ��ȭ��ȣ

    // �ʱ� ���� �޴� ǥ��
    void displayEntryMenu();
    // ����� �α��� ó��
    bool loginUser();
    // �� ȸ������ ó��
    void registerCustomerAccount();

    // �ʱ� ������ ���� ����
    void createInitialAdminAccount();
    // �ʱ� ���� ������ ����
    void createInitialServices();

    // ���� �޴� ���
    void displayMainMenu();
    // ���� �޴� �Է� ó��
    void handleMainMenuInput(int choice);

    // �� ���� �߰�
    void addNewReservation();
    // ���� ���� ���
    void cancelExistingReservation();
    // Ư�� ���� ��ȸ
    void viewSpecificReservation();
    // ��� ���� ��ȸ
    void viewAllReservations();
    // �� ���� ��ȸ (�� ����)
    void viewMyReservations();

    // ���� ���� Ȯ�� (����/����)
    void employeeViewTodayReservations();

    // ����� ���� (���� ���� ���� �޴�)
    void manageUsers();
    // �� ����/�� ���� �߰�
    void addStaffOrCustomerAccount();
    // ����/�� ���� ����
    void deleteStaffOrCustomerAccount();
    // ��� ����� ��� ����
    void viewAllUsers();
    // ����� �˻� (ID)
    void searchUser();


    // ���� ���� (���� ���� ���� �޴�)
    void manageServices();
    // ���� �߰�
    void addService();
    // ���� ����
    void updateService();
    // ���� ����
    void deleteService();
    // ���� ��� ����
    void viewServices();
};