// AdminDAO.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "AdminDAO.h"
#include <string>

std::vector<class Admin *> AdminDAO::AllAdmins;

std::string AdminDAO::wtos(const std::wstring &w)
{
	int	len = WideCharToMultiByte(GetACP(), 0, w.c_str(), -1, NULL, 0, NULL, NULL);
	char *buf = new char[len];
	WideCharToMultiByte(GetACP(), 0, w.c_str(), -1, buf, len, NULL, NULL);
	std::string s(buf);
	delete[] buf;
	return s;
}

std::wstring AdminDAO::stow(const std::string &s)
{
	int len = MultiByteToWideChar(GetACP(), 0, s.c_str(), -1, NULL, 0);
	wchar_t*buf = new wchar_t[len];
	MultiByteToWideChar(GetACP(), 0, s.c_str(), -1, buf, len);
	std::wstring w(buf);
	delete[] buf;
	return w;
}

bool AdminDAO::file_exists(std::string const &path)
{
	std::fstream f(path.c_str());
	bool exists = f.is_open();
	f.close();
	return exists;
}

bool AdminDAO::loadAll()
{
	AdminDAO::AllAdmins.clear();
	std::wstring path = System::getWorkingDirectory() + L"\\" + System::getAdminFileName();
	if (file_exists(wtos(path)))
	{
		std::ifstream fin(wtos(path));
		std::string Username;
		std::string Password;
		std::string tempstring;
		while (1)
		{
			std::getline(fin, tempstring);
			if (tempstring == "////") 
				return true;
			std::getline(fin, Username);
			std::getline(fin, Password);
			Admin * TempAdmin;
			TempAdmin = new Admin(Username, Password);
			AdminDAO::AllAdmins.push_back(TempAdmin);		
		}
	}
	else
		return false;
	return true;
}

bool AdminDAO::saveAll()
{
	std::wstring path = System::getWorkingDirectory() + L"\\" + System::getAdminFileName();
	if (file_exists(wtos(path)))
	{
		std::ofstream fout(wtos(path));
		for (int i = 0; i < (int)AdminDAO::AllAdmins.size(); i++)
		{
			fout << "//" << std::endl;
			fout << (* AdminDAO::AllAdmins[i]).getUsername() << std::endl;
			fout << (* AdminDAO::AllAdmins[i]).getPassword() << std::endl;
		}
		fout << "////";
	}
	else
		return false;
	return true;
}

void AdminDAO::create(std::string const &username, std::string const &password)
{
	Admin* TempAdmin;
	TempAdmin = new Admin(username, password);
	AdminDAO::AllAdmins.push_back(TempAdmin);
}

void AdminDAO::remove(std::string const &username)
{
	for (int i = 0; i < (int)AdminDAO::AllAdmins.size(); i++)
	{
		if (AdminDAO::AllAdmins[i]->getUsername() == username)
			AdminDAO::AllAdmins.erase(AdminDAO::AllAdmins.begin()+i);
	}
}