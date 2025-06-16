// Service.h
#pragma once

#include <string> // std::string
#include <vector> // std::vector

// ���ϼ� ���� ����
class Service {
public:
    // �⺻ ������
    Service();
    // �Ű����� ������
    Service(const std::string& serviceId, const std::string& name, double price, int durationMinutes);

    // ���� ID ��ȯ
    std::string getServiceId() const;
    // ���� �̸� ��ȯ
    std::string getName() const;
    // ���� ���� ��ȯ
    double getPrice() const;
    // ���� �ҿ� �ð� ��ȯ
    int getDurationMinutes() const;

    // CSV ���ڿ� ��ȯ
    std::string toCsvString() const;
    // CSV ���ڿ��κ��� Service ��ü ����
    static Service fromCsvString(const std::string& csvLine);

private:
    std::string serviceId;      // ���� ���� ID
    std::string name;           // ���� �̸�
    double price;               // ���� ����
    int durationMinutes;        // ���� �ҿ� �ð� (��)
};