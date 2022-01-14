#pragma once
#include "User.h"
#include "Student.h"
#include "Lecturer.h"
#include <vector>
#include <set>
#include <string>
#include <iostream>

class Course {
private:
	std::string courseName;
	std::string typeOfCourse;
	double minimumCourseGrade;
	std::vector<Student> studentArray;
	Lecturer lecturer;
public:
	Course(std::string courseName = "", std::string typeOfCourse = "", double minimumCourseGrade = 0.0);

	Lecturer returnLecturer() const;
	std::string getCourseName() const;
	std::string getTypeOfCourse() const;
	double getMinimumCourseGrade() const;

	//void modifyStudentInCourse(std::string credential, std::string oldData, std::string newData);

	std::set<Student> findUnionIntersectionDifference();

private:
	std::string userInput() const;
	std::string userInput2() const;
	std::string userInput3() const;
	bool doesCourseExist(std::string courseName);
	//bool checkIfIsStudentOrLecturer()
};