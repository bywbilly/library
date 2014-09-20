// Reader.cpp
// Author: Chen Qiming
// Date: 2010/12/27

#include "Reader.h"

int Reader::ReaderNumberNow;

Reader::Reader(std::string const &username, std::string const &password):User(username, password)
{
	ReaderNumber = ++ReaderNumberNow;
	PenaltyBefore = 0;
}

Reader::~Reader()
{

}

int Reader::getReaderNumber() const
{
    return ReaderNumber;
}

void Reader::setReaderNumber(int readernumber)
{
    ReaderNumber = readernumber;
}

void Reader::setReaderNumberNow(int readernumbernow)
{
	Reader::ReaderNumberNow = readernumbernow;
}

int Reader::getReaderNumberNow()
{
	return ReaderNumberNow;
}

void Reader::setPenaltyBefore(int penaltybefore)
{
	PenaltyBefore = penaltybefore;
}

int Reader::getPenaltyBefore()
{
	return PenaltyBefore;
}
