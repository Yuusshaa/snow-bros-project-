#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>

using namespace std;

class Login
{
private:
	string currentLoggedInUser, filename;

public:
	Login(string filename);
	bool registerUser(string username, string password);
	bool loginUser(string username, string password);
	string getCurrentLoggedInUser() { return currentLoggedInUser; }
	int getNextUserID();
	string getTimestamp();
	string hashPassword(string password);
	~Login() {}
};

