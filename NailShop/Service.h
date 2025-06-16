// Service.h
#pragma once

#include <string> // std::string
#include <vector> // std::vector

// 네일샵 서비스 정보
class Service {
public:
    // 기본 생성자
    Service();
    // 매개변수 생성자
    Service(const std::string& serviceId, const std::string& name, double price, int durationMinutes);

    // 서비스 ID 반환
    std::string getServiceId() const;
    // 서비스 이름 반환
    std::string getName() const;
    // 서비스 가격 반환
    double getPrice() const;
    // 서비스 소요 시간 반환
    int getDurationMinutes() const;

    // CSV 문자열 변환
    std::string toCsvString() const;
    // CSV 문자열로부터 Service 객체 생성
    static Service fromCsvString(const std::string& csvLine);

private:
    std::string serviceId;      // 서비스 고유 ID
    std::string name;           // 서비스 이름
    double price;               // 서비스 가격
    int durationMinutes;        // 서비스 소요 시간 (분)
};