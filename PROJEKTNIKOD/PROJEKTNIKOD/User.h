#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class User {
protected:
	std::string userName;
	std::string password;
	std::string type;
public:

	User(std::string userName = "", std::string password = "");
	std::string getUserName() const;
	std::string getPassword() const;
	std::string getType() const;

	friend std::istream& operator>>(std::ifstream& ifs, User& rhs)
	{
		char delim = ',';
		std::string type;
		std::getline(ifs, rhs.type, delim);
		std::getline(ifs, rhs.userName, delim);
		std::getline(ifs, rhs.password);
		//ifs.ignore();
		return ifs;
	}

	friend std::ostream& operator<<(std::ofstream& ofs, const User& rhs)
	{
		if (rhs.getUserName() != "" && rhs.getPassword() != "" && rhs.getType() != "") {
			return ofs << rhs.type << ',' << rhs.userName << ',' << rhs.password << std::endl;
		}
		return ofs;
	}

	friend std::ostream& operator<<(std::ostream& os, const User& rhs) {
		if (rhs.type != "" && rhs.userName != "" && rhs.password != "") {
			return os << rhs.type << ',' << rhs.userName << std::endl;
		}
		return os;
	}

	bool operator==(const User& other) const;
	bool operator!=(const User& other) const;
	//bool operator>(const User& other) const;
	bool operator<(const User& other) const;
	bool operator>=(const User& other) const;
	bool operator<=(const User& other) const;

	void checkInbox() const;
	void filterInbox() const;
	void textFriend(std::string friendName) const;
	bool checkIfIsLecturer(std::string courseName) const;
	bool checkIfIsEitherStudentOrLecturer(std::string courseName) const;
	bool checkUserName() const;
	void setUserName(std::string name);
protected:
	void setType(std::string type);

	std::vector<User> returnUsers();

	bool checkUserName(std::string name) const;

	bool checkIfUserIsAlreadyInAFile(std::string userName) const;

	//void setUserName(std::string name);
	void setPassword(std::string password);
};