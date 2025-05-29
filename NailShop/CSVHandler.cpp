#include "CSVHandler.h"
#include <iostream> // cerr 사용을 위함
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void CSVHandler::writeCSV(const string& filename, const vector<vector<string>>& data)
{
	ofstream userFile(filename); // CSV 파일 열기, filename으로 하는 이유는 고객, 직원, 예약 상황에 따른 csv파일을 구분하려고
	if (!userFile.is_open()) { // 파일 열기 실패 여부 확인
		cerr << "파일 열기 실패" << filename << endl; // 파일 열기 실패 에러 메시지
		return; // 파일 열기 실패 시 함수 종료
	}

	// csv파일의 제목줄
	userFile << "Name, ID, Password" << endl;

	// CSV 파일에 데이터 쓰기
	// 문법 설명: c+11부터 지원, STL 컨테이너 순회시 깔끔 (그 줄을 다 읽어온다는 의미)
	for (const auto& row : data) { // 2차원 벡터의 각 행에 대해
		for (size_t i = 0; i < row.size(); ++i) { // 각 행의 열에 대해
			userFile << row[i]; // 열 데이터를 파일에 씀
			if (i < row.size() - 1) {
				userFile << ","; // 마지막 열이 아니면 쉼표 추가
			}
		}
		userFile << endl; // 행 끝에 줄바꿈 추가
	}
	userFile.close(); // 파일 닫기
}

vector<vector<string>>CSVHandler::readCSV(const string& filename)
{
	ifstream file(filename); // CSV 파일 열기
	vector<vector<string>> data; // 데이터를 저장할 2차원 벡터

	if (!file.is_open()) { // 파일 열기 실패 여부 확인
		cerr << "파일 열기 실패: " << filename << endl; // 파일 열기 실패 에러 메시지
		return data; // 빈 데이터 반환
	}

	string line; //	한 줄씩 읽기 위한 문자열 변수

	while (getline(file, line)) { // 파일에서 한 줄씩 읽기
		vector<string> row; // 현재 행을 저장할 벡터
		size_t pos = 0; // 현재 위치
		while ((pos = line.find(',')) != string::npos) { // 쉼표를 찾을 때까지 반복
			row.push_back(line.substr(0, pos)); // 쉼표 이전의 문자열을 행에 추가
			line.erase(0, pos + 1); // 쉼표 이후의 문자열로 줄임
		}
		row.push_back(line); // 마지막 열 추가 (쉼표가 없는 경우)
		data.push_back(row); // 행을 데이터에 추가
	}

	file.close(); // 파일 닫기
	return data; // 읽은 데이터 반환
}