//Service.cpp
#include "Service.h"
#include "CSVHandler.h" // CSVHandler::parseCsvLine, CSVHandler::formatCsvLine ���
#include <iomanip> // std::fixed, std::setprecision
#include <iostream> // for std::cerr

// Service �⺻ ������
Service::Service() : serviceId(""), name(""), price(0.0), durationMinutes(0) {
}

// Service �Ű����� ������
Service::Service(const std::string& serviceId, const std::string& name, double price, int durationMinutes)
    : serviceId(serviceId), name(name), price(price), durationMinutes(durationMinutes) {
}

// Getter �޼��� ����
std::string Service::getServiceId() const {
    return serviceId;
}

std::string Service::getName() const {
    return name;
}

double Service::getPrice() const {
    return price;
}

int Service::getDurationMinutes() const {
    return durationMinutes;
}

// ���� �޼��� ����
void Service::update(const std::string& newName, double newPrice, int newDurationMinutes) {
    name = newName;
    price = newPrice;
    durationMinutes = newDurationMinutes;
}

// CSV ���ڿ��� ��ȯ
std::string Service::toCsvString() const {
    std::vector<std::string> fields;
    fields.push_back(serviceId);
    fields.push_back(name);
    // ������ ������ ��ȯ�Ͽ� ����
    fields.push_back(std::to_string(static_cast<long long>(price)));
    fields.push_back(std::to_string(durationMinutes));
    return CSVHandler::formatCsvLine(fields);
}

// CSV ���ڿ��κ��� Service ��ü ����
Service Service::fromCsvString(const std::string& csvLine) {
    std::vector<std::string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 4) {
        // ���ڿ��� ���ڷ� ��ȯ�� �� ���� ó�� �߰�
        try {
            std::string serviceId = fields[0];
            std::string name = fields[1];
            double price = std::stod(fields[2]); // double�� �ٽ� ��ȯ
            int durationMinutes = std::stoi(fields[3]);
            return Service(serviceId, name, price, durationMinutes);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Service::fromCsvString - ���� �Ľ� ���� (Invalid Argument): " << e.what() << " in line: " << csvLine << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Service::fromCsvString - ���� �Ľ� ���� (Out of Range): " << e.what() << " in line: " << csvLine << std::endl;
        }
    }
    std::cerr << "Service::fromCsvString - CSV ���� ���� ����: " << csvLine << std::endl;
    return Service(); // ���� �߻� �� �⺻ Service ��ü ��ȯ
}