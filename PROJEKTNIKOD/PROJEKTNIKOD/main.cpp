#include <iostream>
#include "Student.h"
#include "User.h"
#include "Lecturer.h"
#include "Course.h"
#include "CoreUser.h"
#include "Administrator.h"
#include <fstream>
#include <filesystem>
#include "HelpFileForAdministrator.h"
#include "HelpForStudent.h"

auto sign() {
	auto readUsers = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);
	if (readUsers) {
		std::string userName, pass;
		std::cout << "Enter user name :" << std::endl;
		//std::cin >> userName;
		std::getline(std::cin, userName, '\n');
		std::cout << "Enter password: " << std::endl;
		std::getline(std::cin, pass, '\n');

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
			readUsers.close();
			readUsers = std::ifstream("./KORISNICI/Admin.txt", std::ios::in);
			CoreUser admin;
			admin.setTypePassword(true);
			readUsers >> admin;
			if (admin.getUserName() == userName && admin.getPassword() == pass) {
				readUsers.close();
				admin.setTypePassword(false);
				return admin;
			}
			admin.setTypePassword(false);
			readUsers.close();
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
	//CoreUser a;

	auto openFileForTheFirstTime = std::ifstream("./KORISNICI/Korisnici.txt", std::ios::in);

	if (openFileForTheFirstTime) {
		std::string option;
		do {
			std::cout << "--exit to finish this program, anything else to continue working: " << std::endl;
			std::getline(std::cin, option, '\n');

			if (option == "--exit") {
				break;
			}

			CoreUser userSign = sign();
			if (userSign.getUserName() != "") {	
				std::string userCourseInput;
				if (!userSign.checkIfIsAdmin(userSign.getUserName())) {
					std::cout << "List of courses you attend or are a lecturer in: " << std::endl;
					userSign.showCourses();
					std::cout << "List of your friends: " << std::endl;
					userSign.showFriends();
					std::cout << "Pick a course you wanna work on: " << std::endl;
					std::getline(std::cin, userCourseInput, '\n');

				}			
				if (userSign.checkIfIsLecturer(userCourseInput)) {
					std::string internOption;
					do {
						Lecturer l(userSign.getUserName());
						std::cout << "Your options: " << std::endl;
						std::cout << "--logout to log out" << std::endl;
						std::cout << "[0] to check requests and sign student to course " + userCourseInput << std::endl;
						std::cout << "[1] to list students in course" + userCourseInput << std::endl;
						std::cout << "[2] to write grade to a student" << std::endl;
						std::cout << "[3] to check inbox" << std::endl;
						std::cout << "WARNING: if you are going to check inbox, those messages won't be there for filtering" << std::endl;
						std::cout << "[4] to filter inbox" << std::endl;
						std::cout << "[5] to text friend" << std::endl;
						std::cout << "[6] to check friend requests" << std::endl;
						std::cout << "[7] to send friend request" << std::endl;
						std::cout << "[8] to see chat history with someone" << std::endl;
						std::cout << "Enter your option: " << std::endl;
						std::getline(std::cin, internOption, '\n');
						if (internOption == "0") {
							l.signStudentToCourse(userCourseInput);
						}
						else if (internOption == "1") {
							l.showStudentInCourse(userCourseInput);
						}
						else if (internOption == "2") {
							l.writeGrade();
						}
						else if (internOption == "3") {
							l.checkInbox();
						}
						else if (internOption == "4") {
							l.filterInbox();
						}
						else if (internOption == "5") {
							std::cout << "Your friends: " << std::endl;
							l.showFriends();
							std::cout << "Enter friend name you want to text: " << std::endl;
							std::string friendName;
							std::getline(std::cin, friendName, '\n');
							l.textFriend(friendName);
						}
						else if (internOption == "6") {
							l.checkFriendRequests();
						}
						else if (internOption == "7") {
							std::cout << "All users on this system: " << std::endl;
							l.showAllUsers();
							std::cout << "Enter name of a person you want to be your friend: " << std::endl;
							std::string potentialFriendName;
							std::getline(std::cin, potentialFriendName, '\n');
							l.sendFriendRequest(potentialFriendName);
						}
						else if (internOption == "8") {
							l.printChatWithFriend();
						}
						else if (internOption == "--logout") {

						}
						else {
							std::cout << "Wrong option, try again!" << std::endl;
						}
					} while (internOption != "--logout");
				}
				else if (userSign.checkIfIsEitherStudentOrLecturer(userCourseInput)) {
					std::string internOption;
					helpForStudentFunc(userSign.getUserName());
				}
				else if (userSign.checkIfIsAdmin(userSign.getUserName())) {
					administratorMainWork(userSign.getUserName(), userSign.getPassword());
				}
				else if (userSign.getUserName() != "") {
					std::cout << "You aren't on this course, but here are your options: " << std::endl;
					std::string internOption;
					helpForStudentFunc(userSign.getUserName());
				}
				else if (option == "--exit") {

				}
				else {
					std::cout << "Your account doesn't exist" << std::endl;
				}
			}
		} while (option != "--exit");
		
	}
	else {
		std::cout << "First entry to this system, creating only administrator: " << std::endl;
		std::cout << "Enter username: " << std::endl;
		std::string userName, password;
		std::getline(std::cin, userName, '\n');
		std::cout << "Enter password: " << std::endl;
		std::getline(std::cin, password, '\n');
		//Administrator admin(userName, password);
		administratorMainWork(userName, password);
	}

	return 0;
}