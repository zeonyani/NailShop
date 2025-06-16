//Service.h
#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>
#include <sstream> // for toCsvString and fromCsvString

class Service {
private:
    std::string serviceId;      // 서비스 ID (예: SVC001)
    std::string name;           // 서비스 이름 (예: 기본 네일 관리)
    double price;               // 서비스 가격
    int durationMinutes;        // 소요 시간 (분)

public:
    // 기본 생성자
    Service();
    // 매개변수 생성자
    Service(const std::string& serviceId, const std::string& name, double price, int durationMinutes);

    // Getter 메서드
    std::string getServiceId() const;
    std::string getName() const;
    double getPrice() const;
    int getDurationMinutes() const;

    // 수정 메서드
    void update(const std::string& newName, double newPrice, int newDurationMinutes);

    // CSV 문자열로 변환
    std::string toCsvString() const;
    // CSV 문자열로부터 Service 객체 생성
    static Service fromCsvString(const std::string& csvLine);
};

#endif // SERVICE_H