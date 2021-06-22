#pragma once
#include <exception>


struct WrongShapeTensorException : public std::exception {
    const char* what() const noexcept
    {
        return "+++ Wrong Shape +++ (the size of the rows or colums have to be equal)";
    }
};

struct WrongSize : public std::exception {
    const char* what() const noexcept
    {
        return "+++ wrong size +++";
    }
};

