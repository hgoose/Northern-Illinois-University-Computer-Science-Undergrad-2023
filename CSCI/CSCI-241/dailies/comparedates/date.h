#ifndef DATE_H
#define DATE_H

class date
{
    friend bool operator<(const date&, const date&);

    int month = 1,
        day = 1,
        year = 1900;

public:

    date() = default;
    
    date(int month, int day, int year)
    {
        this->month = month;
        this->day = day;
        this->year = year;
    }
};

#endif
