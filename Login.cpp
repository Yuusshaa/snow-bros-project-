#include "Login.h"
#include <iostream>
#include <fstream>
#include<ctime>
#include<string>
using namespace std;

Login::Login(string filename)
{
    this->filename = filename;
    currentLoggedInUser = "";
}

bool Login::registerUser(string username, string password)
{
    ifstream readFile(filename);
    string line;
    while (getline(readFile, line))
    {
        string storedUsername = line.substr(line.find(',') + 1);  
        storedUsername = storedUsername.substr(0, storedUsername.find(','));
        if (storedUsername == username)
        {
            readFile.close();
            cout << "Username already exists!" << endl;
            return false;
        }
    }
    readFile.close();

    ofstream writeFile(filename, ios::app);
    writeFile << getNextUserID() << "," << username << "," << hashPassword(password) << "," << getTimestamp() << endl;
    writeFile.close();

    cout << "Registered successfully!" << endl;
    return true;
}

bool Login::loginUser(string username, string password)
{
    ifstream readFile(filename);
    string line;

    while (getline(readFile, line))
    {
        int first = line.find(',');                    // after ID
        int second = line.find(',', first + 1);         // after username
        int third = line.find(',', second + 1);        // after password_hash

        string storedUsername = line.substr(first + 1, second - first - 1);
        string storedHash = line.substr(second + 1, third - second - 1);

        if (storedUsername == username && storedHash == hashPassword(password))
        {
            readFile.close();
            currentLoggedInUser = username;
            cout << "Login successful!" << endl;
            return true;
        }
    }

    readFile.close();
    cout << "Invalid username or password!" << endl;
    return false;
}

int Login::getNextUserID()
{
    ifstream readFile(filename);
    string line;
    int count = 0;
    while (getline(readFile, line)) count++;
    readFile.close();
    return count + 1;
}

string Login::hashPassword(string password)
{
    int hash = 0;
    for (int i = 0; i < password.length(); i++)
    {
        hash = hash + (password[i] * (i + 1));
    }
    return to_string(hash);
}

string Login::getTimestamp()
{
    time_t now = time(0);
    tm timeInfo;
    localtime_s(&timeInfo, &now);
    tm* ltm = &timeInfo;

    string date = to_string(1900 + ltm->tm_year) + "-"
        + to_string(1 + ltm->tm_mon) + "-"
        + to_string(ltm->tm_mday);
    return date;
}


