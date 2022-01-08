#include "User.h"
#include <iostream>

User::User(std::string userName, std::string password) : userName(userName), password(password) {}

std::string User::getUserName() const {
	return this->userName;
}

std::string User::getPassword() const {
	return this->password;
}

void User::setType(std::string type) {
	this->type = type;
}

std::string User::getType() const {
	return this->type;
}

