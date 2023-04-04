/*
Final Project Milestone 4
Module: Item
Filename: Item.h
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

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include <iostream>
#include <fstream>

#include "POS.h"
#include "PosIO.h"
#include "Error.h"

namespace sdds
{
	class Item : public PosIO
	{
	private:
		char sku[MAX_SKU_LEN];
		char *name;
		double price;
		bool taxed;
		int c_quantity;

	protected:
		int c_displayType;
		Error err;

	public:
		// Constructors
		Item();

		// Copy Constructor
		Item(const Item &rhs);
		Item &operator=(const Item &rhs);

		// Destructor
		virtual ~Item();

		// Member operator overloads
		bool operator==(const char *sku) const;
		bool operator==(Item &right) const;
		bool operator>(Item &other) const;
		int operator+=(int quantity);
		int operator-=(int quantity);
		operator bool() const;

		// Setter
		Item &displayType(int type);
		Item &clear();

		// Getter
		virtual char itemType() const = 0;
		double cost() const;
		int quantity() const;

		// IO funcs
		virtual std::ostream &write(std::ostream &ostr) const;
		virtual std::istream &read(std::istream &istr);
		virtual std::ofstream &save(std::ofstream &ofstr) const;
		virtual std::ifstream &load(std::ifstream &ifstr);

		std::ostream &bprint(std::ostream &ostr) const;
	};
	// Helper
	double operator+=(double &left, const Item &right);
}
#endif