/*
	Small concole app to demonstrate the calculation-method of the new PPS-FIO Membership
	Copyright (C) 2012  Lukas Zurschmiede <l.zurschmiede@delightsoftware.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fcntl.h>
#include <stdlib.h>

using namespace std;

void createSections();
void calculate(map<string, float> *copy, float amount);

float sum;
map<string, float> sections;
map<string, float> payments;

int main(int argc, char **argv) {
	createSections();
	map<string, float> *copy = new map<string, float>();
	map<string, float>::const_iterator it;
	string line;
	float amount;
	
	// get the recomment total
	for (it = sections.begin(); it != sections.end(); it++) {
		sum += it->second;
	}
	
	while (true) {
		// copy sections to calculate different paid amounts after
		for (it = sections.begin(); it != sections.end(); it++) {
			copy->insert( pair<string, float>(it->first, it->second) );
		}
		
		// Get paid amount or exit
		cout << "Amount paid (NaN to exit): ";
		getline(cin, line);
		amount = atof(line.c_str());
		if (!amount) {
			break;
		}
		cout << endl;
		
		// calculate section contributions and show them
		payments.clear();
		calculate(copy, amount);
		
		cout << "Total recommendend: " << sum << endl;
		cout << "Payments:" << endl;
		for (it = payments.begin(); it != payments.end(); it++) {
			cout << " * " << it->first << ": " << it->second << endl;
		}
		cout << "***********" << endl;
		
	}
	return 0;
}

void calculate(map<string, float> *copy, float amount) {
	if (amount <= 0) {
		return;
	}
	
	if (copy->size() > 0) {
		map<string, float>::const_iterator it;
		string least;
		float due, smallest;
		
		// If the amount is bigger than the recommendend sum, give each section the procentula amount of it
		if (amount >= sum) {
			for (it = copy->begin(); it != copy->end(); it++) {
				payments.insert( pair<string, float>(it->first, amount * (it->second / sum)) );
			}
			return;
		}
		
		// get the smallest amount and the current due amount
		for (it = copy->begin(); it != copy->end(); it++) {
			smallest = smallest <= 0 || it->second < smallest ? it->second : smallest;
		}
		due = amount / copy->size();
		
		// if the due is smaller than the smallest amount, give the same amount to each unpaid section
		if (due <= smallest) {
			for (it = copy->begin(); it != copy->end(); it++) {
				payments.insert( pair<string, float>(it->first, due) );
			}
			copy->clear();
			return;
		}
		
		// pay the smalles section and rerun this calculation with all other sections expect the one we pay here
		for (it = copy->begin(); it != copy->end(); it++) {
			if (due >= it->second) {
				payments.insert( pair<string, float>(it->first, it->second) );
				amount -= it->second;
				copy->erase(it->first);
			}
		}
		calculate(copy, amount);
	}
}


void createSections() {
	/*sections.insert( pair<string, float>("PPS", 40) );
	sections.insert( pair<string, float>("A",   30) );
	sections.insert( pair<string, float>("AA", 120) );
	return;*/
	string line1, line2;
	float amount;
	while (true) {
		cout << endl << "Enter the name of the Section: ";
		getline(cin, line1);
		
		if (line1.empty()) {
			break;
		}
		
		amount = 0.0;
		while (amount <= 0) {
			cout << "Recommend amount: ";
			getline(cin, line2);
			amount = atof(line2.c_str());
			if (amount <= 0) {
				cout << endl << endl << "invalid, write a valid float/double..." << endl;
			}
		}
		sections.insert( pair<string, float>(line1, amount) );
	}
}
