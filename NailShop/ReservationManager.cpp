// ReservationManager.cpp
#include "ReservationManager.h" // ReservationManager 클래스
#include <iostream>             // 콘솔 출력
#include <random>               // 난수 생성
#include <sstream>              // 문자열 스트림
#include <algorithm>            // std::max
#include <string>               // std::string::substr
#include <iomanip>              // 출력 포맷팅

using namespace std;            // std:: 네임스페이스 사용

// ReservationManager 생성자
ReservationManager::ReservationManager() : nextReservationId(1) {
    cout << "예약 관리자 초기화. 예약 데이터 로드 중..." << endl;
    loadReservations(); // 예약 데이터 로드
}

// ReservationManager 소멸자
ReservationManager::~ReservationManager() {
    cout << "예약 관리자 종료. 예약 데이터 저장 중..." << endl;
    saveReservations(); // 예약 데이터 저장
}

// CSV 파일로부터 예약 데이터 로드
void ReservationManager::loadReservations() {
    vector<string> reservationLines = CSVHandler::readCsv(RESERVATIONS_FILE);
    if (reservationLines.empty()) {
        cout << "예약 데이터 파일 없음/비어있음. 새 파일 생성 가능." << endl;
        nextReservationId = 1; // 파일이 없거나 비어있으면 ID 1부터 시작
        return;
    }

    int maxId = 0;
    for (const string& line : reservationLines) {
        Reservation reservation = Reservation::fromCsvString(line);
        if (reservation.getReservationId() != "") { // 유효한 예약 정보 추가
            reservations.emplace(reservation.getReservationId(), reservation);
            // 숫자 부분만 추출하여 최대 ID 갱신
            try {
                int idNum = stoi(reservation.getReservationId().substr(3));
                maxId = max(maxId, idNum);
            }
            catch (const invalid_argument& e) {
                cerr << "오류: 예약 ID 파싱 실패 - " << reservation.getReservationId() << endl;
            }
            catch (const out_of_range& e) {
                cerr << "오류: 예약 ID 범위 초과 - " << reservation.getReservationId() << endl;
            }
        }
    }
    nextReservationId = maxId + 1; // 다음 ID 설정
    cout << "총 " << reservations.size() << "개 예약 데이터 로드 완료. 다음 예약 ID: " << nextReservationId << endl;
}

// CSV 파일에 예약 데이터 저장
void ReservationManager::saveReservations() {
    vector<string> dataToSave;
    for (const auto& pair : reservations) {
        dataToSave.push_back(pair.second.toCsvString());
    }
    CSVHandler::writeCsv(RESERVATIONS_FILE, dataToSave);
    cout << "총 " << reservations.size() << "개 예약 데이터 저장 완료." << endl;
}

// 새 예약 추가
bool ReservationManager::addReservation(const string& customerId, const string& service, const string& dateTime) {
    string id = generateUniqueId(); // 고유 ID 생성
    if (reservations.find(id) == reservations.end()) { // ID 중복 확인
        reservations.emplace(id, Reservation(id, customerId, service, dateTime)); // 새 예약 객체 추가
        saveReservations(); // 파일에 저장
        cout << "예약 추가 완료. 예약 ID: " << id << endl;
        return true;
    }
    return false; // ID 중복으로 추가 실패
}

// 예약 삭제
bool ReservationManager::deleteReservation(const string& reservationId) {
    if (reservations.erase(reservationId)) { // 예약 삭제 시도
        saveReservations(); // 파일에 저장
        cout << "예약 ID " << reservationId << " 삭제 완료." << endl;
        return true; // 삭제 성공
    }
    else {
        cout << "오류: 예약 ID " << reservationId << " 찾을 수 없음." << endl;
        return false; // 삭제 실패
    }
}

// 특정 예약 정보 출력
void ReservationManager::printReservation(const string& reservationId) const {
    auto it = reservations.find(reservationId); // 예약 ID 검색
    if (it != reservations.end()) { // 예약 ID 존재
        const Reservation& res = it->second; // 예약 객체 참조
        cout << "--- 예약 정보 ---" << endl;
        cout << "ID: " << res.getReservationId() << endl;
        cout << "고객 ID: " << res.getCustomerId() << endl;
        cout << "서비스: " << res.getService() << endl;
        cout << "날짜/시간: " << res.getDateTime() << endl;
        cout << "-----------------" << endl;
    }
    else {
        cout << "오류: 예약 ID " << reservationId << " 찾을 수 없음." << endl;
    }
}

// 특정 예약 정보 조회 (객체 반환)
const Reservation* ReservationManager::getReservation(const std::string& reservationId) const {
    auto it = reservations.find(reservationId);
    if (it != reservations.end()) {
        return &(it->second); // Reservation 객체 주소 반환
    }
    return nullptr; // 찾지 못함
}

// 모든 예약 정보 출력
void ReservationManager::printAllReservations() const {
    if (reservations.empty()) { // 예약 없음
        cout << "등록된 예약 없음." << endl;
        return;
    }
    cout << "\n--- 전체 예약 목록 ---" << endl;
    cout << left << setw(10) << "ID"
        << setw(15) << "고객 ID"
        << setw(15) << "서비스"
        << setw(20) << "날짜/시간" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (const auto& pair : reservations) { // 모든 예약 순회
        const Reservation& res = pair.second;
        cout << left << setw(10) << res.getReservationId()
            << setw(15) << res.getCustomerId()
            << setw(15) << res.getService()
            << setw(20) << res.getDateTime() << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}

// 특정 고객의 예약 출력
void ReservationManager::printReservationsByCustomerId(const std::string& customerId) const {
    bool found = false;
    cout << "\n--- 고객 ID '" << customerId << "' 예약 목록 ---" << endl;
    cout << left << setw(10) << "ID"
        << setw(15) << "서비스"
        << setw(20) << "날짜/시간" << endl;
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
        cout << "해당 고객의 예약 없음." << endl;
    }
    cout << "-----------------------------------------" << endl;
}

// 고유 예약 ID 생성
string ReservationManager::generateUniqueId() {
    stringstream ss;
    ss << "RES" << nextReservationId++; // "RES" 접두사 + 숫자 조합
    return ss.str();
}

// 특정 날짜의 예약 출력
void ReservationManager::printReservationsForDate(const std::string& date) const {
    bool found = false;
    std::cout << "\n--- " << date << " 예약 목록 ---" << std::endl;
    std::cout << left << setw(15) << "예약 ID"
        << setw(15) << "고객 ID"
        << setw(15) << "서비스"
        << setw(10) << "시간" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;
        // 예약 날짜 부분 추출 (예: "2025-06-20 15:00" -> "2025-06-20")
        if (res.getDateTime().length() >= 10) { // 최소 길이 확인
            std::string reservationDate = res.getDateTime().substr(0, 10);
            if (reservationDate == date) {
                std::cout << left << setw(15) << res.getReservationId()
                    << setw(15) << res.getCustomerId()
                    << setw(15) << res.getService();
                if (res.getDateTime().length() >= 16) { // "YYYY-MM-DD HH:MM" 길이 확인
                    std::cout << setw(10) << res.getDateTime().substr(11, 5) << std::endl; // 시간만 출력
                }
                else {
                    std::cout << setw(10) << "시간 정보 없음" << std::endl;
                }
                found = true;
            }
        }
    }
    if (!found) {
        std::cout << "해당 날짜에 예약 없음." << std::endl;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
}