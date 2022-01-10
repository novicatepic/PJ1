#include <iostream>
#include "Student.h"
#include "User.h"
#include "Lecturer.h"
#include "Course.h"
#include "CoreUser.h"
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
				CoreUser u;
				u.setTypePassword(true);
				readUsers >> u;
				if (u.getUserName() == userName && u.getPassword() == pass && u.getUserName() != "") {
					readUsers.close();
					u.setTypePassword(false);
					return u;
				}
				u.setTypePassword(false);
			}
			throw std::exception("Your account doesn't exist, sorry");
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			readUsers.close();
			CoreUser u;
			return u;
		}
	}
}

int main() {



	Student s("Novica", "12345");
	//s.sendFriendRequest("Janko");
	Student j("Janko", "Jankovic");
	//Student r("Janko", "sadas");
	//s.sendFriendRequest("Janko");
	//s.textFriend("Janko");
	//j.checkInbox();
	//j.checkFriendRequests();
	//j.checkFriendRequests();
	//j.checkInbox();
	//j.textFriend("Novica");
	//s.checkInbox();
	//s.textFriend("Zoran");
	//Student s("Novica", "12345")
	//Student newSt("Igor", "111");
	Student makeNew("Jovan", "122");
	Course c("OET");
	//makeNew.signToCourse("OET");
	Lecturer l("Zoran", "22222");
	//l.signLecturerToCourse("OET");
	//l.signStudentToCourse("OET");
	//Course c1("Programiranje");
	//makeNew.signToCourse("OET");
	//j.signToCourse("Programiranje");
	//l.signStudentToCourse("Programiranje");
	Administrator a("Mrkela", "Dorat");
	
	//a.addUserToCourse();
	//Lecturer lr = c.returnLecturer();
	//std::cout << lr.getUserName();
	//a.removeCourse();
	//a.addUserToCourse();
	//a.removeUserFromCourse();

	//a.addNewCourse();
	//a.modifyUsers();

	//Course cNew("OET", l);
	//j.signToCourse("OET");
	//l.signStudentToCourse("OET");

	//Administrator a("Jovan", "21321");

	//a.modifyUsers();

	//a.addNewCourse();

	//a.removeCourse();

	//a.addUserToCourse();

	//a.removeUserFromCourse();

	//l.signLecturerToCourse("Programiranje");
	//Lecturer r("Drazen", "8432");
	//r.signLecturerToCourse("Programiranje");
	/*namespace fs = std::filesystem;
	fs::path path = std::filesystem::current_path() / "KURSEVI";
	for (auto const& entry : fs::directory_iterator(path)) {
		std::cout << entry.path().filename() << std::endl;
	}*/

	//Course kurs("SPA");
	//newSt.addStudentDirectlyToCourse("SPA");
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