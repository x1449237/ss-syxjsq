#pragma once

#include <string>

struct DateInput {
    int year{};
    int month{};
    int day{};
    int weekday{};
    int offsetDays{};
};

struct DateResult {
    bool ok{};
    int year{};
    int month{};
    int day{};
    int weekday{};
    std::string error;
};

bool isLeapYear(int year);
int daysInMonth(int year, int month);
DateResult addDays(DateInput input);
