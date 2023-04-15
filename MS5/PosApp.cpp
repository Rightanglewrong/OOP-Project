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
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "PosApp.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Bill.h"
#include "Item.h"
#include "POS.h"

using namespace std;
namespace sdds
{
    // Constructors
    PosApp::PosApp()
    {
        fileName[0] = '\0';
        for (int i = 0; i < MAX_NO_ITEMS; ++i)
        {
            Iptr[i] = nullptr;
        }
        nptr = 0;
        actionTitle[0] = '\0';
    }

    PosApp::PosApp(const char *file)
    {
        strcpy(fileName, file);
        for (int i = 0; i < MAX_NO_ITEMS; ++i)
        {
            Iptr[i] = nullptr;
        }
        nptr = 0;
        actionTitle[0] = '\0';
    }

    // Destructor
    PosApp::~PosApp()
    {
        for (int i = 0; i < nptr; i++)
        {
            if (Iptr[i] != nullptr)
            {
                delete Iptr[i];
                Iptr[i] = nullptr;
            }
        }
    }

    // Setters
    ostream &PosApp::stockItem(std::ostream &ostr)
    {
        int itemChosen = 0;
        int qty = -1;
        setActionTitle("Select an item to stock");
        printActionTitle();

        itemChosen = selectItem();
        ostr << "Selected Item:\n";
        Item *stocked = Iptr[itemChosen - 1];
        stocked->displayType(2);
        stocked->write(ostr);

        ostr << "Enter quantity to add: ";
        do
        {
            cin >> qty;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Integer, try again: ";
                qty = -1;
            }
            else if (qty < 1 || qty > 69)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "[1<=value<=69], retry: Enter quantity to add: ";
                qty = -1;
            }
        } while (qty == -1);
        stocked->operator+=(qty);

        setActionTitle("DONE!");
        printActionTitle();
        return ostr;
    }

    ostream &PosApp::removeItem(std::ostream &ostr)
    {
        int itemChosen = 0;
        setActionTitle("Remove Item");
        printActionTitle();

        itemChosen = selectItem();

        cout << "Removing...." << endl;
        Item *terminated = Iptr[itemChosen - 1];
        terminated->displayType(2);
        terminated->write(ostr);

        delete terminated;
        terminated = nullptr;
        for (int i = itemChosen - 1; i < nptr - 1; i++)
        {
            Iptr[i] = Iptr[i + 1];
        }
        nptr--;

        setActionTitle("DONE!");
        printActionTitle();
        return ostr;
    }

    std::ostream &PosApp::saveRecs(std::ostream &ostr)
    {
        setActionTitle("Saving Data");
        printActionTitle();

        ofstream file(fileName);
        if (!file.is_open())
        {
            file.clear();
            file.close();
        }
        for (int i = 0; i < nptr; i++)
        {
            Iptr[i]->save(file);
            file << endl;
        }

        file.close();
        return ostr;
    }

    std::ostream &PosApp::loadRecs(std::ostream &ostr)
    {
        char type = '\0';
        setActionTitle("Loading Items");
        printActionTitle();

        ifstream input(fileName);

        if (!input.is_open())
        {
            ostr << "Couldnt open File";
            ofstream output(fileName);
            if (!output)
            {
                ostr << "TESTING: unable to create output file " << fileName << endl;
            }
            else
            {
                output.close();
                input.open(fileName);
                if (!input)
                {
                    ostr << "TESTING: failed to open new " << fileName << " after creating it." << endl;
                }
            }
        }

        for (int i = 0; i < MAX_NO_ITEMS; i++)
        {
            delete Iptr[i];
            Iptr[i] = nullptr;
        }
        nptr = 0;

        while (input >> type && nptr < MAX_NO_ITEMS)
        {
            input.ignore();

            if (type == 'P')
            {
                Iptr[nptr] = new Perishable;
                Iptr[nptr]->load(input);
                nptr++;
            }
            else if (type == 'N')
            {
                Iptr[nptr] = new NonPerishable;
                Iptr[nptr]->load(input);
                nptr++;
            }
            else
            {
                cout << "TESTING: Invalid item type" << endl;
            }
        }

        input.close();
        return ostr;
    }

    std::ostream &PosApp::addItem(std::ostream &ostr)
    {
        setActionTitle("Adding Item to the store");
        printActionTitle();
        char perishable;
        Item *item = nullptr;

        if (nptr >= MAX_NO_ITEMS)
        {
            ostr << "Inventory Full!" << std::endl;
            return ostr;
        }
        ostr << "Is the Item perishable? (Y)es/(N)o: ";
        std::cin >> perishable;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            ostr << "Invalid Input!" << endl;
        }
        if (perishable == 'y' || perishable == 'Y')
        {
            item = new Perishable();
        }
        else if (perishable == 'n' || perishable == 'N')
        {
            item = new NonPerishable();
        }
        else
        {
            ostr << "Wasnt y or n";
        }

        item->read(cin);
        if (cin.fail())
        {
            ostr << *item << ", try again..." << endl;
            cin.clear();
            cin.ignore();
            delete item;
        }
        else
        {
            Iptr[nptr++] = item;
            setActionTitle("DONE!");
            printActionTitle();
        }

        return ostr;
    }

    void PosApp::setActionTitle(const char *str)
    {
        strncpy(actionTitle, str, 73);
        actionTitle[73] = '\0';
    }

    void PosApp::sortItems()
    {
        int i, j;
        Item *temp;
        bool swapped;
        bool flag = true;

        for (i = 0; i < nptr - 1 && flag == true; i++)
        {
            swapped = false;
            for (j = 0; j < nptr - i - 1; j++)
            {
                if (strcmp(Iptr[j]->getName(), Iptr[j + 1]->getName()) > 0)
                {
                    temp = Iptr[j];
                    Iptr[j] = Iptr[j + 1];
                    Iptr[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped)
            {
                flag = false;
            }
        }
    }

    int PosApp::search(const char *sku)
    {
        int index = -1;
        for (int i = 0; i < nptr; i++)
        {
            if (*Iptr[i] == sku)
            {
                index = i;
            }
        }
        return index;
    }

    // Getters
    std::ostream &PosApp::listItems(bool showTotal, std::ostream &ostr)
    {
        double totalAssets = 0.0;
        setActionTitle("Listing Items");
        printActionTitle();
        sortItems();
        ostr << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
        ostr << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;

        for (int i = 0; i < nptr; i++)
        {
            ostr << right << setw(4) << (i + 1) << " | ";
            Iptr[i]->displayType(1);
            Iptr[i]->write(cout);
            ostr << endl;
            totalAssets += Iptr[i]->cost() * Iptr[i]->quantity();
        }
        ostr << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
        if (showTotal)
        {
            ostr << setw(48) << right << "Total Asset: $  |" << setw(14) << fixed << setprecision(2) << totalAssets << "|" << endl;
            ostr << "-----------------------------------------------^--------------^" << endl;
            ostr << endl;
        }

        return ostr;
    }

    std::ostream &PosApp::POS(std::ostream &ostr)
    {
        cout << ">>>> Starting Point of Sale..................................................\n";
        Bill bill;
        bool flag = true;
        char sku[MAX_SKU_LEN + 1];
        int index = -1;

        bill.clear();
        cin.ignore(1000, '\n');

        while (flag)
        {
            ostr << "Enter SKU or <ENTER> only to end sale...\n> ";
            cin.getline(sku, MAX_SKU_LEN + 1, '\n');

            if (sku[0] == '\0')
            {
                flag = false;
            }
            else
            {
                if (cin.fail())
                {
                    ostr << ERROR_POS_SKU << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else
                {
                    index = search(sku);
                    if (index == -1)
                    {
                        ostr << "!!!!! Item Not Found !!!!!" << endl;;
                    }
                    else
                    {
                        if (Iptr[index]->quantity() == 0)
                        {
                            ostr << ERROR_POS_STOCK << endl;
                            cin.clear();
                        }
                        else
                        {
                            Iptr[index]->operator-=(1);
                            Iptr[index]->displayType(POS_FORM);
                            Iptr[index]->write(cout);
                            bill.add(Iptr[index]);
                            ostr << "\n>>>>> Added to bill" << endl;
                            ostr << ">>>>> Total: " << setprecision(2) << bill.total() << endl;
                        }
                    }
                }
            }
        }
        bill.print(ostr);
        return ostr;
    }

    int PosApp::selectItem()
    {
        int choice = 0;
        setActionTitle("Item Selection by row number");
        printActionTitle();

        cout << "Press <ENTER> to start....";
        cin.ignore(1000, '\n');
        cin.get();

        listItems(false);

        cout << "Enter the row number: ";
        do
        {
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Integer, try again: ";
                choice = 0;
            }
            else if (choice < 1 || choice > nptr)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "[1<=value<=26], retry: Enter the row number: ";
                choice = 0;
            }
        } while (choice == 0);
        return choice;
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
        cout << "5- POS" << endl;
        cout << "0- exit program" << endl;
        cout << "> ";

        while (flag == true)
        {
            cin >> value;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(255, '\n');
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

    void PosApp::printActionTitle()
    {
        cout << ">>>> " << left << setw(72) << setfill('.') << actionTitle << setfill(' ') << setw(2) << std::endl;
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
