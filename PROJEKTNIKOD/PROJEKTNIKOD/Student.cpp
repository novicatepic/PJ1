#include "Student.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <iomanip>
#include <string>
#include <filesystem>

Student::Student(std::string userName, std::string password) : User(userName, password) {
	this->setType("Student");
	namespace fs = std::filesystem;
	fs::path path = std::filesystem::current_path();
	fs::path studentSubfolderPath = path / "STUDENTI" / this->userName;
	create_directory(studentSubfolderPath);
	std::ofstream studentFile("./STUDENTI/" + this->userName + "/" + "FRIENDS.TXT");
	std::ofstream requestFile("./STUDENTI/" + this->userName + "/" + "FRIENDREQUESTS.TXT");
	studentFile.close();
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

void Student::checkFriendRequests() const {

}