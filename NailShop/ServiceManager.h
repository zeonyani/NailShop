// ServiceManager.h
#pragma once

#include <string>   // std::string
#include <map>      // std::map
#include <vector>   // std::vector
#include "Service.h"    // Service 클래스
#include "CSVHandler.h" // CSVHandler

// 서비스 목록 관리
class ServiceManager {
public:
    // 생성자
    ServiceManager();
    // 소멸자
    ~ServiceManager();

    // 새 서비스 추가
    bool addService(const std::string& name, double price, int durationMinutes);
    // 기존 서비스 수정
    bool updateService(const std::string& serviceId, const std::string& newName, double newPrice, int newDurationMinutes);
    // 서비스 삭제
    bool deleteService(const std::string& serviceId);
    // 특정 서비스 정보 조회 (ID)
    const Service* getService(const std::string& serviceId) const;
    // 특정 서비스 정보 조회 (이름)
    const Service* getServiceByName(const std::string& serviceName) const;
    // 모든 서비스 목록 출력
    void printAllServices() const;

private:
    std::map<std::string, Service> services; // 서비스 ID-Service 맵
    const std::string SERVICES_FILE = "services.csv"; // 서비스 데이터 파일 경로
    int nextServiceId; // 다음 서비스 ID 카운터

    // 고유 서비스 ID 생성
    std::string generateUniqueId();
    // CSV 파일로부터 서비스 데이터 로드
    void loadServices();
    // CSV 파일에 서비스 데이터 저장
    void saveServices();
};