#pragma once
#include "User.h"
#include "Lecturer.h"
#include <fstream>
#include <string>
#include <vector>

class Student : public User {
protected:

	//std::vector<bool(std::string)> predoncitions;

public:
	Student(std::string userName = "", std::string password = "");

	//METODA DA STUDENT PODNESE PRIJAVU DA BI SE PRIJAVIO NA ZELJENI KURS
	void signToCourse(std::string courseName) const noexcept(false);
	
	//OVU METODU KORISTI ADMINISTRATOR DA DIREKTNO DODA STUDENTA U KURS, JER IMA TU MOGUCNOST 
	void addStudentDirectlyToCourse(std::string courseName);

	//PREDAVAC AUTOMATSKI POSTAJE PRIJATELJ SA SVIM STUDENTIMA, KAO STO RECIMO NA BBB MOZEMO PISATI PROFESORIMA
	void automaticLecturerFriend(std::string) const;

protected:


private:
	//OVE 3 FUNKCIJE SU ZA PREDUSLOVE, TO NECU RADITI, NE VRIJEDI
	bool didListenCourse(std::string);
	bool howManyDidHeFinish(std::string, size_t);
	bool minimumGradeCondition();

	//PROVJERA DA LI JE STUDENT VEC POSLAO ZAHTJEV ZA PRIJATELJSTVO
	bool checkIfRequestIsAlreadyMade(std::string course, std::string name) const;

};