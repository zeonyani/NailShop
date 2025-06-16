//ServiceManager.cpp
#include "ServiceManager.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip> // std::setw, std::left 사용

const std::string ServiceManager::SERVICES_FILE = "services.csv";

ServiceManager::ServiceManager() : nextServiceId(1) {
    loadServices(); // 서비스 로드 및 초기 서비스 생성 로직 포함
}

ServiceManager::~ServiceManager() {
    saveServices(true);
}

void ServiceManager::loadServices() {
    std::vector<std::string> lines = CSVHandler::readCsv(SERVICES_FILE);
    services.clear();
    nextServiceId = 1; // 서비스 ID는 파일에서 로드된 최대값 + 1로 설정

    // 기존 서비스 로드 로직
    for (const std::string& line : lines) {
        Service service = Service::fromCsvString(line);
        if (!service.getServiceId().empty()) {
            services[service.getServiceId()] = service;
            // nextServiceId 업데이트 로직은 그대로 유지
            if (service.getServiceId().rfind("SVC", 0) == 0) {
                try {
                    int idNum = std::stoi(service.getServiceId().substr(3));
                    if (idNum >= nextServiceId) {
                        nextServiceId = idNum + 1;
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "경고: 서비스 ID 숫자 파싱 오류 (invalid_argument): " << e.what() << " - " << service.getServiceId() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "경고: 서비스 ID 숫자 파싱 오류 (out_of_range): " << e.what() << " - " << service.getServiceId() << std::endl;
                }
            }
        }
    }

    // 파일에서 로드된 서비스가 없는 경우, 원하는 초기 서비스 4개를 추가
    if (services.empty()) {
        std::cout << "서비스 파일이 비어있어 초기 서비스를 생성합니다." << std::endl;
        // '기본 케어', '젤 네일', '이달의 아트', '패디큐어' 추가
        services["SVC001"] = Service("SVC001", "기본 케어", 20000, 60);
        services["SVC002"] = Service("SVC002", "젤 네일", 35000, 90);
        services["SVC003"] = Service("SVC003", "이달의 아트", 50000, 120);
        services["SVC004"] = Service("SVC004", "패디큐어", 40000, 90); // 새로운 ID 할당
        nextServiceId = 5; // 다음 ID는 5부터 시작하도록 설정

        // 초기 서비스 추가 후 바로 저장 (silent=true로 메시지 없이 저장)
        saveServices(true);
    }
}

void ServiceManager::saveServices(bool silent) {
    // ... (기존 saveServices 구현 유지)
    std::vector<std::string> lines;
    for (const auto& pair : services) {
        lines.push_back(pair.second.toCsvString());
    }
    if (CSVHandler::writeCsv(SERVICES_FILE, lines)) {
        if (!silent) {
            std::cout << "서비스 데이터가 성공적으로 저장되었습니다." << std::endl;
        }
    }
    else {
        if (!silent) {
            std::cerr << "오류: 서비스 데이터 저장에 실패했습니다." << std::endl;
        }
    }
}

// 서비스 ID로 서비스 조회: 해당 ID의 서비스 객체 포인터 반환
const Service* ServiceManager::getService(const std::string& serviceId) const {
    auto it = services.find(serviceId);
    if (it != services.end()) {
        return &(it->second);
    }
    return nullptr; // 서비스 없음
}

// 서비스 이름으로 서비스 조회: 해당 이름의 서비스 객체 포인터 반환
const Service* ServiceManager::getServiceByName(const std::string& serviceName) const {
    for (const auto& pair : services) {
        if (pair.second.getName() == serviceName) {
            return &(pair.second);
        }
    }
    return nullptr; // 서비스 없음
}

// 모든 서비스 목록 반환
const std::map<std::string, Service>& ServiceManager::getAllServices() const {
    return services;
}

// 모든 서비스 정보 출력: 콘솔에 형식화된 서비스 목록 표시
void ServiceManager::printAllServices() const {
    if (services.empty()) {
        std::cout << "등록된 서비스 없음." << std::endl;
        return;
    }
    std::cout << "\n--- 모든 서비스 목록 ---\n" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(10) << "ID"
        << std::setw(25) << "이름"
        << std::setw(10) << "가격"
        << std::setw(15) << "소요 시간 (분)" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;

    for (const auto& pair : services) {
        const Service& service = pair.second;
        std::cout << std::left << std::setw(10) << service.getServiceId()
            << std::setw(25) << service.getName()
            << std::setw(10) << static_cast<int>(service.getPrice()) // 가격은 정수로 출력
            << std::setw(15) << service.getDurationMinutes() << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
}