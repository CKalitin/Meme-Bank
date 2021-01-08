#include "Bank.h"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;
using namespace bank;

int main() {
	while (true) {
		bank::Commands();
	}
}

void bank::Commands() {
	string inputs[] = { "", "", "" };
	cin >> inputs[0] >> inputs[1] >> inputs[2];

	if (inputs[0] == "Account" & inputs[1] != "" & inputs[2] != "") {
		bank::CreateAccount(inputs[1], inputs[2]);
	}
}

void bank::CreateAccount(string accountName, string password) {
	cout << "Created Account: " << accountName << " | Password: " << password << endl;
}
