#include "Administrator.h"
#include "Lecturer.h"
#include "Student.h"
#include "Course.h"
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;
fs::path path = std::filesystem::current_path();

Administrator::Administrator(std::string userName, std::string password) : CoreUser(userName, password) {
	this->setType("Administrator");

	if (!checkIfUserIsAlreadyInAFile(userName)) {
		auto writeAdministrator = std::ofstream("./KORISNICI/Admin.txt", std::ios::out);
		this->setTypePassword(true);
		writeAdministrator << *this;
		writeAdministrator.close();
		this->setTypePassword(false);
		//auto writeUsers = std::ofstream("./KORISNICI/Korisnici.txt", std::ios::app | std::ios::out);
		//auto writePassword = std::ofstream("./KORISNICI/Sifre.txt", std::ios::app | std::ios::out);
		//this->typePassword = true;
		//writeUsers << *this;
		//this->typePassword = false;
		//writeUsers.close();
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
		std::cout << "Enter user name: " << std::endl;
		std::string userName, password, type; 
		std::getline(std::cin, userName, '\n');

		Student s(userName);

		if (!checkIfUserIsAlreadyInAFile(userName)) {
			throw std::exception("Can't add a user you didn't create!");
		}
		if (s.isGraded(courseName)) {
			throw std::exception("This student is already graded, so you can't add him/her to the course!");
		}

		//std::cout << "Enter password: " << std::endl;
		//std::getline(std::cin, password, '\n');
		std::cout << "Is it Student or Lecturer: " << std::endl;
		std::getline(std::cin, type, '\n');


		if (s.checkIfIsEitherStudentOrLecturer(courseName)) {
			throw std::exception("Person already exists in this course!");
		}

		if (type == "Lecturer") {
			//Lecturer l(userName, password);
			Lecturer l(userName, password);
			l.replaceLecturer(courseName);
			l.signLecturerToCourse(courseName);
		}
		else if (type == "Student") {
			Student s(userName, password);
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
		std::cout << "Enter existing user name or 'Lecturer' to remove lecturer: " << std::endl;
		std::string userName;
		std::getline(std::cin, userName, '\n');

		if (userName == "Lecturer") {
			auto writeOver = std::ofstream("./KURSEVI/" + courseName + "/PREDAVAC.txt", std::ios::out);
			writeOver.close();
			throw std::exception("Lecturer removed!");
		}

		if (!checkIfUserIsAlreadyInAFile(userName)) {
			throw std::exception("Can't remove user that doesn't exist!");
		}

		std::vector<Student> students;
		Lecturer lecturer;

		checkLecturer >> lecturer;
		checkLecturer.close();

		if (userName == "Lecturer") {
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
		/*std::cout << "Enter lecturer credentials: " << std::endl;
		std::string lecturerName, lecturerPassword;
		std::cout << "Enter lecturer name: " << std::endl;
		std::getline(std::cin, lecturerName, '\n');
		std::cout << "Enter lecturer password: " << std::endl;
		std::getline(std::cin, lecturerPassword, '\n');
		Lecturer r(lecturerName, lecturerPassword);*/
		Course c(courseName);

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


		fs::remove_all(path / "KURSEVI" / courseName);

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void Administrator::modifyCourses() {
	std::cout << "Which course do you want to modify: " << std::endl;
	std::string courseName;
	std::getline(std::cin, courseName, '\n');

	try {
		if (!doesCourseExist(courseName)) {
			throw std::exception("This course doesn't exist!");
		}

		std::cout << "Do you want to add, remove users from course or change course name ('1'/'2'/'3') : " << std::endl;
		std::string choice;
		std::getline(std::cin, choice, '\n');
		if (choice == "1") {
			this->addUserToCourse();
		}
		else if (choice == "2") {
			this->removeUserFromCourse();
		}
		else if (choice == "3") {
			std::string newCourseName;
			std::cout << "Enter new course name :" << std::endl;
			std::getline(std::cin, newCourseName, '\n');
			fs::rename(path / "KURSEVI" / courseName, path / "KURSEVI" /  newCourseName);
		}
		else {
			throw std::exception("Unknown option, sorry!");
		}

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void Administrator::modifyUsers() {
	std::cout << "Enter username of the user you want to modify: " << std::endl;
	std::string userName;
	std::getline(std::cin, userName, '\n');
	
	namespace fs = std::filesystem;

	fs::path path = std::filesystem::current_path();

	try {
		if (!checkUserName(userName)) {
			throw std::exception("User doesn't exist!");
		}

		std::cout << "Change password of this user: " << std::endl;
		std::cout << "Enter new password: " << std::endl;
		std::string answer;
		std::getline(std::cin, answer, '\n');
		std::vector<User> users;


		this->typePassword = true;
		
		auto openFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);

		while (openFile.good()) {
			User u;
			u.setTypePassword(true);
			openFile >> u;
			if (u.getUserName() == userName) {
				u.setPassword(answer);
				users.push_back(u);
			}
			else {
				users.push_back(u);
			}
		}
		openFile.close();

		for (auto elem : users) {
			auto writeNew = std::ofstream("./KORISNICI/Korisnici.txt", std::ios::out);
			if (writeNew) {
				//this->typePassword = true;
				for (auto elem : users) {
					elem.setTypePassword(true);
					writeNew << elem;
				}

				writeNew.close();
			}
		}
		this->typePassword = false;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

//DODAJEMO NOVOG KORISNIKA
void Administrator::addUser() {
	std::string userName;
	std::cout << "Enter user name for new user: " << std::endl;
	std::getline(std::cin, userName, '\n');
	try {
		if (checkIfUserIsAlreadyInAFile(userName)) {
			throw std::exception("Can't add user that already exists!");
		}

		std::cout << "Enter a password for new user: " << std::endl;
		std::string password;
		std::getline(std::cin, password, '\n');

		auto writeToFile = std::ofstream("./KORISNICI/Korisnici.txt", std::ios::out | std::ios::app);
		if (writeToFile) {
			User u(userName, password);
			u.setTypePassword(true);
			writeToFile << u;
			u.setTypePassword(false);
			writeToFile.close();
		}

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

//IZBACUJEMO KORISNIKA IZ SVIH MOGUCIH STAVKI, OSIM CHATOVA
void Administrator::removeUser() {
	std::string userName;
	std::cout << "Enter user name of the user you want to remove: " << std::endl;
	std::getline(std::cin, userName, '\n');

	try {
		if (!checkIfUserIsAlreadyInAFile(userName)) {
			throw std::exception("User doesn't exist, so you can't remove non-existing user!");
		}
		rewriteUsersFile(userName);
		rewriteCoursesFilesOrFriends(userName, "KURSEVI");
		rewriteCoursesFilesOrFriends(userName, "STUDENTI");
		removeUserFolder(userName);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

}

//PREPISUJEMO FAJL SA KORISNICIMA
void Administrator::rewriteUsersFile(std::string userName) {
	std::vector<User> users;
	auto readFile = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	if (readFile) {
		while (readFile.peek() != EOF) {
			User u;
			u.setTypePassword(true);
			readFile >> u;
			if (u.getUserName() != "" && u.getUserName() != userName) {
				u.setTypePassword(false);
				users.push_back(u);
			}
		}
		readFile.close();
	}

	auto rewriteUsersFile = std::ofstream("./KORISNICI/Korisnici.txt", std::ios::out);
	for (auto elem : users) {
		elem.setTypePassword(true);
		rewriteUsersFile << elem;
		elem.setTypePassword(false);
	}

	rewriteUsersFile.close();
}

//CHATOVI OSTAJU POSTOJECI, KAO STO SU NA DRUSTVENIM MREZAMA, SVE OSTALO SE BRISE
void Administrator::rewriteCoursesFilesOrFriends(std::string userName, std::string folderName) {
	for (auto const& entry : fs::directory_iterator(path / folderName)) {
		std::string subFolderName = entry.path().filename().string();

		if (subFolderName != "FRIENDREQUESTS.TXT" && subFolderName != "FRIENDS.TXT" && subFolderName != "CHATS") {
			for (auto const& entryIN : fs::directory_iterator(path / folderName / subFolderName)) {
				std::string fileName = entryIN.path().filename().string();
				auto readCourseFile = std::ifstream("./" + folderName + "/" + subFolderName + "/" + fileName, std::ios::in);
				std::vector<User> usersData;
				if (readCourseFile) {
					while (readCourseFile.peek() != EOF) {
						User u;
						readCourseFile >> u;
						if (u.getUserName() != "" && u.getUserName() != userName) {
							usersData.push_back(u);
						}
					}
					readCourseFile.close();
				}
				auto rewriteCourseFile = std::ofstream("./" + folderName + "/" + subFolderName + "/" + fileName, std::ios::out);
				for (auto elem : usersData) {
					rewriteCourseFile << elem;
				}
				rewriteCourseFile.close();
			}
		}	
	}
}

void Administrator::removeUserFolder(std::string userName) {
	fs::remove_all(path / "STUDENTI" / userName);
}

void Administrator::showAllUsers() const {
	auto readUsers = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	if (readUsers) {
		while (readUsers.peek() != EOF) {
			User u;
			readUsers >> u;
			if (u.getUserName() != "") {
				std::cout << u;
			}
		}
		readUsers.close();
	}
}
