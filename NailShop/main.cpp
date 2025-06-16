// main.cpp

#include "SystemManager.h" // SystemManager Ŭ����
#include "Reservation.h"   // Reservation Ŭ����
#include "CSVHandler.h"    // CSVHandler
#include "Service.h"       // Service
#include "ServiceManager.h"// ServiceManager
#include "ReservationManager.h" // ReservationManager
#include "User.h"          // User
#include "UserManager.h"   // UserManager
#include "Admin.h"         // Admin
#include "Customer.h"      // Customer
#include "Staff.h"         // Staff


#include <iostream>        // �ܼ� ���

int main() {
    // SystemManager ��ü ����
    SystemManager systemManager;

    // �ý��� ���� �Լ� ȣ��
    systemManager.run();

    // ���α׷� ����
    return 0;
}