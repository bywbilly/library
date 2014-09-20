// BookDAO.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include "System.h"
#include "Book.h"

class Book;

class BookDAO
{
public:
	/**
	 *	This method is called to read all Book objects from some file.
	 *	You can get the current working directory using System::getWorkingDirectory().
	 *	You are supposed to call this method only once in ILibrary::initialize().
	 */
	static bool loadAll();

	/**
	 *	This method is called to write all Book objects to some file.
	 *	You can get the current working directory using System::getWorkingDirectory().
	 *	You are supposed to call this method only once in ILibrary::finalize().
	 */
	static bool saveAll();

	static bool file_exists(std::string const &);
	
	static std::string wtos(const std::wstring &);
	
	static std::wstring stow(const std::string &);

	/**
	all the book* are here
	*/
	static std::vector<Book *> AllBooks;

	/**
	create a new book
	*/
	static void create(int KindNumberOfBook, bool BookBorrowable);

	/**
	remove a book
	*/
	static void remove(Book const&);
};
