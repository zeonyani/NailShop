// ServiceManager.cpp
#include "ServiceManager.h" // ServiceManager 클래스
#include <iostream>         // 콘솔 출력
#include <sstream>          // std::stringstream
#include <algorithm>        // std::max
#include <iomanip>          // 출력 포맷팅

using namespace std;        // std:: 네임스페이스 사용

// ServiceManager 생성자
ServiceManager::ServiceManager() : nextServiceId(1) {
    cout << "ServiceManager 초기화. 서비스 데이터 로드 중..." << endl;
    loadServices(); // 서비스 데이터 로드
}

// ServiceManager 소멸자
ServiceManager::~ServiceManager() {
    cout << "ServiceManager 종료. 서비스 데이터 저장 중..." << endl;
    saveServices(); // 서비스 데이터 저장
}

// CSV 파일로부터 서비스 데이터 로드
void ServiceManager::loadServices() {
    vector<string> serviceLines = CSVHandler::readCsv(SERVICES_FILE);
    if (serviceLines.empty()) {
        cout << "서비스 데이터 파일 없음/비어있음. 새 파일 생성 가능." << endl;
        nextServiceId = 1; // 파일이 없거나 비어있으면 ID 1부터 시작
        return;
    }

    int maxId = 0;
    for (const string& line : serviceLines) {
        Service service = Service::fromCsvString(line);
        if (service.getServiceId() != "") { // 유효한 서비스 정보 추가
            services.emplace(service.getServiceId(), service);
            // 숫자 부분만 추출하여 최대 ID 갱신
            try {
                int idNum = stoi(service.getServiceId().substr(3));
                maxId = max(maxId, idNum);
            }
            catch (const invalid_argument& e) {
                cerr << "오류: 서비스 ID 파싱 실패 - " << service.getServiceId() << " (" << e.what() << ")" << endl;
            }
            catch (const out_of_range& e) {
                cerr << "오류: 서비스 ID 범위 초과 - " << service.getServiceId() << " (" << e.what() << ")" << endl;
            }
        }
    }
    nextServiceId = maxId + 1; // 다음 ID 설정
    cout << "총 " << services.size() << "개 서비스 데이터 로드 완료. 다음 서비스 ID: " << nextServiceId << endl;
}

// CSV 파일에 서비스 데이터 저장
void ServiceManager::saveServices() {
    vector<string> dataToSave;
    for (const auto& pair : services) {
        dataToSave.push_back(pair.second.toCsvString());
    }
    CSVHandler::writeCsv(SERVICES_FILE, dataToSave);
    cout << "총 " << services.size() << "개 서비스 데이터 저장 완료." << endl;
}

// 고유 서비스 ID 생성
string ServiceManager::generateUniqueId() {
    stringstream ss;
    ss << "SVC" << nextServiceId++;
    return ss.str();
}

// 새 서비스 추가
bool ServiceManager::addService(const string& name, double price, int durationMinutes) {
    string id = generateUniqueId();
    if (services.find(id) == services.end()) {
        services.emplace(id, Service(id, name, price, durationMinutes));
        saveServices(); // 저장
        cout << "서비스 '" << name << "' (ID: " << id << ") 추가 완료." << endl;
        return true;
    }
    return false; // ID 충돌 (거의 발생하지 않음)
}

// 기존 서비스 수정
bool ServiceManager::updateService(const string& serviceId, const string& newName, double newPrice, int newDurationMinutes) {
    auto it = services.find(serviceId);
    if (it != services.end()) {
        it->second = Service(serviceId, newName, newPrice, newDurationMinutes); // 객체 업데이트
        saveServices(); // 저장
        cout << "서비스 ID '" << serviceId << "' 업데이트 완료." << endl;
        return true;
    }
    cout << "오류: 서비스 ID '" << serviceId << "' 찾을 수 없음. 업데이트 실패." << endl;
    return false;
}

// 서비스 삭제
bool ServiceManager::deleteService(const string& serviceId) {
    if (services.erase(serviceId)) {
        saveServices(); // 저장
        cout << "서비스 ID '" << serviceId << "' 삭제 완료." << endl;
        return true;
    }
    cout << "오류: 서비스 ID '" << serviceId << "' 찾을 수 없음. 삭제 실패." << endl;
    return false;
}

// 특정 서비스 정보 조회 (ID)
const Service* ServiceManager::getService(const std::string& serviceId) const {
    auto it = services.find(serviceId);
    if (it != services.end()) {
        return &(it->second);
    }
    return nullptr;
}

// 특정 서비스 정보 조회 (이름)
const Service* ServiceManager::getServiceByName(const std::string& serviceName) const {
    for (const auto& pair : services) {
        if (pair.second.getName() == serviceName) {
            return &(pair.second);
        }
    }
    return nullptr;
}

// 모든 서비스 목록 출력
void ServiceManager::printAllServices() const {
    if (services.empty()) {
        cout << "등록된 서비스 없음." << endl;
        return;
    }
    cout << "\n--- 전체 서비스 목록 ---" << endl;
    cout << left << setw(9) << "ID"
        << setw(13) << "이름"
        << right << setw(10) << "가격"
        << setw(13) << "소요시간(분)" << endl;
    cout << "------------------------------------------" << endl;
    for (const auto& pair : services) {
        const Service& svc = pair.second;
        cout << left << setw(9) << svc.getServiceId()
            << setw(13) << svc.getName()
            << right << setw(8) << fixed << setprecision(0) << svc.getPrice() << "원"
            << setw(9) << svc.getDurationMinutes() << "분" << endl;
    }
    cout << "------------------------------------------" << endl;
}