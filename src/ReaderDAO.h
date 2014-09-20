// ReaderDAO.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <iostream>
#include "System.h"
#include "Reader.h"

class ReaderDAO
{
public:
	/**
	 *	This method is called to read all Reader objects from some file.
	 *	You can get the current working directory using System::getWorkingDirectory().
	 *	You are supposed to call this method only once in ILibrary::initialize().
	 */
	static bool loadAll();

	/**
	 *	This method is called to write all Reader objects to some file.
	 *	You can get the current working directory using System::getWorkingDirectory().
	 *	You are supposed to call this method only once in ILibrary::finalize().
	 */
	static bool saveAll();

	/**
	create a new reader
	*/
    static void create(std::string const &, std::string const &, Reader::Type);
	
	/**
	remove reader
	*/
	static void remove(std::string const &username);

    static bool file_exists(std::string const &);
	static std::string wtos(const std::wstring &);
	static std::wstring stow(const std::string &);

	/**
	all the reader* are here
	*/
	static std::vector<Reader *> AllReaders;

};
