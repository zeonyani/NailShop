#include "SystemManager.h"
#include <iostream>
#include <limits> // numeric_limits�� ���� �ʿ�
#include <string> // getline�� ���� �ʿ�

// !!! ����: using namespace std; ������� ���� �̸� �浹 ���ɼ��� �����ϰ� ����Ͻʽÿ�. !!!
using namespace std;

// ������ ����
SystemManager::SystemManager() {
    cout << "���ϼ� ���� �ý����� �����մϴ�." << endl;
}

// �ý��� ���� ����
void SystemManager::run() {
    int choice;
    do {
        displayMainMenu();
        cout << "�޴��� �����ϼ���: ";
        cin >> choice;

        // �Է� ���� ���� (cin ������ getline ��� �� �ʼ�)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        handleMainMenuInput(choice);

        // ���α׷� ���� (0��)�� �ƴ� ��쿡�� ��� ����
        if (choice != 0) {
            cout << "\n����Ϸ��� Enter�� ��������...";
            cin.get(); // Enter �Է� ���
        }

    } while (choice != 0); // 0�� �Է��ϸ� ����
    cout << "���ϼ� ���� �ý����� �����մϴ�." << endl;
}

// ���� �޴� ���
void SystemManager::displayMainMenu() {
    cout << "\n--- ���� �޴� ---" << endl;
    cout << "1. ���� ����" << endl;
    cout << "0. ���α׷� ����" << endl;
}

// ���� �޴� �Է� ó��
void SystemManager::handleMainMenuInput(int choice) {
    switch (choice) {
    case 1:
        reservationMenu(); // ���� ���� ���� �޴� ȣ��
        break;
    case 0:
        // ���� �޽����� run() �Լ����� ó��
        break;
    default:
        cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << endl;
        break;
    }
}

// ���� ���� ���� �޴� ���
void SystemManager::reservationMenu() {
    int choice;
    do {
        cout << "\n--- ���� ���� �޴� ---" << endl;
        cout << "1. �� ���� �߰�" << endl;
        cout << "2. ���� ��� (����)" << endl;
        cout << "3. Ư�� ���� ��ȸ" << endl;
        cout << "4. ��ü ���� ��� ����" << endl;
        cout << "0. �ڷΰ��� (���� �޴�)" << endl;
        cout << "�޴��� �����ϼ���: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ���� ����

        handleReservationMenuInput(choice);

        // �ڷΰ���(0��)�� �ƴ� ��쿡�� ��� ����
        if (choice != 0) {
            cout << "\n����Ϸ��� Enter�� ��������...";
            cin.get();
        }

    } while (choice != 0);
}

// ���� ���� �޴� �Է� ó��
void SystemManager::handleReservationMenuInput(int choice) {
    switch (choice) {
    case 1:
        addNewReservation();
        break;
    case 2:
        cancelExistingReservation();
        break;
    case 3:
        viewSpecificReservation();
        break;
    case 4:
        viewAllReservations();
        break;
    case 0:
        // �ڷΰ��� (���� �޴��� ���ư�)
        break;
    default:
        cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << endl;
        break;
    }
}

// --- ���� ���� ��� �Լ� ���� ---

void SystemManager::addNewReservation() {
    string customerId, service, datetime;
    cout << "���ο� ������ �߰��մϴ�." << endl;
    cout << "�� ID�� �Է��ϼ���: ";
    getline(cin, customerId);
    cout << "���� ������ �Է��ϼ��� (��: ���Ͼ�Ʈ, �е�ť��): ";
    getline(cin, service);
    cout << "���� ��¥ �� �ð��� �Է��ϼ��� (��: 2025-06-20 15:00): ";
    getline(cin, datetime);

    reservationManager.addReservation(customerId, service, datetime);
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