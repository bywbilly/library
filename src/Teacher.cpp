// Teacher.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "Teacher.h"

Teacher::Teacher(std::string const &username, std::string const &password):Reader(username, password)
{
	Reader::setReaderType(TEACHER);
}

Teacher::~Teacher()
{

}

bool Teacher::borrow(Book &book)
{
	if ((int)Teacher::getBorrowedBooks().size() == Teacher::getBorrowLimit()) 
		return false;
	if ((int)Teacher::getPenalty() - Teacher::getPenaltyBefore() > 0) 
		return false;
	if (!book.isBorrowable()) 
		return false;
	if (book.isLentOut()) 
		return false;
	if (book.getReserveStatus() 
		&& book.getReserveNumberOfBook() != Reader::getReaderNumber() && book.getReservedDate().getNumber() + System::getReservedBookExpiredDays() > System::getCurrentDate().getNumber()) 
			return false;
	book.setReader(this);
	book.setReserveStatus(false);
	book.lendOut();
	book.setRenewStatus(false);
	book.setBorrowedDate(System::getCurrentDate());
	return true;
}

bool Teacher::returnBook(Book &book)
{
    if (book.getReader() != this) 
		return false;
    if (!book.isLentOut()) 
		return false;
    book.returnIn();
    book.setRenewStatus(false);
	if(book.getReserveStatus()) 
		book.setReservedDate(System::getCurrentDate());
	if(book.getBorrowedDate().getNumber() + System::getBorrowedBookExpiredDays() <= System::getCurrentDate().getNumber())
		setPenaltyBefore(getPenaltyBefore() + 1 + System::getCurrentDate().getNumber() - book.getBorrowedDate().getNumber() - System::getBorrowedBookExpiredDays());
	return true;
}

bool Teacher::renew(Book &book)
{
	if (book.getReader() != this) 
		return false;
	if (!book.isBorrowable()) 
		return false;
	if (!book.isLentOut()) 
		return false;
	if ((int)Teacher::getPenalty() - Teacher::getPenaltyBefore() > 0) 
		return false;
	if (book.getRenewStatus()) 
		return false;
	book.setRenewStatus(true);
	book.setBorrowedDate(System::getCurrentDate());
	return true;
}

std::vector<Book *> Teacher::getBorrowedBooks()
{
    std::vector<Book *> BookVector;
    BookVector.clear();
    for (int i = 0; i < (int)BookDAO::AllBooks.size(); i++)
    {
        if (BookDAO::AllBooks[i]->getReaderNumberOfBook() == getReaderNumber() 
			&& BookDAO::AllBooks[i]->isLentOut())
			{
			    BookVector.push_back(BookDAO::AllBooks[i]);
		    }
    }
    return BookVector;
}

bool Teacher::reserve(Book & book)
{
	if ((int)Teacher::getPenalty() - Teacher::getPenaltyBefore() > 0) 
		return false;
	std::vector<Book *> BookVector = book.getKind().getBooks();
	for (int i = 0; i < (int)BookVector.size(); i++)
	{
		if (!BookVector[i]->isBorrowable()) 
			continue;
		if (BookVector[i]->isLentOut() 
			&& BookVector[i]->getReader() == this) 
				return false;
		if (BookVector[i]->isLentOut()) 
			continue;
		if (BookVector[i]->getReserveStatus() 
			&& BookVector[i]->getReservedDate().getNumber() + System::getReservedBookExpiredDays() > System::getCurrentDate().getNumber()
			&& BookVector[i]->getReserveNumberOfBook() == this->getReaderNumber())
				return false;
		if (BookVector[i]->getReserveStatus() 
			&& BookVector[i]->getReservedDate().getNumber() + System::getReservedBookExpiredDays() > System::getCurrentDate().getNumber()) 
				continue;
		BookVector[i]->setReserveStatus(true);
		BookVector[i]->setReservedDate(System::getCurrentDate());
		BookVector[i]->setReserveNumberOfBook(Reader::getReaderNumber());
		return true;
	}
	for (int i = 0; i < (int)BookVector.size(); i++)
	{
		if (!BookVector[i]->isBorrowable()) 
			continue;
		if (BookVector[i]->getReserveStatus())
			continue;
		BookVector[i]->setReserveStatus(true);
		BookVector[i]->setReservedDate(System::getCurrentDate());
		BookVector[i]->setReserveNumberOfBook(Reader::getReaderNumber());
		return true;
	}
	return false;
}

std::vector<Book *> Teacher::getReservedBooks()
{
	std::vector<Book *> BookVector;
	BookVector.clear();
	for (int i = 0; i < (int)BookDAO::AllBooks.size(); i++)
	{
		if ((BookDAO::AllBooks[i]->getReserveNumberOfBook() == getReaderNumber() 
				&& BookDAO::AllBooks[i]->getReserveStatus() 
				&& BookDAO::AllBooks[i]->getReservedDate().getNumber() + System::getReservedBookExpiredDays() > System::getCurrentDate().getNumber())
				||(BookDAO::AllBooks[i]->getReserveNumberOfBook() == getReaderNumber()
					&&BookDAO::AllBooks[i]->getReserveStatus()
					&&BookDAO::AllBooks[i]->isLentOut() == true))
					{
						BookVector.push_back(BookDAO::AllBooks[i]);
					}
	}
	return BookVector;
}

int Teacher::getPenalty()
{
	int penalty = 0;
	for (int i = 0; i < (int)Teacher::getBorrowedBooks().size(); i++)
	{
		if (Teacher::getBorrowedBooks()[i]->getBorrowedDate().getNumber() + System::getBorrowedBookExpiredDays() <= System::getCurrentDate().getNumber())
		{
			penalty += (1 + System::getCurrentDate().getNumber() - Teacher::getBorrowedBooks()[i]->getBorrowedDate().getNumber() - System::getBorrowedBookExpiredDays());
		}
	}
	penalty += getPenaltyBefore();
	return penalty;
}
