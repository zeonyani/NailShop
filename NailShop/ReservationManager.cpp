// ReservationManager.cpp
#include "ReservationManager.h"
#include <iostream>     // �ܼ� ���
#include <algorithm>    // std::find_if
#include <ctime>        // std::time_t, std::tm, localtime_s (�ð� ó��)
#include <iomanip>      // std::put_time, std::setfill, std::setw
#include <sstream>      // std::stringstream
#include <stdexcept>    // std::invalid_argument, std::out_of_range

const std::string ReservationManager::RESERVATIONS_FILE = "reservations.csv";

// ReservationManager ������
ReservationManager::ReservationManager(const ServiceManager& svcManager)
    : serviceManager(svcManager), nextReservationId(1) {
    loadReservations(); // ���� ������ �ε�
}

// ReservationManager �Ҹ���
ReservationManager::~ReservationManager() {
    saveReservations(true); // �Ҹ� �ÿ��� �޽��� ���� ���� (silent=true)
}

// ���� ���� ID ����
// �� �Լ��� ReservationManager�� ��� �Լ����� ��� (Ŭ���� �̸�::�Լ� �̸�)
std::string ReservationManager::generateUniqueId() {
    std::string newId = "RES" + std::to_string(nextReservationId);
    while (reservations.count(newId)) { // Ȥ�ó� ID�� �ߺ��Ǹ� ���� ID ���
        nextReservationId++;
        newId = "RES" + std::to_string(nextReservationId);
    }
    nextReservationId++; // ���� ������ ���� ID ����
    return newId;
}

// ���� ������ �ε�
void ReservationManager::loadReservations() {
    std::vector<std::string> lines = CSVHandler::readCsv(RESERVATIONS_FILE);
    reservations.clear(); // ���� ������ ����
    nextReservationId = 1; // ID ī���� �ʱ�ȭ

    for (const std::string& line : lines) {
        Reservation reservation = Reservation::fromCsvString(line);
        if (!reservation.getReservationId().empty()) {
            reservations[reservation.getReservationId()] = reservation;
            // nextReservationId ������Ʈ
            if (reservation.getReservationId().rfind("RES", 0) == 0) {
                try {
                    int idNum = std::stoi(reservation.getReservationId().substr(3));
                    if (idNum >= nextReservationId) {
                        nextReservationId = idNum + 1;
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "���: ���� ID �Ľ� ���� (Invalid Argument): " << e.what() << " in line: " << line << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "���: ���� ID �Ľ� ���� (Out of Range): " << e.what() << " in line: " << line << std::endl;
                }
            }
        }
    }
}

// ���� ������ ����
void ReservationManager::saveReservations(bool silent) {
    std::vector<std::string> lines;
    for (const auto& pair : reservations) {
        lines.push_back(pair.second.toCsvString());
    }
    if (CSVHandler::writeCsv(RESERVATIONS_FILE, lines)) {
        if (!silent) {
            // ���� ������ ���� �Ϸ� �޽��� ����
        }
    }
    else {
        std::cerr << "����: ���� �����͸� ���Ͽ� �������� ���߽��ϴ�." << std::endl;
    }
}

// ���� �߰�
bool ReservationManager::addReservation(const std::string& customerId, const std::string& serviceName,
    const std::chrono::system_clock::time_point& reservationTime) {

    // ���� ��ȿ�� Ȯ��
    const Service* service = serviceManager.getServiceByName(serviceName);
    if (service == nullptr) {
        std::cout << "����: '" << serviceName << "' ���񽺰� �������� �ʽ��ϴ�." << std::endl;
        return false;
    }

    // ���� �ð� ��ħ Ȯ��
    if (!isTimeSlotAvailable(reservationTime, service->getDurationMinutes())) {
        std::cout << "����: �ش� �ð��� �̹� �ٸ� ������ �ֽ��ϴ�. �ٸ� �ð��� �������ּ���." << std::endl;
        return false;
    }

    std::string newReservationId = generateUniqueId();
    Reservation newReservation(newReservationId, customerId, serviceName,
        Reservation::getFormattedDateTime(reservationTime)); // time_point�� ���ڿ��� ��ȯ�Ͽ� �����ڿ� ����

    reservations[newReservationId] = newReservation;
    saveReservations(); // ������� ����
    std::cout << "'" << serviceName << "' ���� ������ ���������� �Ϸ�Ǿ����ϴ�. ���� ID: " << newReservationId << std::endl;
    return true;
}

// ���� ���
bool ReservationManager::cancelReservation(const std::string& reservationId) {
    auto it = reservations.find(reservationId);
    if (it != reservations.end()) {
        reservations.erase(it);
        saveReservations(); // ������� ����
        std::cout << "���� ID '" << reservationId << "'�� ���������� ��ҵǾ����ϴ�." << std::endl;
        return true;
    }
    std::cout << "����: ���� ID '" << reservationId << "'�� ã�� �� �����ϴ�." << std::endl;
    return false;
}

// ���� ID�� ���� ��ȸ
const Reservation* ReservationManager::getReservation(const std::string& reservationId) const {
    auto it = reservations.find(reservationId);
    if (it != reservations.end()) {
        return &(it->second);
    }
    return nullptr;
}

// Ư�� ���� ��� ���� ��ȸ
std::vector<const Reservation*> ReservationManager::getReservationsByCustomer(const std::string& customerId) const {
    std::vector<const Reservation*> customerReservations;
    for (const auto& pair : reservations) {
        if (pair.second.getCustomerId() == customerId) {
            customerReservations.push_back(&(pair.second));
        }
    }
    return customerReservations;
}

// Ư�� ��¥�� ��� ���� ��ȸ
std::vector<const Reservation*> ReservationManager::getReservationsByDate(const std::string& dateStr) const {
    std::vector<const Reservation*> dailyReservations;
    // �Էµ� ��¥ ���ڿ��� time_point�� ��ȯ (��¥�� �ʿ��ϹǷ� �ð��� 00:00���� ����)
    std::tm t = {};
    std::istringstream ss(dateStr + " 00:00");
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M");
    if (ss.fail()) {
        std::cerr << "����: �߸��� ��¥ �����Դϴ�. (YYYY-MM-DD)" << std::endl;
        return dailyReservations; // �� ���� ��ȯ
    }
    std::chrono::system_clock::time_point targetDateStart = std::chrono::system_clock::from_time_t(std::mktime(&t));

    // ���� �� 00:00 ���
    std::chrono::system_clock::time_point targetDateEnd = targetDateStart + std::chrono::hours(24);

    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;
        std::chrono::system_clock::time_point resTime = res.getReservationTime();

        // ���� �ð��� ��ǥ ��¥�� ���۰� ���� �� ���� ���̿� �ִ��� Ȯ��
        if (resTime >= targetDateStart && resTime < targetDateEnd) {
            dailyReservations.push_back(&res);
        }
    }
    // �ð� ������ ����
    std::sort(dailyReservations.begin(), dailyReservations.end(), [](const Reservation* a, const Reservation* b) {
        return a->getReservationTime() < b->getReservationTime();
        });

    return dailyReservations;
}

// ��� ���� ���� ���
void ReservationManager::printAllReservations() const {
    if (reservations.empty()) {
        std::cout << "��ϵ� ������ �����ϴ�." << std::endl;
        return;
    }
    std::cout << "\n--- ��� ���� ��� ---\n" << std::endl;
    std::cout << std::left << std::setw(15) << "���� ID"
        << std::setw(15) << "�� ID"
        << std::setw(25) << "���� �̸�"
        << std::setw(20) << "���� �ð�" << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;
        std::cout << std::left << std::setw(15) << res.getReservationId()
            << std::setw(15) << res.getCustomerId()
            << std::setw(25) << res.getServiceName()
            << std::setw(20) << res.getFormattedDateTime() << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
}

// �ð� ��ħ Ȯ��
bool ReservationManager::isTimeSlotAvailable(const std::chrono::system_clock::time_point newStartTime, int newDurationMinutes) const {
    // ���� ���� �ð� ���
    std::chrono::system_clock::time_point newEndTime = newStartTime + std::chrono::minutes(newDurationMinutes);

    for (const auto& pair : reservations) {
        const Reservation& existingRes = pair.second;
        // ���� ������ ���� �ð�
        std::chrono::system_clock::time_point existingStartTime = existingRes.getReservationTime();
        // ���� ���� ������ �ҿ� �ð� ��������
        const Service* existingService = serviceManager.getServiceByName(existingRes.getServiceName());
        if (existingService == nullptr) {
            // �� ���� ������ ������ �� �� �����Ƿ� ��� �޽��� ��� �� ��ŵ
            continue;
        }
        int existingDurationMinutes = existingService->getDurationMinutes();
        // ���� ������ ���� �ð� ���
        std::chrono::system_clock::time_point existingEndTime = existingStartTime + std::chrono::minutes(existingDurationMinutes);

        // �� ������ ��ġ�� �ʴ� ���� ���� �� ����
        // 1. ���ο� ������ ���� ���ຸ�� ������ ���� ������ ���: newEndTime <= existingStartTime
        // 2. ���ο� ������ ���� ���ຸ�� ������ �ʰ� �����ϴ� ���: newStartTime >= existingEndTime
        // ���� ��ġ�� ���� �� �� ���� ��찡 �ƴ� ���
        if (!(newEndTime <= existingStartTime || newStartTime >= existingEndTime)) {
            return false; // �ð��� ��ħ
        }
    }
    return true; // �ð��� ��ġ�� ����
}

// ��� ���� ��� ��ȯ ����
const std::map<std::string, Reservation>& ReservationManager::getAllReservations() const {
    return reservations;
}