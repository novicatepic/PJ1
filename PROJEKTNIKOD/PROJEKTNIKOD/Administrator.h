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
	void showAllUsers() const;
private:
	void rewriteUsersFile(std::string userName);
	void rewriteCoursesFilesOrFriends(std::string userName, std::string folderName);
	void removeUserFolder(std::string userName);
	//void rewriteOtherFriends(std::string userName);
	
};