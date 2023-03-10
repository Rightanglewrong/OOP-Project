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
#include <iostream>
#include <cstring>
#include "PosApp.h"
using namespace std;
namespace sdds
{
    // Constructors
    PosApp::PosApp()
    {
        fileName[0] = '\0';
    }

    PosApp::PosApp(const char *file)
    {
        strcpy(fileName, file);
    }

    // Destructor
    PosApp::~PosApp()
    {
    }

    // Setters
    ostream &PosApp::stockItem(std::ostream &ostr)
    {
        ostr << ">>>> Select an item to stock................................................." << endl;
        ostr << "Running stockItem()" << endl;
        return ostr;
    }

    ostream &PosApp::removeItem(std::ostream &ostr)
    {
        ostr << ">>>> Remove Item............................................................." << endl;
        ostr << "Running removeItem()" << endl;
        ;
        return ostr;
    }

    std::ostream &PosApp::saveRecs(std::ostream &ostr)
    {
        ostr << ">>>> Saving Data............................................................." << endl;
        ostr << "Saving data in " << fileName << endl;
        return ostr;
    }

    std::ostream &PosApp::loadRecs(std::ostream &ostr)
    {
        ostr << ">>>> Loading Items..........................................................." << endl;
        ostr << "Loading data from " << fileName << endl;
        return ostr;
    }

    std::ostream &PosApp::addItem(std::ostream &ostr)
    {
        ostr << ">>>> Adding Item to the store................................................" << endl;
        ostr << "Running addItem()" << endl;
        ;
        return ostr;
    }

    // Getters
    std::ostream &PosApp::listItems(std::ostream &ostr) const
    {
        ostr << ">>>> Listing Items..........................................................." << endl;
        ostr << "Running listItems()" << endl;
        return ostr;
    }

    std::ostream &PosApp::POS(std::ostream &ostr)
    {
        ostr << ">>>> Starting Point of Sale.................................................." << endl;
        ostr << "Running POS()" << endl;
        return ostr;
    }

    // Display
    int PosApp::menu()
    {
        int value;
        bool flag = true;
        cout << "The Sene-Store" << endl;
        cout << "1- List items" << endl;
        cout << "2- Add item" << endl;
        cout << "3- Remove item" << endl;
        cout << "4- Stock item" << endl;
        cout << "5- Point of Sale" << endl;
        cout << "0- exit program" << endl;
        cout << "> ";

        while (flag == true)
        {
            cin >> value;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(255,'\n');
                cout << "Invalid Integer, try again: ";
            }
            else if (value >= 6 || value <= -1)
            {
                cout << "[0<=value<=5], retry: > ";
            }
            else
            {
                flag = false;
            }
        }
        return value;
    }

    void PosApp::run()
    {
        int value = -1;
        loadRecs();
        while (value != 0)
        {
            value = menu();
            if (value == 0)
            {
                saveRecs();
                cout << "Goodbye!" << endl;
                return;
            }
            else if (value == 1)
            {
                listItems();
            }
            else if (value == 2)
            {
                addItem();
            }
            else if (value == 3)
            {
                removeItem();
            }
            else if (value == 4)
            {
                stockItem();
            }
            else if (value == 5)
            {
                POS();
            }
        }
    }
}
