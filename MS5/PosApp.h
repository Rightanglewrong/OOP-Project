/*
Final Project Milestone 5
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
2023/04/11  Milestone 5 release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#ifndef SDDS_POSAPP_H_
#define SDDS_POSAPP_H_
#include <iostream>
#include "Item.h"
#include "Bill.h"

namespace sdds
{
    class PosApp
    {
        char fileName[255];
        Item* Iptr[MAX_NO_ITEMS];
        int nptr;
        char actionTitle[74];

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
        void setActionTitle(const char* str);
        void sortItems();
        int selectItem();
        int search(const char* sku);

        // Getters
        std::ostream &listItems(bool showTotal = true, std::ostream &ostr = std::cout);
        std::ostream &POS(std::ostream &ostr = std::cout);

        // Display
        int menu();
        void printActionTitle();

        void run();
        // Deconstructors
        ~PosApp();
    };
    // Helper
};
#endif