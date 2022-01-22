#pragma once
#include "CoreUser.h"
#include "Student.h"

//TAKODJE DA SE NE BI DUPLIRAO KOD U MEJNU
//JER KORISNIK BIRA NA KOJEM CE KURSU RADITI
//AKO JE STUDENT NA TOM KURSU, BICE MU PONUDJENE OPCIJE ZA STUDENTA
//U SUPROTNOM, AKO NIJE STUDENT NA TOM KURSU, NUDE MU SE OPCIJE KOJE STUDENT IMA
//ZATO BI BILO DUPLIRANJE KODA

std::string internOption;
void helpForStudentFunc(std::string userName) {
	do {

		CoreUser userSign(userName);
		/*std::cout << "List of courses you attend or are a lecturer in: " << std::endl;
		userSign.showCourses();
		std::cout << "List of your friends: " << std::endl;
		userSign.showFriends();*/
		Student s(userSign.getUserName());
		std::cout << "Your options: " << std::endl;
		std::cout << "--logout to log out" << std::endl;
		std::cout << "[1] to check inbox" << std::endl;
		std::cout << "WARNING: if you are going to check inbox, those messages won't be there for filtering" << std::endl;
		std::cout << "[2] to filter inbox" << std::endl;
		std::cout << "[3] to text friend" << std::endl;
		std::cout << "[4] to check friend requests" << std::endl;
		std::cout << "[5] to send friend request" << std::endl;
		std::cout << "[6] to sign to a course" << std::endl;
		std::cout << "[7] to see chat history" << std::endl;
		std::getline(std::cin, internOption, '\n');
		if (internOption == "1") {
			s.checkInbox();
		}
		else if (internOption == "2") {
			s.filterInbox();
		}
		else if (internOption == "3") {
			std::cout << "Your friends: " << std::endl;
			s.showFriends();
			std::cout << "Enter friend name you want to text: " << std::endl;
			std::string friendName;
			std::getline(std::cin, friendName, '\n');
			s.textFriend(friendName);
		}
		else if (internOption == "4") {
			s.checkFriendRequests();
		}
		else if (internOption == "5") {
			std::cout << "All users on this system: " << std::endl;
			s.showAllUsers();
			std::cout << "Enter name of a person you want to be your friend: " << std::endl;
			std::string potentialFriendName;
			std::getline(std::cin, potentialFriendName, '\n');
			s.sendFriendRequest(potentialFriendName);
		}
		else if (internOption == "6") {
			std::cout << "Here are the courses: " << std::endl;
			s.listCourses();
			std::cout << "Enter a course name you want to sign in :" << std::endl;
			std::string courseName;
			std::getline(std::cin, courseName, '\n');
			s.signToCourse(courseName);
		}
		else if (internOption == "7") {
			s.printChatWithFriend();
		}

	} while (internOption != "--logout");
}
