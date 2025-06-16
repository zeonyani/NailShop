//ServiceManager.cpp
#include "ServiceManager.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip> // std::setw, std::left ���

const std::string ServiceManager::SERVICES_FILE = "services.csv";

ServiceManager::ServiceManager() : nextServiceId(1) {
    loadServices(); // ���� �ε� �� �ʱ� ���� ���� ���� ����
}

ServiceManager::~ServiceManager() {
    saveServices(true);
}

void ServiceManager::loadServices() {
    std::vector<std::string> lines = CSVHandler::readCsv(SERVICES_FILE);
    services.clear();
    nextServiceId = 1; // ���� ID�� ���Ͽ��� �ε�� �ִ밪 + 1�� ����

    // ���� ���� �ε� ����
    for (const std::string& line : lines) {
        Service service = Service::fromCsvString(line);
        if (!service.getServiceId().empty()) {
            services[service.getServiceId()] = service;
            // nextServiceId ������Ʈ ������ �״�� ����
            if (service.getServiceId().rfind("SVC", 0) == 0) {
                try {
                    int idNum = std::stoi(service.getServiceId().substr(3));
                    if (idNum >= nextServiceId) {
                        nextServiceId = idNum + 1;
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "���: ���� ID ���� �Ľ� ���� (invalid_argument): " << e.what() << " - " << service.getServiceId() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "���: ���� ID ���� �Ľ� ���� (out_of_range): " << e.what() << " - " << service.getServiceId() << std::endl;
                }
            }
        }
    }

    // ���Ͽ��� �ε�� ���񽺰� ���� ���, ���ϴ� �ʱ� ���� 4���� �߰�
    if (services.empty()) {
        std::cout << "���� ������ ����־� �ʱ� ���񽺸� �����մϴ�." << std::endl;
        // '�⺻ �ɾ�', '�� ����', '�̴��� ��Ʈ', '�е�ť��' �߰�
        services["SVC001"] = Service("SVC001", "�⺻ �ɾ�", 20000, 60);
        services["SVC002"] = Service("SVC002", "�� ����", 35000, 90);
        services["SVC003"] = Service("SVC003", "�̴��� ��Ʈ", 50000, 120);
        services["SVC004"] = Service("SVC004", "�е�ť��", 40000, 90); // ���ο� ID �Ҵ�
        nextServiceId = 5; // ���� ID�� 5���� �����ϵ��� ����

        // �ʱ� ���� �߰� �� �ٷ� ���� (silent=true�� �޽��� ���� ����)
        saveServices(true);
    }
}

void ServiceManager::saveServices(bool silent) {
    // ... (���� saveServices ���� ����)
    std::vector<std::string> lines;
    for (const auto& pair : services) {
        lines.push_back(pair.second.toCsvString());
    }
    if (CSVHandler::writeCsv(SERVICES_FILE, lines)) {
        if (!silent) {
            std::cout << "���� �����Ͱ� ���������� ����Ǿ����ϴ�." << std::endl;
        }
    }
    else {
        if (!silent) {
            std::cerr << "����: ���� ������ ���忡 �����߽��ϴ�." << std::endl;
        }
    }
}

// ���� ID�� ���� ��ȸ: �ش� ID�� ���� ��ü ������ ��ȯ
const Service* ServiceManager::getService(const std::string& serviceId) const {
    auto it = services.find(serviceId);
    if (it != services.end()) {
        return &(it->second);
    }
    return nullptr; // ���� ����
}

// ���� �̸����� ���� ��ȸ: �ش� �̸��� ���� ��ü ������ ��ȯ
const Service* ServiceManager::getServiceByName(const std::string& serviceName) const {
    for (const auto& pair : services) {
        if (pair.second.getName() == serviceName) {
            return &(pair.second);
        }
    }
    return nullptr; // ���� ����
}

// ��� ���� ��� ��ȯ
const std::map<std::string, Service>& ServiceManager::getAllServices() const {
    return services;
}

// ��� ���� ���� ���: �ֿܼ� ����ȭ�� ���� ��� ǥ��
void ServiceManager::printAllServices() const {
    if (services.empty()) {
        std::cout << "��ϵ� ���� ����." << std::endl;
        return;
    }
    std::cout << "\n--- ��� ���� ��� ---\n" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(10) << "ID"
        << std::setw(25) << "�̸�"
        << std::setw(10) << "����"
        << std::setw(15) << "�ҿ� �ð� (��)" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;

    for (const auto& pair : services) {
        const Service& service = pair.second;
        std::cout << std::left << std::setw(10) << service.getServiceId()
            << std::setw(25) << service.getName()
            << std::setw(10) << static_cast<int>(service.getPrice()) // ������ ������ ���
            << std::setw(15) << service.getDurationMinutes() << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
}