#pragma once
#include "User.h"
#include "CoreUser.h"

class Administrator : public CoreUser {
private:

public:
	Administrator(std::string userName = "", std::string password = "");

	void addUserToCourse();
	void removeUserFromCourse();

	void addUser();
	void removeUser();

	void modifyCourses();
	void modifyUsers();

	void addNewCourse();
	void removeCourse();

private:
};