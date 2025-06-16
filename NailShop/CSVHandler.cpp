// CSVHandler.cpp
#include "CSVHandler.h" // CSVHandler Ŭ����
#include <fstream>      // ���� �����
#include <sstream>      // ���ڿ� ��Ʈ��
#include <iostream>     // �ܼ� ���

using namespace std;    // std:: ���ӽ����̽� ���

// CSV ���� �б�
vector<string> CSVHandler::readCsv(const string& filePath) {
    vector<string> lines;       // ���� �� ����
    ifstream file(filePath);    // ���� ��Ʈ��

    if (file.is_open()) {       // ���� ���� Ȯ��
        string line;
        while (getline(file, line)) { // �� �پ� �б�
            if (!line.empty()) { // �� �� �ǳʶٱ�
                lines.push_back(line);    // ���Ϳ� �߰�
            }
        }
        file.close();               // ���� ��Ʈ�� �ݱ�
    }
    else {
        // ���� ���ų� �� �� ���� �� �ȳ� �޽���
        cerr << "����: ���� ã�� �� ���ų� �� �� ����: " << filePath << ". �� ���� ���� ����." << endl;
    }
    return lines;                   // ���� �� ��ȯ
}

// CSV ���� ���� (�����)
bool CSVHandler::writeCsv(const string& filePath, const vector<string>& data) {
    ofstream file(filePath);    // ���� ��Ʈ�� ���� (����� ���)

    if (file.is_open()) {       // ���� ���� Ȯ��
        for (const string& line : data) { // �� �� ���Ͽ� ����
            file << line << endl;
        }
        file.close();               // ���� ��Ʈ�� �ݱ�
        return true;                // ���� ����
    }
    else {
        cerr << "����: ���� ���� �Ǵ� ���� ����: " << filePath << endl; // ���� �޽���
        return false;               // ���� ����
    }
}

// CSV ���Ͽ� ������ �߰�
bool CSVHandler::appendToCsv(const string& filePath, const string& dataLine) {
    ofstream file(filePath, ios::app); // ���� ��Ʈ�� (�߰� ���)

    if (file.is_open()) {               // ���� ���� Ȯ��
        file << dataLine << endl;       // ������ �߰�
        file.close();                   // ���� ��Ʈ�� �ݱ�
        return true;                    // �߰� ����
    }
    else {
        cerr << "����: ���� ���� ����: " << filePath << endl; // ���� �޽���
        return false;                   // �߰� ����
    }
}

// CSV �� �� �Ľ�
vector<string> CSVHandler::parseCsvLine(const string& line, char delimiter) {
    vector<string> fields;          // �Ľ̵� �ʵ� ����
    stringstream ss(line);          // ���ڿ� ��Ʈ��
    string field;

    while (getline(ss, field, delimiter)) { // ������ ���� �Ľ�
        fields.push_back(field);    // ���Ϳ� �߰�
    }
    return fields;                  // �Ľ̵� �ʵ� ��ȯ
}

// ���ڿ� ���͸� CSV �� �ٷ� ������
string CSVHandler::formatCsvLine(const vector<string>& fields, char delimiter) {
    stringstream ss;                // ���ڿ� ��Ʈ��
    for (size_t i = 0; i < fields.size(); ++i) { // �� �ʵ� ��ȸ
        ss << fields[i];
        if (i < fields.size() - 1) { // ������ �ʵ� �ƴϸ� ������ �߰�
            ss << delimiter;
        }
    }
    return ss.str();                // �����õ� ���ڿ� ��ȯ
}