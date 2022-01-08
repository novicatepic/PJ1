#include "Course.h"
#include <iostream>
#include <fstream>
#include <filesystem>

Course::Course(std::string courseName) : courseName(courseName) {
	auto openCourse = std::ifstream("./KURSEVI/" + courseName + "STUDENTI.txt", std::ios::in);
	if (!openCourse) {

		//std::cout << "This course doesn't exist!" << std::endl;
		namespace fs = std::filesystem;
		fs::path path = std::filesystem::current_path();
		fs::path courseFolderPath = path / "KURSEVI" / this->courseName;
		create_directory(courseFolderPath);
		/*courseFolderPath = path / "KURSEVI" / this->courseName / "PREDAVACCHAT";
		create_directory(courseFolderPath);
		courseFolderPath = path / "KURSEVI" / this->courseName / "STUDENTCHAT";
		create_directory(courseFolderPath);*/
		auto makeFiles = std::ofstream("./KURSEVI/" + courseName + "/PREDAVAC.txt");
		makeFiles.close();
		makeFiles = std::ofstream("./KURSEVI/" + courseName + "/STUDENTI.txt");
		makeFiles.close();
		makeFiles = std::ofstream("./KURSEVI/" + courseName + "/ZAHTJEVI.txt");
		makeFiles.close();
		/*makeFiles = std::ofstream("./KURSEVI/" + courseName + "/PREDAVACCHAT/" + "INBOX.txt");
		makeFiles.close();
		makeFiles = std::ofstream("./KURSEVI/" + courseName + "/STUDENTCHAT/" + "INBOX.txt");*/
		makeFiles.close();
		//l.signLecturerToCourse(courseName);
	}
	else {
		while (openCourse.good()) {
			User u;
			openCourse >> u;
			if (u.getType() == "Student") {
				Student st(u.getUserName(), u.getPassword());
				studentArray.push_back(st);
			}
			else if (u.getType() == "Lecturer") {
				Lecturer l(u.getUserName(), u.getPassword());
				this->lecturer = l;
			}
		}
	}
	openCourse.close();
}

Lecturer Course::returnLecturer() const {
	return this->lecturer;
}

std::string Course::getCourseName() const {
	return this->courseName;
}
