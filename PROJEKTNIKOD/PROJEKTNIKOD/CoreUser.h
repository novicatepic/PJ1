#pragma once
#include <iostream>
#include <string>
#include <fstream>

class CoreUser {
protected:
	std::string userName;
	std::string password;
	bool typePassword = false;
	std::string type;
public:
	CoreUser(std::string userName = "", std::string password = "");

	std::string getUserName() const;
	std::string getPassword() const;
	std::string getType() const;
	void setUserName(std::string name);
	void setPassword(std::string password);
	void setTypePassword(bool typePassword);
	void setType(std::string type);
	bool checkIfIsEitherStudentOrLecturer(std::string courseName) const;
	void showCourses() const;
	void showFriends() const;
	void showAllUsers() const;
	void listCourses() const;
	bool checkIfIsLecturer(std::string courseName) const;
	bool doesCourseExist(std::string courseName);

	friend std::istream& operator>>(std::ifstream& ifs, CoreUser& rhs)
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

	friend std::ostream& operator<<(std::ofstream& ofs, const CoreUser& rhs)
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

	friend std::ostream& operator<<(std::ostream& os, const CoreUser& rhs) {
		if (rhs.typePassword) {
			 os << rhs.userName << ', ' << rhs.password << std::endl;
		}
		else {
			os << rhs.userName << std::endl;
		}
		return os;

	}

	bool checkIfIsAdmin(std::string name) const;

protected:
	bool checkUserName() const;
	bool checkIfUserIsAlreadyInAFile(std::string userName) const;
	bool checkUserName(std::string name) const;


private:

};