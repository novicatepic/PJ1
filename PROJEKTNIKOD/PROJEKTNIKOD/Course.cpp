#include "Course.h"
#include <iostream>
#include <fstream>
#include <filesystem>

Course::Course(std::string courseName) : courseName(courseName) {
	auto openCourse = std::ifstream("./KURSEVI/" + courseName + "STUDENTI.txt", std::ios::in);
	if (!openCourse) {
		std::cout << "This course doesn't exist!" << std::endl;
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
