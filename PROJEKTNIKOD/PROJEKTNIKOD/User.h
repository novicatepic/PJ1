#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "CoreUser.h"

class User : virtual public CoreUser {
protected:

public:

	User(std::string userName = "", std::string password = "");

	bool operator==(const User& other) const;
	bool operator!=(const User& other) const;
	//bool operator>(const User& other) const;
	bool operator<(const User& other) const;
	bool operator>=(const User& other) const;
	bool operator<=(const User& other) const;
	void checkInbox() const;
	void filterInbox() const;
	void textFriend(std::string friendName) const;
	bool checkIfIsAlreadyAFriend(std::string friendName) const;
	void sendFriendRequest(std::string userName) const;
	void checkFriendRequests() const;



protected:
	bool checkIfFriendRequestIsAlreadyMade(std::string name) const;
	std::vector<User> returnUsers();
};