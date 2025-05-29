#pragma once

#include <string>
#include <vector>
using namespace std;

class CSVHandler {
public:
    // CSV 파일을 저장
    static void writeCSV(const string& filename, const vector<vector<string>>& data);
    // static 키워드는 객체를 만들지 않고도 바로 사용할 수 있도록 함 (new 없이)

    // CSV 파일을 읽어서 반환
    static vector<vector<string>> readCSV(const string& filename);
    // 콜바이 밸류가 아닌 콜바이 레퍼런스를 이용해 성능과 속도 잡음. const를 써서 문자열 절대 안바꾸겠다는 의미
};