#include "Date.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, Date const& date)
{
    return os << "Date is " << date._d << '/' << date._m << '/' << date._y;
}