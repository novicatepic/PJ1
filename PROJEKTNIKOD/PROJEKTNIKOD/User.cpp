#include "User.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

User::User(std::string userName, std::string password) : userName(userName), password(password) {
	auto makeUsersFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	//auto makeStudent

	if (!makeUsersFile) {
		namespace fs = std::filesystem;
		fs::path path = std::filesystem::current_path();
		fs::path userFolder = path / "KORISNICI";
		create_directory(userFolder);

		std::ofstream("./KORISNICI/Korisnici.txt", std::ios::out);

		fs::path studentSubfolder = path / "STUDENTI";
		create_directory(studentSubfolder);
	}
}

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

void User::filterInbox() const {
	std::string filter;
	std::cout << "Enter filter string: " << std::endl;
	std::getline(std::cin, filter);
	auto openChat = std::ifstream("./STUDENTI/" + this->userName + "/CHATS/INBOX.txt");
	if (openChat) {
		std::string readString;

		while (openChat.good()) {
			std::getline(openChat, readString, '\n');
			size_t found = readString.find(filter);
			if (found != std::string::npos) {
				std::cout << readString << std::endl;
			}
		}
		openChat.close();
	}
}

bool User::checkIfUserIsAlreadyInAFile(std::string userName) const {
	auto readUsers = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);

	if (readUsers) {
		while (readUsers.good()) {
			User u;
			u.setTypePassword(true);
			readUsers >> u;
			if (u.getUserName() == userName) {
				u.setTypePassword(false);
				readUsers.close();
				return true;
			}
			u.setTypePassword(false);
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
		if (st.getUserName() != "") {
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

bool User::checkIfIsLecturer(std::string courseName) const {
	auto courseFile = std::ifstream("./KURSEVI/" + courseName + "/PREDAVAC.txt");

	if (courseFile) {
		User p;
		courseFile >> p;
		if (p.getUserName() == this->userName) {
			return true;
		}
	}

	courseFile.close();

	return false;
}

bool User::checkIfIsEitherStudentOrLecturer(std::string courseName) const {
	auto courseFile = std::ifstream("./KURSEVI/" + courseName + "/STUDENTI.txt");

	if (courseFile) {
		while (courseFile.good()) {
			User u;
			courseFile >> u;
			if (u.getUserName() == this->userName)
				return true;
		}
	}

	courseFile.close();

	if (checkIfIsLecturer(courseName) == true)
		return true;

	return false;

}

bool User::checkUserName() const {
	auto credentialsFile = std::ifstream("./KORISNICI/" + this->userName + "/Korisnici.txt");
	if (credentialsFile) {
		while (credentialsFile.good()) {
			User u;
			credentialsFile >> u;
			if (u.getUserName() == this->userName) {
				return true;
			}
		}
		credentialsFile.close();
	}

	return false;
}

bool User::checkUserName(std::string name) const {
	auto credentialsFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	while (credentialsFile.good()) {
		User u;
		credentialsFile >> u;
		if (u.getUserName() == name) {
			return true;
		}
	}
	credentialsFile.close();

	return false;
}

std::vector<User> User::returnUsers() {
	std::vector<User> users;

	auto changeUserFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	this->typePassword = true;
	if (changeUserFile) {
		while (changeUserFile.good()) {
			User u;
			changeUserFile >> u;
			if (u.getUserName() != "") {
				users.push_back(u);
			}
		}
		changeUserFile.close();
	}
	this->typePassword = false;
	return users;
}

void User::setUserName(std::string name) {
	this->userName = name;
}

void User::setPassword(std::string password) {
	this->password = password;
}

bool User::operator==(const User& other) const {
	if (this->userName == other.userName)
		return true;

	return false;
}

bool User::operator!=(const User& other) const {
	return !(*this == other);
}

/*bool User::operator>(const User& other) const {
	if (this->userName.size() > other.userName.size())
		return 1;

	return 0;
}*/

bool User::operator<(const User& other) const {
	if (this->userName < other.userName)
		return true;

	return false;
}

bool User::operator>=(const User& other) const {
	if (this->userName.size() >= other.userName.size())
		return true;

	return false;
}

bool User::operator<=(const User& other) const {
	if (this->userName.size() <= other.userName.size())
		return true;

	return false;
}

void User::setTypePassword(bool typePassword) {
	this->typePassword = typePassword;
}