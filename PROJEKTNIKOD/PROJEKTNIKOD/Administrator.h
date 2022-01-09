#pragma once
#include "User.h"

class Administrator : public User {
private:

public:
	Administrator(std::string userName = "", std::string password = "");

	void addUserToCourse();
	void removeUserFromCourse();

	void modifyCourses();
	void modifyUsers();

	void addNewCourse();
	void removeCourse();

private:
	bool doesCourseExist(std::string courseName);
	void modifyHelper(std::string);

};