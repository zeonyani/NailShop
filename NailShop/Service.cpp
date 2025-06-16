// Service.cpp
#include "Service.h"    // Service 클래스
#include "CSVHandler.h" // CSVHandler
#include <vector>       // std::vector
#include <sstream>      // std::stringstream
#include <iomanip>      // std::fixed, std::setprecision
#include <iostream>     // cerr, cout

using namespace std;    // std:: 네임스페이스 사용

// 기본 생성자
Service::Service() : serviceId(""), name(""), price(0.0), durationMinutes(0) {}

// 매개변수 생성자
Service::Service(const string& serviceId, const string& name, double price, int durationMinutes)
    : serviceId(serviceId), name(name), price(price), durationMinutes(durationMinutes) {
}

// 서비스 ID 반환
string Service::getServiceId() const {
    return serviceId;
}

// 서비스 이름 반환
string Service::getName() const {
    return name;
}

// 서비스 가격 반환
double Service::getPrice() const {
    return price;
}

// 서비스 소요 시간 (분) 반환
int Service::getDurationMinutes() const {
    return durationMinutes;
}

// 서비스 정보 CSV 문자열 변환
string Service::toCsvString() const {
    vector<string> fields;
    fields.push_back(serviceId);
    fields.push_back(name);
    // 가격 문자열 변환
    stringstream ss_price;
    ss_price << fixed << setprecision(2) << price; // 소수점 둘째 자리까지 고정
    fields.push_back(ss_price.str());
    fields.push_back(to_string(durationMinutes));
    return CSVHandler::formatCsvLine(fields);
}

// CSV 문자열로부터 Service 객체 생성
Service Service::fromCsvString(const string& csvLine) {
    vector<string> fields = CSVHandler::parseCsvLine(csvLine);
    if (fields.size() == 4) { // 서비스 정보 필드 수 (4개)
        try {
            string serviceId = fields[0];
            string name = fields[1];
            double price = stod(fields[2]); // 문자열 double 변환
            int durationMinutes = stoi(fields[3]); // 문자열 int 변환
            return Service(serviceId, name, price, durationMinutes);
        }
        catch (const invalid_argument& e) {
            cerr << "CSV 파싱 오류 (Service - 숫자 변환): " << e.what() << " on line: " << csvLine << endl;
        }
        catch (const out_of_range& e) {
            cerr << "CSV 파싱 오류 (Service - 범위 초과): " << e.what() << " on line: " << csvLine << endl;
        }
    }
    return Service(); // 잘못된 형식 시 기본 Service 객체 반환
}