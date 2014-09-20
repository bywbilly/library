// Date.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "Date.h"

Date::Date(int y = 1900, int m = 1, int d = 1)
{
    year = y;
    month = m;
    day = d;
    int mo[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    number = 0;
    int y1 = 1900, m1 = 1;
    while (y1 < y)
    {
        int opt = 0;
        if (y1 % 400 == 0) opt = 1; 
		else
			if (y1 % 100 != 0 && y1 % 4 == 0) opt = 1;
				number += 365 + opt;
        y1++;
    }
    int opt = 0;
    if (y1 % 400 == 0) opt = 1; 
	else
		if (y1 % 100 != 0 && y1 % 4 == 0) opt = 1;
			if (opt == 1) mo[2] = 29;
				while (m1 < m)
				{
					number += mo[m1];
					m1++;
				}
    number += d;
}

Date::~Date()
{

}

int Date::getYear() const
{
    return year;
}

int Date::getMonth() const
{
    return month;
}

int Date::getDay() const
{
    return day;
}

int Date::getNumber() const
{
    return number;
}
