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
	bool typePassword = false;
public:

	User(std::string userName = "", std::string password = "");
	std::string getUserName() const;
	std::string getPassword() const;
	std::string getType() const;
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
	void setPassword(std::string password);
	void setTypePassword(bool typePassword);



	friend std::istream& operator>>(std::ifstream& ifs, User& rhs)
	{
		if (rhs.typePassword) {
			char delim = ',';
			//std::getline(ifs, rhs.type, delim);
			std::getline(ifs, rhs.userName, delim);
			std::getline(ifs, rhs.password, '\n');
			//ifs.ignore();
			return ifs;
		}
		else {
			char delim = ',';
			//std::getline(ifs, rhs.type, delim);
			std::getline(ifs, rhs.userName, '\n');
			return ifs;
		}
	}

	friend std::ostream& operator<<(std::ofstream& ofs, const User& rhs)
	{
		if (rhs.typePassword) {
			if (rhs.getUserName() != "" && rhs.getPassword() != "") {
				return ofs << rhs.userName << ',' << rhs.password << std::endl;
			}
		}
		else {
			if (rhs.getUserName() != "") {
				return ofs << rhs.userName << std::endl;
			}
		}
		return ofs;
	}

	friend std::ostream& operator<<(std::ostream& os, const User& rhs) {
		return os << rhs.userName << std::endl;
		return os;
	}

protected:
	void setType(std::string type);

	std::vector<User> returnUsers();

	bool checkUserName(std::string name) const;

	bool checkIfUserIsAlreadyInAFile(std::string userName) const;

	//void setUserName(std::string name);

};