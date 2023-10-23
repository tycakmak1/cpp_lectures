#ifndef GUARD_EC237AFF_C170_4346_9A8A_FB682EE584B8
#define GUARD_EC237AFF_C170_4346_9A8A_FB682EE584B8
#include <iosfwd>

class Date
{
    int _d, _m, _y;

public:
    Date() = default;

    Date(int day, int month, int year) : _d{day}, _m{month}, _y{year} {}

    friend std::ostream& operator<<(std::ostream&, Date const&);
}; // class Date

#endif // GUARD_EC237AFF_C170_4346_9A8A_FB682EE584B8
