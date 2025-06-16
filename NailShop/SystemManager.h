#pragma once

#include <string>
#include "ReservationManager.h"
#include "UserManager.h" // UserManager Ŭ���� ����� ���� �����ϱ�
#include "User.h"        // UserType�� ���� ����ϱ� ���� �����ϱ�

class SystemManager {
public:
    SystemManager();
    void run();

private:
    ReservationManager reservationManager;
    UserManager userManager;             // ����� ������ ���� UserManager ��ü
    UserType currentLoggedInUserType;    // ���� �α��ε� ������� ����
    std::string currentLoggedInUserId;   // ���� �α��ε� ������� ID

    // --- �α��� ���� �Լ� ---
    bool loginUser();

    // --- �޴� ���� �Լ��� ---
    void displayMainMenu();
    void handleMainMenuInput(int choice);

    // --- ���� ���� ��� �Լ��� (ReservationManager�� ����� Ȱ��) ---
    void addNewReservation();
    void cancelExistingReservation();
    void viewSpecificReservation();
    void viewAllReservations();
    void viewMyReservations();        // ���� �α��ε� ���� ���ุ ���͸��Ͽ� ��ȸ�ϱ� (�� ����)

    // --- ���Ѻ� Ưȭ ��� (�̱��� �Լ��� ����) ---
    void employeeViewTodayReservations();
};