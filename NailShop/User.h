#pragma once
#include <string>

using namespace std;
class User {
public:
	User() = default;  // �⺻ ������
	User(const std::string& id, const std::string& pw, const std::string& name, const std::string& phone)
		: id(id), pw(pw), name(name), phone(phone) {
	}  // �Ű����� ������
    // ���̵�, �̸�, ����ȣ�� �������� �Լ���
    string getId() const;
    string getName() const;
    string getPhone() const;

	// ��й�ȣ �ܺο��� ������ �� ���� ���� Ÿ��(���Ȼ�) -> �񱳸� ��ĥ �� �ֵ���!
    bool checkPw(const std::string& password) const;
    
    // ��ȭ��ȣ ���� �Լ��� ������ �ٲ� �� �ֵ��� �ؾ���(��ȭ��ȣ�� ���� �ٲ��)
    void setPhone(const std::string& phoneNumber);

    virtual ~User() = default;  // ���� �Ҹ���

private:
    std::string id;
    std::string pw;
    std::string name;
    std::string phone;
};
