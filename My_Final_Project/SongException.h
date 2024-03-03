#ifndef SONGEXCEPTION_H
#define SONGEXCEPTION_H

#include<exception>
#include<string>


class SongException: public std::exception
{

    std::string errorDescription;
public:

    SongException(const std::string& description);

    // C-style string (const char*) representing the exception's description
    //The noexcept specifier indicates that this function does not throw any exceptions.
    const char* what() const noexcept override;

};

#endif // SONGEXCEPTION_H
