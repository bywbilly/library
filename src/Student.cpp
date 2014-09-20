// Student.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "Student.h"

Student::Student(std::string const &username, std::string const &password):Reader(username, password)
{
	Reader::setReaderType(STUDENT);
}

Student::~Student()
{

}

bool Student::borrow(Book &book)
{
	if ((int)Student::getBorrowedBooks().size() == Student::getBorrowLimit()) 
		return false;
	if ((int)Student::getPenalty() - Student::getPenaltyBefore() > 0) 
		return false;
	if (book.isBorrowable() == false) 
		return false;
	if (book.isLentOut() == true) 
		return false;
	if (book.getReserveStatus() 
		&& book.getReservedDate().getNumber() + System::getReservedBookExpiredDays() > System::getCurrentDate().getNumber()) 
		return false;
	book.setReader(this);
	book.setReserveStatus(false);
	book.lendOut();
	book.setRenewStatus(false);
	book.setBorrowedDate(System::getCurrentDate());
	return true;
}

bool Student::returnBook(Book &book)
{
    if (book.getReader() != this) 
		return false;
    if (!book.isLentOut()) 
		return false;
    book.returnIn();
	book.setRenewStatus(false);
	if (book.getReserveStatus()) 
		book.setReservedDate(System::getCurrentDate());
    if (book.getBorrowedDate().getNumber() + System::getBorrowedBookExpiredDays() <= System::getCurrentDate().getNumber())
		setPenaltyBefore(getPenaltyBefore() + 1 + System::getCurrentDate().getNumber() - book.getBorrowedDate().getNumber() - System::getBorrowedBookExpiredDays());
	return true;
}

bool Student::renew(Book &book)
{
	if (book.getReader() != this) 
		return false;
	if (!book.isBorrowable()) 
		return false;
	if (!book.isLentOut()) 
		return false;
	if ((int)Student::getPenalty() - Student::getPenaltyBefore() > 0) 
		return false;
	if (book.getRenewStatus()) 
		return false;
	book.setRenewStatus(true);
	book.setBorrowedDate(System::getCurrentDate());
	return true;
}

std::vector<Book *> Student::getBorrowedBooks()
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

bool Student::reserve(Book & book)
{
    return false;
}

std::vector<Book *> Student::getReservedBooks()
{
	std::vector<Book *> reservedBooks;
    reservedBooks.clear();
    return reservedBooks;
}

int Student::getPenalty()
{
	int penalty = 0;
	for (int i = 0; i < (int)Student::getBorrowedBooks().size(); i++)
	{
		if (Student::getBorrowedBooks()[i]->getBorrowedDate().getNumber() + System::getBorrowedBookExpiredDays() <= System::getCurrentDate().getNumber())
		{
			penalty += (1 + System::getCurrentDate().getNumber() - Student::getBorrowedBooks()[i]->getBorrowedDate().getNumber() - System::getBorrowedBookExpiredDays());
		}
	}
	penalty += getPenaltyBefore();
	return penalty;
};
