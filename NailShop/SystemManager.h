#pragma once
#include <string>
// #include <map> // ���� SystemManager.h���� map�� ���� ������� �����Ƿ� �ּ� ó�� �Ǵ� ���� ����
#include "ReservationManager.h" // ReservationManager ��ü�� ����ϹǷ� ����

// �ý��� ������ Ŭ����
class SystemManager {
public:
    // ������: �ʿ��� ��� ReservationManager ��ü�� �ʱ�ȭ�մϴ�.
    SystemManager();

    // �ý����� �����ϰ� ���� �޴� ������ �����ϴ� �Լ�
    void run();

private:
    // ���� ������ ���� ReservationManager ��ü
    ReservationManager reservationManager;

    // --- �޴� ���� �Լ��� ---
    void displayMainMenu(); // ���� �޴��� ����ϴ� �Լ�
    void handleMainMenuInput(int choice); // ���� �޴� ������ ó���ϴ� �Լ�

    // --- ���� ���� ���� �޴� ���� �Լ��� ---
    void reservationMenu(); // ���� ���� ���� �޴��� ����ϴ� �Լ�
    void handleReservationMenuInput(int choice); // ���� ���� �޴� ������ ó���ϴ� �Լ�

    // --- ���� ���� ��� �Լ��� (ReservationManager�� ����) ---
    void addNewReservation(); // ���ο� ���� �߰��� ���� ����� �Է� ó��
    void cancelExistingReservation(); // ���� ���� ��Ҹ� ���� ����� �Է� ó��
    void viewSpecificReservation(); // Ư�� ���� ��ȸ�� ���� ����� �Է� ó��
    void viewAllReservations(); // ��ü ���� ��� ��ȸ
};