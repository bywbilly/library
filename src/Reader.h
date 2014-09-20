// Reader.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

#include <vector>
#include <string>
#include "User.h"

class Book;


class Reader : public User
{
public:
	enum Type {STUDENT, TEACHER};
	Reader(std::string const &username, std::string const &password);
    virtual ~Reader();
    
	virtual Type getType() const = 0;
    virtual int getBorrowLimit() const = 0;

    virtual bool borrow(Book &) = 0;
    virtual bool returnBook(Book &) = 0;
    virtual bool renew(Book &) = 0;
    virtual bool reserve(Book &) = 0;
    
	virtual std::vector<Book *> getBorrowedBooks() = 0;
    virtual std::vector<Book *> getReservedBooks() = 0;
    
	virtual int getPenalty() = 0;

	int getReaderNumber() const;
	void setReaderNumber(int);

	static void setReaderNumberNow(int);
	static int getReaderNumberNow();

	virtual void setReaderType(Type type) {ReaderType = type;}

	void setPenaltyBefore(int);
	int getPenaltyBefore();

private:
	
	/**
	all the penalty for the books you have already returned.
	*/
	int PenaltyBefore;
	
	Type ReaderType;

	/**
	the id of reader
	*/
	int ReaderNumber;

	/**
	used to get ReaderNumber  once used, it will ++
	*/
	static int ReaderNumberNow;
};
