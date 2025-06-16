// main.cpp

#include "SystemManager.h" // SystemManager 클래스
#include "Reservation.h"   // Reservation 클래스
#include "CSVHandler.h"    // CSVHandler
#include "Service.h"       // Service
#include "ServiceManager.h"// ServiceManager
#include "ReservationManager.h" // ReservationManager
#include "User.h"          // User
#include "UserManager.h"   // UserManager
#include "Admin.h"         // Admin
#include "Customer.h"      // Customer
#include "Staff.h"         // Staff


#include <iostream>        // 콘솔 출력

int main() {
    // SystemManager 객체 생성
    SystemManager systemManager;

    // 시스템 실행 함수 호출
    systemManager.run();

    // 프로그램 종료
    return 0;
}