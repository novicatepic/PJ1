#pragma once
#include "CoreUser.h"
#include <iostream>
#include <set>
#include "Administrator.h"
#include "Student.h"

//DA SE NE BI DUPLIRAO KOD U MEJNU
//JER JEDNOM IMAM PRVO POKRETANJE PROGRAMA, TAD SE KREIRA ADMINISTRATOR
//I KASNIJE SE KORISNIK MOZE PRIJAVITI KORISNIK KAO ADMIN
//IMA ISTE FUNKCIONALNOSTI

void administratorMainWork(std::string userName, std::string password) {

	std::string choice;
	
	do {
		Administrator admin(userName, password);
		std::cout << "--logout to log out" << std::endl;
		std::cout << "[0] Option to show all users" << std::endl;
		std::cout << "[1] Option to add new user" << std::endl;
		std::cout << "[2] Option to remove user" << std::endl;
		std::cout << "[3] Option to modify users" << std::endl;
		std::cout << "[4] Option to modify courses" << std::endl;
		std::cout << "[5] Option to create new course" << std::endl;
		std::cout << "[6] Option to remove course" << std::endl;
		std::cout << "[7] Option to add user to the course" << std::endl;
		std::cout << "[8] Option to remove user from course" << std::endl;
		std::cout << "[9] Option to show union/intersection/difference of courses" << std::endl;
		std::cout << "Pick your poison: " << std::endl;
		std::cout << std::endl;
		std::cout << "Enter option: " << std::endl;
		std::getline(std::cin, choice, '\n');
		//std::cin >> choice;

		if (choice == "0") {
			admin.showAllUsers();
		}
		else if (choice == "1") {
			admin.addUser();
		}
		else if (choice == "2") {
			admin.removeUser();
		}
		else if (choice == "3") {
			admin.modifyUsers();
		}
		else if (choice == "4") {
			admin.modifyCourses();
		}
		else if (choice == "5") {
			admin.addNewCourse();
		}
		else if (choice == "6") {
			admin.removeCourse();
		}
		else if (choice == "7") {
			admin.addUserToCourse();
		}
		else if (choice == "8") {
			admin.removeUserFromCourse();
		}
		else if (choice == "9") {
			admin.showCourses();
			std::cout << "Enter course name: " << std::endl;
			std::string courseName;
			std::getline(std::cin, courseName, '\n');
			if (!admin.doesCourseExist(courseName)) {
				std::cout << "Sorry, course doesn't exist!" << std::endl;
			}
			else {
				Course course(courseName);
				std::set<Student> studentSet = course.findUnionIntersectionDifference();
				//std::set<Student>::iterator studentSetIterator;
				for (auto iterator = studentSet.begin(); iterator != studentSet.end(); iterator++) {
					std::cout << *iterator;
				}
			}
		}
		else if (choice == "--logout") {

		}
		else {
			std::cout << "Wrong option, try again: " << std::endl;
		}
	} while (choice != "--logout");
}