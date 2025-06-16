//Service.cpp
#include "Service.h"
#include "CSVHandler.h" // CSVHandler::parseCsvLine, CSVHandler::formatCsvLine 사용
#include <iomanip> // std::fixed, std::setprecision
#include <iostream> // for std::cerr

// Service 기본 생성자
Service::Service() : serviceId(""), name(""), price(0.0), durationMinutes(0) {
}

// Service 매개변수 생성자
Service::Service(const std::string& serviceId, const std::string& name, double price, int durationMinutes)
    : serviceId(serviceId), name(name), price(price), durationMinutes(durationMinutes) {
}

// Getter 메서드 구현
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

// 수정 메서드 구현
void Service::update(const std::string& newName, double newPrice, int newDurationMinutes) {
    name = newName;
    price = newPrice;
    durationMinutes = newDurationMinutes;
}

// CSV 문자열로 변환
std::string Service::toCsvString() const {
    std::vector<std::string> fields;
    fields.push_back(serviceId);
    fields.push_back(name);
    // 가격을 정수로 변환하여 저장
    fields.push_back(std::to_string(static_cast<long long>(price)));
    fields.push_back(std::to_string(durationMinutes));
    return CSVHandler::formatCsvLine(fields);
}

// CSV 문자열로부터 Service 객체 생성
Service Service::fromCsvString(const std::string& csvLine) {
    std::vector<std::string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 4) {
        // 문자열을 숫자로 변환할 때 예외 처리 추가
        try {
            std::string serviceId = fields[0];
            std::string name = fields[1];
            double price = std::stod(fields[2]); // double로 다시 변환
            int durationMinutes = std::stoi(fields[3]);
            return Service(serviceId, name, price, durationMinutes);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Service::fromCsvString - 숫자 파싱 오류 (Invalid Argument): " << e.what() << " in line: " << csvLine << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Service::fromCsvString - 숫자 파싱 오류 (Out of Range): " << e.what() << " in line: " << csvLine << std::endl;
        }
    }
    std::cerr << "Service::fromCsvString - CSV 라인 형식 오류: " << csvLine << std::endl;
    return Service(); // 오류 발생 시 기본 Service 객체 반환
}