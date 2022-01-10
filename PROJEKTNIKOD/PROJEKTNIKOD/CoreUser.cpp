#include "CoreUser.h"
#include <iostream>
#include <fstream>
#include <filesystem>

CoreUser::CoreUser(std::string userName, std::string password) : userName(userName), password(password) {
	auto makeUsersFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	//auto makeStudent

	if (!makeUsersFile) {
		namespace fs = std::filesystem;
		fs::path path = std::filesystem::current_path();
		fs::path userFolder = path / "KORISNICI";
		create_directory(userFolder);

		std::ofstream("./KORISNICI/Korisnici.txt", std::ios::out);

		fs::path studentSubfolder = path / "STUDENTI";
		create_directory(studentSubfolder);
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
	}

	readUsers.close();
	return false;
}


bool CoreUser::checkUserName() const {
	auto credentialsFile = std::ifstream("./KORISNICI/" + this->userName + "/Korisnici.txt");
	if (credentialsFile) {
		while (credentialsFile.good()) {
			CoreUser u;
			credentialsFile >> u;
			if (u.getUserName() == this->userName) {
				return true;
			}
		}
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
