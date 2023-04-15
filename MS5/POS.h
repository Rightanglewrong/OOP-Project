/*
Final Project Milestone 4
Module: POS
Filename: POS.h
Version 1.1
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/03/20  Preliminary release
2023/03/26  Milestone 3 addition
2023/04/04  Milestone 4 Release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#ifndef SDDS_POS_H_
#define SDDS_POS_H_
#include "Error.h"

namespace sdds
{
    const double TAX = 0.13;
    const int MAX_SKU_LEN = 7;

    const int MIN_YEAR = 2000;
    const int MAX_YEAR = 2030;

    const int MAX_STOCK_NUMBER = 99;
    const int MAX_NO_ITEMS = 200;

    // Milestone 3
    const int MAX_NAME_LEN = 40;

    const int POS_LIST = 1;
    const int POS_FORM = 2;

    const char *const ERROR_POS_SKU = "SKU too long";
    const char *const ERROR_POS_NAME = "Item name too long";
    const char *const ERROR_POS_PRICE = "Invalid price value";
    const char *const ERROR_POS_TAX = "Invalid tax status";
    const char *const ERROR_POS_QTY = "Invalid quantity value";
    const char *const ERROR_POS_STOCK = "Item out of stock";
    const char *const ERROR_POS_EMPTY = "Invalid Empty Item";

}
#endif