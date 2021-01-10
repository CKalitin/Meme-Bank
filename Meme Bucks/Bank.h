#pragma once
#include <string>
#include <vector>

using namespace std;

namespace bank
{
	int accountLineNumber;
	bool signedIn = false;
	string accountLine;
	vector<string> accountLineValues;

	void Commands();
	void CreateAccount(string, string);
	int GetAccountLine(string);
	void SignIn(string, string);
	void SignOut();
	void Balance();
	void Deposit(float);
	void Withdraw(float);
	void UpdateAccountLine();
	void Help();
};
