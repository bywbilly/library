// Book.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "Book.h"
#include "Kind.h"
#include "KindDAO.h"
#include "ReaderDAO.h"

Book::Book(int kindnumberofbook, bool bookonlyread)
{
	KindNumberOfBook = kindnumberofbook;
	ReaderNumberOfBook = 0;
	ReserveNumberOfBook = 0;
	IsRenewed = false;
	IsBorrowed = false;
	IsReserved = false;
	BookBorrowable = bookonlyread;
}

Book::~Book()
{

}

Kind &Book::getKind() const
{
	for (int i = 0; i < (int)KindDAO::AllKinds.size(); i++)
	{
		if (KindDAO::AllKinds[i]->getKindNumber() == KindNumberOfBook)
			return * KindDAO::AllKinds[i];
	}
}

void Book::setKind(Kind const & kind)
{
	KindNumberOfBook = kind.getKindNumber();
}

Reader * Book::getReader() const
{
	if (!this->isLentOut())
		return NULL;
	for(int i = 0; i < (int)ReaderDAO::AllReaders.size(); i++)
	{
		if (getReaderNumberOfBook() == ReaderDAO::AllReaders[i]->getReaderNumber())
			return ReaderDAO::AllReaders[i];
	}
	return NULL;
}

void Book::setReader(Reader const * reader)
{
	ReaderNumberOfBook = reader->getReaderNumber();
}

void Book::setReaderNumberOfBook(int readernumberofbook)
{
	ReaderNumberOfBook = readernumberofbook;
}

Date Book::getBorrowedDate() const
{
	return BookBorrowedDate;
}

bool Book::isBorrowable() const
{
	if (BookBorrowable)
		return true;
	else
		return false;
}

bool Book::isLentOut() const
{
	if (IsBorrowed)
		return true;
	else
		return false;
}

void Book::setBorrowedDate(Date date)
{
	BookBorrowedDate = date;
}

void Book::setReservedDate(Date date)
{
	BookReservedDate = date;
}

Date Book::getReservedDate()
{
	return BookReservedDate;
}

int Book::getReaderNumberOfBook() const
{
	return ReaderNumberOfBook;
}

int Book::getReserveNumberOfBook() const
{
	return ReserveNumberOfBook;
}

void Book::lendOut()
{
	IsBorrowed = true;
}

void Book::returnIn()
{
	IsBorrowed = false;
}

int Book::getKindNumberOfBook() const
{
	return KindNumberOfBook;
}

bool Book::getReserveStatus() const
{
	return IsReserved;
}

void Book::setReserveStatus(bool status)
{
	IsReserved = status;
}

bool Book::getRenewStatus()
{
	return IsRenewed;
}

void Book::setRenewStatus(bool status)
{
	IsRenewed = status;
}

void Book::setReserveNumberOfBook(int reservenumberofbook)
{
	ReserveNumberOfBook = reservenumberofbook;
}

bool Book::isAvailable() const
{
	if (!BookBorrowable)
		return false;
	if (IsBorrowed && BookBorrowedDate.getNumber() + System::getBorrowedBookExpiredDays() > System::getCurrentDate().getNumber())
		return false;
	if (IsReserved && BookReservedDate.getNumber() + System::getReservedBookExpiredDays() > System::getCurrentDate().getNumber())
		return false;
	return true;
}
