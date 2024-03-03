#include "SongException.h"

SongException::SongException(const std::string& description)
{
    errorDescription = description;
}

const char* SongException::what() const noexcept
{
    return errorDescription.c_str();
}
