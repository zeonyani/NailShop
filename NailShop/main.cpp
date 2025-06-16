// main.cpp

// SystemManager 클래스를 사용하기 위해 헤더 파일을 포함
// 이 헤더 파일에는 SystemManager 클래스의 선언이 포함됨
#include "SystemManager.h" 

int main() {
    // 1. SystemManager 객체를 생성
    // SystemManager는 네일샵 시스템의 전반적인 관리(메뉴 표시, 사용자 입력 처리,
    // 그리고 ReservationManager와 같은 하위 관리자 기능 호출 등)를 담당
    // 객체가 생성될 때 SystemManager의 생성자가 호출
    SystemManager systemManager;

    // 2. systemManager 객체의 run() 함수를 호출하여 시스템을 시작
    // run() 함수 내부에는 콘솔 메뉴를 반복적으로 보여주고 사용자의 입력을 처리하는
    // 메인 루프가 구현되어 있음. 사용자가 '0'을 입력하여 종료를 선택할 때까지 
    // 이 루프가 계속 실행
    systemManager.run();

    // 3. 프로그램이 성공적으로 실행되고 종료되었음을 운영체제에 알림
    // '0'은 일반적으로 성공적인 종료를 의미하는 반환 값
    return 0;
}