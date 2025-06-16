#include "User.h"
#include <iostream>

using namespace std;

// ������: name �Ķ���Ͱ� �߰���!
User::User(const string& userId, const string& password, UserType type, const string& name)
    : userId(userId), password(password), type(type), name(name) {
}

string User::getUserId() const { return userId; }
string User::getPassword() const { return password; }
UserType User::getUserType() const { return type; }
bool User::checkPassword(const string& inputPassword) const { return password == inputPassword; }
string User::getName() const { return name; } // getName ������!