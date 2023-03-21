/*
Final Project Milestone 2
Module: Error
Filename: Error.h
Version 1.0
Author	Benny Yang
Student ID: 112654223
Email: byang68@myseneca.ca
Revision History
-----------------------------------------------------------
Date        Reason
2023/03/20  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#ifndef SDDS_ERROR_H_
#define SDDS_ERROR_H_

namespace sdds
{
    class Error
    {
        char *errMessage; // error message pointer
    public:
        // Constructors & Destructor
        Error();
        Error(const char *str);
        Error(Error &copy);
        Error &operator=(const char *str);
        Error &operator=(Error &copy);
        ~Error();

        // Getters
        operator bool() const;

        // Setters
        Error &clear();

        std::ostream &display(std::ostream &ostr = std::cout) const;
    };
    // Helper
    std::ostream &operator<<(std::ostream &ostr, const Error &error);

}

#endif