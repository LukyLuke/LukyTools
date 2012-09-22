/*
	Useful functions around ESR from switzerland
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

/**
 * Compile:
 * $ gcc -o esr_reference esr_reference.cpp -lstdc++
 * or
 * $ g++ -o esr_reference esr_reference.cpp
 * 
 * 
 * Return the Number including the Checksum:
 * $ ./esr_reference NUMBER
 * 
 * 
 * Check for a valid Checksum:
 * $ ./esr_reference -v|--validate NUMBER
 * 
 * 
 * Create new Numbers:
 * $ ./esr_reference -b|--begin BEGIN -e|--end END -p|--prefix PREFIX -s|--suffix SUFFIX
 *  BEGIN:  The first number between PREFIX and SUFFIX - count up from START to END
 *  END:    The last number between PREFIX and SUFFIX - count up from START to END
 *  PREFIX: The Number before the calculated part
 *  SUFFIX: The Number after the calculated part
 * 
 *  The Number is built as folow: PREFIX START->END SUFFIX
 *  The result is a list of numbers printed out
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "esr_checksum.h"

using namespace std;

string number;
string prefix;
string suffix;
int start = 0;
int end = 0;

int main(int argc, char* argv[]) {
	int opts = 1;
	
	// Just add the Checksum
	if (argv[1][0] != '-') {
		number = argv[1];
		cout << number << checksum(number) << endl;
		return 0;
		
	} else {
		while (opts < argc) {
			string o = argv[opts];
			
			if ((o == "-h") || (o == "--help")) {
				cout << "Return the Number including the Checksum:" << endl;
				cout << "$ ./esr NUMBER" << endl << endl;
				cout << "Check for a valid Checksum:" << endl;
				cout << "$ ./esr -v|--validate NUMBER" << endl << endl;
				cout << "Create new Numbers:" << endl;
				cout << "$ ./esr -b|--begin BEGIN -e|--end END -p|--prefix PREFIX -s|--suffix SUFFIX" << endl;
				cout << "  BEGIN:  The first number between PREFIX and SUFFIX - count up from START to END" << endl;
				cout << "  END:    The last number between PREFIX and SUFFIX - count up from START to END" << endl;
				cout << "  PREFIX: The Number before the calculated part" << endl;
				cout << "  SUFFIX: The Number after the calculated part" << endl << endl;
				cout << "  The Number is built as folow: PREFIX START->END SUFFIX" << endl;
				cout << "  The result is a list of numbers printed out" << endl;
				return 0;
				
			} else if ((o == "-b") || (o == "--begin")) {
                start = abs(atoi(argv[++opts]));
				
			} else if ((o == "-e") || (o == "--end")) {
                end = abs(atoi(argv[++opts]));
				
			} else if ((o == "-s") || (o == "--suffix")) {
				suffix = argv[++opts];
				
			} else if ((o == "-p") || (o == "--prefix")) {
				prefix = argv[++opts];
				
			} else if ((o == "-v") || (o == "--validate")) {
				number = argv[++opts];
				char c = number.at(number.length() - 1);
				start = atoi(&c);
				end = checksum(number.substr(0, number.length()-1));
				if (start == end) {
					cout << "Checksum VALID" << endl;
				} else {
					cout << "Checksum NOT VALID, sould be " << end << " but is " << start << endl;
				}
				return 0;
			}
			
			opts++;
		}
	}
	
	// Check for inverted Start/End params
	if (start > end) {
		int _s = start;
		start = end;
		end = _s;
	}
	
	// Create the numbers
	char num[1];
	while (start <= end) {
		sprintf(num, "%d", start);
		number = prefix;
		number.append(num);
		number.append(suffix);
		cout << number << checksum(number) << endl;
		start++;
	}
	
	return 0;
}
