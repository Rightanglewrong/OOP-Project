/*
Final Project Milestone 4
Module: PosIO
Filename: PosIO.cpp
Version 1.0
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/03/26  Preliminary Release
2023/04/04  Milestone 4 Release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#include <iostream>
#include <fstream>
#include "PosIO.h"

namespace sdds
{   
    std::ostream &operator<<(std::ostream &ostr, const PosIO &obj)
    {
        obj.write(ostr);
        return ostr;
    }

    std::istream &operator>>(std::istream &istr, PosIO &obj)
    {
        obj.read(istr);
        return istr;
    }

    std::ofstream &operator<<(std::ofstream &ofstr, const PosIO &obj)
    {
        obj.save(ofstr);
        return ofstr;
    }

    std::ifstream &operator>>(std::ifstream &ifstr, PosIO &obj)
    {
        obj.load(ifstr);
        return ifstr;
    }
}