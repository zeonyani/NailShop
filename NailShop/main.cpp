#include "SystemManager.h" // SystemManager Ŭ���� ����� ���� �����ϱ�
#include <iostream> // cout, endl ����� ���� �����ϱ�

using namespace std;

int main() {
    // SystemManager ��ü �����ϱ�
    SystemManager systemManager;

    // systemManager ��ü�� run() �Լ��� ȣ���Ͽ� �ý��� �����ϱ�
    // �� run() �Լ� ���ο��� �α��� ������ ����ǰ�, �α��� ���� ��
    // ���ѿ� ���� �޴��� ǥ�õǸ� ���α׷��� ����Ǳ�
    systemManager.run();

    // ���α׷��� ���������� ����Ǿ����� �ü���� �˸���
    return 0;
}