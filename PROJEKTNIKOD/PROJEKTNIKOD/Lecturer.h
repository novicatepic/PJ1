#pragma once
#include "User.h"
#include "Student.h"
#include <string>
#include <iostream>


class Lecturer : public User {
private:

public:
	Lecturer(std::string userName = "", std::string password = "");

	//METODA ZA PREGLED ZAHTJEVA I UPIS JEDNOG STUDENTA NA KURS
	void signStudentToCourse(std::string courseName);

	//METODA DA SE KORISNIK UPISE NA KURS, KORISTI JE ISKLJUCIVO ADMINISTRATOR
	void signLecturerToCourse(std::string courseName);

	//ADMINISTRATOR KORISTI OVU METODU DA PREPISE FAJL SA PREDAVACEM UKOLIKO ZELI
	void replaceLecturer(std::string courseName) const;

	//UPIS OCJENE STUDENTU
	void writeGrade() const;

	//NEPOTREBNA METODA, NE RADIM CETVRTU STAVKU
	void finishedListening() const;

	//PRIKAZ STUDENATA U JEDNOM KURSU
	void showStudentInCourse(std::string courseName) const;
public:
	//POMOCNE FUNKCIJE DA SE VIDI KOLIKO STUDENATA I KOLIKO PREDAVACA IMA
	//IMPLEMENTACIJA U Lecturer.cpp
	//POMOCNE SAMO ZA ISPIS U MAINU, NEBITNE FUNKCIJE
	friend size_t howManyStudents(std::string courseName);
	friend size_t howManyLecturers(std::string courseName);
};


