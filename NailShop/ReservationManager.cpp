// ReservationManager.cpp
#include "ReservationManager.h" // ReservationManager Ŭ����
#include <iostream>             // �ܼ� ���
#include <random>               // ���� ����
#include <sstream>              // ���ڿ� ��Ʈ��
#include <algorithm>            // std::max
#include <string>               // std::string::substr
#include <iomanip>              // ��� ������

using namespace std;            // std:: ���ӽ����̽� ���

// ReservationManager ������
ReservationManager::ReservationManager() : nextReservationId(1) {
    cout << "���� ������ �ʱ�ȭ. ���� ������ �ε� ��..." << endl;
    loadReservations(); // ���� ������ �ε�
}

// ReservationManager �Ҹ���
ReservationManager::~ReservationManager() {
    cout << "���� ������ ����. ���� ������ ���� ��..." << endl;
    saveReservations(); // ���� ������ ����
}

// CSV ���Ϸκ��� ���� ������ �ε�
void ReservationManager::loadReservations() {
    vector<string> reservationLines = CSVHandler::readCsv(RESERVATIONS_FILE);
    if (reservationLines.empty()) {
        cout << "���� ������ ���� ����/�������. �� ���� ���� ����." << endl;
        nextReservationId = 1; // ������ ���ų� ��������� ID 1���� ����
        return;
    }

    int maxId = 0;
    for (const string& line : reservationLines) {
        Reservation reservation = Reservation::fromCsvString(line);
        if (reservation.getReservationId() != "") { // ��ȿ�� ���� ���� �߰�
            reservations.emplace(reservation.getReservationId(), reservation);
            // ���� �κи� �����Ͽ� �ִ� ID ����
            try {
                int idNum = stoi(reservation.getReservationId().substr(3));
                maxId = max(maxId, idNum);
            }
            catch (const invalid_argument& e) {
                cerr << "����: ���� ID �Ľ� ���� - " << reservation.getReservationId() << endl;
            }
            catch (const out_of_range& e) {
                cerr << "����: ���� ID ���� �ʰ� - " << reservation.getReservationId() << endl;
            }
        }
    }
    nextReservationId = maxId + 1; // ���� ID ����
    cout << "�� " << reservations.size() << "�� ���� ������ �ε� �Ϸ�. ���� ���� ID: " << nextReservationId << endl;
}

// CSV ���Ͽ� ���� ������ ����
void ReservationManager::saveReservations() {
    vector<string> dataToSave;
    for (const auto& pair : reservations) {
        dataToSave.push_back(pair.second.toCsvString());
    }
    CSVHandler::writeCsv(RESERVATIONS_FILE, dataToSave);
    cout << "�� " << reservations.size() << "�� ���� ������ ���� �Ϸ�." << endl;
}

// �� ���� �߰�
bool ReservationManager::addReservation(const string& customerId, const string& service, const string& dateTime) {
    string id = generateUniqueId(); // ���� ID ����
    if (reservations.find(id) == reservations.end()) { // ID �ߺ� Ȯ��
        reservations.emplace(id, Reservation(id, customerId, service, dateTime)); // �� ���� ��ü �߰�
        saveReservations(); // ���Ͽ� ����
        cout << "���� �߰� �Ϸ�. ���� ID: " << id << endl;
        return true;
    }
    return false; // ID �ߺ����� �߰� ����
}

// ���� ����
bool ReservationManager::deleteReservation(const string& reservationId) {
    if (reservations.erase(reservationId)) { // ���� ���� �õ�
        saveReservations(); // ���Ͽ� ����
        cout << "���� ID " << reservationId << " ���� �Ϸ�." << endl;
        return true; // ���� ����
    }
    else {
        cout << "����: ���� ID " << reservationId << " ã�� �� ����." << endl;
        return false; // ���� ����
    }
}

// Ư�� ���� ���� ���
void ReservationManager::printReservation(const string& reservationId) const {
    auto it = reservations.find(reservationId); // ���� ID �˻�
    if (it != reservations.end()) { // ���� ID ����
        const Reservation& res = it->second; // ���� ��ü ����
        cout << "--- ���� ���� ---" << endl;
        cout << "ID: " << res.getReservationId() << endl;
        cout << "�� ID: " << res.getCustomerId() << endl;
        cout << "����: " << res.getService() << endl;
        cout << "��¥/�ð�: " << res.getDateTime() << endl;
        cout << "-----------------" << endl;
    }
    else {
        cout << "����: ���� ID " << reservationId << " ã�� �� ����." << endl;
    }
}

// Ư�� ���� ���� ��ȸ (��ü ��ȯ)
const Reservation* ReservationManager::getReservation(const std::string& reservationId) const {
    auto it = reservations.find(reservationId);
    if (it != reservations.end()) {
        return &(it->second); // Reservation ��ü �ּ� ��ȯ
    }
    return nullptr; // ã�� ����
}

// ��� ���� ���� ���
void ReservationManager::printAllReservations() const {
    if (reservations.empty()) { // ���� ����
        cout << "��ϵ� ���� ����." << endl;
        return;
    }
    cout << "\n--- ��ü ���� ��� ---" << endl;
    cout << left << setw(10) << "ID"
        << setw(15) << "�� ID"
        << setw(15) << "����"
        << setw(20) << "��¥/�ð�" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (const auto& pair : reservations) { // ��� ���� ��ȸ
        const Reservation& res = pair.second;
        cout << left << setw(10) << res.getReservationId()
            << setw(15) << res.getCustomerId()
            << setw(15) << res.getService()
            << setw(20) << res.getDateTime() << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}

// Ư�� ���� ���� ���
void ReservationManager::printReservationsByCustomerId(const std::string& customerId) const {
    bool found = false;
    cout << "\n--- �� ID '" << customerId << "' ���� ��� ---" << endl;
    cout << left << setw(10) << "ID"
        << setw(15) << "����"
        << setw(20) << "��¥/�ð�" << endl;
    cout << "-----------------------------------------" << endl;
    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;
        if (res.getCustomerId() == customerId) {
            cout << left << setw(10) << res.getReservationId()
                << setw(15) << res.getService()
                << setw(20) << res.getDateTime() << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "�ش� ���� ���� ����." << endl;
    }
    cout << "-----------------------------------------" << endl;
}

// ���� ���� ID ����
string ReservationManager::generateUniqueId() {
    stringstream ss;
    ss << "RES" << nextReservationId++; // "RES" ���λ� + ���� ����
    return ss.str();
}

// Ư�� ��¥�� ���� ���
void ReservationManager::printReservationsForDate(const std::string& date) const {
    bool found = false;
    std::cout << "\n--- " << date << " ���� ��� ---" << std::endl;
    std::cout << left << setw(15) << "���� ID"
        << setw(15) << "�� ID"
        << setw(15) << "����"
        << setw(10) << "�ð�" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;
        // ���� ��¥ �κ� ���� (��: "2025-06-20 15:00" -> "2025-06-20")
        if (res.getDateTime().length() >= 10) { // �ּ� ���� Ȯ��
            std::string reservationDate = res.getDateTime().substr(0, 10);
            if (reservationDate == date) {
                std::cout << left << setw(15) << res.getReservationId()
                    << setw(15) << res.getCustomerId()
                    << setw(15) << res.getService();
                if (res.getDateTime().length() >= 16) { // "YYYY-MM-DD HH:MM" ���� Ȯ��
                    std::cout << setw(10) << res.getDateTime().substr(11, 5) << std::endl; // �ð��� ���
                }
                else {
                    std::cout << setw(10) << "�ð� ���� ����" << std::endl;
                }
                found = true;
            }
        }
    }
    if (!found) {
        std::cout << "�ش� ��¥�� ���� ����." << std::endl;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
}