// Admin.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "Admin.h"
#include "ReaderDAO.h"
#include "AdminDAO.h"
#include "KindDAO.h"
#include "ReaderDAO.h"
#include "Book.h"

Admin::Admin(std::string const &username, std::string const &password):User(username, password)
{
	
}

Admin::~Admin()
{

}

bool Admin::createReader(std::string const &username, std::string const &password, Reader::Type type)
{
	if (username == "") 
		return false;
	if (password == "") 
		return false;
	if (!IsVisibleString(password)) 
		return false;
	for (int i = 0; i < (int)ReaderDAO::AllReaders.size(); i++)
	{
		if (ReaderDAO::AllReaders[i]->getUsername() == username) 
			return false;
	}
	ReaderDAO::create(username, password, type);
	return true;
}

bool Admin::removeReader(std::string const &username)
{
	for (int i = 0; i < (int)ReaderDAO::AllReaders.size(); i++)
	{
		if (ReaderDAO::AllReaders[i]->getUsername() == username)
		{
			if (ReaderDAO::AllReaders[i]->getBorrowedBooks().size())
				return false;
			if (ReaderDAO::AllReaders[i]->getReservedBooks().size())
				return false;
			ReaderDAO::remove(username);
			return true;
		}
	}
	return false;
}

bool Admin::createAdmin(std::string const &username, std::string const &password)
{
	if (username == "") 
		return false;
	if (password == "") 
		return false;
	if (!IsVisibleString(password)) 
		return false;
	for (int i = 0; i < (int)AdminDAO::AllAdmins.size(); i++)
	{
		if (AdminDAO::AllAdmins[i]->getUsername() == username) 
			return false;
	}
	AdminDAO::create(username, password);
	return true;
}

bool Admin::removeAdmin(std::string const &username)
{
	if (username == getUsername()) 
		return false;
	for (int i = 0; i < (int)AdminDAO::AllAdmins.size(); i++)
	{
		if (AdminDAO::AllAdmins[i]->getUsername() == username) 
		{
			AdminDAO::remove(username);
			return true;
		}
	}
	return false;
}

bool Admin::createKind(std::string const &isbn, std::wstring const &name, std::wstring const &authors, std::wstring const &index)
{
	if (name == L"") 
		return false;
	if (index == L"") 
		return false;
	if (authors == L"") 
		return false;
	for (int i = 0; i < (int)KindDAO::AllKinds.size(); i++)
	{
		if (KindDAO::AllKinds[i]->getISBN() == isbn) 
			return false;
	}
	KindDAO::create(isbn, name, authors, index);
	return true;
}

bool Admin::removeKind(std::string const &isbn)
{
	for (int i = 0; i < (int)KindDAO::AllKinds.size(); i++)
	{
		if (KindDAO::AllKinds[i]->getISBN() == isbn) 
		{
			for (int j = 0; j < (int)KindDAO::AllKinds[i]->getBooks().size(); j++)
			{
				if (KindDAO::AllKinds[i]->getBooks()[j]->isLentOut()) 
					return false;
				if (KindDAO::AllKinds[i]->getBooks()[j]->getReserveStatus() 
					&& KindDAO::AllKinds[i]->getBooks()[j]->getReservedDate().getNumber() + System::getReservedBookExpiredDays() > System::getCurrentDate().getNumber())
					return false;
			}
			KindDAO::remove(isbn);
			return true;
		}
	}
	return false;
}

bool Admin::createBook(Kind const &kind, bool borrowable)
{
	BookDAO::create(kind.getKindNumber(), borrowable);
	return true;
}

bool Admin::removeBook(Book const &book)
{
	if (book.isLentOut()) 
		return false;
	if (book.getReserveStatus()) 
		return false;
	BookDAO::remove(book);
	return true;
}

std::vector<Reader const *> Admin::getAllReaders()
{
	std::vector<Reader const *> allReaders;
	for (int i = 0; i < (int)ReaderDAO::AllReaders.size(); i++)
	{
		allReaders.push_back(ReaderDAO::AllReaders[i]);
	}
	return allReaders;
}

std::vector<Admin const *> Admin::getAllAdmins()
{
	std::vector<Admin const *> allAdmins;
	for (int i = 0; i < (int)AdminDAO::AllAdmins.size(); i++)
	{
		allAdmins.push_back(AdminDAO::AllAdmins[i]);
	}
	return allAdmins;
}

Reader *Admin::getReaderByName(std::wstring const &name)
{
	for (int i = 0; i < (int)ReaderDAO::AllReaders.size(); i++)
	{
		if (ReaderDAO::AllReaders[i]->getUsername() == ReaderDAO::wtos(name))
			return ReaderDAO::AllReaders[i];
	}
	return NULL;
}

Admin *Admin::getAdminByName(std::wstring const &name)
{
	for (int i = 0; i < (int)AdminDAO::AllAdmins.size(); i++)
	{
		if (AdminDAO::AllAdmins[i]->getUsername() == AdminDAO::wtos(name))
			return AdminDAO::AllAdmins[i];
	}
	return NULL;
}

bool Admin::IsVisibleString(const std::string &str)
{
	bool result = true;
	for (std::string::const_iterator iter = str.begin(); iter != str.end(); ++iter)   
	{   
		if ((unsigned char)(*iter) < 32 || (unsigned char)(*iter) > 126)   
		{   
			result = false;
			break;
		}
	}
	return result;
}
