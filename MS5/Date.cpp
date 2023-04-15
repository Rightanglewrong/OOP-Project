/*
Final Project Milestone 4
Module: Date
Filename: Date.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Date.h"
#include "POS.h"
using namespace std;

namespace sdds
{
    // Given Funcs
    void Date::getSystemDate(int &year, int &mon, int &day, int &hour, int &min, bool dateOnly)
    {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if (dateOnly)
        {
            hour = min = 0;
        }
        else
        {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }

    int uniqueDateValue(int year, int mon, int day, int hour, int min)
    {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
    }

    int daysOfMonth(int year, int month)
    {
        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    // Constructor
    Date::Date()
    {
        c_dateOnly = false;
        getSystemDate(year, month, day, hour, minute, c_dateOnly);
    }

    Date::Date(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
        hour = 0;
        minute = 0;
        c_dateOnly = true;
        validate();
    }

    Date::Date(int y, int mon, int d, int h)
    {
        c_dateOnly = false;
        year = y;
        month = mon;
        day = d;
        hour = h;
        minute = 0;
        validate();
    }

    Date::Date(int y, int mon, int d, int h, int min)
    {
        c_dateOnly = false;
        year = y;
        month = mon;
        day = d;
        hour = h;
        minute = min;
        validate();
    }

    // Copy Constructor
    Date::Date(Date &src)
    {
        year = src.year;
        month = src.month;
        day = src.day;
        hour = src.hour;
        minute = src.minute;
        c_dateOnly = src.c_dateOnly;
        err = src.err;
    }

    // Setter
    void Date::validate()
    {
        bool flag = true;
        if (year < MIN_YEAR || year > MAX_YEAR)
        {
            flag = false;
            err = "Invalid Year";
        }
        if ((month < 1 || month > 12) && flag)
        {
            flag = false;
            err = "Invalid Month";
        }
        if ((day < 1 || day > daysOfMonth(year, month)) && flag)
        {
            flag = false;
            err = "Invalid Day";
        }
        if ((hour < 0 || hour > 23) && flag && !c_dateOnly)
        {
            flag = false;
            err = "Invalid Hour";
        }
        if ((minute < 0 || minute > 59) && flag && !c_dateOnly)
        {
            flag = false;
            err = "Invlid Minute";
        }
    }
    // Setter
    Date &Date::dateOnly(bool value)
    {
        if (value)
        {
            hour = minute = 0;
            c_dateOnly = value;
        }
        else
        {
            c_dateOnly = value;
        }
        return *this;
    }

    // Getter
    Error &Date::error()
    {
        return err;
    }

    Date::operator bool() const
    {
        return !(err.operator bool());
    }

    // Overloaded Comparisons Operators
    bool Date::operator==(const Date other) const
    {
        int src = uniqueDateValue(year, month, day, hour, minute);
        int rhs = uniqueDateValue(other.year, other.month, other.day, other.hour, other.minute);
        return src == rhs;
    }

    bool Date::operator!=(const Date other) const
    {
        int src = uniqueDateValue(year, month, day, hour, minute);
        int rhs = uniqueDateValue(other.year, other.month, other.day, other.hour, other.minute);
        return src != rhs;
    }

    bool Date::operator<(const Date other) const
    {
        int src = uniqueDateValue(year, month, day, hour, minute);
        int rhs = uniqueDateValue(other.year, other.month, other.day, other.hour, other.minute);
        return src < rhs;
    }

    bool Date::operator>(const Date other) const
    {
        int src = uniqueDateValue(year, month, day, hour, minute);
        int rhs = uniqueDateValue(other.year, other.month, other.day, other.hour, other.minute);
        return src > rhs;
    }

    bool Date::operator<=(const Date other) const
    {
        int src = uniqueDateValue(year, month, day, hour, minute);
        int rhs = uniqueDateValue(other.year, other.month, other.day, other.hour, other.minute);
        return src <= rhs;
    }

    bool Date::operator>=(const Date other) const
    {
        int src = uniqueDateValue(year, month, day, hour, minute);
        int rhs = uniqueDateValue(other.year, other.month, other.day, other.hour, other.minute);
        return src >= rhs;
    }

    // Helpers and funcs for read and display
    ostream &Date::display(ostream &ostr) const
    {
        if (err)
        {
            ostr << err << "(";
        }
        ostr << year << "/";
        ostr << std::right << setfill('0') << std::setw(2) << month << "/" << setw(2) << day;
        if (!c_dateOnly)
        {
            ostr << ", " << setfill('0') << setw(2) << hour << ":" << setw(2) << minute;
        }
        if (err)
        {
            ostr << ")";
        }
        ostr << setfill(' ') << std::left;

        return ostr;
    }

    istream &Date::read(istream &istr)
    {
        err.clear();
        year = month = day = hour = minute = 0;
        // bool flag = true;
        char delim;

        if (!(istr >> year))
        {
            err = "Cannot read year entry";
            return istr;
        }
        istr >> delim;

        if (!(istr >> month))
        {
            err = "Cannot read month entry";
            return istr;
        }
        istr >> delim;

        if (!(istr >> day))
        {
            err = "Cannot read day entry";
            return istr;
        }

        if (!c_dateOnly)
        {
            istr >> delim;
            if (!(istr >> hour))
            {
                err = "Cannot read hour entry";
                return istr;
            }
            istr >> delim;

            if (!(istr >> minute))
            {
                err = "Cannot read minute entry";
                return istr;
            }
        }
        else
        {
            hour = 0;
            minute = 0;
        }
        
        return istr;
    }

    // Helper
    ostream &operator<<(ostream &ostr, const Date &date)
    {
        return date.display(ostr);
    }

    istream &operator>>(istream &istr, Date &date)
    {
        return date.read(istr);
    }
}