#include "Student.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <iomanip>
#include <string>
#include <filesystem>
#include "Course.h"
#include <string>
#include <vector>

Student::Student(std::string userName, std::string password) : CoreUser(userName, password) {
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
		std::ofstream gradedFile("./STUDENTI/" + this->userName + "/OCJENE.txt");
		std::ofstream listenedFile("./STUDENTI/" + this->userName + "/ODSLUSANI.txt");
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

		Course c(courseName);
		Lecturer l = c.returnLecturer();

		this->automaticLecturerFriend(l.getUserName());

		writeToCourse << *this;
		writeToCourse.close();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}



void Student::automaticLecturerFriend(std::string lecturerName) const {
	auto writeFriend = std::ofstream("./STUDENTI/" + this->userName + "/FRIENDS.txt", std::ios::out | std::ios::app);
	auto writeLecturerFriend = std::ofstream("./STUDENTI/" + lecturerName + "/FRIENDS.txt", std::ios::out | std::ios::app);
	if (writeFriend) {
		if (!checkIfIsAlreadyAFriend(lecturerName)) {
			Lecturer l(lecturerName);
			writeFriend << l;
			writeLecturerFriend << *this;
		}
	}
	writeFriend.close();
	writeLecturerFriend.close();
}

bool Student::didListenCourse(std::string courseName) {
	Course c(courseName);
	//std::ofstream gradedFile("./STUDENTI/" + this->userName + "/OCJENE.txt");
	//std::ofstream listenedFile("./STUDENTI/" + this->userName + "/ODSLUSANI.txt");
	
	auto openListened = std::ifstream("./STUDENTI/" + this->userName + "/ODSLUSANI.txt", std::ios::in);
	try {
		if (!openListened) {
			throw std::exception("Something wrong with file!");
		}

		while (openListened.good()) {
			std::string cName;
			openListened >> cName;
			if (cName != "" && cName == courseName) {
				openListened.close();
				return true;
			}

		}

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	openListened.close();
	return false;
}

bool Student::howManyDidHeFinish(std::string typeOfCourse, size_t number) {
	//std::ofstream gradedFile("./STUDENTI/" + this->userName + "/OCJENE.txt");
	//std::ofstream listenedFile("./STUDENTI/" + this->userName + "/ODSLUSANI.txt");

	size_t res = 0;

	auto readFinished = std::ifstream("./STUDENTI/" + this->userName + "/OCJENE.txt", std::ios::in);
	try {
		if (!readFinished) {
			throw std::exception("Something wrong with file!");
		}

		std::string readString;
		std::getline(readFinished, readString, ':');
		//std::getline(readFinished, readString, '\n');
		if (readString != "") {
			Course c(readString);
			if (c.getTypeOfCourse() == typeOfCourse) {
				res++;
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	readFinished.close();
	if (res >= number) {
		return true;
	}

	return false;
}

bool Student::minimumGradeCondition() {
	//double minGrade;
	
	//std::ofstream gradedFile("./STUDENTI/" + this->userName + "/OCJENE.txt");
	//std::ofstream listenedFile("./STUDENTI/" + this->userName + "/ODSLUSANI.txt");
	size_t studentCounter = 0, courseCounter = 0;
	std::string userInput;

	do {
		std::cout << "Enter course to check if student finished it with certain grade, '-exit' for exiting this option: " << std::endl;
		std::getline(std::cin, userInput, '\n');
		if (userInput == "-exit") {

		}
		else if (!doesCourseExist(userInput)) {
			std::cout << "This course doesn't exist!" << std::endl;
		}
		else {
			courseCounter++;
			Course c(userInput);
			auto readGrades =  std::ifstream("./STUDENTI/" + this->userName + "/OCJENE.txt");
			std::string helpRead, courseName;
			while (readGrades.good()) {
				std::getline(readGrades, helpRead, ':');
				std::getline(readGrades, helpRead, ':');
				courseName = helpRead;
				std::getline(readGrades, helpRead, '\n');
			}
			readGrades.close();
			double grade = std::stod(helpRead);
			if (c.getMinimumCourseGrade() <= grade && courseName == c.getCourseName()) {
				studentCounter++;
			}
		}
	} while (userInput != "-exit");

	//auto readFinished = std::ifstream("./STUDENTI/" + this->userName + "/OCJENE.txt", std::ios::in);

	if (studentCounter == courseCounter) {
		return true;
	}

	return false;

}