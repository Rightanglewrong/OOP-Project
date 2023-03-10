/*
Final Project Milestone 1
Module: POS
Filename: PosApp.cpp
Version 1.0
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/03/09  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#ifndef SDDS_POSAPP_H_
#define SDDS_POSAPP_H_
#include <iostream>

namespace sdds
{
    class PosApp
    {
        char fileName[255];

    public:
        // Constructors
        PosApp();
        PosApp(const char *file);

        // Copy Constructors
        PosApp(const PosApp &src) = delete;
        PosApp &operator=(const PosApp &src) = delete;

        // Setters
        std::ostream &stockItem(std::ostream &ostr = std::cout);
        std::ostream &removeItem(std::ostream &ostr = std::cout);
        std::ostream &saveRecs(std::ostream &ostr = std::cout);
        std::ostream &loadRecs(std::ostream &ostr = std::cout);
        std::ostream &addItem(std::ostream &ostr = std::cout);

        // Getters
        std::ostream &listItems(std::ostream &ostr = std::cout) const;
        std::ostream &POS(std::ostream &ostr = std::cout);

        // Display
        int menu();

        void run();
        // Deconstructors
        ~PosApp();
    };
    // Helper
};
#endif