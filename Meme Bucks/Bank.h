#pragma once

class Bank
{
	int numAccounts;
	static int maxAccounts;
public:
	void AddAccount();
	int GetNumAccounts();
};
