// ReaderDAO.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "ReaderDAO.h"
#include "Student.h"
#include "Teacher.h"
#include <string>

std::vector<class Reader *> ReaderDAO::AllReaders;

std::string ReaderDAO::wtos(const std::wstring &w)
{
	int	len = WideCharToMultiByte(GetACP(), 0, w.c_str(), -1, NULL, 0, NULL, NULL);
	char *buf = new char[len];
	WideCharToMultiByte(GetACP(), 0, w.c_str(), -1, buf, len, NULL, NULL);
	std::string s(buf);
	delete[] buf;
	return s;
}

std::wstring ReaderDAO::stow(const std::string &s)
{
	int len = MultiByteToWideChar(GetACP(), 0, s.c_str(), -1, NULL, 0);
	wchar_t*buf = new wchar_t[len];
	MultiByteToWideChar(GetACP(), 0, s.c_str(), -1, buf, len);
	std::wstring w(buf);
	delete[] buf;
	return w;
}

bool ReaderDAO::file_exists(std::string const &path)
{
    std::fstream f(path.c_str());
    bool exists = f.is_open();
    f.close();
    return exists;
}

bool ReaderDAO::loadAll()
{
	ReaderDAO::AllReaders.clear();
	std::wstring path = System::getWorkingDirectory() + L"\\" + System::getReaderFileName();
	if (file_exists(wtos(path)))
	{
		std::ifstream fin(wtos(path));
		int ReaderNumberNow = 0;
		Reader::setReaderNumberNow(0);
		std::string Username;
		std::string Password;
		std::string type;
		int readernumber;
		int penaltybefore;
		fin >> ReaderNumberNow;
		std::string tempstring;
		while (1)
		{
			std::getline(fin, tempstring);//把fin没读进去的回车读掉
			std::getline(fin, tempstring);
			if(tempstring == "////") 
				return true;
			std::getline(fin, type);
			std::getline(fin, Username);
			std::getline(fin, Password);
			fin >> readernumber;
			fin >> penaltybefore;
			if (type == "STUDENT")
			{
				Reader* TempStudent;
				TempStudent = new Student(Username, Password);
				TempStudent->setReaderNumber(readernumber);
				TempStudent->setPenaltyBefore(penaltybefore);
				ReaderDAO::AllReaders.push_back(TempStudent);
			}
			if (type == "TEACHER")
			{
				Reader* TempTeacher;
				TempTeacher = new Teacher(Username, Password);
				TempTeacher->setReaderNumber(readernumber);
				TempTeacher->setPenaltyBefore(penaltybefore);
				ReaderDAO::AllReaders.push_back(TempTeacher);
			}
		}
		Reader::setReaderNumberNow(ReaderNumberNow);
	}
	else
		return false;
	return true;
}

bool ReaderDAO::saveAll()
{
	std::wstring path = System::getWorkingDirectory() + L"\\" + System::getReaderFileName();
	if (file_exists(wtos(path)))
	{
		std::ofstream fout(wtos(path));
		int number = Reader::getReaderNumberNow();
		fout << number << std::endl;
		for (int i = 0; i < (int)ReaderDAO::AllReaders.size(); i++)
		{
			fout << "//" << std::endl;
			if ((* ReaderDAO::AllReaders[i]).getType() == Reader::STUDENT)
				fout << "STUDENT" << std::endl;
			if ((* ReaderDAO::AllReaders[i]).getType() == Reader::TEACHER)
				fout << "TEACHER" << std::endl;
			fout << (* ReaderDAO::AllReaders[i]).getUsername() << std::endl;
			fout << (* ReaderDAO::AllReaders[i]).getPassword() << std::endl;
			fout << (* ReaderDAO::AllReaders[i]).getReaderNumber() << std::endl;
			fout << (* ReaderDAO::AllReaders[i]).getPenaltyBefore() << std::endl;
		}
		fout << "////";
	}
	else
		return false;
	return true;
}

void ReaderDAO::create(std::string const &username, std::string const &password, Reader::Type type)
{
	if (type == Reader::STUDENT)
	{
		Reader* TempStudent;
		TempStudent = new Student(username, password);
		Reader::setReaderNumberNow(Reader::getReaderNumberNow());
		(*TempStudent).setReaderNumber(Reader::getReaderNumberNow());
		(*TempStudent).setPenaltyBefore(0);
		ReaderDAO::AllReaders.push_back(TempStudent);
	}
	if (type == Reader::TEACHER)
	{
		Reader* TempTeacher;
		TempTeacher = new Teacher(username, password);
		Reader::setReaderNumberNow(Reader::getReaderNumberNow());
		(*TempTeacher).setReaderNumber(Reader::getReaderNumberNow());
		(*TempTeacher).setPenaltyBefore(0);
		ReaderDAO::AllReaders.push_back(TempTeacher);
	}
}

void ReaderDAO::remove(std::string const &username)
{
	for (int i = 0; i < (int)ReaderDAO::AllReaders.size(); i++)
	{
		if (ReaderDAO::AllReaders[i]->getUsername() == username)
			ReaderDAO::AllReaders.erase(ReaderDAO::AllReaders.begin()+i);
	}
}
