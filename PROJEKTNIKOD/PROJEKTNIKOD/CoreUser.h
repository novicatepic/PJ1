#pragma once
#include <iostream>
#include <string>
#include <fstream>

class CoreUser {
protected:
	std::string userName;
	std::string password;
	bool typePassword = false;
	//TIP, DA LI JE PREDAVAC ILI STUDENT
	//BESPOTREBNO, TO JE BILA POCETNA IMPLEMENTACIJA
	std::string type;
public:
	CoreUser(std::string userName = "", std::string password = "");

	//GETTERI
	std::string getUserName() const;
	std::string getPassword() const;
	std::string getType() const;

	//SETTERI
	void setUserName(std::string name);
	void setPassword(std::string password);
	void setTypePassword(bool typePassword);
	void setType(std::string type);

	//PROVJERA DA LI JE OSOBA ILI STUDENT ILI PREDAVAC NA KURSU, BITNO KOD DODAVANJA
	bool checkIfIsEitherStudentOrLecturer(std::string courseName) const;

	//PRIKAZ KURSEVA KOJE POHADJA STUDENT
	void showCourses() const;

	//PRIKAZ SVIH PRIJATELJA STUDENTA/PREDAVACA
	void showFriends() const;

	//PRIKAZ SVIH KORISNIKA
	void showAllUsers() const;

	//PRIKAZ SVIH KURSEVA NA SISTEMU
	void listCourses() const;

	//PROVJERA DA LI JE KORISNIK PREDAVAC NA NEKOM KURSU
	bool checkIfIsLecturer(std::string courseName) const;

	//PROVJERA DA LI KURS POSTOJI
	bool doesCourseExist(std::string courseName);

	//PROVJERA DA LI JE STUDENT OCIJENJEN NA KURSU
	bool isGraded(std::string courseName) const;


	//PREKLOPLJEN OPERATOR ZA CITANJE IZ FAJLA
	//TYPEPASSWORD SETOVANO NA TRUE OMOGUCAVA CITANJE LOZINKE ADMINISTRATORU
	//U SUPROTNOM SE LOZINKA NE ISCITAVA
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

	//UPIS U FAJL
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

	//ISPIS NA IZLAZNI TOK
	friend std::ostream& operator<<(std::ostream& os, const CoreUser& rhs) {
		if (rhs.typePassword) {
			 os << rhs.userName << ', ' << rhs.password << std::endl;
		}
		else {
			os << rhs.userName << std::endl;
		}
		return os;

	}

	//PROVJERA DA LI JE KORISNIK ADMINISTRATOR U SISTEMU
	bool checkIfIsAdmin(std::string name) const;



protected:



	//PROVJERA DA LI KORISNIK POSTOJI U SISTEMU
	bool checkUserName() const;

	bool checkIfUserIsAlreadyInAFile(std::string userName) const;
	bool checkUserName(std::string name) const;

};