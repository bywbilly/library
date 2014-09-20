// Kind.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

#include <string>
#include <vector>

class Book;

class Kind
{
public:
	Kind(std::string const &isbn, std::wstring const &name, std::wstring const &authors, std::wstring const &index);
	virtual ~Kind();

	std::string getISBN() const;
	std::wstring getName() const;
	std::vector<std::wstring> getAuthors() const;
	std::wstring getIndex() const;

	void setISBN(std::string const &);
	void setName(std::wstring const &);
	void setAuthors(std::wstring const &);
	void setIndex(std::wstring const &);

	size_t countBooks() const;
	std::vector<Book *> getBooks() const;

    int getKindNumber() const;
    void setKindNumber(int);
    static void setKindNumberNow(int);
    static int getKindNumberNow();
private:
    std::string KindISBN;
    std::wstring KindName;
    std::wstring KindAuthors;
    std::wstring KindIndex;

	/*
	the id of the kind
	**/
    int KindNumber;

	/**
	used to get KindNumber  once used, it will ++  
	*/
    static int KindNumberNow;
};
