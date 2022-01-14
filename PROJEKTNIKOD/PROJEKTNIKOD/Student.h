#pragma once
#include "User.h"
#include "Lecturer.h"
#include <fstream>
#include <string>
#include <vector>

class Student : public User {
protected:

	//std::vector<bool(std::string)> predoncitions;

public:
	Student(std::string userName = "", std::string password = "");

	void signToCourse(std::string courseName) const noexcept(false);
	void addStudentDirectlyToCourse(std::string courseName);
	void automaticLecturerFriend(std::string) const;

protected:


private:
	bool didListenCourse(std::string);
	bool howManyDidHeFinish(std::string, size_t);
	bool minimumGradeCondition();
	bool isStudentVersatile(std::string);

	//bool checkIfIsLecturer(std::string course, std::string name) const;
	bool checkIfRequestIsAlreadyMade(std::string course, std::string name) const;

};