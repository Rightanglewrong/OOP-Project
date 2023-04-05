/*
Final Project Milestone 4
Module: Item
Filename: Item.cpp
Version 1.0
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/03/26  Preliminary release
2023/04/04  Milestone 4 Release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include "Item.h"

namespace sdds
{
    // Constructor
    Item::Item()
    {
        sku[0] = '\0';
        name = nullptr;
        price = 0.0;
        taxed = false;
        c_quantity = 0;
        c_displayType = 0;
    }

    // Copy & Assignment
    Item::Item(const Item &copy)
    {
        strcpy(sku, copy.sku);
        name = new char[strlen(copy.name) + 1];
        strcpy(name, copy.name);
        price = copy.price;
        taxed = copy.taxed;
        c_quantity = copy.c_quantity;
        c_displayType = copy.c_displayType;
        err = copy.err;
    }

    Item &Item::operator=(const Item &copy)
    {
        strcpy(sku, copy.sku);
        if (name != nullptr)
        {
            delete[] name;
            name = nullptr;
        }
        name = new char[strlen(copy.name) + 1];
        strcpy(name, copy.name);
        price = copy.price;
        taxed = copy.taxed;
        c_quantity = copy.c_quantity;
        c_displayType = copy.c_displayType;
        err = copy.err;

        return *this;
    }

    // Member Operator overloads
    bool Item::operator==(Item &rhs) const
    {
        return (strcmp(sku, rhs.sku) == 0 ? 1 : 0);
    }

    bool Item::operator==(const char *rhsSku) const
    {
        return (strcmp(sku, rhsSku) == 0 ? 1 : 0);
    }

    bool Item::operator>(Item &other) const
    {
        return (strcmp(sku, other.sku) > 0 ? 1 : 0);
    }

    int Item::operator+=(int quant)
    {
        c_quantity += quant;
        if (c_quantity > MAX_STOCK_NUMBER)
        {
            c_quantity = MAX_STOCK_NUMBER;
            err = ERROR_POS_QTY;
        }
        return c_quantity;
    }

    int Item::operator-=(int quant)
    {
        c_quantity -= quant;
        if (c_quantity < 0)
        {
            c_quantity = 0;
            err = ERROR_POS_STOCK;
        }
        return c_quantity;
    }

    Item::operator bool() const
    {
        // return (err ? 0 : 1);
        return !(err);
    }

    // Setter
    Item &Item::displayType(int type)
    {
        if (type == POS_LIST || type == POS_FORM)
        {
            c_displayType = type;
        }
        return *this;
    }

    Item &Item::clear()
    {
        err.clear();
        return *this;
    }

    // Getter
    double Item::cost() const
    {
        return (taxed ? price * (1 + TAX) : price);
    }

    int Item::quantity() const { return c_quantity; }

    // Helper
    double operator+=(double &lhs, const Item &rhs)
    {
        return lhs += rhs.cost() * rhs.quantity();
    }

    // Deconstructor
    Item::~Item()
    {
        if (name != nullptr)
        {
            delete[] name;
            name = nullptr;
        }
    }

    // IO funcs
    std::ostream &Item::write(std::ostream &ostr) const
    {
        if (!err)
        {
            if (c_displayType == POS_LIST)
            {
                char tempName[21];
                strncpy(tempName, name, 20);
                tempName[20] = '\0';

                ostr << std::setw(7) << std::left << sku << "|";
                ostr << std::setw(20) << tempName;
                ostr << "|" << std::setw(7) << std::right << std::fixed << std::setprecision(2) << price << "|";
                ostr << std::setw(3) << (taxed ? " X |" : "   |");
                ostr << std::setw(4) << std::right << c_quantity << "|";
                ostr << std::setw(9) << std::fixed << std::setprecision(2) << cost() * c_quantity << "|" << std::left;
            }
            else if (c_displayType == POS_FORM)
            {
                ostr << std::setfill(' ') << "=============v" << std::endl;
                ostr << std::setw(13) << std::left << "Name:" << name << std::endl;
                ostr << std::setw(13) << std::left << "Sku:" << sku << std::endl;
                ostr << std::setw(13) << std::left << "Price:" << price << std::endl;
                ostr << std::setw(13) << std::left << "Price + tax:";
                if (taxed)
                {
                    ostr << cost() << std::endl;
                }
                else
                {
                    ostr << "N/A" << std::endl;
                }
                ostr << std::setw(13) << std::left << "Stock Qty:" << c_quantity << std::endl;
            }
        }
        else
        {
            err.display();
        }
        return ostr;
    }

    std::istream &Item::read(std::istream &istr)
    {
        bool flag = true;
        char input[MAX_NAME_LEN + 3];

        // Sku
        std::cout << "Sku" << std::endl;
        do
        {
            std::cout << "> ";
            istr >> input;
            if (strlen(input) > MAX_SKU_LEN)
            {
                std::cout << ERROR_POS_SKU << std::endl;
            }
            else
            {
                strcpy(sku, input);
            }
        } while (strlen(input) > MAX_SKU_LEN);

        // Name
        std::cout << "Name" << std::endl;
        do
        {
            std::cout << "> ";
            istr.clear();
            istr.ignore(100, '\n');
            istr.getline(input, MAX_NAME_LEN + 2);
            input[strlen(input)] = '\0';

            if (strlen(input) > MAX_NAME_LEN)
            {
                std::cout << ERROR_POS_NAME << std::endl;
            }
            else
            {
                if (name != nullptr)
                {
                    delete[] name;
                    name = nullptr;
                }
                name = new char[strlen(input) + 1];
                strcpy(name, input);
            }
        } while (strlen(input) > MAX_NAME_LEN);

        // Price
        std::cout << "Price" << std::endl;
        do
        {
            std::cout << "> ";
            if (istr >> price)
            {
                if (price > 0.0)
                {
                    flag = false;
                }
            }
            if (flag)
            {
                std::cout << ERROR_POS_PRICE << std::endl;
                istr.clear();
                istr.ignore(100, '\n');
            }
        } while (flag);

        // Taxed
        std::cout << "Taxed?" << std::endl;
        std::cout << "(Y)es/(N)o: ";
        flag = true;
        do
        {
            istr >> input;
            if (strcmp(input, "y") == 0 || strcmp(input, "n") == 0)
            {
                taxed = (strcmp(input, "y") == 0 ? true : false);
                flag = false;
            }
            else
                std::cout << "Only 'y' and 'n' are acceptable: ";
        } while (flag);

        // Quantity
        std::cout << "Quantity" << std::endl;
        flag = true;
        do
        {
            std::cout << "> ";
            if (istr >> c_quantity)
            {
                if (c_quantity > 0 && c_quantity < MAX_STOCK_NUMBER)
                    flag = false;
            }
            if (flag)
            {
                std::cout << ERROR_POS_QTY << std::endl;
                istr.clear();
                istr.ignore(100, '\n');
            }
        } while (flag);

        return istr;
    }

    std::ofstream &Item::save(std::ofstream &ofstr) const
    {
        if (err.getError() != nullptr)
        {
            std::cerr << err.getError();
        }
        else
            ofstr << itemType()
                  << ',' << sku
                  << ',' << name
                  << ',' << std::fixed << std::setprecision(2) << price
                  << ',' << (taxed ? '1' : '0')
                  << ',' << c_quantity;
        return ofstr;
    }

    std::ifstream &Item::load(std::ifstream &ifstr)
    {
        char sk[255];
        char nam[255];
        double pric;
        char isTaxed;
        int quantity;

        err.clear();

        ifstr.getline(sk, 255, ',');
        if (strlen(sk) > MAX_SKU_LEN)
        {
            err = ERROR_POS_SKU;
            return ifstr;
        }

        ifstr.getline(nam, 255, ',');
        if (strlen(nam) > MAX_NAME_LEN)
        {
            err = ERROR_POS_NAME;
            return ifstr;
        }

        ifstr >> pric;
        if (ifstr.fail() || pric < 0.0)
        {
            err = ERROR_POS_PRICE;
            return ifstr;
        }

        ifstr.ignore();

        ifstr.get(isTaxed);
        if (isTaxed != '1' && isTaxed != '0')
        {
            err = ERROR_POS_TAX;
            return ifstr;
        }

        ifstr.ignore();

        ifstr >> quantity;
        if (quantity < 1 || quantity > MAX_STOCK_NUMBER)
        {
            err = ERROR_POS_QTY;
            // return ifstr;
        }

        if (err.getError() == nullptr)
        {
            std::snprintf(sku, MAX_SKU_LEN, "%s", sk);
            if (name)
                delete[] name;             // Free previous memory if any
            name = new char[MAX_NAME_LEN]; // Allocate memory for m_name
            std::snprintf(name, MAX_NAME_LEN, "%s", nam);
            price = pric;
            if (isTaxed == '1')
                taxed = true;
            else
                taxed = false;
            c_quantity = quantity;
        }

        else
        {
            std::cout << err.getError();
        }
        return ifstr;
    }

    std::ostream &Item::bprint(std::ostream &ostr) const
    {
        char tempName[21];
        strncpy(tempName, name, 20);
        tempName[20] = '\0';

        ostr << "| " << std::left;
        ostr << std::setw(20) << tempName;
        ostr << "|" << std::setw(10) << std::right << std::fixed << std::setprecision(2) << cost() << " |";
        ostr << "  " << (taxed ? "T" : " ") << "  |" << std::endl;
        return ostr;
    }
}
