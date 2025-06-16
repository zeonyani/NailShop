// Service.cpp
#include "Service.h"    // Service Ŭ����
#include "CSVHandler.h" // CSVHandler
#include <vector>       // std::vector
#include <sstream>      // std::stringstream
#include <iomanip>      // std::fixed, std::setprecision
#include <iostream>     // cerr, cout

using namespace std;    // std:: ���ӽ����̽� ���

// �⺻ ������
Service::Service() : serviceId(""), name(""), price(0.0), durationMinutes(0) {}

// �Ű����� ������
Service::Service(const string& serviceId, const string& name, double price, int durationMinutes)
    : serviceId(serviceId), name(name), price(price), durationMinutes(durationMinutes) {
}

// ���� ID ��ȯ
string Service::getServiceId() const {
    return serviceId;
}

// ���� �̸� ��ȯ
string Service::getName() const {
    return name;
}

// ���� ���� ��ȯ
double Service::getPrice() const {
    return price;
}

// ���� �ҿ� �ð� (��) ��ȯ
int Service::getDurationMinutes() const {
    return durationMinutes;
}

// ���� ���� CSV ���ڿ� ��ȯ
string Service::toCsvString() const {
    vector<string> fields;
    fields.push_back(serviceId);
    fields.push_back(name);
    // ���� ���ڿ� ��ȯ
    stringstream ss_price;
    ss_price << fixed << setprecision(2) << price; // �Ҽ��� ��° �ڸ����� ����
    fields.push_back(ss_price.str());
    fields.push_back(to_string(durationMinutes));
    return CSVHandler::formatCsvLine(fields);
}

// CSV ���ڿ��κ��� Service ��ü ����
Service Service::fromCsvString(const string& csvLine) {
    vector<string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 4) { // ���� ���� �ʵ� �� (4��)
        try {
            string serviceId = fields[0];
            string name = fields[1];
            double price = stod(fields[2]); // ���ڿ� double ��ȯ
            int durationMinutes = stoi(fields[3]); // ���ڿ� int ��ȯ
            return Service(serviceId, name, price, durationMinutes);
        }
        catch (const invalid_argument& e) {
            cerr << "CSV �Ľ� ���� (Service - ���� ��ȯ): " << e.what() << " on line: " << csvLine << endl;
        }
        catch (const out_of_range& e) {
            cerr << "CSV �Ľ� ���� (Service - ���� �ʰ�): " << e.what() << " on line: " << csvLine << endl;
        }
    }
    return Service(); // �߸��� ���� �� �⺻ Service ��ü ��ȯ
}