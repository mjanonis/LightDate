# LightDate
Simple and basic header only C++ date library

## Usage

Make a date 1990-02-22
```
Date a {1990,Month::feb,22};
```

```
Date error {1990,Month::feb,30};
```
Throws a runtime_error

```
Date a {2018,Month::jan,1};
Date b {2018,Month::jan,3};
```
a - b == 2
