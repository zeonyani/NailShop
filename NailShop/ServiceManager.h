//ServiceManager.h
#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Service.h"
#include "CSVHandler.h"

class ServiceManager {
private:
    static const std::string SERVICES_FILE;
    std::map<std::string, Service> services;
    int nextServiceId;

    void loadServices();
    void saveServices(bool silent = false);

public:
    ServiceManager();
    ~ServiceManager();

    // 서비스 ID로 서비스 조회
    const Service* getService(const std::string& serviceId) const;
    // 서비스 이름으로 서비스 조회
    const Service* getServiceByName(const std::string& serviceName) const;
    // 모든 서비스 목록 반환
    const std::map<std::string, Service>& getAllServices() const;
    // 모든 서비스 정보 출력
    void printAllServices() const;
};

#endif // SERVICE_MANAGER_H