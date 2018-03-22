# LightDate
Simple and basic header only C++ date library

## Usage

```
Date a {1990,Month::feb,22};
```
Makes a date 1990-02-22

```
Date error {1990,Month::feb,30};
```
Throws a runtime_error

```
Date a {2018,Month::jan,1};
Date b {2018,Month::jan,3};
```
Date - Date returns integer that is equal to days between those two days (e.g.: a - b == 2) </br>
Date - int returns a Date int days before the original one (e.g.: b - 2 == Date{2018,Month::jan,1}) </br>
Date + Date N/A </br>
Date + int returns a Date int days ahead the original one (e.g.: a + 10 == Date{2018,Month::jan,11}) </br>

Date++ increments the Date by one day </br> 
Date-- decrements the Date by one day </br>

Comparison operators are also provided </br>
a < b == true </br>

operator<< outputs the date in accordance with the ISO 8601 standard </br>




