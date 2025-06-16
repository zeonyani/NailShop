//Service.h
#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>
#include <sstream> // for toCsvString and fromCsvString

class Service {
private:
    std::string serviceId;      // ���� ID (��: SVC001)
    std::string name;           // ���� �̸� (��: �⺻ ���� ����)
    double price;               // ���� ����
    int durationMinutes;        // �ҿ� �ð� (��)

public:
    // �⺻ ������
    Service();
    // �Ű����� ������
    Service(const std::string& serviceId, const std::string& name, double price, int durationMinutes);

    // Getter �޼���
    std::string getServiceId() const;
    std::string getName() const;
    double getPrice() const;
    int getDurationMinutes() const;

    // ���� �޼���
    void update(const std::string& newName, double newPrice, int newDurationMinutes);

    // CSV ���ڿ��� ��ȯ
    std::string toCsvString() const;
    // CSV ���ڿ��κ��� Service ��ü ����
    static Service fromCsvString(const std::string& csvLine);
};

#endif // SERVICE_H