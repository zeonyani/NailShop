#include "SystemManager.h" // SystemManager 클래스 사용을 위해 포함하기
#include <iostream> // cout, endl 사용을 위해 포함하기

using namespace std;

int main() {
    // SystemManager 객체 생성하기
    SystemManager systemManager;

    // systemManager 객체의 run() 함수를 호출하여 시스템 시작하기
    // 이 run() 함수 내부에서 로그인 과정이 진행되고, 로그인 성공 시
    // 권한에 따른 메뉴가 표시되며 프로그램이 실행되기
    systemManager.run();

    // 프로그램이 성공적으로 종료되었음을 운영체제에 알리기
    return 0;
}