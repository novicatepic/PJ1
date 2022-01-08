#include "User.h"
#include <iostream>
#include <fstream>
#include <vector>

User::User(std::string userName, std::string password) : userName(userName), password(password) { }

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

void User::checkInbox() const {
	auto inboxFile = std::ifstream("./STUDENTI/" + this->userName + "/CHATS/" + "INBOX.txt", std::ios::in);

	if (inboxFile) {
		std::cout << "Your inbox: " << std::endl;

		while (inboxFile.good()) {
			std::string getLine;
			std::getline(inboxFile, getLine, '\n');
			std::cout << getLine << std::endl;
		}

	}

	inboxFile.close();

	auto removeInbox = std::ofstream("./STUDENTI/" + this->userName + "/CHATS/" + "INBOX.txt", std::ios::out);
	removeInbox.close();
}

bool User::checkIfUserIsAlreadyInAFile(std::string userName, std::string password) const {
	auto readUsers = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);

	if (readUsers) {
		while (readUsers.good()) {
			User u;
			readUsers >> u;
			if (u.getUserName() == userName && u.getPassword() == password) {
				readUsers.close();
				return true;
			}
		}
	}
	
	readUsers.close();
	return false;
}