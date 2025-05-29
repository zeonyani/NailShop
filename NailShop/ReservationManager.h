#pragma once
#include <map>
#include <string>
#include "Reservation.h"
using namespace std;

class ReservationManager {
public:
	ReservationManager() = default; // �⺻ ������
	ReservationManager(const ReservationManager&) = delete; // ���� ������ ����
	
private:
	map<string, Reservation> reservations; // ���� ID�� Ű�� �ϴ� ���� ���� ��



};