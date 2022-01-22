#include "User.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

User::User(std::string userName, std::string password) : CoreUser(userName, password) { }

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


void User::sendFriendRequest(std::string userName) const {
	try {
		auto getFriendFile = std::ifstream("./STUDENTI/" + userName + "/" + "FRIENDREQUESTS.TXT", std::ios::in);
		if (!getFriendFile) {
			throw std::exception("Person to whom you want to send friend request doesn't exist!");
		}
		getFriendFile.close();
		if (checkIfFriendRequestIsAlreadyMade(userName)) {
			throw std::exception("You've already made a request, wait!");
		}
		if (checkIfIsAlreadyAFriend(userName)) {
			throw std::exception("This person is already your friend!");
		}
		auto openFriendFile = std::ofstream("./STUDENTI/" + userName + "/" + "FRIENDREQUESTS.TXT", std::ios::out | std::ios::app);
		if (openFriendFile) {
			openFriendFile << *this;
		}
		openFriendFile.close();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

bool User::checkIfFriendRequestIsAlreadyMade(std::string userName) const {
	auto getFriendFile = std::ifstream("./STUDENTI/" + userName + "/" + "FRIENDREQUESTS.TXT", std::ios::in);
	if (getFriendFile) {
		while (getFriendFile.good()) {
			User u;
			getFriendFile >> u;
			if (u.getUserName() == userName) {
				getFriendFile.close();
				return true;
			}
		}
	}

	getFriendFile.close();
	return false;
}

void User::checkFriendRequests() const {
	try {

		auto openFriendRequests = std::ifstream("./STUDENTI/" + this->userName + "/" + "FRIENDREQUESTS.TXT", std::ios::in);
		std::vector<User> users;
		if (openFriendRequests) {
			std::cout << "Current people want to become your friends: " << std::endl;
			while (openFriendRequests.good()) {
				User u;
				openFriendRequests >> u;
				if (std::find(users.begin(), users.end(), u) == users.end()) {
					users.push_back(u);
					std::cout << u;
				}
			}
		}
		openFriendRequests.close();

		std::cout << "Do you want any of them to become your friends: (y/n)" << std::endl;
		std::string choice;
		std::getline(std::cin, choice, '\n');

		if (choice == "y") {
			std::cout << "What's the name of the student you wanna get friends with: " << std::endl;
			std::string name;
			//std::cin >> name;
			std::getline(std::cin, name, '\n');

			if (this->checkIfIsAlreadyAFriend(name)) {
				throw std::exception("This person is already your friend!");
			}

			auto friendFile = std::ofstream("./STUDENTI/" + this->userName + "/FRIENDS.TXT", std::ios::out | std::ios::app);

			//auto friendRequestFile = std::ifstream("./STUDENTI/" + this->userName + "/" + "FRIENDREQUESTS.TXT", std::ios::in);
			if (friendFile) {
				for (auto elem : users) {
					if (elem.getUserName() == name && elem.getUserName() != "") {
						friendFile << elem;
						auto friendFile2 = std::ofstream("./STUDENTI/" + name + "/FRIENDS.TXT", std::ios::out | std::ios::app);
						friendFile2 << *this;
					}

				}
			}
			friendFile.close();

			auto rewriteRequests = std::ofstream("./STUDENTI/" + this->userName + "/" + "FRIENDREQUESTS.TXT", std::ios::out);
			if (rewriteRequests) {
				for (auto elem : users) {
					if (elem.getUserName() != name && elem.getUserName() != "") {
						rewriteRequests << elem;
					}
				}
			}

			rewriteRequests.close();
		}
		else if (choice == "n") {

		}
		else {
			std::cout << "Sorry, didn't understand you!" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

}

bool User::checkIfIsAlreadyAFriend(std::string friendName) const {
	auto friendsFile = std::ifstream("./STUDENTI/" + this->userName + "/FRIENDS.txt");

	if (friendsFile) {
		while (friendsFile.good()) {
			User u;
			friendsFile >> u;
			if (u.getUserName() == friendName) {
				return true;
			}
		}
	}
	friendsFile.close();

	return false;

}

void User::printChatWithFriend() const {
	std::string friendName;
	std::cout << "Here are your friends: " << std::endl;
	showFriends();
	std::cout << "Enter name of the friend you want to see chat history: " << std::endl;
	std::getline(std::cin, friendName, '\n');
	try {
		if (!checkIfIsAlreadyAFriend(friendName)) {
			throw std::exception("This person is not your friend or he/she doesn't exist!");
		}
		auto openChatFile = std::ifstream("./STUDENTI/" + friendName + "/CHATS/" + this->getUserName() + ".TXT", std::ios::in);
		if (openChatFile) {
			while (openChatFile.good()) {
				std::string stringRead;
				std::getline(openChatFile, stringRead, '\n');
				std::cout << stringRead << std::endl;
			}
			openChatFile.close();
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
