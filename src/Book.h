// Book.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

#include "Date.h"
#include "BookDAO.h"
#include "Reader.h"

class Kind;

class Book
{
public:
    Book(int, bool);
    virtual ~Book();

    Kind &getKind() const;
    void setKind(Kind const &);

	Reader * getReader() const;
	void setReader(Reader const *);

    Date getBorrowedDate() const;

    /**
     *	Return whether this book is available to borrow or not.
     *	Return true if this book is available, false otherwise.
     */
    bool isAvailable() const;

    /**
     *	Return whether this book has been lent out or not.
     *	Return true if this book has been lent out, false otherwise.
     */
    bool isLentOut() const;

	void setBorrowedDate(Date);
	
	Date getReservedDate();
	void setReservedDate(Date);

	int getReaderNumberOfBook() const;
	void setReaderNumberOfBook(int);

	int getReserveNumberOfBook() const;
	void setReserveNumberOfBook(int);
	
	int getKindNumberOfBook() const;

	void lendOut();
	void returnIn();
	
	bool getReserveStatus() const;
	void setReserveStatus(bool);
	
	bool getRenewStatus();
	void setRenewStatus(bool);
	
	bool isBorrowable() const;

private:
	Date BookBorrowedDate;
	Date BookReservedDate;
	bool BookBorrowable;
	
	/**
	return true if book is borrowed
	*/
	bool IsBorrowed;

	/**
	return true if book has been reserved
	*/
	bool IsReserved;

	/**
	return true if book has been renewed once
	*/
	bool IsRenewed;

	/**
	the id for the kind of the book
	*/
	int KindNumberOfBook;

	/**
	the id for the reader of the book
	*/
	int ReaderNumberOfBook;

	/**
	the id for the reserver of the book
	*/
	int	ReserveNumberOfBook;
};
