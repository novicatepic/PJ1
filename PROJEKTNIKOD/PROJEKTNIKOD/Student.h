#pragma once
#include "User.h"
#include <fstream>
#include <string>

class Student : public User {
private:

public:
	Student(std::string userName = "", std::string password = "");

	void signToCourse(std::string courseName) const noexcept(false);

	void sendFriendRequest(std::string userName) const;
	void checkFriendRequests() const;
	void textFriend(std::string friendName) const;

	void textLecturer(std::string courseName) const;

protected:


private:
	bool checkIfIsInsideCourse(std::string course) const;
};