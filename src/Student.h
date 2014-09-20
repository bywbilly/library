// Student.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

#include "Reader.h"
#include "Book.h"
#include "System.h"

class Student : public Reader
{
public:
	Student(std::string const &username, std::string const &password);
	virtual ~Student();

	Type getType() const { return STUDENT; }
	int getBorrowLimit() const { return 5; }

	bool reserve(Book &);
	bool borrow(Book &);
	bool returnBook(Book &);
	bool renew(Book &);
	int getPenalty();

	std::vector<Book *> getBorrowedBooks();
	std::vector<Book *> getReservedBooks();
};
