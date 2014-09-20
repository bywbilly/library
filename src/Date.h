// Date.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

class Date
{
public:
	Date() {year = 1900; month = 1; day = 1; number = 1;}
	Date(int year, int month, int day);
	~Date();
    int getNumber() const;
	int getYear() const;
	int getMonth() const;
	int getDay() const;

private:
    int year;
    int month;
    int day;
    int number;
};
