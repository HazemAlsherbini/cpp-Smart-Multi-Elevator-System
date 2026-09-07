#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
	short _Day;
	short _Month;
	short _Year;
public:
	clsDate()
	{
        time_t T = time(0);
        tm* now = localtime(&T);

        _Year = now->tm_year + 1900;
        _Month = now->tm_mon + 1;
        _Day = now->tm_mday;
    }
    clsDate(string Date)
    {
        vector<string> vDate = clsString::Split(Date, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);

    }
    clsDate(short Day,short Month,short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }
    clsDate(short Days, short Year)
    {
        *this = GetDateFromTotalDaysInAYear(Year, Days);
    }

    void setDay(short Day)
    {
        _Day = Day;
    }
    short getDay()
    {
        return _Day;
    }
    _declspec(property(get = getDay, put = setDay)) short Day;

    void setMonth(short Month)
    {
        _Month = Month;
    }
    short getMonth()
    {
        return _Month;
    }
    _declspec(property(get = getMonth, put = setMonth)) short Month;

    void setYear(short Year)
    {
        _Year = Year;
    }
    short getYear()
    {
        return _Year;
    }
    _declspec(property(get = getYear, put = setYear)) short Year;

    static bool IsDateValid(clsDate Date)
    {
        if (Date._Month < 1 || Date._Month > 12)
            return false;
        if (Date._Day < 1 || Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            return false;
        return true;
    }
    bool IsDateValid()
    {
        return IsDateValid(*this);
    }

    static clsDate GetSystemDate()
    {
        time_t T = time(0);
        tm* now = localtime(&T);

        short Year = now->tm_year + 1900;
        short Month = now->tm_mon + 1;
        short Day = now->tm_mday;

        return clsDate(Day, Month, Year);
    }
    static clsDate GetDateFromTotalDaysInAYear(short Year, short Days)
    {
        short Month = 1;

        while (true)
        {
            short MonthDays = NumberOfDaysInAMonth(Year, Month);

            if (Days > MonthDays)
            {
                Days -= MonthDays;
                Month++;
            }
            else
            {
                break;
            }
        }
        return clsDate(Days,Month,Year);
    }
    static string GetSystemDateAndTimeString()
    {
        time_t T = time(0);
        tm* now = localtime(&T);

        string Date = to_string(now->tm_mday) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_year + 1900);
        string Time = to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
        return Date + " - " + Time;
    }


    static bool LeapYearOrNot(short Year)
    {
        return (Year % 400 == 0) || (Year % 100 != 0 && Year % 4 == 0);

    }
    bool LeapYearOrNot()
    {
        return LeapYearOrNot(_Year);
        // When you type like this -----> return LeapYearOrNot(this->_Year);
        // The compiler convert it to this ----> return LeapYearOrNot((*this)._Year);
        // [(*this)._Year;] IS EQUIVALENT TO [this->_Year;]
    }

    static short GetDayIndex(short Year, short Month , short Day)
    {
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + 12 * a - 2;

        // Gregorian :
        // 0: Sun , 1: Mon ...etc
        return (Day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
    }
    static short GetDayIndex(const clsDate & Date)
    {
        return GetDayIndex(Date._Year,Date._Month,Date._Day);
    }
    short GetDayIndex()
    {
        return GetDayIndex(*this);
    }

    static string GetDayName(short DayIndex)
    {
        string Days[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
        return Days[DayIndex];
    }
    string GetDayName()
    {
        return GetDayName(GetDayIndex(*this));
    }
    static string GetMonthName(short Month)
    {
        string Months[] = { "Jan","Feb","Mar","Apr","May","June","July","Aug","Sep","Oct","Nov","Dec" };
        return Months[Month - 1];
    }
    string GetMonthName()
    {
        return GetMonthName(this->_Month);
    }

    void printMonthCalender(short Year, short Month)
    {
        short Current = GetDayIndex(Year, Month, 1);
        short NumOfDays = NumberOfDaysInAMonth(Year, Month);

        printf("---------------%s-----------------\n", GetMonthName(Month).c_str());
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        short i;
        for (i = 0; i < Current; i++)
            printf("     ");
        for (int j = 1; j <= NumOfDays; j++)
        {
            printf("%5d", j);
            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n-----------------------------------\n\n");

    }
    void printYearCalender(short Year)
    {
        printf("\n----------------------------------\n");
        printf("          Calender - %d          ", Year);
        printf("\n----------------------------------\n\n");

        for (short Month = 1; Month <= 12; Month++)
        {
            printMonthCalender(Year, Month);
        }

    }

    static short NumberOfDaysInAMonth(short Year, short Month)
    {
        int arrDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (Month == 2) ? (LeapYearOrNot(Year) ? 29 : 28) : arrDays[Month - 1];
    }
    static short NumberOfDaysInAMonth(const clsDate& Date)
    {
        return NumberOfDaysInAMonth(Date._Year,Date._Month);
    }
    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(*this);
    }

    static short NumberOfHoursInAMonth(short Year, short Month)
    {
        return NumberOfDaysInAMonth(Year, Month) * 24;
    }
    static int NumberOfMinutesInAMonth(short Year, short Month)
    {
        return NumberOfHoursInAMonth(Year, Month) * 60;
    }
    static int NumberOfSecondsInAMonth(short Year, short Month)
    {
        return NumberOfMinutesInAMonth(Year, Month) * 60;
    }

    static short NumberOfHoursInAMonth(const clsDate& Date)
    {
        return NumberOfHoursInAMonth(Date._Year, Date._Month);
    }
    static int NumberOfMinutesInAMonth(const clsDate& Date)
    {
        return NumberOfMinutesInAMonth(Date._Year, Date._Month);
    }
    static int NumberOfSecondsInAMonth(const clsDate& Date)
    {
        return NumberOfSecondsInAMonth(Date._Year, Date._Month) ;
    }

    short NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(*this);
    }
    int NumberOfMinutesInAMonth()
    {
        return NumberOfMinutesInAMonth(*this);
    }
    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(*this);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return (LeapYearOrNot(Year) ? 366 : 365);
    }
    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }
    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }
    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }
    short NumberOfDaysInAYear()
    {
        return NumberOfDaysInAYear(this->_Year);
    }
    short NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(this->_Year);
    }
    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(this->_Year);
    }
    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(this->_Year);
    }

    static bool IsLastDayInMonth(const clsDate& Date)
    {
        return (Date._Day == NumberOfDaysInAMonth(Date._Year, Date._Month)) ? true : false;
    }
    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }
    static bool IsFirstDayInMonth(short Day)
    {
        return Day == 1;
    }
    static bool IsFirstMonthInYear(short Month)
    {
        return Month == 1;
    }
    static bool IsEndOfWeek(short DayIndex)
    {
        return DayIndex == 6;
    }
    static bool IsWeekEnd(short DayIndex)
    {
        return (DayIndex == 6 || DayIndex == 5);
    }
    static bool IsBusinessDay(short DayIndex)
    {
        return !(IsWeekEnd(DayIndex));
    }
    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }
    bool IsLastMonthInYear()
    {
        return IsLastMonthInYear(this->_Month);
    }
    bool IsFirstDayInMonth()
    {
        return IsFirstDayInMonth(this->_Day);
    }
    bool IsFirstMonthInYear()
    {
        return IsFirstMonthInYear(this->_Month);
    }
    bool IsEndOfWeek()
    {
        return IsEndOfWeek(GetDayIndex(*this));
    }
    bool IsWeekEnd()
    {
        return IsWeekEnd(GetDayIndex(*this));
    }
    bool IsBusinessDay()
    {
        return IsBusinessDay(GetDayIndex(*this));
    }

    static short DaysUntilTheEndOfWeek(short DayIndex)
    {
        return 6 - DayIndex;
    }
    static short DaysUntilTheEndOfMonth(const clsDate& Date)
    {
        return NumberOfDaysInAMonth(Date._Year, Date._Month) - Date._Day;
    }
    static short DaysUntilTheEndOfYear(const clsDate& Date)
    {
        return NumberOfDaysInAYear(Date._Year) - DaysFromYearBeginning(Date);
    }
    static short DaysFromYearBeginning(const clsDate& Date)
    {
        short Days = Date._Day;
        for (short i = 1; i < Date._Month; i++)
        {
            Days += NumberOfDaysInAMonth(Date._Year, i);
        }
        return Days;
    }
    short DaysUntilTheEndOfWeek()
    {
        return DaysUntilTheEndOfWeek(GetDayIndex(*this));
    }
    short DaysUntilTheEndOfMonth()
    {
        return DaysUntilTheEndOfMonth(*this);
    }
    short DaysUntilTheEndOfYear()
    {
        return DaysUntilTheEndOfYear(*this);
    }
    short DaysFromYearBeginning()
    {
        return DaysFromYearBeginning(*this);
    }

    static bool IsDate1BeforeDate2(const clsDate& Date1, const clsDate& Date2)
    {
        return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? ((Date1._Month < Date2._Month) ? true : ((Date1._Month == Date2._Month) ? ((Date1._Day < Date2._Day) ? true : false) : false)) : false);
    }
    static bool IsDate1EqualToDate2(const clsDate& Date1, const clsDate& Date2)
    {
        return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false) : false) : false;
    }
    static bool IsDate1AfterDate2(const clsDate& Date1, const clsDate& Date2)
    {
        return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2);
    }
    bool IsDate1BeforeDate2(const clsDate& Date2)
    {
        return IsDate1BeforeDate2(*this, Date2);
    }
    bool IsDate1EqualToDate2(const clsDate& Date2)
    {
        return IsDate1EqualToDate2(*this, Date2);
    }
    bool IsDate1AfterDate2(const clsDate& Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    

    static string Print(const clsDate& Date)
    {
        if (!IsDateValid(Date))
            return "InvalidDate";
        else
            return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year) + '\n';
    }
    string Print()
    {
        return Print(*this);
    }

    static void SwapDates( clsDate& Date1,  clsDate& Date2)
    {
        clsDate Temp = Date1;
        Date1 = Date2;
        Date2 = Temp;
    }
    void SwapDates(clsDate& Date2)
    {
        clsDate Temp = *this;
        *this = Date2;
        Date2 = Temp;
    }

    static int GetDifferenceInDays(clsDate& Date1, clsDate Date2, bool IncludeEndingDay = false)
    {
        int Days = 0;
        short SwapFlagValue = 1;
        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;

        }
        if (Date1._Year == Date2._Year)
        {
            if (Date1._Month == Date2._Month)
            {
                Days = Date2._Day - Date1._Day;
            }
            else
            {
                Days = DaysFromYearBeginning(Date2) - DaysFromYearBeginning(Date1);
            }
        }
        else
        {
            Days = DaysFromYearBeginning(Date2);
            while (true)
            {
                Date2._Year--;
                if (Date2._Year == Date1._Year)
                {
                    Days += (NumberOfDaysInAYear(Date1._Year) - DaysFromYearBeginning(Date1));
                    break;
                }
                else
                {
                    Days += NumberOfDaysInAYear(Date2._Year);
                }
            }
        }
        return IncludeEndingDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
    }
    int GetDifferenceInDays(clsDate& Date2, bool IncludeEndingDay)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndingDay);
    }

    static int CalculateAgeInDays( clsDate& DateOfBirth)
    {
        return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate());
    }

    static clsDate DecreaseOneDayFromDate(clsDate & Date)
    {
        if (IsFirstDayInMonth(Date._Day))
        {
            if (IsFirstMonthInYear(Date._Month))
            {
                Date._Month = 12;
                Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
                Date._Year--;
            }
            else
            {
                Date._Month--;
                Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
            }
        }
        else
        {
            Date._Day--;
        }

        return Date;
    }
    static clsDate DecreaseDateByXDays(clsDate & Date, short DaysToSubstract)
    {
        for (short Day = 1; Day <= DaysToSubstract; Day++)
        {
            Date = DecreaseOneDayFromDate(Date);
        }
        return Date;
    }
    static clsDate DecreaseDateByOneWeek(clsDate & Date)
    {
        Date = DecreaseDateByXDays(Date, 7);
        return Date;

    }
    static clsDate DecreaseDateByXWeeks(clsDate & Date, short WeeksToSubstract)
    {
        for (short Week = 1; Week <= WeeksToSubstract; Week++)
            Date = DecreaseDateByOneWeek(Date);
        return Date;

    }
    static clsDate DecreaseDateByOneMonth(clsDate& Date)
    {
        if (IsFirstMonthInYear(Date._Month))
        {
            Date._Month--;
            Date._Year--;
            if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
                Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        }
        else
        {
            Date._Month--;
            if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
                Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        }
        return Date;
    }
    static clsDate DecreaseDateByXMonths(clsDate& Date, short MonthsToSubstract)
    {
        for (short Week = 1; Week <= MonthsToSubstract; Week++)
            Date = DecreaseDateByOneMonth(Date);
        return Date;
    }
    static clsDate DecreaseDateByOneYear(clsDate& Date)
    {
        Date._Year--;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    static clsDate DecreaseDateByXYears(clsDate& Date, short YearsToSubstract)
    {
        Date._Year -= YearsToSubstract;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    static clsDate DecreaseDateByOneDecade(clsDate& Date)
    {
        Date._Year -= 10;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    static clsDate DecreaseDateByXDecades(clsDate &Date, short Decades)
    {

        Date._Year -= 10 * Decades;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    static clsDate DecreaseDateByOneCentury(clsDate& Date)
    {
        Date._Year -= 100;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    static clsDate DecreaseDateByOneMillennium(clsDate& Date)
    {
        Date._Year -= 1000;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    void DecreaseOneDayFromDate()
    {
        DecreaseOneDayFromDate(*this);
    }
    void DecreaseDateByXDays(short DaysToSubstract)
    {
        DecreaseDateByXDays(*this, DaysToSubstract);
    }
    void DecreaseDateByOneWeek()
    {
        DecreaseDateByOneWeek(*this);
    }
    void DecreaseDateByXWeeks(short WeeksToSubstract)
    {
        DecreaseDateByXWeeks(*this, WeeksToSubstract);
    }
    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(*this);
    }
    void DecreaseDateByXMonths(short MonthsToSubstract)
    {
        DecreaseDateByXMonths(*this, MonthsToSubstract);
    }
    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(*this);
    }
    void DecreaseDateByXYears(short YearsToSubstract)
    {
        DecreaseDateByXYears(*this, YearsToSubstract);
    }
    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(*this);
    }
    void DecreaseDateByXDecades(short Decades)
    {
        DecreaseDateByXDecades(*this ,Decades);
    }
    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(*this);
    }
    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(*this);
    }

    static clsDate AddingOneDayToDate(clsDate & Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date._Month))
            {
                Date._Year++;
                Date._Month = 1;
                Date._Day = 1;
            }
            else
            {
                Date._Month++;
                Date._Day = 1;
            }
        }
        else
        {
            Date._Day++;
        }
        return Date;
    }
    static clsDate AddDaysToDate(clsDate& Date, short DaysToAdd)
    {
        short TotalDaysFromYearBeginning = DaysToAdd + DaysFromYearBeginning(Date);

        Date._Month = 1;
        Date._Day = 1;

        while (true)
        {
            short DaysInYear = NumberOfDaysInAYear(Date._Year);
            if (TotalDaysFromYearBeginning > DaysInYear)
            {
                TotalDaysFromYearBeginning -= DaysInYear;
                Date._Year++;
            }
            else if (TotalDaysFromYearBeginning > NumberOfDaysInAMonth(Date._Year, Date._Month))
            {
                TotalDaysFromYearBeginning -= NumberOfDaysInAMonth(Date._Year, Date._Month);
                Date._Month++;
            }
            else
            {
                Date._Day = TotalDaysFromYearBeginning;
                break;
            }
        }
        return Date;
    }
    static clsDate IncreaseDateByXDays(clsDate& Date, short Days)
    {
        for (short Day = 1; Day <= Days; Day++)
        {
            Date = AddingOneDayToDate(Date);
        }
        return Date;
    }
    static clsDate IncreaseDateByOneWeek(clsDate& Date)
    {
        Date = IncreaseDateByXDays(Date, 7);
        return Date;
    }
    static clsDate IncreaseDateByXWeeks(clsDate& Date, short Weeks)
    {
        for (short Week = 1; Week <= Weeks; Week++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }

        return Date;
    }
    static clsDate IncreaseDateByOneMonth(clsDate& Date)
    {
        if (!IsLastMonthInYear(Date._Month))
        {
            Date._Month++;
        }
        else
        {
            Date._Month = 1;
            Date._Year++;
        }

        //Check Days
        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Year, Date._Month);
        if (Date._Day > NumberOfDaysInCurrentMonth)
        {
            Date._Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }
    static clsDate IncreaseDateByXMonths(clsDate& Date, short Months)
    {
        for (short Month = 1; Month <= Months; Month++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }
    static clsDate IncreaseDateByOneYear(clsDate& Date)
    {
        Date._Year++;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    static clsDate IncreaseDateByXYears(clsDate& Date, short Years)
    {
        Date._Year += Years;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    static clsDate IncreaseDateByOneDecade(clsDate& Date)
    {
        Date._Year += 10;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    static clsDate IncreaseDateByXDecades(clsDate& Date, short Decades)
    {

        Date._Year += 10 * Decades;
        if (Date._Day > NumberOfDaysInAMonth(Date._Year, Date._Month))
            Date._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
        return Date;
    }
    static clsDate IncreaseDateByOneCentury(clsDate& Date)
    {
        Date._Year += 100;
        return Date;
    }
    static clsDate IncreaseDateByOneMillennium(clsDate& Date)
    {
        Date._Year += 1000;
        return Date;
    }
    void AddingOneDayToDate()
    {
        AddingOneDayToDate(*this);
    }
    void AddDaysToDate( short DaysToAdd)
    {
        AddDaysToDate(*this , DaysToAdd);
    }
    void IncreaseDateByXDays( short Days)
    {
        IncreaseDateByXDays(*this, Days);
    }
    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(*this);
    }
    void IncreaseDateByXWeeks( short Weeks)
    {
        IncreaseDateByXWeeks(*this, Weeks);
    }
    void IncreaseDateByOneMonth()
    {
        IncreaseDateByOneMonth(*this);
    }
    void IncreaseDateByXMonths( short Months)
    {
        IncreaseDateByXMonths(*this, Months);
    }
    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }
    void IncreaseDateByXYears( short Years)
    {
        IncreaseDateByXYears(*this, Years);
    }
    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }
    void IncreaseDateByXDecades( short Decades)
    {
        IncreaseDateByXDecades(*this, Decades);
    }
    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }
    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }

};

