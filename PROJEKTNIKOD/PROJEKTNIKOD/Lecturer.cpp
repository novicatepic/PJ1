#include "Lecturer.h"
#include <fstream>
#include <iostream>

Lecturer::Lecturer(std::string userName, std::string password) : User(userName, password) {
	this->setType("Lecturer");

	if (!checkIfUserIsAlreadyInAFile(userName, password)) {
		auto writeUsers = std::ofstream("./KORISNICI/Korisnici.txt", std::ios::app | std::ios::out);
		writeUsers << *this;
		writeUsers.close();
	}
}

void Lecturer::signStudentToCourse(std::string courseName) {
	auto readFile = std::ifstream("./KURSEVI/" + courseName + "/ZAHTJEVI.txt", std::ios::in);
	if (readFile) {
		std::cout << "You have " << howManyStudents(courseName) << "students who want to go to this course!" << std::endl;
		std::cout << "Here they are: " << std::endl;
		while (readFile.good()) {
			User u;
			readFile >> u;
			std::cout << u;
		}
		readFile.close();
	}
	auto writeFile = std::ofstream("./KURSEVI/" + courseName + "/STUDENTI.txt", std::ios::out | std::ios::app);
	std::cout << "Enter username of student who you want to assign to this course: " << std::endl;
	std::string userName; 
	std::cin >> userName;
	auto readAgain = std::ifstream("./KURSEVI/" + courseName + "/ZAHTJEVI.txt", std::ios::in);
	if (readAgain && writeFile) {
		while (readAgain.good()) {
			User u;
			readAgain >> u;
			if (u.getUserName() == userName) {
				writeFile << u;
			}
		}
	}
	writeFile.close();
	readAgain.close();
}

void Lecturer::writeStudentToFile(std::string courseName) {

}

size_t Lecturer::howManyStudents(std::string courseName) {
	auto readFile = std::ifstream("./KURSEVI/" + courseName + "/ZAHTJEVI.txt", std::ios::in);
	size_t studentCounter = 0;
	if (readFile) {
		while (readFile.good()) {
			User u;
			readFile >> u;
			if (u.getUserName() != "" && u.getPassword() != "" && u.getType() == "Student") {
				studentCounter++;
			}
		}
	}
	return studentCounter;
}

size_t Lecturer::howManyLecturers(std::string courseName) {
	size_t counter = 0;
	auto readHowManyLecturers = std::ifstream("./KURSEVI/" + courseName + "/PREDAVAC.txt", std::ios::in);
	if (readHowManyLecturers) {
		while (readHowManyLecturers.good()) {
			User u;
			readHowManyLecturers >> u;
			if (u.getUserName() != "" && u.getPassword() != "" && u.getType() == "Lecturer") {
				counter++;
			}
		}
	}
	readHowManyLecturers.close();
	return counter;
}

void Lecturer::signLecturerToCourse(std::string courseName) {
	try {
		auto writeToCourse = std::ofstream("./KURSEVI/" + courseName + "/PREDAVAC.txt", std::ios::out | std::ios::app);
		if (writeToCourse) {
			if (howManyLecturers(courseName) == 0) {
				writeToCourse << *this;
				writeToCourse.close();
			}
			else {
				throw std::exception("There is already one lecturer in this course!");
		}

		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}