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

	if (!checkIfUserIsAlreadyInAFile(userName)) {
		auto writeUsers = std::ofstream("./KORISNICI/Korisnici.txt", std::ios::app | std::ios::out);
		this->typePassword = true;
		writeUsers << *this;
		this->typePassword = false;
		writeUsers.close();
	}
	else {
		//std::cout << "This student already exists!" << std::endl;
	}
}

void Student::signToCourse(std::string courseName) const noexcept(false) {
	try {
		auto readFile = std::ifstream("./KURSEVI/" + courseName + "/STUDENTI.txt", std::ios::in);
		if (!readFile) {
			throw std::exception("This course doesn't exist!");
		}
		readFile.close();
		if (checkIfIsEitherStudentOrLecturer(courseName)) {
			throw std::exception("Student/Lecturer is already inside this course!");
		}
		if (checkIfRequestIsAlreadyMade(courseName, this->getUserName())) {
			throw std::exception("You've already made a request, wait for the professor to accept it!");
		}

		auto writeToCourse = std::ofstream("./KURSEVI/" + courseName + "/ZAHTJEVI.txt", std::ios::out | std::ios::app);
		writeToCourse << *this;
		writeToCourse.close();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

bool Student::checkIfRequestIsAlreadyMade(std::string course, std::string name) const {
	auto textFile = std::ifstream("./KURSEVI/" + course + "/ZAHTJEVI.txt", std::ios::in);

	if (textFile) {
		while (textFile.good()) {
			Student s;
			textFile >> s;
			if (s.getUserName() == name)
				return true;
		}
	}

	textFile.close();
	return false;
}

void Student::addStudentDirectlyToCourse(std::string courseName) {
	try {
		if (checkIfIsEitherStudentOrLecturer(courseName)) {
			throw std::exception("This course doesn't exist or student is already inside this course!");
		}
		if (checkIfIsLecturer(courseName)) {
			throw std::exception("Can't be added as a student, already a lecturer in here!");
		}
		if (checkUserName()) {
			throw std::exception("This user name already exists, cannot be added!");
		}

		auto writeToCourse = std::ofstream("./KURSEVI/" + courseName + "/STUDENTI.txt", std::ios::out | std::ios::app);
		writeToCourse << *this;
		writeToCourse.close();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void Student::sendFriendRequest(std::string userName) const {
	try {
		auto getFriendFile = std::ifstream("./STUDENTI/" + userName + "/" + "FRIENDREQUESTS.TXT", std::ios::in);
		if (!getFriendFile) {
			throw std::exception("Person to whom you want to send friend request doesn't exist!");
		}
		getFriendFile.close();
		if (checkIfFriendRequestIsAlreadyMade(userName)) {
			throw std::exception("You've already made a request, wait!");
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

bool Student::checkIfFriendRequestIsAlreadyMade(std::string userName) const {
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

void Student::automaticLecturerFriend(std::string lecturerName, std::string lecturerPassword) const {
	auto writeFriend = std::ofstream("./STUDENTI/" + this->userName + "/FRIENDS.txt", std::ios::out | std::ios::app);
	auto writeLecturerFriend = std::ofstream("./STUDENTI/" + lecturerName + "/FRIENDS.txt", std::ios::out | std::ios::app);
	if (writeFriend) {
		Lecturer l(lecturerName, lecturerPassword);
		writeFriend << l;
		writeLecturerFriend << *this;
	}
	writeFriend.close();
	writeLecturerFriend.close();
}

void Student::checkFriendRequests() const {
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

bool Student::checkIfIsAlreadyAFriend(std::string friendName) const {
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
