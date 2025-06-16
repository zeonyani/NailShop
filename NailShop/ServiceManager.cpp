// ServiceManager.cpp
#include "ServiceManager.h" // ServiceManager Ŭ����
#include <iostream>         // �ܼ� ���
#include <sstream>          // std::stringstream
#include <algorithm>        // std::max
#include <iomanip>          // ��� ������

using namespace std;        // std:: ���ӽ����̽� ���

// ServiceManager ������
ServiceManager::ServiceManager() : nextServiceId(1) {
    cout << "ServiceManager �ʱ�ȭ. ���� ������ �ε� ��..." << endl;
    loadServices(); // ���� ������ �ε�
}

// ServiceManager �Ҹ���
ServiceManager::~ServiceManager() {
    cout << "ServiceManager ����. ���� ������ ���� ��..." << endl;
    saveServices(); // ���� ������ ����
}

// CSV ���Ϸκ��� ���� ������ �ε�
void ServiceManager::loadServices() {
    vector<string> serviceLines = CSVHandler::readCsv(SERVICES_FILE);
    if (serviceLines.empty()) {
        cout << "���� ������ ���� ����/�������. �� ���� ���� ����." << endl;
        nextServiceId = 1; // ������ ���ų� ��������� ID 1���� ����
        return;
    }

    int maxId = 0;
    for (const string& line : serviceLines) {
        Service service = Service::fromCsvString(line);
        if (service.getServiceId() != "") { // ��ȿ�� ���� ���� �߰�
            services.emplace(service.getServiceId(), service);
            // ���� �κи� �����Ͽ� �ִ� ID ����
            try {
                int idNum = stoi(service.getServiceId().substr(3));
                maxId = max(maxId, idNum);
            }
            catch (const invalid_argument& e) {
                cerr << "����: ���� ID �Ľ� ���� - " << service.getServiceId() << " (" << e.what() << ")" << endl;
            }
            catch (const out_of_range& e) {
                cerr << "����: ���� ID ���� �ʰ� - " << service.getServiceId() << " (" << e.what() << ")" << endl;
            }
        }
    }
    nextServiceId = maxId + 1; // ���� ID ����
    cout << "�� " << services.size() << "�� ���� ������ �ε� �Ϸ�. ���� ���� ID: " << nextServiceId << endl;
}

// CSV ���Ͽ� ���� ������ ����
void ServiceManager::saveServices() {
    vector<string> dataToSave;
    for (const auto& pair : services) {
        dataToSave.push_back(pair.second.toCsvString());
    }
    CSVHandler::writeCsv(SERVICES_FILE, dataToSave);
    cout << "�� " << services.size() << "�� ���� ������ ���� �Ϸ�." << endl;
}

// ���� ���� ID ����
string ServiceManager::generateUniqueId() {
    stringstream ss;
    ss << "SVC" << nextServiceId++;
    return ss.str();
}

// �� ���� �߰�
bool ServiceManager::addService(const string& name, double price, int durationMinutes) {
    string id = generateUniqueId();
    if (services.find(id) == services.end()) {
        services.emplace(id, Service(id, name, price, durationMinutes));
        saveServices(); // ����
        cout << "���� '" << name << "' (ID: " << id << ") �߰� �Ϸ�." << endl;
        return true;
    }
    return false; // ID �浹 (���� �߻����� ����)
}

// ���� ���� ����
bool ServiceManager::updateService(const string& serviceId, const string& newName, double newPrice, int newDurationMinutes) {
    auto it = services.find(serviceId);
    if (it != services.end()) {
        it->second = Service(serviceId, newName, newPrice, newDurationMinutes); // ��ü ������Ʈ
        saveServices(); // ����
        cout << "���� ID '" << serviceId << "' ������Ʈ �Ϸ�." << endl;
        return true;
    }
    cout << "����: ���� ID '" << serviceId << "' ã�� �� ����. ������Ʈ ����." << endl;
    return false;
}

// ���� ����
bool ServiceManager::deleteService(const string& serviceId) {
    if (services.erase(serviceId)) {
        saveServices(); // ����
        cout << "���� ID '" << serviceId << "' ���� �Ϸ�." << endl;
        return true;
    }
    cout << "����: ���� ID '" << serviceId << "' ã�� �� ����. ���� ����." << endl;
    return false;
}

// Ư�� ���� ���� ��ȸ (ID)
const Service* ServiceManager::getService(const std::string& serviceId) const {
    auto it = services.find(serviceId);
    if (it != services.end()) {
        return &(it->second);
    }
    return nullptr;
}

// Ư�� ���� ���� ��ȸ (�̸�)
const Service* ServiceManager::getServiceByName(const std::string& serviceName) const {
    for (const auto& pair : services) {
        if (pair.second.getName() == serviceName) {
            return &(pair.second);
        }
    }
    return nullptr;
}

// ��� ���� ��� ���
void ServiceManager::printAllServices() const {
    if (services.empty()) {
        cout << "��ϵ� ���� ����." << endl;
        return;
    }
    cout << "\n--- ��ü ���� ��� ---" << endl;
    cout << left << setw(9) << "ID"
        << setw(13) << "�̸�"
        << right << setw(10) << "����"
        << setw(13) << "�ҿ�ð�(��)" << endl;
    cout << "------------------------------------------" << endl;
    for (const auto& pair : services) {
        const Service& svc = pair.second;
        cout << left << setw(9) << svc.getServiceId()
            << setw(13) << svc.getName()
            << right << setw(8) << fixed << setprecision(0) << svc.getPrice() << "��"
            << setw(9) << svc.getDurationMinutes() << "��" << endl;
    }
    cout << "------------------------------------------" << endl;
}