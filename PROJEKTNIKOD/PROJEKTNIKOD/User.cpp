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

void User::textFriend(std::string friendName) const {
	auto openFriends = std::ifstream("./STUDENTI/" + this->userName + "/" + "FRIENDS.TXT", std::ios::in);
	std::vector<User> friends;
	while (openFriends.good()) {
		User st;
		openFriends >> st;
		if (st.getUserName() != "" && st.getPassword() != "") {
			friends.push_back(st);
		}
	}
	openFriends.close();

	size_t helpCounter = 0;

	try {
		for (auto elem : friends) {
			if (elem.getUserName() != friendName) {
				helpCounter++;
			}
		}
		if (helpCounter == friends.size()) {
			throw std::exception("This student is not your friend!");
		}



		auto chatFile = std::ofstream("./STUDENTI/" + this->userName + "/CHATS/" + friendName + ".txt", std::ios::out | std::ios::app);
		
		std::ofstream chatFriendFile;
		std::ofstream inboxFriendFile;

		/*if (checkIfIsLecturer(courseName, friendName)) {
			chatFriendFile = std::ofstream("./KURSEVI/" + courseName + "/PREDAVACCHAT/" + this->userName + ".txt", std::ios::out | std::ios::app);
			inboxFriendFile = std::ofstream("./KURSEVI/" + courseName + "/PREDAVACCHAT/" + "INBOX.txt", std::ios::out | std::ios::app);
		}*/
			chatFriendFile = std::ofstream("./STUDENTI/" + friendName + "/CHATS/" + this->getUserName() + ".txt", std::ios::out | std::ios::app);
			inboxFriendFile = std::ofstream("./STUDENTI/" + friendName + "/CHATS/" + "INBOX.txt", std::ios::out | std::ios::app);

		if (chatFile) {
			std::cout << "Enter your message: " << std::endl;
			std::string message;
			//std::cin.ignore();
			std::getline(std::cin, message, '\n');
			chatFile << this->getUserName() << ": " << std::endl;
			chatFile << message << std::endl;
			chatFriendFile << this->getUserName() << ": " << std::endl;
			chatFriendFile << message << std::endl;
			inboxFriendFile << this->getUserName() << ": " << std::endl;
			inboxFriendFile << message << std::endl;
		}

		chatFile.close();
		chatFriendFile.close();
		inboxFriendFile.close();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}