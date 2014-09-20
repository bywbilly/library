// BookDAO.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "BookDAO.h"
#include <string>
#include <fstream>

static std::vector<Book *> AllBooks;

std::string BookDAO::wtos(const std::wstring &w)
{
	int	len = WideCharToMultiByte(GetACP(), 0, w.c_str(), -1, NULL, 0, NULL, NULL);
	char *buf = new char[len];
	WideCharToMultiByte(GetACP(), 0, w.c_str(), -1, buf, len, NULL, NULL);
	std::string s(buf);
	delete[] buf;
	return s;
}

std::wstring BookDAO::stow(const std::string &s)
{
	int len = MultiByteToWideChar(GetACP(), 0, s.c_str(), -1, NULL, 0);
	wchar_t*buf = new wchar_t[len];
	MultiByteToWideChar(GetACP(), 0, s.c_str(), -1, buf, len);
	std::wstring w(buf);
	delete[] buf;
	return w;
}

bool BookDAO::file_exists(std::string const &path)
{
	std::fstream f(path.c_str());
	bool exists = f.is_open();
	f.close();
	return exists;
}

bool BookDAO::loadAll()
{
	BookDAO::AllBooks.clear();
	std::wstring path = System::getWorkingDirectory() + L"\\" + System::getBookFileName();
	if (file_exists(wtos(path)))
	{
		std::ifstream fin(wtos(path));
		int kindnumberofbook, year1, year2, month1, month2, day1, day2, tempnumber;
		std::string tempstring;
		bool onlyread, tempbool;
 		while (1)
		{
			std::getline(fin, tempstring);
			if(tempstring == "////") 
				return true;
			fin >> kindnumberofbook;
			fin >> onlyread;
			fin >> year1;
			fin >> month1;
			fin >> day1;
			fin >> year2;
			fin >> month2;
			fin >> day2;
			Book* TempBook;
			TempBook = new Book(kindnumberofbook, onlyread);
			TempBook->setBorrowedDate(Date(year1, month1, day1));
			TempBook->setReservedDate(Date(year2, month2, day2));
			fin >> tempbool;
			if(tempbool) TempBook->lendOut(); 
			else TempBook->returnIn();
			fin >> tempbool;
			TempBook->setReserveStatus(tempbool);
			fin >> tempbool;
			TempBook->setRenewStatus(tempbool);
			fin >> tempnumber;
			TempBook->setReaderNumberOfBook(tempnumber);
			fin >> tempnumber;
			TempBook->setReserveNumberOfBook(tempnumber);
			BookDAO::AllBooks.push_back(TempBook);
			std::getline(fin, tempstring); //把fin之后没读进去的回车读掉;
		}
	}
	else
		return false;
}

bool BookDAO::saveAll()
{
	std::wstring path = System::getWorkingDirectory() + L"\\" + System::getBookFileName();
	if (file_exists(wtos(path)))
	{
		std::ofstream fout(wtos(path));
		for (int i = 0; i < (int)BookDAO::AllBooks.size(); i++)
		{
			fout << "//" << std::endl; 
			fout << BookDAO::AllBooks[i]->getKindNumberOfBook() << std::endl;
			fout << BookDAO::AllBooks[i]->isBorrowable() << std::endl;
			fout << BookDAO::AllBooks[i]->getBorrowedDate().getYear() << std::endl;
			fout << BookDAO::AllBooks[i]->getBorrowedDate().getMonth() << std::endl;
			fout << BookDAO::AllBooks[i]->getBorrowedDate().getDay() << std::endl;
			fout << BookDAO::AllBooks[i]->getReservedDate().getYear() << std::endl;
			fout << BookDAO::AllBooks[i]->getReservedDate().getMonth() << std::endl;
			fout << BookDAO::AllBooks[i]->getReservedDate().getDay() << std::endl;
			fout << BookDAO::AllBooks[i]->isLentOut() << std::endl;
			fout << BookDAO::AllBooks[i]->getReserveStatus() << std::endl;
			fout << BookDAO::AllBooks[i]->getRenewStatus() << std::endl;
			fout << BookDAO::AllBooks[i]->getReaderNumberOfBook() << std::endl;
			fout << BookDAO::AllBooks[i]->getReserveNumberOfBook() << std::endl; 
		}
		fout << "////";
	}
	else
		return false;
	return true;
}

void BookDAO::create(int KindNumberOfBook, bool BookBorrowable)
{
	Book* TempBook;
	TempBook = new Book(KindNumberOfBook, BookBorrowable);
	BookDAO::AllBooks.push_back(TempBook);
}

void BookDAO::remove(Book const &book)
{
	for (int i = 0; i < (int)BookDAO::AllBooks.size(); i++)
	{
		if (BookDAO::AllBooks[i] == &book)
			BookDAO::AllBooks.erase(BookDAO::AllBooks.begin()+i);
	}
}