/*
Final Project Milestone 2
Module: Error
Filename: Error.cpp
Version 1.0
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/03/20  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#include <iostream>
#include <cstring>
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
        errMessage = new char[strlen(str) + 1];
        strcpy(errMessage, str);
    }

    // Copy & Assignment op
    Error::Error(Error &copy)
    {
        errMessage = nullptr;
        *this = copy;
    }

    Error &Error::operator=(Error &copy)
    {
        delete[] errMessage;
        errMessage = nullptr;
        if (copy)
        {
            errMessage = new char[strlen(copy.errMessage) + 1];
            strcpy(errMessage, copy.errMessage);
        }
        return *this;
    }

    Error &Error::operator=(const char *str)
    {
        delete[] errMessage;
        if (str != nullptr && str[0] != '\0')
        {
            errMessage = new char[strlen(str) + 1];
            strcpy(errMessage, str);
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
        return (errMessage != nullptr);
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
        return error.display(ostr);
    }

}