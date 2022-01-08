#include "Lecturer.h"
#include <fstream>
#include <iostream>

Lecturer::Lecturer(std::string userName, std::string password) : User(userName, password) {
	this->setType("Lecturer");
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
			studentCounter++;
		}
	}
	return studentCounter;
}
