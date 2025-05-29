#include "CSVHandler.h"
#include <iostream> // cerr ����� ����
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void CSVHandler::writeCSV(const string& filename, const vector<vector<string>>& data)
{
	ofstream userFile(filename); // CSV ���� ����, filename���� �ϴ� ������ ��, ����, ���� ��Ȳ�� ���� csv������ �����Ϸ���
	if (!userFile.is_open()) { // ���� ���� ���� ���� Ȯ��
		cerr << "���� ���� ����" << filename << endl; // ���� ���� ���� ���� �޽���
		return; // ���� ���� ���� �� �Լ� ����
	}

	// csv������ ������
	userFile << "Name, ID, Password" << endl;

	// CSV ���Ͽ� ������ ����
	// ���� ����: c+11���� ����, STL �����̳� ��ȸ�� ��� (�� ���� �� �о�´ٴ� �ǹ�)
	for (const auto& row : data) { // 2���� ������ �� �࿡ ����
		for (size_t i = 0; i < row.size(); ++i) { // �� ���� ���� ����
			userFile << row[i]; // �� �����͸� ���Ͽ� ��
			if (i < row.size() - 1) {
				userFile << ","; // ������ ���� �ƴϸ� ��ǥ �߰�
			}
		}
		userFile << endl; // �� ���� �ٹٲ� �߰�
	}
	userFile.close(); // ���� �ݱ�
}

vector<vector<string>>CSVHandler::readCSV(const string& filename)
{
	ifstream file(filename); // CSV ���� ����
	vector<vector<string>> data; // �����͸� ������ 2���� ����

	if (!file.is_open()) { // ���� ���� ���� ���� Ȯ��
		cerr << "���� ���� ����: " << filename << endl; // ���� ���� ���� ���� �޽���
		return data; // �� ������ ��ȯ
	}

	string line; //	�� �پ� �б� ���� ���ڿ� ����

	while (getline(file, line)) { // ���Ͽ��� �� �پ� �б�
		vector<string> row; // ���� ���� ������ ����
		size_t pos = 0; // ���� ��ġ
		while ((pos = line.find(',')) != string::npos) { // ��ǥ�� ã�� ������ �ݺ�
			row.push_back(line.substr(0, pos)); // ��ǥ ������ ���ڿ��� �࿡ �߰�
			line.erase(0, pos + 1); // ��ǥ ������ ���ڿ��� ����
		}
		row.push_back(line); // ������ �� �߰� (��ǥ�� ���� ���)
		data.push_back(row); // ���� �����Ϳ� �߰�
	}

	file.close(); // ���� �ݱ�
	return data; // ���� ������ ��ȯ
}