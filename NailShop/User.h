#pragma once // ��� ������ �� ���� ���Եǵ��� �ϱ�

#include <string> // std::string ����ϱ�

// --- ���⿡ UserType enum class ���� �߰��ϱ� ---
// UserType enum class�� ����� ������ ������ ������
// None: �α��ε��� �ʰų� �� �� ���� ����
// Customer: �� ����
// Employee: ���� ����
// Owner: ���� ����
enum class UserType {
    None,       // �ʱ� ���� �Ǵ� �α��ε��� ���� ����
    Customer,   // ��
    Employee,   // ����
    Owner       // ����
};
// --- UserType ���� �� ---


// User Ŭ������ ���� ����� ������ ����(ID, ��й�ȣ, ����)�� ������
class User {
public:
    // ������: User ��ü ���� �� ȣ��Ǳ�
    User(const std::string& userId, const std::string& password, UserType type);

    // ����� ID�� ��ȯ�ϴ� �Լ�
    std::string getUserId() const;
    // ��й�ȣ�� ��ȯ�ϴ� �Լ� (���Ȼ� �ܺ� ���� ����, �׽�Ʈ��)
    std::string getPassword() const;
    // ����� ������ ��ȯ�ϴ� �Լ�
    UserType getUserType() const;

    // �Էµ� ��й�ȣ�� ����� ��й�ȣ�� ��ġ�ϴ��� Ȯ���ϴ� �Լ�
    // ��ȯ��: ��ġ�ϸ� true, ����ġ�ϸ� false
    bool checkPassword(const std::string& inputPassword) const;

private:
    // ����� ID
    std::string userId;
    // ����� ��й�ȣ
    std::string password;
    // ����� ���� (UserType enum class ���)
    UserType type;
};