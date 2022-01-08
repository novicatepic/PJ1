#include <iostream>
#include "Student.h"
#include "User.h"
#include "Lecturer.h"
#include "Course.h"
#include "Administrator.h"
#include <fstream>

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
	Student st("Marko", "Markovic");

	//st.signToCourse("Programiranje");
	//Course c("Programiranje");
	//Lecturer l;
	//l.signStudentToCourse("Programiranje");
	
	Student s2("Janko", "Jankovic");
	//st.sendFriendRequest("Janko");
	//s2.checkFriendRequests();
	//st.textFriend("Janko");
	Lecturer l("Zoren", "12345");
	Lecturer l2("Markan", "222");

	//User u = sign();

	//User u;

	//u = sign();
	//Student s(u.getUserName(), u.getPassword());
	//s.checkInbox();

	//l.signLecturerToCourse("Programiranje");

	//s2.checkInbox();

	Course c("Matematika");
	st.signToCourse("Matematika");
	//l.signStudentToCourse("Matematika");

	//std::cin.ignore();
	//st.textFriend(l.getUserName());
	//std::cin.ignore();

	//l.checkInbox();
	
	//l.textFriend(st.getUserName());

	//st.checkInbox();

	Administrator a;
	a.removeCourse();

	return 0;
}