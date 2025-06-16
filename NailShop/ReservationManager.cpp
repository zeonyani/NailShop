// ReservationManager.cpp
#include "ReservationManager.h"
#include <iostream>     // 콘솔 출력
#include <algorithm>    // std::find_if
#include <ctime>        // std::time_t, std::tm, localtime_s (시간 처리)
#include <iomanip>      // std::put_time, std::setfill, std::setw
#include <sstream>      // std::stringstream
#include <stdexcept>    // std::invalid_argument, std::out_of_range

const std::string ReservationManager::RESERVATIONS_FILE = "reservations.csv";

// ReservationManager 생성자
ReservationManager::ReservationManager(const ServiceManager& svcManager)
    : serviceManager(svcManager), nextReservationId(1) {
    loadReservations(); // 예약 데이터 로드
}

// ReservationManager 소멸자
ReservationManager::~ReservationManager() {
    saveReservations(true); // 소멸 시에는 메시지 없이 저장 (silent=true)
}

// 고유 예약 ID 생성
// 이 함수가 ReservationManager의 멤버 함수임을 명시 (클래스 이름::함수 이름)
std::string ReservationManager::generateUniqueId() {
    std::string newId = "RES" + std::to_string(nextReservationId);
    while (reservations.count(newId)) { // 혹시나 ID가 중복되면 다음 ID 사용
        nextReservationId++;
        newId = "RES" + std::to_string(nextReservationId);
    }
    nextReservationId++; // 다음 예약을 위해 ID 증가
    return newId;
}

// 예약 데이터 로드
void ReservationManager::loadReservations() {
    std::vector<std::string> lines = CSVHandler::readCsv(RESERVATIONS_FILE);
    reservations.clear(); // 기존 데이터 비우기
    nextReservationId = 1; // ID 카운터 초기화

    for (const std::string& line : lines) {
        Reservation reservation = Reservation::fromCsvString(line);
        if (!reservation.getReservationId().empty()) {
            reservations[reservation.getReservationId()] = reservation;
            // nextReservationId 업데이트
            if (reservation.getReservationId().rfind("RES", 0) == 0) {
                try {
                    int idNum = std::stoi(reservation.getReservationId().substr(3));
                    if (idNum >= nextReservationId) {
                        nextReservationId = idNum + 1;
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "경고: 예약 ID 파싱 오류 (Invalid Argument): " << e.what() << " in line: " << line << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "경고: 예약 ID 파싱 오류 (Out of Range): " << e.what() << " in line: " << line << std::endl;
                }
            }
        }
    }
}

// 예약 데이터 저장
void ReservationManager::saveReservations(bool silent) {
    std::vector<std::string> lines;
    for (const auto& pair : reservations) {
        lines.push_back(pair.second.toCsvString());
    }
    if (CSVHandler::writeCsv(RESERVATIONS_FILE, lines)) {
        if (!silent) {
            // 예약 데이터 저장 완료 메시지 제거
        }
    }
    else {
        std::cerr << "오류: 예약 데이터를 파일에 저장하지 못했습니다." << std::endl;
    }
}

// 예약 추가
bool ReservationManager::addReservation(const std::string& customerId, const std::string& serviceName,
    const std::chrono::system_clock::time_point& reservationTime) {

    // 서비스 유효성 확인
    const Service* service = serviceManager.getServiceByName(serviceName);
    if (service == nullptr) {
        std::cout << "오류: '" << serviceName << "' 서비스가 존재하지 않습니다." << std::endl;
        return false;
    }

    // 예약 시간 겹침 확인
    if (!isTimeSlotAvailable(reservationTime, service->getDurationMinutes())) {
        std::cout << "오류: 해당 시간에 이미 다른 예약이 있습니다. 다른 시간을 선택해주세요." << std::endl;
        return false;
    }

    std::string newReservationId = generateUniqueId();
    Reservation newReservation(newReservationId, customerId, serviceName,
        Reservation::getFormattedDateTime(reservationTime)); // time_point를 문자열로 변환하여 생성자에 전달

    reservations[newReservationId] = newReservation;
    saveReservations(); // 변경사항 저장
    std::cout << "'" << serviceName << "' 서비스 예약이 성공적으로 완료되었습니다. 예약 ID: " << newReservationId << std::endl;
    return true;
}

// 예약 취소
bool ReservationManager::cancelReservation(const std::string& reservationId) {
    auto it = reservations.find(reservationId);
    if (it != reservations.end()) {
        reservations.erase(it);
        saveReservations(); // 변경사항 저장
        std::cout << "예약 ID '" << reservationId << "'가 성공적으로 취소되었습니다." << std::endl;
        return true;
    }
    std::cout << "오류: 예약 ID '" << reservationId << "'를 찾을 수 없습니다." << std::endl;
    return false;
}

// 예약 ID로 예약 조회
const Reservation* ReservationManager::getReservation(const std::string& reservationId) const {
    auto it = reservations.find(reservationId);
    if (it != reservations.end()) {
        return &(it->second);
    }
    return nullptr;
}

// 특정 고객의 모든 예약 조회
std::vector<const Reservation*> ReservationManager::getReservationsByCustomer(const std::string& customerId) const {
    std::vector<const Reservation*> customerReservations;
    for (const auto& pair : reservations) {
        if (pair.second.getCustomerId() == customerId) {
            customerReservations.push_back(&(pair.second));
        }
    }
    return customerReservations;
}

// 특정 날짜의 모든 예약 조회
std::vector<const Reservation*> ReservationManager::getReservationsByDate(const std::string& dateStr) const {
    std::vector<const Reservation*> dailyReservations;
    // 입력된 날짜 문자열을 time_point로 변환 (날짜만 필요하므로 시간은 00:00으로 가정)
    std::tm t = {};
    std::istringstream ss(dateStr + " 00:00");
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M");
    if (ss.fail()) {
        std::cerr << "오류: 잘못된 날짜 형식입니다. (YYYY-MM-DD)" << std::endl;
        return dailyReservations; // 빈 벡터 반환
    }
    std::chrono::system_clock::time_point targetDateStart = std::chrono::system_clock::from_time_t(std::mktime(&t));

    // 다음 날 00:00 계산
    std::chrono::system_clock::time_point targetDateEnd = targetDateStart + std::chrono::hours(24);

    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;
        std::chrono::system_clock::time_point resTime = res.getReservationTime();

        // 예약 시간이 목표 날짜의 시작과 다음 날 시작 사이에 있는지 확인
        if (resTime >= targetDateStart && resTime < targetDateEnd) {
            dailyReservations.push_back(&res);
        }
    }
    // 시간 순으로 정렬
    std::sort(dailyReservations.begin(), dailyReservations.end(), [](const Reservation* a, const Reservation* b) {
        return a->getReservationTime() < b->getReservationTime();
        });

    return dailyReservations;
}

// 모든 예약 정보 출력
void ReservationManager::printAllReservations() const {
    if (reservations.empty()) {
        std::cout << "등록된 예약이 없습니다." << std::endl;
        return;
    }
    std::cout << "\n--- 모든 예약 목록 ---\n" << std::endl;
    std::cout << std::left << std::setw(15) << "예약 ID"
        << std::setw(15) << "고객 ID"
        << std::setw(25) << "서비스 이름"
        << std::setw(20) << "예약 시간" << std::endl;
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

// 시간 겹침 확인
bool ReservationManager::isTimeSlotAvailable(const std::chrono::system_clock::time_point newStartTime, int newDurationMinutes) const {
    // 예약 종료 시간 계산
    std::chrono::system_clock::time_point newEndTime = newStartTime + std::chrono::minutes(newDurationMinutes);

    for (const auto& pair : reservations) {
        const Reservation& existingRes = pair.second;
        // 기존 예약의 시작 시간
        std::chrono::system_clock::time_point existingStartTime = existingRes.getReservationTime();
        // 기존 예약 서비스의 소요 시간 가져오기
        const Service* existingService = serviceManager.getServiceByName(existingRes.getServiceName());
        if (existingService == nullptr) {
            // 이 경우는 데이터 오류로 볼 수 있으므로 경고 메시지 출력 후 스킵
            continue;
        }
        int existingDurationMinutes = existingService->getDurationMinutes();
        // 기존 예약의 종료 시간 계산
        std::chrono::system_clock::time_point existingEndTime = existingStartTime + std::chrono::minutes(existingDurationMinutes);

        // 두 예약이 겹치지 않는 경우는 다음 두 가지
        // 1. 새로운 예약이 기존 예약보다 완전히 빨리 끝나는 경우: newEndTime <= existingStartTime
        // 2. 새로운 예약이 기존 예약보다 완전히 늦게 시작하는 경우: newStartTime >= existingEndTime
        // 따라서 겹치는 경우는 위 두 가지 경우가 아닌 경우
        if (!(newEndTime <= existingStartTime || newStartTime >= existingEndTime)) {
            return false; // 시간이 겹침
        }
    }
    return true; // 시간이 겹치지 않음
}

// 모든 예약 목록 반환 구현
const std::map<std::string, Reservation>& ReservationManager::getAllReservations() const {
    return reservations;
}