#pragma once
#include "User.h"
#include "Lecturer.h"
#include <fstream>
#include <string>

class Student : public User {
private:

public:
	Student(std::string userName = "", std::string password = "");

	void signToCourse(std::string courseName) const noexcept(false);

	void sendFriendRequest(std::string userName) const;
	void checkFriendRequests() const;

	//void textFriend(std::string friendName) const;

	void addStudentDirectlyToCourse(std::string courseName);

	void automaticLecturerFriend(std::string s1, std::string s2) const;

	bool checkIfIsAlreadyAFriend(std::string friendName);
protected:


private:
	bool checkIfIsInsideCourse(std::string course) const;
	bool checkIfIsLecturer(std::string course, std::string name) const;
	bool checkIfRequestIsAlreadyMade(std::string course, std::string name) const;
	bool checkIfIsLecturer(std::string courseName) const;
};