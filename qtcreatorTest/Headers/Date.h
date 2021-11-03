//
// Created by picci on 27/10/2021.
//

#ifndef QTCREATORTEST_DATE_H
#define QTCREATORTEST_DATE_H


#include <string>
#include <cstdio>
#include <ctime>

using namespace std;

typedef enum {
    YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, WEEK
} TimeUnit;


class Date {
private:
    const char Compare(const Date &OtherDate, TimeUnit FromPart = YEAR) const {
        for (; FromPart <= SECOND; FromPart = (TimeUnit) (FromPart + 1)) {
            if (Data[FromPart] < OtherDate.Data[FromPart])
                return -1;
            else if (Data[FromPart] > OtherDate.Data[FromPart])
                return 1;
        }
        return 0;
    };

    short Data[6];

    class DatePart;

public:
    Date() {
        Clear();
    }

    bool IsLeapYear(short Year) const {
        return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
    }

    short DaysInMonth(short Month = 0) const {
        switch (Month == 0 ? Data[MONTH] : Month) {
            case 1:
                return 31;
            case 2:
                return IsLeapYear(Data[YEAR]) ? 29 : 28;
            case 3:
                return 31;
            case 4:
                return 30;
            case 5:
                return 31;
            case 6:
                return 30;
            case 7:
                return 31;
            case 8:
                return 31;
            case 9:
                return 30;
            case 10:
                return 31;
            case 11:
                return 30;
            case 12:
                return 31;
        }
        return 0;
    }

    string Format() const;

    operator string() const;

    Date &operator=(const string &Text);

    friend ostream &operator<<(ostream &stream, const Date &Date) {
        stream << Date.operator string();
        return stream;
    }

    bool operator<=(const Date &OtherDate) const { return (Compare(OtherDate) <= 0); }

    bool operator>=(const Date &OtherDate) const { return (Compare(OtherDate) >= 0); }

    bool operator<(const Date &OtherDate) const { return (Compare(OtherDate) < 0); }

    bool operator>(const Date &OtherDate) const { return (Compare(OtherDate) > 0); }

    bool operator==(const Date &OtherDate) const { return (Compare(OtherDate) == 0); }

    DatePart operator[](TimeUnit PartName);

    unsigned long Difference(Date &OtherDate, TimeUnit Unit, bool RoundUp = true) const;

    void SetToNow();

    bool IsEmpty() const { return (Data[YEAR] == 0); }

    void Clear(bool OnlyTime = false) {
        if (!OnlyTime)
            Data[YEAR] = Data[MONTH] = Data[DAY] = 0;

        Data[HOUR] = Data[MINUTE] = Data[SECOND] = 0;
        WithTime = false;
    }

    bool WithTime;
};

class Date::DatePart {
private:
    Date &BaseDate;
    TimeUnit Part;

public:
    DatePart(Date &BaseDate, TimeUnit Part) : BaseDate(BaseDate), Part(Part) {}

    operator short() const {
        if (Part <= SECOND)
            return BaseDate.Data[Part];
        else if (Part == WEEK) {
            // actually, this case is unused
            short Value = 0;
            for (char i = 1; i < BaseDate.Data[MONTH]; ++i)
                Value += BaseDate.DaysInMonth(i);
            Value += BaseDate.Data[DAY];

            return (Value - 1) / 7 + 1;
        }

        return 0;
    }

    DatePart &operator=(short Value) {
        if (Part <= SECOND)
            BaseDate.Data[Part] = Value;

        return *this;
    }

    DatePart &operator=(const DatePart &DatePart) {
        return operator=((short) DatePart);
    }

    DatePart &operator+=(short Value);

    DatePart &operator-=(short Value);

    DatePart &operator++() {
        operator+=(1);
        return *this;
    }
};

inline Date::DatePart Date::operator[](TimeUnit Part) {
    return DatePart(*this, Part);
}



#endif //QTCREATORTEST_DATE_H
