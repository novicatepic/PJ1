#include "Student.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <iomanip>
#include <string>
#include <filesystem>
#include <vector>

Student::Student(std::string userName, std::string password) : User(userName, password) {
	this->setType("Student");
	auto open = std::ifstream("./STUDENTI/" + this->userName + "/" + "FRIENDS.TXT");
	if (!open) {
		namespace fs = std::filesystem;
		fs::path path = std::filesystem::current_path();
		fs::path studentSubfolderPath = path / "STUDENTI" / this->userName;
		fs::path chatPath = path / "STUDENTI" / this->userName / "CHATS";
		create_directory(studentSubfolderPath);
		create_directory(chatPath);
		std::ofstream studentFile("./STUDENTI/" + this->userName + "/" + "FRIENDS.TXT");
		std::ofstream requestFile("./STUDENTI/" + this->userName + "/" + "FRIENDREQUESTS.TXT");
		studentFile.close();
		requestFile.close();
	}

	if (!checkIfUserIsAlreadyInAFile(userName, password)) {
		auto writeUsers = std::ofstream("./KORISNICI/Korisnici.txt", std::ios::app | std::ios::out);
		writeUsers << *this;
		writeUsers.close();
	}
}

void Student::signToCourse(std::string courseName) const noexcept(false) {
	try {
		if (checkIfIsInsideCourse(courseName)) {
			throw std::exception("This course doens't exist or student is already inside this course!");
		}
		auto writeToCourse = std::ofstream("./KURSEVI/" + courseName + "/ZAHTJEVI.txt", std::ios::out | std::ios::app);
		writeToCourse << *this;
		writeToCourse.close();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void Student::addStudentDirectlyToCourse(std::string courseName) {
	try {
		if (checkIfIsInsideCourse(courseName)) {
			throw std::exception("This course doens't exist or student is already inside this course!");
		}
		auto writeToCourse = std::ofstream("./KURSEVI/" + courseName + "/STUDENTI.txt", std::ios::out | std::ios::app);
		writeToCourse << *this;
		writeToCourse.close();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

bool Student::checkIfIsInsideCourse(std::string courseName) const {
	auto readFile = std::ifstream("./KURSEVI/" + courseName + "/STUDENTI.txt", std::ios::in);
	if (!readFile) {
		return true;
	}

	while (readFile.good()) {
		Student st;
		readFile >> st;
		if (st.userName == this->userName && st.password == this->password)
			return true;
	}

	readFile.close();

	return false;
}

void Student::sendFriendRequest(std::string userName) const {
	try {
		auto getFriendFile = std::ifstream("./STUDENTI/" + userName + "/" + "FRIENDREQUESTS.TXT", std::ios::in);
		if (!getFriendFile) {
			throw std::exception("This file cannot be opened, it doesn't exist");
		}
		getFriendFile.close();
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

void Student::automaticLecturerFriend(std::string s1, std::string s2) const {
	auto writeFriend = std::ofstream("./STUDENTI/" + this->userName + "/FRIENDS.txt", std::ios::out | std::ios::app);
	auto writeLecturerFriend = std::ofstream("./STUDENTI/" + s1 + "/FRIENDS.txt", std::ios::out | std::ios::app);
	if (writeFriend) {
		Lecturer l(s1, s2);
		writeFriend << l;
		writeLecturerFriend << *this;
	}
	writeFriend.close();
	writeLecturerFriend.close();
}

void Student::checkFriendRequests() const {
	auto openFriendRequests = std::ifstream("./STUDENTI/" + this->userName + "/" + "FRIENDREQUESTS.TXT", std::ios::in);
	std::vector<User> users;
	if (openFriendRequests) {
		std::cout << "Current people want to become your friends: " << std::endl;
		while (openFriendRequests.good()) {
			User u;
			openFriendRequests >> u;
			users.push_back(u);
			std::cout << u;
		}
	}
	openFriendRequests.close();

	std::cout << "Do you want any of them to become your friends: (y/n)" << std::endl;
	std::string choice;
	std::cin >> choice;

	if (choice == "y") {
		std::cout << "What's the name of the student you wanna get friends with: " << std::endl;
		std::string name;
		std::cin >> name;
		auto friendFile = std::ofstream("./STUDENTI/" + this->userName + "/" + "FRIENDS.TXT", std::ios::out | std::ios::app);

		//auto friendRequestFile = std::ifstream("./STUDENTI/" + this->userName + "/" + "FRIENDREQUESTS.TXT", std::ios::in);
		if (friendFile) {
			for (auto elem : users) {
				if (elem.getUserName() == name) {
					friendFile << elem;
					auto friendFile2 = std::ofstream("./STUDENTI/" + name + "/" + "FRIENDS.TXT", std::ios::out | std::ios::app);
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

/*void Student::textFriend(std::string friendName) const {
	auto openFriends = std::ifstream("./STUDENTI/" + this->userName + "/" + "FRIENDS.TXT", std::ios::in);
	std::vector<Student> friends;
	while (openFriends.good()) {
		Student st;
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
		}
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
}*/

bool Student::checkIfIsLecturer(std::string course, std::string name) const {
	auto textFile = std::ifstream("./KURSEVI/" + course + "PREDAVAC.txt", std::ios::in);
	if (textFile) {
		Lecturer l;
		textFile >> l;
		if (l.getUserName() == name)
			return true;
	}

	return false;
}

/*void Student::textLecturer(std::string courseName) const {
	try {
		if (checkIfIsInsideCourse(courseName)) {
			throw std::exception("This student is not in this course!");
		}

		auto textFile = std::ofstream("./KURSEVI/" + courseName + "/PREDAVACCHAT/" + this->userName + ".txt", std::ios::out | std::ios::app);
		auto textStudentFile = std::ofstream("./KURSEVI/" + courseName + "/STUDENTCHAT/" + "Predavac" + ".txt", std::ios::out | std::ios::app);

		if (textFile && textStudentFile) {
			std::cout << "Enter your message: " << std::endl;
			std::string message;
			//std::cin.ignore();
			std::getline(std::cin, message, '\n');
			textFile << this->getUserName() << ": " << std::endl;
			textFile << message << std::endl;
			textStudentFile << this->getUserName() << ": " << std::endl;
			textStudentFile << message << std::endl;
		}
		textFile.close();
		textStudentFile.close();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}*/

