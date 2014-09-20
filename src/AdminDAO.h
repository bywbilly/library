// AdminDAO.h
// Author: Chen Qiming
// Date: 2010/12/27

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include "System.h"
#include "Admin.h"

class AdminDAO
{
public:
	/**
	 *	This method is called to read all Admin objects from some file.
	 *	You can get the current working directory using System::getWorkingDirectory().
	 *	You are supposed to call this method only once in ILibrary::initialize().
	 */
	static bool loadAll();
	
	/**
	 *	This method is called to write all Admin objects to some file.
	 *	You can get the current working directory using System::getWorkingDirectory().
	 *	You are supposed to call this method only once in ILibrary::finalize().
	 */
	static bool saveAll();
	
	/**
	create a new admin
	 */
	static void create(std::string const &, std::string const &);
	
	/**
	remove a admin
	 */
	static void remove(std::string const &username);

	static bool file_exists(std::string const &);
	
	static std::string wtos(const std::wstring &);
	
	static std::wstring stow(const std::string &);

	/**
	all the admin* is here
	 */
	static std::vector<Admin *> AllAdmins;
};
