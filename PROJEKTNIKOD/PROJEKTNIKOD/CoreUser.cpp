#include "CoreUser.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

CoreUser::CoreUser(std::string userName, std::string password) : userName(userName), password(password) {
	auto makeUsersFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	//auto makeStudent

	if (!makeUsersFile) {

		fs::path path = std::filesystem::current_path();
		fs::path userFolder = path / "KORISNICI";
		create_directory(userFolder);
		std::ofstream("./KORISNICI/Korisnici.txt", std::ios::out);

		fs::path studentSubfolder = path / "STUDENTI";
		create_directory(studentSubfolder);

		fs::path coursesSubFolder = path / "KURSEVI";
		create_directory(coursesSubFolder);
	}
}

bool CoreUser::checkIfUserIsAlreadyInAFile(std::string userName) const {
	auto readUsers = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);

	if (readUsers) {
		while (readUsers.good()) {
			CoreUser u;
			u.setTypePassword(true);
			readUsers >> u;
			if (u.getUserName() == userName) {
				u.setTypePassword(false);
				readUsers.close();
				return true;
			}
			u.setTypePassword(false);
		}
		readUsers.close();
	}

	//auto readUsers = std::ifstream("./KORISNICI/Admin.txt", std::ios::in);
	auto credentialsFile = std::ifstream("./KORISNICI/Admin.txt", std::ios::in);
	if (credentialsFile) {
		CoreUser u;
		u.setTypePassword(true);
		credentialsFile >> u;
		if (u.getUserName() == userName) {
			u.setTypePassword(false);
			return true;
		}
		u.setTypePassword(false);
		credentialsFile.close();
	}

	return false;
}


bool CoreUser::checkUserName() const {
	auto credentialsFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	if (credentialsFile) {
		while (credentialsFile.good()) {
			CoreUser u;
			u.setTypePassword(true);
			credentialsFile >> u;
			if (u.getUserName() == this->userName) {
				u.setTypePassword(false);
				return true;
			}
			u.setTypePassword(false);
		}
		credentialsFile.close();
	}

	credentialsFile = std::ifstream("./KORISNICI/Admin.txt", std::ios::in);
	if (credentialsFile) {
		CoreUser u;
		u.setTypePassword(true);
		credentialsFile >> u;
		if (u.getUserName() == this->userName) {
			u.setTypePassword(false);
			return true;
		}
		u.setTypePassword(false);
		credentialsFile.close();
	}

	return false;
}

bool CoreUser::checkUserName(std::string name) const {
	auto credentialsFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	while (credentialsFile.good()) {
		CoreUser u;
		u.setTypePassword(true);
		credentialsFile >> u;
		if (u.getUserName() == name) {
			u.setTypePassword(false);
			return true;
		}
		u.setTypePassword(false);
	}
	credentialsFile.close();

	credentialsFile = std::ifstream("./KORISNICI/Admin.txt", std::ios::in);
	if (credentialsFile) {
		CoreUser u;
		u.setTypePassword(true);
		credentialsFile >> u;
		if (u.getUserName() == name) {
			u.setTypePassword(false);
			return true;
		}
		u.setTypePassword(false);
		credentialsFile.close();
	}

	return false;
}

bool CoreUser::checkIfIsEitherStudentOrLecturer(std::string courseName) const {
	auto courseFile = std::ifstream("./KURSEVI/" + courseName + "/STUDENTI.txt");

	if (courseFile) {
		while (courseFile.good()) {
			CoreUser u;
			courseFile >> u;
			if (u.getUserName() == this->userName)
				return true;
		}
	}

	courseFile.close();

	if (checkIfIsLecturer(courseName) == true)
		return true;

	return false;

}


bool CoreUser::checkIfIsLecturer(std::string courseName) const {
	auto courseFile = std::ifstream("./KURSEVI/" + courseName + "/PREDAVAC.txt");

	if (courseFile) {
		CoreUser p;
		courseFile >> p;
		if (p.getUserName() == this->userName) {
			return true;
		}
	}

	courseFile.close();

	return false;
}

std::string CoreUser::getUserName() const {
	return this->userName;
}

std::string CoreUser::getPassword() const {
	return this->password;
}

std::string CoreUser::getType() const {
	return this->type;
}

void CoreUser::setUserName(std::string name) {
	this->userName = name;
}

void CoreUser::setPassword(std::string password) {
	this->password = password;
}


void CoreUser::setTypePassword(bool typePassword) {
	this->typePassword = typePassword;
}

void CoreUser::setType(std::string type) {
	this->type = type;
}


bool CoreUser::doesCourseExist(std::string courseName) {
	namespace fs = std::filesystem;
	fs::path path = std::filesystem::current_path();

	for (auto const& entry : fs::directory_iterator(path / "KURSEVI")) {
		if (entry.path().filename() == courseName)
			return true;
	}

	return false;
}

void CoreUser::showCourses() const {
	fs::path path = std::filesystem::current_path();

	for (auto const& entry : fs::directory_iterator(path / "KURSEVI")) {
		std::string subFolderName = entry.path().filename().string();

		if (subFolderName != "FRIENDREQUESTS.TXT" && subFolderName != "FRIENDS.TXT") {
			for (auto const& entryIN : fs::directory_iterator(path / "KURSEVI" / subFolderName)) {
				std::string fileName = entryIN.path().filename().string();
				auto readCourseFile = std::ifstream("./KURSEVI/" + subFolderName + "/" + fileName, std::ios::in);
				if (readCourseFile) {
					while (readCourseFile.peek() != EOF) {
						CoreUser u;
						readCourseFile >> u;
						if (u.getUserName() == this->userName) {
							if (fileName == "PREDAVAC.txt") {
								std::cout << "You are a lecturer in course " + subFolderName << std::endl;
							}
							else if (fileName == "STUDENTI.txt") {
								std::cout << "You are a student in course " + subFolderName << std::endl;
							}
						}
					}
				}
			}
		}
	}
}

void CoreUser::showFriends() const {
	auto readFriends = std::ifstream("./STUDENTI/" + this->userName + "/FRIENDS.txt", std::ios::in);
	if (readFriends) {
		while (readFriends.good()) {
			CoreUser u;
			readFriends >> u;
			if (u.getUserName() != "") {
				std::cout << u.getUserName() << std::endl;
			}
		}
		readFriends.close();
	}
}

bool CoreUser::checkIfIsAdmin(std::string name) const {
	auto readAdmin = std::ifstream("./KORISNICI/Admin.txt", std::ios::in);
	if (readAdmin) {
		CoreUser u;
		u.setTypePassword(true);
		readAdmin >> u;

		if (u.getUserName() == name) {
			u.setTypePassword(false);
			return true;
		}
		u.setTypePassword(false);
		readAdmin.close();
	}

	return false;
}

void CoreUser::showAllUsers() const {
	auto showUsersFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	if (showUsersFile) {
		while (showUsersFile.peek() != EOF) {
			CoreUser core;
			core.setTypePassword(true);
			showUsersFile >> core;
			if (core.getUserName() != this->userName) {
				std::cout << core.getUserName() << std::endl;
			}
			core.setTypePassword(false);
		}
		showUsersFile.close();
	}
}

void CoreUser::listCourses() const {
	fs::path path = std::filesystem::current_path();

	for (auto const& entry : fs::directory_iterator(path / "KURSEVI")) 
		std::cout << entry.path().filename() << std::endl;
}

bool CoreUser::isGraded(std::string courseName) const {
	auto openCourseFile = std::ifstream("./KURSEVI/" + courseName + "/POLOZILI.txt", std::ios::in);
	if (openCourseFile) {
		while (openCourseFile.good()) {
			CoreUser readUser;
			openCourseFile >> readUser;
			if (readUser.getUserName() != "" && readUser.getUserName() == this->userName) {
				return true;
			}
		}

		openCourseFile.close();
	}

	return false;
}