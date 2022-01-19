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


	//OPERATORI PREKLOPLJENI PREVASHODNO ZA UNIJU, INTERSEKCIJU, PRESJEK
	//S OBZIROM DA UNIJA, INTERSEKCIJA I PRESJEK U NEKIM SLUCAJEVIMA NE RADE 
	//ONDA SAM RUCNO IMPLEMENTIRAO
	//OSTAVIO SAM OPERATORE IAKO SU BESPOTREBNI
	bool operator==(const User& other) const;
	bool operator!=(const User& other) const;
	//bool operator>(const User& other) const;
	bool operator<(const User& other) const;
	bool operator>=(const User& other) const;
	bool operator<=(const User& other) const;

	//PROVJERA INBOKSA, KAD SE PROVJERI INBOKS BRISU SE PORUKE IZ ISTOG
	void checkInbox() const;

	//FILTRIRANJE PORUKA IZ INBOKSA
	void filterInbox() const;

	//SLANJE PORUKE PRIJATELJU
	void textFriend(std::string friendName) const;

	//PROVJERA DA LI JE KORISNIK VEC PRIJATELJ, POMOCNA FUNKCIJA
	bool checkIfIsAlreadyAFriend(std::string friendName) const;
	
	//SLANJE ZAHTJEVA ZA PRIJATELJSTVO DRUGOM KORISNIKU, UKOLIKO VEC NISU PRIJATELJI
	void sendFriendRequest(std::string userName) const;

	//PROVJERA ZAHTJEVA ZA PRIJATELJSTVO
	//I POTENCIJALNO PRIHVATANJE NEKOG OD ZAHTJEVA
	void checkFriendRequests() const;



protected:
	//PROVJERA DA LI JE KORISNIK VEC POSLAO ZAHTJEV ZA PRIJATELJSTVO, DA SE NE DUPLIRA
	bool checkIfFriendRequestIsAlreadyMade(std::string name) const;

	//VRACANJE VECTORA SVIH KORISNIKA
	std::vector<User> returnUsers();
};