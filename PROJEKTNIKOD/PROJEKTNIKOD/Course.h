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
	//BESPOTREBAN ATRIBUT, MISLIO RADITI CETVRTU STAVKU, ALI NECU
	double minimumCourseGrade;
	std::vector<Student> studentArray;
	Lecturer lecturer;
public:
	Course(std::string courseName = "", std::string typeOfCourse = "", double minimumCourseGrade = 0.0);

	//GETTERI
	Lecturer returnLecturer() const;
	std::string getCourseName() const;
	std::string getTypeOfCourse() const;
	double getMinimumCourseGrade() const;

	//NALAZENJE UNIJE, INTERSEKCIJE, RAZLIKE
	std::set<Student> findUnionIntersectionDifference();

private:
	//POMOCNE FUNKCIJE ZA UNOS KORISNIKA, NISTA SPECIJALNO
	std::string userInput() const;
	std::string userInput2() const;
	std::string userInput3() const;

	//PROVJERA POSTOJANOSTI KURSA
	bool doesCourseExist(std::string courseName);
};