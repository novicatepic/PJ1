#pragma once
//#include "User.h"
//#include "Student.h"
#include "Lecturer.h"
#include <vector>
#include <string>
#include <iostream>

class Course {
private:
	std::string courseName;
	std::vector<Student> studentArray;
	Lecturer lecturer;
public:
	Course(std::string courseName = "");

	Lecturer returnLecturer() const;

	std::string getCourseName() const;
};