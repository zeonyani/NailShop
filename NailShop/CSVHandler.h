// CSVHandler.h
#pragma once

#include <string>   // std::string
#include <vector>   // std::vector
#include <map>      // std::map (���� ������ ����)

// CSV ���� �б�/���� ��ƿ��Ƽ
class CSVHandler {
public:
    // CSV ���� �б� (�� �� ���ڿ� ���� ��ȯ)
    static std::vector<std::string> readCsv(const std::string& filePath);

    // CSV ���� ���� (���� ���� �����)
    static bool writeCsv(const std::string& filePath, const std::vector<std::string>& data);

    // CSV ���Ͽ� ������ �߰� (���� ���� ����)
    static bool appendToCsv(const std::string& filePath, const std::string& dataLine);

    // CSV �� �� �Ľ� (���ڿ� ���� ��ȯ)
    static std::vector<std::string> parseCsvLine(const std::string& line, char delimiter = ',');

    // ���ڿ� ���͸� CSV �� �ٷ� ��ȯ
    static std::string formatCsvLine(const std::vector<std::string>& fields, char delimiter = ',');
};