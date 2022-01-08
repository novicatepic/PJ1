#pragma once
#include "User.h"
//#include "Course.h"
#include "Student.h"
#include <string>
#include <iostream>


class Lecturer : public User {
private:

public:
	Lecturer(std::string userName = "", std::string password = "");
	void signStudentToCourse(std::string courseName);
	void signLecturerToCourse(std::string courseName);

public:
	friend size_t howManyStudents(std::string courseName);
	friend size_t howManyLecturers(std::string courseName);
};


