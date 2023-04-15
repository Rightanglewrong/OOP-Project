/*
Final Project Milestone 4
Module: Perishable
Filename: Perishable.h
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

#ifndef SDDS_PERISHABLE_H_
#define SDDS_PERISHABLE_H_
#include "Date.h"
#include "Item.h"

namespace sdds
{
    class Perishable : public Item
    {
    private:
        Date c_expiryDate;

    public:
        Perishable();
        char itemType() const;

        virtual std::ostream &write(std::ostream &ostr) const;
        virtual std::istream &read(std::istream &istr);
        virtual std::ifstream &load(std::ifstream &ifstr);
        virtual std::ofstream &save(std::ofstream &ofstr) const;
    };

}

#endif