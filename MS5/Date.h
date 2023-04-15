/*
Final Project Milestone 4
Module: Date
Filename: Date.h
Version 1.0
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/03/20  Preliminary release
2023/04/04  Milestone 4 Release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#ifndef SDDS_DATE_H_
#define SDDS_DATE_H_
#include <iostream>
#include "Error.h"

namespace sdds
{
    class Date
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        bool c_dateOnly;
        Error err;

        // Given Func
        void getSystemDate(int &year, int &mon, int &day, int &hour, int &min, bool dateOnly);

        void validate();

    public:
        // Constructors
        Date();
        Date(int year, int month, int day);
        Date(int year, int month, int day, int hour);
        Date(int year, int month, int day, int hour, int minute);
        Date(Date &src);

        // Setter
        Date &dateOnly(bool dateOnly);

        // Getter
        Error &error();

        // Overloaded Operators
        operator bool() const;
        std::istream &read(std::istream &istr = std::cin);
        std::ostream &display(std::ostream &ostr = std::cout) const;

        // Overloaded Comparisons Operators
        bool operator==(const Date other) const;
        bool operator!=(const Date other) const;
        bool operator<(const Date other) const;
        bool operator>(const Date other) const;
        bool operator<=(const Date other) const;
        bool operator>=(const Date other) const;
    };
    // Given Func
    int uniqueDateValue(int year, int mon, int day, int hour, int min);
    // Given Func
    int daysOfMonth(int year, int month);

    std::ostream &operator<<(std::ostream &ostr, const Date &date);
    std::istream &operator>>(std::istream &istr, Date &date);
}

#endif