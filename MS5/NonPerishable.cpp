/*
Final Project Milestone 4
Module: NonPerishable
Filename: NonPerishable.cpp
Version 1.0
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/04/04  Milestone 4 Release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#include "NonPerishable.h"
#include <iostream>
#include <fstream>

namespace sdds
{
    char NonPerishable::itemType() const
    {
        return 'N';
    }

    std::ostream& NonPerishable::write(std::ostream &ostr) const
    {
        if (err.getError() == nullptr)
        {
            Item::write(ostr);
            if (c_displayType == 1)
            {
                ostr << "     N / A   |";
            }
            else
            {
                ostr << "=============^" << std::endl;
            }
        }
        return ostr;
    }
}