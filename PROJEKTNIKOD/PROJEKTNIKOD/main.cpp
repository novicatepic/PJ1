#include <iostream>
#include "Student.h"
#include "User.h"
#include "Lecturer.h"
#include "Course.h"
#include "Administrator.h"
#include <fstream>
#include <filesystem>

auto sign() {
	auto readUsers = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	if (readUsers) {
		std::string userName, pass;
		std::cout << "Enter user name :" << std::endl;
		std::cin >> userName;
		std::cout << "Enter password: " << std::endl;
		std::cin >> pass;

		try {
			while (readUsers.good()) {
				User u;
				readUsers >> u;
				if (u.getUserName() == userName && u.getPassword() == pass && u.getUserName() != "") {
					readUsers.close();
					return u;
				}
			}
			throw std::exception("Your account doesn't exist, sorry");
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			readUsers.close();
			User u;
			return u;
		}
	}
}

int main() {
	Student s("Novica", "12345");
	//s.sendFriendRequest("Janko");
	Student j("Janko", "Jankovic");
	//j.checkFriendRequests();
	//j.checkInbox();
	//j.textFriend("Novica");
	//s.checkInbox();
	//s.textFriend("Zoran");
	//Student s("Novica", "12345")
	Student newSt("Igor", "111");
	Student makeNew("Jovan", "122");
	//newSt.signToCourse()
	//Lecturer l("Novica", "22222");
	//Course c("Programiranje", l);
	
	//j.signToCourse("Programiranje");
	//l.signStudentToCourse("Programiranje");

	//Course cNew("OET", l);
	//j.signToCourse("OET");
	//l.signStudentToCourse("OET");

	Administrator a("Jovan", "21321");

	a.modifyUsers();

	//a.addNewCourse();

	//a.removeCourse();

	//a.addUserToCourse();

	//a.removeUserFromCourse();

	//l.signLecturerToCourse("Programiranje");
	Lecturer r("Drazen", "8432");
	//r.signLecturerToCourse("Programiranje");
	/*namespace fs = std::filesystem;
	fs::path path = std::filesystem::current_path() / "KURSEVI";
	for (auto const& entry : fs::directory_iterator(path)) {
		std::cout << entry.path().filename() << std::endl;
	}*/

	Course kurs("SPA");
	newSt.addStudentDirectlyToCourse("SPA");
	//Course kurs2("OSI");
	//r.signLecturerToCourse("OSI");
	//s.addStudentDirectlyToCourse("OSI");
	//newSt.addStudentDirectlyToCourse("OSI");
	//std::set<Student> rez = kurs.findUnionIntersectionDifference();

	//for (auto elem : rez)
		//std::cout << elem;

	//s.textFriend("Janko");
	//j.filterInbox();

	//r.signLecturerToCourse("SPA");
	//s.addStudentDirectlyToCourse("SPA");
	//r.writeGrade("SPA");

	//Student sprim("Cak", "Noris");
	//sprim.addStudentDirectlyToCourse("OSI");

	return 0;
}