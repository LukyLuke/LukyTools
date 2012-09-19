/*
    Parses an ESR-Number into its different parts
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

#ifndef ESR_PARSER_H
#define ESR_PARSER_H

#include <string>
#include "esr_checksum.h"

using namespace std;

enum ESR_Currency {
    ESR_CHF=1,
    NESR_CHF=3,
    ESRPLUS_CHF=4,
    ESR_OUR_CREDIT_CHF=11,
    ESRPLUS_OUR_CREDIT_CHF=14,
    ESR_EUR=21,
    ESR_OUR_CREDIT_EUR=23,
    ESRPLUS_EUR=31,
    ESRPLUS_OUR_CREDIT_EUR=33
};

struct esr_number {
    string parsed_number;
    enum ESR_Currency type;
    string type_name;
    float amount;
    string account;
    string account_formatted;
    string number;
    unsigned int check_amount;
    unsigned int check_number;
    bool valid_amount;
    bool valid_account;
    bool valid_number;
};

void parse_esr(const string number, esr_number *result) {
    if (result == NULL) return;
    result->parsed_number = number;

    if (number.length() <= 5) return;

    // Positions of Separation-Chars
    string::size_type pos  = number.find_first_of('>');
    string::size_type end  = number.find_first_of('+');
    string::size_type last = number.find_last_of('>');

    if (pos > end || pos > last || end > last) return;

    // Parse ESR-Type
    switch(atoi(number.substr(0, 2).c_str())) {
    case ESR_CHF:
        result->type = ESR_CHF;
        result->type_name = "ESR in CHF";
        break;
    case NESR_CHF:
        result->type = NESR_CHF;
        result->type_name = "N-ESR in CHF";
        break;
    case ESRPLUS_CHF:
        result->type = ESRPLUS_CHF;
        result->type_name = "ESR+ in CHF";
        break;
    case ESR_OUR_CREDIT_CHF:
        result->type = ESR_OUR_CREDIT_CHF;
        result->type_name = "ESR in CHF for our credit";
        break;
    case ESRPLUS_OUR_CREDIT_CHF:
        result->type = ESRPLUS_OUR_CREDIT_CHF;
        result->type_name = "ESR+ in CHF for our credit";
        break;
    case ESR_EUR:
        result->type = ESR_EUR;
        result->type_name = "ESR in EUR";
        break;
    case ESR_OUR_CREDIT_EUR:
        result->type = ESR_OUR_CREDIT_EUR;
        result->type_name = "ESR in EUR for our credit";
        break;
    case ESRPLUS_EUR:
        result->type = ESRPLUS_EUR;
        result->type_name = "ESR+ in EUR";
        break;
    case ESRPLUS_OUR_CREDIT_EUR:
        result->type = ESRPLUS_OUR_CREDIT_EUR;
        result->type_name = "ESR+ in EUR for our credit";
        break;
    default:
        result->type = ESR_CHF;
        result->type_name = "ESR in EUR - Type not known: " + number.substr(0, 2);
    }

    // Parse the amount - if available
    if (pos > 4) {
        result->amount = atoi(number.substr(3, pos-6).c_str());
        result->amount += atof(number.substr(pos-3, 2).c_str())/100;
    } else {
        result->amount = 0.0;
    }

    // Checksum to the first Separator
    result->check_amount = checksum( number.substr(0, pos-1) );
    result->valid_amount = result->check_amount == atoi(number.substr(pos-1, 1).c_str());

    // Parse the Reference-Number
    result->number = number.substr(pos+1, end - pos - 1);
    result->check_number = checksum(result->number.substr(0, result->number.length()-1));
    result->valid_number = result->check_number == atoi(number.substr(end-1, 1).c_str());

    // Parse the Account
    result->account = number.substr(end+2, last - end - 2);
    result->valid_account =  atoi(number.substr(last-1, 1).c_str()) == checksum(result->account.substr(0, result->account.length()-1));
    result->account_formatted = result->account.substr(0, 2) + "-" + result->account.substr(2, result->account.length()-3) + "-" + result->account.substr(result->account.length()-1, 1);
}

#endif // ESR_PARSER_H
