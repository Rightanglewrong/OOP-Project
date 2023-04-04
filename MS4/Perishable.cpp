/*
Final Project Milestone 4
Module: Perishable
Filename: Perishable.cpp
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

#include <iomanip>
#include "Perishable.h"
#include "Item.h"

namespace sdds
{

    Perishable::Perishable() : Item(), c_expiryDate(){};

    char Perishable::itemType() const
    {
        return 'P';
    }

    std::ostream &Perishable::write(std::ostream &ostr) const
    {
        // if (Item::err.getError() == nullptr)
        if (*this)
        {
            Item::write(ostr);
            if (c_displayType == POS_LIST)
            {
                ostr << "  " << c_expiryDate << " |";
            }
            else
            {
                ostr << "Expiry date: " << c_expiryDate << std::endl;
                ostr << "=============^" << std::endl;
            }
        }
        return ostr;
    }

    std::istream &Perishable::read(std::istream &istr)
    {
        Item::read(istr);
        if (istr.good())
        {
            std::cout << "Expiry date (YYYY/MM/DD)" << std::endl;
            std::cout << "> ";
            Date date;
            date.dateOnly(true);
            date.read(istr);
            if (date.operator bool())
            {
                c_expiryDate = date;
            }
            else
            {
                Item::err = "Invalid Expiry in Date Entry";
            }
        }
        return istr;
    }

    std::ifstream &Perishable::load(std::ifstream &ifstr)
    {
        if (!ifstr.fail() || Item::err.getError() == nullptr)
        {
            Item::load(ifstr);
            if (Item::err.getError() == nullptr)
            {
                c_expiryDate = Date();
                c_expiryDate.dateOnly(true);
                ifstr.ignore(1);
                ifstr >> c_expiryDate;
                if (ifstr.fail())
                {
                    err = c_expiryDate.error();
                }
            }
        }
        return ifstr;
    }

    std::ofstream &Perishable::save(std::ofstream &ofstr) const
    {
        Item::save(ofstr);
        if (*this)
            ofstr << "," << c_expiryDate;
        return ofstr;
    }
}