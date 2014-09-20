// Teacher.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

#include "Reader.h"
#include "Book.h"
#include "System.h"
#include "Kind.h"

class Teacher : public Reader
{
public:
	Teacher(std::string const &username, std::string const &password);
	virtual ~Teacher();

	Type getType() const { return TEACHER; }
	int getBorrowLimit() const { return 10; }

	// TODO: add whatever you need
    bool borrow(Book &) ;
    bool returnBook(Book &) ;
    bool renew(Book &) ;
    bool reserve(Book &) ;
    std::vector<Book *> getBorrowedBooks() ;
    std::vector<Book *> getReservedBooks() ;
    int getPenalty() ;
};
