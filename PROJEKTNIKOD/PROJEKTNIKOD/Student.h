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

protected:


private:
	bool checkIfIsInsideCourse(std::string course) const;
};