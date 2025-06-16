// ServiceManager.h
#pragma once

#include <string>   // std::string
#include <map>      // std::map
#include <vector>   // std::vector
#include "Service.h"    // Service Ŭ����
#include "CSVHandler.h" // CSVHandler

// ���� ��� ����
class ServiceManager {
public:
    // ������
    ServiceManager();
    // �Ҹ���
    ~ServiceManager();

    // �� ���� �߰�
    bool addService(const std::string& name, double price, int durationMinutes);
    // ���� ���� ����
    bool updateService(const std::string& serviceId, const std::string& newName, double newPrice, int newDurationMinutes);
    // ���� ����
    bool deleteService(const std::string& serviceId);
    // Ư�� ���� ���� ��ȸ (ID)
    const Service* getService(const std::string& serviceId) const;
    // Ư�� ���� ���� ��ȸ (�̸�)
    const Service* getServiceByName(const std::string& serviceName) const;
    // ��� ���� ��� ���
    void printAllServices() const;

private:
    std::map<std::string, Service> services; // ���� ID-Service ��
    const std::string SERVICES_FILE = "services.csv"; // ���� ������ ���� ���
    int nextServiceId; // ���� ���� ID ī����

    // ���� ���� ID ����
    std::string generateUniqueId();
    // CSV ���Ϸκ��� ���� ������ �ε�
    void loadServices();
    // CSV ���Ͽ� ���� ������ ����
    void saveServices();
};