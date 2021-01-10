#include "Bank.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
using namespace bank;

int main() {
	cout << "Welcome to Meme Bank!" << endl;
	cout << "If you are new here type \"Help\"" << endl;
	while (true) {
		bank::Commands();
	}
}

void bank::Commands() {
	string input = "";
	cin >> input;

	if (input == "CreateAccount") {
		string inputs[] = { "", "" };
		cout << "Username: ";
		cin >> inputs[0];
		cout << "Password: ";
		cin >> inputs[1];
		CreateAccount(inputs[0], inputs[1]);
	}
	else if (input == "Signin") {
		if (bank::signedIn == true) {
			cout << "Already signed in" << endl;
		}
		string inputs[] = { "", "" };
		cout << "Username: ";
		cin >> inputs[0];
		cout << "Password: ";
		cin >> inputs[1];
		SignIn(inputs[0], inputs[1]);
	}
	else if (input == "Signout") {
		bank::SignOut();
	}
	else if (input == "Balance") {
		bank::Balance();
	}
	else if (input == "Deposit") {
		float newInput;
		cout << "Deposit Ammount: ";
		cin >> newInput;
		bank::Deposit(newInput);
	}
	else if (input == "Withdraw") {
		float newInput;
		cout << "Withdraw Ammount: ";
		cin >> newInput;
		bank::Withdraw(newInput);
	}
	else if (input == "Help") {
		bank::Help();
	}
	else {
		cout << "Command Not Found" << endl;
	}
}

void bank::CreateAccount(string accountName, string password) {
	// DO NOT STORE PASSWORD LIKE THIS!!!!!!!!!! (I'm just learning C++ and don't care too much about this)
	ofstream file("accounts.txt", fstream::in | fstream::out | fstream::app);
	ifstream ifFile("accounts.txt");
	if (file.is_open()) {
		string str;
		while (getline(ifFile, str)) {
			string firstCharsOfFileStr = str.substr(0, accountName.length());
			if (firstCharsOfFileStr == accountName) {
				cout << "Username is taken." << endl;
				return;
			}
		}
		file << "\n" << accountName << ", " << password << ", " << 0 << ", ";
		file.close();
	}
	cout << "Created Account: " << accountName << " | Password: " << password << endl;
}

void bank::SignIn(string accountName, string password) {
	string str;
	int accountLineNumber = 0;
	bool foundAccount = false;
	ifstream file("accounts.txt");
	if (file.is_open()) {
		while (getline(file, str)) {
			accountLineNumber++;
			string firstCharsOfFileStr = str.substr(0, accountName.length());
			if (firstCharsOfFileStr == accountName) {
				foundAccount = true;
				break;
			}
		}
		file.close();
	}

	if (foundAccount == false) {
		cout << "Incorrect Username" << endl;
		return;
	}

	istringstream iss(str);
	vector<string> accountLineValues((istream_iterator<string>(iss)), istream_iterator<string>());
	if (accountLineValues[1] != password) {
		cout << "Incorrect Password" << endl;
		return;
	}
	else {
		bank::accountLineNumber = accountLineNumber;
		bank::signedIn = true;
		bank::accountLine = str;
		bank::accountLineValues = accountLineValues;
	}
}

void bank::SignOut() {
	if (bank::signedIn == false) {
		cout << "Already signed out" << bank::signedIn << endl;
	}
	else {
		bank::accountLineNumber = 0;
		bank::signedIn = false;
		bank::accountLine = "";
		bank::accountLineValues.clear();
	}
}

void bank::Balance() {
	cout << round(stoi(bank::accountLineValues[2]) * 100) / 100 << endl;
}

void bank::Deposit(float ammount) {
	float money = stoi(bank::accountLineValues[2]) + ammount;
	bank::accountLineValues[2] = to_string(money) + ", ";
	bank::UpdateAccountLine();
	cout << "Deposited: " << ammount << " | Total: " << round(stoi(bank::accountLineValues[2]) * 100) / 100 << endl;
} 

void bank::Withdraw(float ammount) {
	float money = stoi(bank::accountLineValues[2]) - ammount;
	if (money > 0) {
		bank::accountLineValues[2] = to_string(money) + ", ";
		bank::UpdateAccountLine();
		cout << "Deposited: " << ammount << " | Total: " << round(stoi(bank::accountLineValues[2]) * 100) / 100 << endl;
	}
	else {
		cout << "Cannot withdraw more than account balance | Account Balanace: " << round(stoi(bank::accountLineValues[2]) * 100) / 100 << endl;
	}

}

void bank::UpdateAccountLine() {
	ifstream file("accounts.txt");
	ofstream temp("temp.txt");

	string str;
	int index = 0;
	while (getline(file, str))
	{
		index++;
		if (index == accountLineNumber)
			temp << accountLineValues[0] + " " + accountLineValues[1] + " " + accountLineValues[2] + " " << endl;
		else
			temp << str << endl;
	}

	temp.close();
	file.close();
	remove("accounts.txt");
	rename("temp.txt", "accounts.txt");
}

void bank::Help() {
	cout << "CreateAccount - Create an account if you do not have one" << endl;
	cout << "Signin         - Use to Sign in" << endl;
	cout << "Signout        - use to Sign out" << endl;
	cout << "Balance        - Shows Account Balance if signed in" << endl;
	cout << "Deposit        - Deposit money if signed in" << endl;
	cout << "Withdraw       - Withdraw money if signed in" << endl;
	cout << "Help           - Shows this" << endl;
}
