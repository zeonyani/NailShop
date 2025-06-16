// CSVHandler.cpp
#include "CSVHandler.h" // CSVHandler 클래스
#include <fstream>      // 파일 입출력
#include <sstream>      // 문자열 스트림
#include <iostream>     // 콘솔 출력

using namespace std;    // std:: 네임스페이스 사용

// CSV 파일 읽기
vector<string> CSVHandler::readCsv(const string& filePath) {
    vector<string> lines;       // 읽은 줄 저장
    ifstream file(filePath);    // 파일 스트림

    if (file.is_open()) {       // 파일 열림 확인
        string line;
        while (getline(file, line)) { // 한 줄씩 읽기
            if (!line.empty()) { // 빈 줄 건너뛰기
                lines.push_back(line);    // 벡터에 추가
            }
        }
        file.close();               // 파일 스트림 닫기
    }
    else {
        // 파일 없거나 열 수 없을 시 안내 메시지
        cerr << "정보: 파일 찾을 수 없거나 열 수 없음: " << filePath << ". 새 파일 생성 가능." << endl;
    }
    return lines;                   // 읽은 줄 반환
}

// CSV 파일 쓰기 (덮어쓰기)
bool CSVHandler::writeCsv(const string& filePath, const vector<string>& data) {
    ofstream file(filePath);    // 파일 스트림 열기 (덮어쓰기 모드)

    if (file.is_open()) {       // 파일 열림 확인
        for (const string& line : data) { // 각 줄 파일에 쓰기
            file << line << endl;
        }
        file.close();               // 파일 스트림 닫기
        return true;                // 쓰기 성공
    }
    else {
        cerr << "오류: 파일 생성 또는 쓰기 실패: " << filePath << endl; // 오류 메시지
        return false;               // 쓰기 실패
    }
}

// CSV 파일에 데이터 추가
bool CSVHandler::appendToCsv(const string& filePath, const string& dataLine) {
    ofstream file(filePath, ios::app); // 파일 스트림 (추가 모드)

    if (file.is_open()) {               // 파일 열림 확인
        file << dataLine << endl;       // 데이터 추가
        file.close();                   // 파일 스트림 닫기
        return true;                    // 추가 성공
    }
    else {
        cerr << "오류: 파일 열기 실패: " << filePath << endl; // 오류 메시지
        return false;                   // 추가 실패
    }
}

// CSV 한 줄 파싱
vector<string> CSVHandler::parseCsvLine(const string& line, char delimiter) {
    vector<string> fields;          // 파싱된 필드 저장
    stringstream ss(line);          // 문자열 스트림
    string field;

    while (getline(ss, field, delimiter)) { // 구분자 기준 파싱
        fields.push_back(field);    // 벡터에 추가
    }
    return fields;                  // 파싱된 필드 반환
}

// 문자열 벡터를 CSV 한 줄로 포맷팅
string CSVHandler::formatCsvLine(const vector<string>& fields, char delimiter) {
    stringstream ss;                // 문자열 스트림
    for (size_t i = 0; i < fields.size(); ++i) { // 각 필드 순회
        ss << fields[i];
        if (i < fields.size() - 1) { // 마지막 필드 아니면 구분자 추가
            ss << delimiter;
        }
    }
    return ss.str();                // 포맷팅된 문자열 반환
}