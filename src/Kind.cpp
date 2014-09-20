// Kind.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "Kind.h"
#include "BookDAO.h"
#include "Book.h"

int Kind::KindNumberNow;
std::vector<class Book *> BookDAO::AllBooks;

Kind::Kind(std::string const &isbn, std::wstring const &name, std::wstring const &authors, std::wstring const &index)
{
    KindISBN = isbn;
    KindName = name;
    KindAuthors = authors;
    KindIndex = index;
	KindNumber = ++Kind::KindNumberNow;
}

Kind::~Kind()
{

}

std::string Kind::getISBN() const
{
    return KindISBN;
}

std::wstring Kind::getName() const
{
    return KindName;
}

std::vector<std::wstring> Kind::getAuthors() const
{
    std::vector<std::wstring> AuthorsVector;
	AuthorsVector.clear();
	int mark = -1;
	for (int i = 0; i < (int)KindAuthors.length(); i++)
	{
		if (KindAuthors[i] == L',' || KindAuthors[i] == L'£¬')
		{
			AuthorsVector.push_back(KindAuthors.substr(mark + 1, i - mark - 1));
			mark = i;
		}
	}
	AuthorsVector.push_back(KindAuthors.substr(mark + 1));
	for (int i = 0; i < (int)AuthorsVector.size(); i++)
	{
		AuthorsVector[i] = AuthorsVector[i].substr(0, AuthorsVector[i].find_last_not_of(' ') + 1);
		if (AuthorsVector[i] != L"") 
			AuthorsVector[i] = AuthorsVector[i].substr(AuthorsVector[i].find_first_not_of(' '));
	}
	for (int i = 0; i < (int)AuthorsVector.size(); ++i)
	{
		if (AuthorsVector[i] == L"") 
		{
			AuthorsVector.erase(AuthorsVector.begin() + i);
			i--;
		}
	}
	return AuthorsVector;
}

std::wstring Kind::getIndex() const
{
    return KindIndex;
}

void Kind::setISBN(std::string const & isbn)
{
    KindISBN = isbn;
}

void Kind::setName(std::wstring const & name)
{
    KindName = name;
}

void Kind::setAuthors(std::wstring const & authors)
{
    KindAuthors = authors;
}

void Kind::setIndex(std::wstring const & index)
{
    KindIndex = index;
}

size_t Kind::countBooks() const
{
    return Kind::getBooks().size();
}

std::vector<Book *> Kind::getBooks() const
{
    std::vector<Book *> BookVector;
    for (int i = 0; i < (int)BookDAO::AllBooks.size(); i++)
    {
        if (BookDAO::AllBooks[i]->getKindNumberOfBook() == getKindNumber())
        {
            BookVector.push_back(BookDAO::AllBooks[i]);
        }
    }
    return BookVector;
}

int Kind::getKindNumber() const
{
	return KindNumber;
}

void Kind::setKindNumberNow(int kindnumbernow)
{
	Kind::KindNumberNow = kindnumbernow;
}

int Kind::getKindNumberNow()
{
	return Kind::KindNumberNow;
}

void Kind::setKindNumber(int kindnumber)
{
    KindNumber = kindnumber;
}
