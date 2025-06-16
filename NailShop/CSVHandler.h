// CSVHandler.h
#pragma once

#include <string>   // std::string
#include <vector>   // std::vector
#include <map>      // std::map (현재 사용되지 않음)

// CSV 파일 읽기/쓰기 유틸리티
class CSVHandler {
public:
    // CSV 파일 읽기 (각 줄 문자열 벡터 반환)
    static std::vector<std::string> readCsv(const std::string& filePath);

    // CSV 파일 쓰기 (기존 내용 덮어쓰기)
    static bool writeCsv(const std::string& filePath, const std::vector<std::string>& data);

    // CSV 파일에 데이터 추가 (기존 내용 유지)
    static bool appendToCsv(const std::string& filePath, const std::string& dataLine);

    // CSV 한 줄 파싱 (문자열 벡터 반환)
    static std::vector<std::string> parseCsvLine(const std::string& line, char delimiter = ',');

    // 문자열 벡터를 CSV 한 줄로 변환
    static std::string formatCsvLine(const std::vector<std::string>& fields, char delimiter = ',');
};