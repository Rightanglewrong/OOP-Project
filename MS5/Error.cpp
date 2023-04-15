/*
Final Project Milestone 4
Module: Error
Filename: Error.cpp
Version 1.1
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/03/20  Preliminary release
2023/03/26  Milestone 3
2023/04/04  Milestone 4 Release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "POS.h"
#include "Error.h"

using namespace std;
namespace sdds
{
	// Constructors
	Error::Error()
	{
		errMessage = nullptr;
	}

	Error::Error(const char *str)
	{
		if (errMessage != nullptr && errMessage[0] != '\0')
		{
			errMessage = new char[strlen(str) + 1];
			strcpy(errMessage, str);
			errMessage[strlen(str)] = '\0';
		}
		else
		{
			errMessage = nullptr;
		}
	}

	// Copy & Assignment op
	Error::Error(const Error &copy)
	{
		if (copy.errMessage != nullptr)
		{
			errMessage = new char[strlen(copy.errMessage) + 1];
			strcpy(errMessage, copy.errMessage);
		}
		else
		{
			errMessage = nullptr;
		}
	}

	Error &Error::operator=(const Error &copy)
	{
		if (*this != copy)
		{
			if (errMessage != nullptr)
			{
				delete[] errMessage;
				errMessage = nullptr;
			}
			errMessage = nullptr;
			if (copy.errMessage != nullptr)
			{
				errMessage = new char[strlen(copy.errMessage) + 1];
				strcpy(errMessage, copy.errMessage);
			}
			else
			{
				errMessage = nullptr;
			}
		}
		return *this;
	}

	Error &Error::operator=(const char *str)
	{
		if (errMessage != nullptr && errMessage[0] != '\0')
		{
			delete[] errMessage;
			errMessage = nullptr;
			errMessage = new char[strlen(str) + 1];
			strcpy(errMessage, str);
		}
		else
		{
			// errMessage = new char[strlen(str) + 1];
			// strcpy(errMessage, str);
			if (errMessage != nullptr)
			{
				delete[] errMessage;
			}
			errMessage = nullptr;
		}
		return *this;
	}

	Error::~Error()
	{
		delete[] errMessage;
		errMessage = nullptr;
	}

	// Getters
	Error::operator bool() const
	{
		return (errMessage != nullptr && errMessage[0] != '\0');
	}

	const char *Error::getError() const
	{
		return errMessage;
	}

	// Setters
	Error &Error::clear()
	{
		delete[] errMessage;
		errMessage = nullptr;
		return *this;
	}

	std::ostream &Error::display(std::ostream &ostr) const
	{
		if (*this)
		{
			ostr << errMessage;
		}
		return ostr;
	}
	// Helper
	std::ostream &operator<<(std::ostream &ostr, const Error &error)
	{
		// return error.display(ostr);
		const char *tempError = error.getError();
		if (tempError != nullptr && tempError[0] != '\0')
		{
			ostr << tempError;
		}
		return ostr;
	}
}