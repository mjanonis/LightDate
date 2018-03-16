#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>

enum Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

class Date {
public:
  Date(int y, Month m, int d)
  {
    if (validDate(y, m, d)) {
      year = y;
      month = m;
      day = d;
    }
    else {
      throw std::runtime_error("Invalid date");
    }
  }
  Date(std::chrono::time_point<std::chrono::_V2::system_clock,
                               std::chrono::nanoseconds>
           n)
  {
    auto now = std::chrono::system_clock::to_time_t(n);
    tm utc_tm = *localtime(&now);
    year = utc_tm.tm_year + 1900;
    month = static_cast<Month>(utc_tm.tm_mon + 1);
    day = utc_tm.tm_mday;
  }

  int getYear() { return year; }
  Month getMonth() { return month; }
  int getDay() { return day; }

  void setYear(int y) { year = y; }
  void setMonth(Month m) { month = m; }
  void setDay(int d) { day = d; }

  Date operator++(int);
  Date& operator++();

private:
  int year;
  Month month;
  int day;

  bool validDate(int y, Month m, int d);
  bool leapYear(int y);
};

Date Date::operator++(int)
{
  Date orig(*this);
  if (validDate(year, month, day + 1)) { day++; }
  else if (validDate(year, static_cast<Month>(month + 1), 1)) {
    day = 1;
    month = static_cast<Month>(month + 1);
  }
  else if (validDate(year + 1, Month::jan, 1)) {
    day = 1;
    month = Month::jan;
    year++;
  }
  return orig;
}

Date& Date::operator++()
{
  if (validDate(year, month, day + 1)) { day++; }
  else if (validDate(year, static_cast<Month>(month + 1), 1)) {
    day = 1;
    month = static_cast<Month>(month + 1);
  }
  else if (validDate(year + 1, Month::jan, 1)) {
    day = 1;
    month = Month::jan;
    ++year;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, Date& dd)
{
  return os << std::setfill('0') << dd.getYear() << "-" << std::setw(2)
            << dd.getMonth() << "-" << std::setw(2) << dd.getDay();
}

bool Date::leapYear(int y)
{
  if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) { return true; }
  return false;
}

bool Date::validDate(int y, Month m, int d)
{
  if (m >= Month::jan && m <= Month::dec) {
    if ((d >= 1 && d <= 31) &&
        (m == Month::jan || m == Month::mar || m == Month::may ||
         m == Month::jul || m == Month::aug || m == Month::oct ||
         m == Month::dec)) {
      return true;
    }
    else if ((d >= 1 && d <= 30) && (m == Month::apr || m == Month::jun ||
                                     m == Month::sep || m == Month::nov)) {
      return true;
    }
    else if (d >= 1 && d <= 28 && m == Month::feb) {
      return true;
    }
    else if (leapYear(y) && m == Month::feb && d == 29) {
      return true;
    }
  }
  return false;
}
