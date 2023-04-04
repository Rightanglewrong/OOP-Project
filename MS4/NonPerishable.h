/*
Final Project Milestone 4
Module: NonPerishable
Filename: NonPerishable.h
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

#ifndef SDDS_NONPERISHABLE_H_
#define SDDS_NONPERISHABLE_H_
#include "Item.h"

namespace sdds
{
    class NonPerishable : public Item
    {
    public:
        char itemType() const;
        std::ostream &write(std::ostream &ostr) const;
    };
}

#endif