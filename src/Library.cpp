// Library.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "Library.h"
#include "ReaderDAO.h"
#include "AdminDAO.h"
#include "BookDAO.h"
#include "KindDAO.h"

Library::Library()
{

}

Library::~Library()
{

}

bool Library::initialize()
{
	if (!BookDAO::loadAll())return false;
	if (!AdminDAO::loadAll())return false;
	if (!ReaderDAO::loadAll())return false;
	if (!KindDAO::loadAll())return false;
	return true;
}

void Library::finalize()
{
	BookDAO::saveAll();
	KindDAO::saveAll();
	ReaderDAO::saveAll();
	AdminDAO::saveAll();
}

Reader *Library::readerLogin(std::string const &username, std::string const &password)
{
	for (int i = 0; i < (int)ReaderDAO::AllReaders.size(); i++)
	{
		if (ReaderDAO::AllReaders[i]->getUsername() == username && ReaderDAO::AllReaders[i]->getPassword() == password)
			return ReaderDAO::AllReaders[i];
	}
	return NULL;
}

Admin *Library::adminLogin(std::string const &username, std::string const &password)
{
	for (int i = 0; i < (int)AdminDAO::AllAdmins.size(); i++)
	{
		if (AdminDAO::AllAdmins[i]->getUsername() == username && AdminDAO::AllAdmins[i]->getPassword() == password)
			return AdminDAO::AllAdmins[i];
	}
	return NULL;
}

std::vector<Kind *> Library::searchByISBN(std::string const &isbn)
{
	std::vector<Kind *> TempVector;
	for (int i = 0; i < (int)KindDAO::AllKinds.size(); i++)
	{
		if (KindDAO::AllKinds[i]->getISBN() == isbn)
		{
			TempVector.push_back(KindDAO::AllKinds[i]);
		}
	}
	return TempVector;
}

std::vector<Kind *> Library::searchByName(std::wstring const &name)
{
	std::vector<Kind *> TempVector;
	for (int i = 0; i < (int)KindDAO::AllKinds.size(); i++)
	{
		if (KindDAO::AllKinds[i]->getName() == name)
		{
			TempVector.push_back(KindDAO::AllKinds[i]);
		}
	}
	return TempVector;
}

std::vector<Kind *> Library::searchByAuthor(std::wstring const &author)
{
	std::vector<Kind *> TempVector;
	for (int i = 0; i < (int)KindDAO::AllKinds.size(); i++)
	{
		for (int j = 0; j < (int)KindDAO::AllKinds[i]->getAuthors().size(); j++)
		{
			if (KindDAO::AllKinds[i]->getAuthors()[j] == author)
			TempVector.push_back(KindDAO::AllKinds[i]);
		}
	}
	return TempVector;
}

std::vector<Kind *> Library::searchByIndex(std::wstring const &index)
{
	std::vector<Kind *> TempVector;
	for (int i = 0; i < (int)KindDAO::AllKinds.size(); i++)
	{
		if (KindDAO::AllKinds[i]->getIndex() == index)
		{
			TempVector.push_back(KindDAO::AllKinds[i]);
		}
	}
	return TempVector;
}

std::vector<Kind *> Library::searchByExpression(std::wstring const &expr)
{
	std::vector<Kind *> TempVector;
	TempVector.clear();
	return TempVector;
}

std::vector<Kind *> Library::searchLikeName(std::wstring const &name)
{
	std::vector<Kind *> TempVector;
	TempVector.clear();
	return TempVector;
}

enum ReorderType { ORDER_BY_ISBN, ORDER_BY_NAME, ORDER_BY_INDEX, ORDER_BY_COPY_COUNT };

void Library::reorderResults(std::vector<Kind *> &kinds, ILibrary::ReorderType reorderType, bool descending)
{

}