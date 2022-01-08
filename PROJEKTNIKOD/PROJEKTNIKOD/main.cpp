#include <iostream>
#include "Student.h"
#include "User.h"
#include "Lecturer.h"
#include "Course.h"
#include <fstream>

int main() {
	Student st("Marko", "Markovic");
	auto upisi = std::ofstream("./KURSEVI/STUDENTI.txt", std::ios::out);
	upisi << st;
	upisi << st;
	upisi << st;
	upisi.close();
	auto citaj = std::ifstream("./KURSEVI/STUDENTI.txt", std::ios::in);
	citaj.close();
	/*while (citaj.good()) {
		citaj >> s2;
		std::cout << s2.getUserName() << s2.getPassword();
		std::cout << std::endl;
	}*/

	//st.signToCourse("Programiranje");
	//Course c("Programiranje");
	//Lecturer l;
	//l.signStudentToCourse("Programiranje");
	
	Student s2("Janko", "Jankovic");
	st.sendFriendRequest("Janko");

	return 0;
}