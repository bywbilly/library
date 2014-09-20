// KindDAO.h
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
#include "Kind.h"

class KindDAO
{
public:
	/**
	 *	This method is called to read all Kind objects from some file.
	 *	You can get the current working directory using System::getWorkingDirectory().
	 *	You are supposed to call this method only once in ILibrary::initialize().
	 */
	static bool loadAll();
	
	/**
	 *	This method is called to write all Kind objects to some file.
	 *	You can get the current working directory using System::getWorkingDirectory().
	 *	You are supposed to call this method only once in ILibrary::finalize().
	 */
	static bool saveAll();

    static bool file_exists(std::string const &);
	static std::string wtos(const std::wstring &);
	static std::wstring stow(const std::string &);
		
	/**
	create a new kind
	*/
	static void create(std::string const &, std::wstring const &, std::wstring const &, std::wstring const &);

	/**
	remove kind
	*/
	static void remove(std::string const &);

	/**
	all the kind* are here
	*/
	static std::vector<Kind *> AllKinds;
};
