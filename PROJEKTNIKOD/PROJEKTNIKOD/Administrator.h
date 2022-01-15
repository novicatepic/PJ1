#pragma once
#include "User.h"
#include "CoreUser.h"

class Administrator : public CoreUser {
private:

public:
	Administrator(std::string userName = "", std::string password = "");

	//DODOAVANJE I UKLANJANJE KORISNIKA SA KURSA
	void addUserToCourse();
	void removeUserFromCourse();

	//DODAVANJE I UKLANJANJE KORISNIKA
	void addUser();
	void removeUser();

	//MODIFIKOVANJE NAZIVA KURSA/KORISNIKA
	void modifyCourses();
	void modifyUsers();

	//DODAVANJE NOVOG KURSA ILI UKLANJANJE ODREDJENOG KURSA
	void addNewCourse();
	void removeCourse();

	//PRIKAZIVANJE SVIH KORISNIKA
	void showAllUsers() const;
private:
	//POMOCNE FUNKCIJE ZA UKLANJANJE KORISNIKA
	void rewriteUsersFile(std::string userName);
	void rewriteCoursesFilesOrFriends(std::string userName, std::string folderName);
	void removeUserFolder(std::string userName);
};