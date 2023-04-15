/*
Final Project Milestone 4
Module: Error
Filename: Error.h
Version 1.1
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/03/20  Preliminary release
2023/03/26  Milestone 3
2023/04/04  Milestone 4 Release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#ifndef SDDS_ERROR_H_
#define SDDS_ERROR_H_
#include <iostream>

namespace sdds
{
	class Error
	{
		char *errMessage;

	public:
		// Constructors & Destructor
		Error();
		Error(const char *str);
		Error(const Error &copy);
		Error &operator=(const char *str);
		Error &operator=(const Error &copy);
		~Error();

		// Getters
		operator bool() const;
		const char *getError() const;

		// Setters
		Error &clear();

		std::ostream &display(std::ostream &ostr = std::cout) const;
	};
	// Helper
	// std::ostream &operator<<(std::ostream &ostr, const Error &error);

}

#endif