/*
    Calculates the MOD10-Checksum of a StringOfInteger
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

#ifndef ESR_CHECKSUM_H
#define ESR_CHECKSUM_H

#include <string>

using namespace std;

unsigned int checkSum[] = {0, 9, 4, 6, 8, 2, 7, 1, 3, 5};

unsigned int checksum(const string &num) {
    int pos, sum = 0;
    char c;
    for (unsigned int i = 0; i < num.length(); i++) {
        c = num.at(i);
        pos = (sum += atoi(&c)) % 10;
        sum = checkSum[pos];
    }
    return (10 - sum);
}

#endif // ESR_CHECKSUM_H
