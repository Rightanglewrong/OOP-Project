/*
Final Project Milestone 4
Module: PosIO
Filename: PosIO.h
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

#ifndef SDDS_POSIO_H_
#define SDDS_POSIO_H_
#include <iostream>
#include <fstream>

#include "POS.h"

namespace sdds
{
    class PosIO
    {
    public:
        virtual std::ostream &write(std::ostream &ostr) const = 0;
        virtual std::istream &read(std::istream &istr) = 0;
        virtual std::ofstream &save(std::ofstream &ofstr) const = 0;
        virtual std::ifstream &load(std::ifstream &ifstr) = 0;
        virtual ~PosIO(){};
    };
    std::ostream &operator<<(std::ostream &ostr, const PosIO &obj);
    std::istream &operator>>(std::istream &istr, PosIO &obj);
    std::ofstream &operator<<(std::ofstream &ofstr, const PosIO &obj);
    std::ifstream &operator>>(std::ifstream &ifstr, PosIO &obj);
}

#endif