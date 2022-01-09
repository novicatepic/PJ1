#include "Administrator.h"
#include "Lecturer.h"
#include "Student.h"
#include "Course.h"
#include <filesystem>
#include <vector>

Administrator::Administrator(std::string userName, std::string password) : User(userName, password) {
	this->setType("Administrator");
	auto open = std::ifstream("./STUDENTI/" + this->userName + "/" + "FRIENDS.TXT");
	if (!open) {
		namespace fs = std::filesystem;
		fs::path path = std::filesystem::current_path();
		fs::path adminSubfolderPath = path / "STUDENTI" / this->userName;
		//fs::path chatPath = path / "STUDENTI" / this->userName / "CHATS";
		create_directory(adminSubfolderPath);
	}
	
	if (!checkIfUserIsAlreadyInAFile(userName, password, "Administrator")) {
		auto writeUsers = std::ofstream("./KORISNICI/Korisnici.txt", std::ios::app | std::ios::out);
		writeUsers << *this;
		writeUsers.close();
	}
}

void Administrator::addUserToCourse() {
	std::string courseName;
	std::cout << "Enter course name" << std::endl;
	std::getline(std::cin, courseName, '\n');
	
	auto checkCourse = std::ifstream("./KURSEVI/" + courseName + "/STUDENTI.txt");

	try {
		if (!checkCourse) {
			throw std::exception("Course doesn't exist!");
		}
		checkCourse.close();
		std::cout << "Enter new user name: " << std::endl;
		std::string userName, password, type; 
		std::getline(std::cin, userName, '\n');
		std::cout << "Enter password: " << std::endl;
		std::getline(std::cin, password, '\n');
		std::cout << "Is it Student or Lecturer: " << std::endl;
		std::getline(std::cin, type, '\n');
		if (type == "Lecturer") {
			//Lecturer l(userName, password);
			Lecturer l(userName, password);
			l.replaceLecturer(courseName);
			l.signLecturerToCourse(courseName);
			//POTREBNO IMPLEMENTIRATI DA SE OBRISE POSTOJECI LECTURER, I OVAJ GA ZAMIJENI
		}
		else if (type == "Student") {
			Student s(userName, password);
			//s.signToCourse(courseName);
			//POTREBNA METODA DA SE DIREKTNO DODA STUDENT U FAJL, BEZ SLANJA ZAHTJEVA
			s.addStudentDirectlyToCourse(courseName);
		}
		else {
			throw std::exception("Type has to be either Student or Lecturer!");
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}


}


//IZBJECI DUPLIRANJE KODA
void Administrator::removeUserFromCourse() {
	std::string courseName;
	std::cout << "Enter course name" << std::endl;
	std::getline(std::cin, courseName, '\n');

	auto checkCourse = std::ifstream("./KURSEVI/" + courseName + "/STUDENTI.txt");
	auto checkLecturer = std::ifstream("./KURSEVI/" + courseName + "/PREDAVAC.txt");

	try {
		if (!checkCourse) {
			throw std::exception("Course doesn't exist!");
		}
		//checkCourse.close();
		std::cout << "Enter existing user name: " << std::endl;
		std::string userName;
		std::getline(std::cin, userName, '\n');

		std::vector<Student> students;
		Lecturer lecturer;

		checkLecturer >> lecturer;
		checkLecturer.close();

		if (lecturer.getUserName() == userName) {
			auto writeOver = std::ofstream("./KURSEVI/" + courseName + "/PREDAVAC.txt", std::ios::out);
			writeOver.close();
		}
		else {
			while (checkCourse.good()) {
				Student st;
				checkCourse >> st;
				students.push_back(st);
			}
			checkCourse.close();
			auto rewriteCourseStudents = std::ofstream("./KURSEVI/" + courseName + "/STUDENTI.txt", std::ios::out);
			for (auto elem : students) {
				if (elem.getUserName() != userName && elem.getUserName() != "") {
					rewriteCourseStudents << elem;
				}
			}
			rewriteCourseStudents.close();
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void Administrator::addNewCourse() {
	std::string courseName;
	std::cout << "Enter new course name: " << std::endl;
	std::getline(std::cin, courseName, '\n');

	try {
		if (doesCourseExist(courseName)) {
			throw std::exception("Course already exists!");
		}
		std::cout << "Enter lecturer credentials: " << std::endl;
		std::string lecturerName, lecturerPassword;
		std::cout << "Enter lecturer name: " << std::endl;
		std::getline(std::cin, lecturerName, '\n');
		std::cout << "Enter lecturer password: " << std::endl;
		std::getline(std::cin, lecturerPassword, '\n');
		Lecturer r(lecturerName, lecturerPassword);
		Course c(courseName, r);

		//r.signLecturerToCourse(courseName);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void Administrator::removeCourse() {
	std::string courseName;
	std::cout << "Enter name of the course you want to remove: " << std::endl;
	std::getline(std::cin, courseName, '\n');

	try {
		if (!doesCourseExist(courseName)) {
			throw std::exception("No course exists, cannot be removed!");
		}

		namespace fs = std::filesystem;
		fs::path path = std::filesystem::current_path();



		fs::remove_all(path / "KURSEVI" / courseName);

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

bool Administrator::doesCourseExist(std::string courseName) {
	namespace fs = std::filesystem;
	fs::path path = std::filesystem::current_path();

	for (auto const& entry : fs::directory_iterator(path / "KURSEVI")) {
		if (entry.path().filename() == courseName)
			return true;
	}

	return false;
}