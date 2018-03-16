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

