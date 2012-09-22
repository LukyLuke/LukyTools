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
 * $ gcc -o esr_parser esr_parser.cpp -lstdc++
 * or
 * $ g++  -o esr_parser esr_parser.cpp
 *
 * Return the Number including the Checksum:
 * $ ./esr_parser NUMBER
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "esr_parser.h"

using namespace std;

void print_esr(esr_number *number);
string number;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        number = argv[1];
        esr_number *result = new esr_number;
        parse_esr(number, result);
        print_esr(result);

    } else {
        cout << "Parse a ESR-Number and return the different Parts:" << endl;
        cout << "$ ./esr_parse NUMBER" << endl << endl;
    }
    return 0;
}

void print_esr(esr_number *number) {
    cout << endl;
    cout << "ESR-Number: " << number->parsed_number << endl;
    cout << "Type: " << number->type_name << " (" << number->type << ")" << endl;
    cout << "Amount: " << number->amount << endl;
    cout << "Account: " << number->account_formatted << endl;
    cout << "Reference: " << number->number << endl;
    cout << endl;
    cout << "Type and Amount: " << (number->valid_amount ? "Valid" : "Failed") << endl;
    cout << "Reference: " << (number->valid_number ? "Valid" : "Failed") << endl;
    cout << "Account: " << (number->valid_account ? "Valid" : "Failed") << endl;
    cout << endl;
}
