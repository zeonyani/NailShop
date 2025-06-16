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

    // ���� ID�� ���� ��ȸ
    const Service* getService(const std::string& serviceId) const;
    // ���� �̸����� ���� ��ȸ
    const Service* getServiceByName(const std::string& serviceName) const;
    // ��� ���� ��� ��ȯ
    const std::map<std::string, Service>& getAllServices() const;
    // ��� ���� ���� ���
    void printAllServices() const;
};

#endif // SERVICE_MANAGER_H