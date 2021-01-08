#include "Bank.h"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

int Bank::maxAccounts = 10;

int main() {
	Bank object;
	while (true) {
		if (GetKeyState('A') & 0x8000)
		{
			object.Bank::AddAccount();
			cout << "Added Accout" << endl;
		}
		system("CLS");
		cout << &Bank::GetNumAccounts << endl;
	}
}

int Bank::GetNumAccounts() {
	return Bank::numAccounts;
}

void Bank::AddAccount()
{
	if (Bank::numAccounts + 1 <= Bank::maxAccounts) {
		Bank::numAccounts += 1;
	}
}
