#include "Course.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <set>
#include <algorithm>

Course::Course(std::string courseName) : courseName(courseName) {
	auto openCourse = std::ifstream("./KURSEVI/" + courseName + "/STUDENTI.txt", std::ios::in);
	if (!openCourse) {
		namespace fs = std::filesystem;
		fs::path path = std::filesystem::current_path();
		fs::path courseFolderPath = path / "KURSEVI" / this->courseName;
		create_directory(courseFolderPath);


		auto makeFiles = std::ofstream("./KURSEVI/" + courseName + "/PREDAVAC.txt");
		makeFiles.close();
		makeFiles = std::ofstream("./KURSEVI/" + courseName + "/STUDENTI.txt");
		makeFiles.close();
		makeFiles = std::ofstream("./KURSEVI/" + courseName + "/ZAHTJEVI.txt");
		makeFiles.close();
		makeFiles = std::ofstream("./KURSEVI/" + courseName + "/POLOZILI.txt");
		makeFiles.close();

		//l.signLecturerToCourse(courseName);
	}
	else {
		User u;
		while (openCourse.good()) {
			openCourse >> u;
			if (u.getType() == "Student") {
				Student st(u.getUserName(), u.getPassword());
				studentArray.push_back(st);
			}
		}
		openCourse.close();
		openCourse = std::ifstream("./KURSEVI/" + courseName + "PREDAVAC.txt", std::ios::in);
		openCourse >> u;
		Lecturer l(u.getUserName(), u.getPassword());
		l.signLecturerToCourse(this->courseName);
	}
	openCourse.close();
}

Lecturer Course::returnLecturer() const {
	return this->lecturer;
}

std::string Course::getCourseName() const {
	return this->courseName;
}

void Course::modifyStudentInCourse(std::string credential, std::string oldData, std::string newData) {
	namespace fs = std::filesystem;

	fs::path path  = std::filesystem::current_path() / "KURSEVI";
	for (auto const& entry : fs::directory_iterator(path / this->courseName)) {
		auto enter = std::ifstream(entry.path().filename(), std::ios::in);
		if (entry.path().filename() != "ZAHTJEVI.txt") {
			if (enter) {
				while (enter.good()) {
					User u;
					enter >> u;
					if (u.getUserName() == lecturer.getUserName() && u.getUserName() == oldData) {
						lecturer.setUserName(newData);
						enter.close();
						auto writeToFile = std::ofstream("./KURSEVI/" + courseName + "/PREDAVAC.txt");
						writeToFile << lecturer;
						writeToFile.close();
					}
					else {
						for (auto elem : studentArray) {
							enter >> u;
							if (u.getUserName() == elem.getUserName()) {
								elem.setUserName(newData);
							}
						}
						enter.close();
						auto writeToFile = std::ofstream("./KURSEVI/" + courseName + "/STUDENTI.txt");
						for (auto elem : studentArray) {
							writeToFile << elem;
						}
						writeToFile.close();
					}
				}
			}
		}
		else {

			std::vector<User> arrayUsers;
			User user;
			if (enter) {
				while (enter.good()) {
					enter >> user;
					if (user.getUserName() == oldData) {
						user.setUserName(newData);
					}
					arrayUsers.push_back(user);
				}
				enter.close();

				auto writeToFile = std::ofstream("./KURSEVI/" + courseName + "/ZAHTJEVI.txt");

				for (auto elem : arrayUsers) {
					writeToFile << elem;
				}
				writeToFile.close();
			}
		}
	}
}

std::set<Student> Course::findUnionIntersectionDifference() {
	std::string courseName = userInput();
	std::set<Student> resVector;
	try {
		if (!doesCourseExist(courseName)) {
			throw std::exception("This course doesn't exist!");
		}

		std::string choice = userInput3();

		std::set<Student> set1;
		std::set<Student> set2;

		std::ifstream readFromCourse;
		std::ifstream readFromCourse2;

		if (choice == "1") {
			readFromCourse = std::ifstream("./KURSEVI/" + this->courseName + "/STUDENTI.txt", std::ios::in);
			readFromCourse2 = std::ifstream("./KURSEVI/" + courseName + "/STUDENTI.txt", std::ios::in);
		}
		else if (choice == "2") {
			readFromCourse = std::ifstream("./KURSEVI/" + this->courseName + "/POLOZILI.txt", std::ios::in);
			readFromCourse2 = std::ifstream("./KURSEVI/" + courseName + "/POLOZILI.txt", std::ios::in);
		}
		else {
			throw std::exception("It must be either 1 for current students or 2 for students that finished this course!");
		}


		if (readFromCourse && readFromCourse2) {
			while (readFromCourse.good()) {
				Student s;
				readFromCourse >> s;
				if (s.getUserName() != "") {
					set1.emplace(s);
				}
			}
			readFromCourse.close();
			while (readFromCourse2.good()) {
				Student s;
				readFromCourse2 >> s;
				if (s.getUserName() != "") {
					set2.emplace(s);
				}
			}
			readFromCourse2.close();
		}

		std::string userInput = userInput2();

		if (userInput == "Union") {
			std::set_union(set1.cbegin(), set1.cend(),
				set2.cbegin(), set2.cend(),
				std::inserter(resVector, resVector.begin()));
		}
		else if (userInput == "Intersection") {
			std::set_intersection(set1.cbegin(), set1.cend(),
				set2.cbegin(), set2.cend(),
				std::inserter(resVector, resVector.begin()));
		}
		else if (userInput == "Difference") {
			std::set_difference(set1.cbegin(), set1.cend(),
				set2.cbegin(), set2.cend(),
				std::inserter(resVector, resVector.begin()));
		}
		else {
			throw std::exception("Input must be Union or Intersection or Difference");
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return resVector;
}

std::string Course::userInput() const {
	std::cout << "Input course name: " << std::endl;
	std::string courseName;
	std::getline(std::cin, courseName, '\n');
	return courseName;
}

std::string Course::userInput2() const {
	std::cout << "Union/Intersection/Difference: " << std::endl;
	std::string answer;
	std::getline(std::cin, answer, '\n');
	return answer;
}

std::string Course::userInput3() const {
	std::cout << "1 for students that are goint to the course, 2 for students that finished the course :" << std::endl;
	std::string answer;
	std::getline(std::cin, answer, '\n');
	return answer;
}

bool Course::doesCourseExist(std::string courseName) {
	namespace fs = std::filesystem;
	fs::path path = std::filesystem::current_path();

	for (auto const& entry : fs::directory_iterator(path / "KURSEVI")) {
		if (entry.path().filename() == courseName)
			return true;
	}

	return false;
}