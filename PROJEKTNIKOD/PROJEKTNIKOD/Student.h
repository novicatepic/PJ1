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

	void addStudentDirectlyToCourse(std::string courseName);

	void automaticLecturerFriend(std::string, std::string) const;

	bool checkIfIsAlreadyAFriend(std::string friendName) const;
protected:


private:

	//bool checkIfIsLecturer(std::string course, std::string name) const;
	bool checkIfRequestIsAlreadyMade(std::string course, std::string name) const;
	bool checkIfFriendRequestIsAlreadyMade(std::string name) const;
};