#include "date_calculator.hpp"

namespace {

bool isValidDate(int year, int month, int day) {
    if (year <= 0 || month < 1 || month > 12) {
        return false;
    }
    return day >= 1 && day <= daysInMonth(year, month);
}

bool isValidWeekday(int weekday) {
    return weekday >= 1 && weekday <= 7;
}

} // namespace

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int year, int month) {
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month < 1 || month > 12) {
        return 0;
    }
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

DateResult addDays(DateInput input) {
    if (!isValidDate(input.year, input.month, input.day)) {
        return {false, 0, 0, 0, 0, "日期无效"};
    }
    if (!isValidWeekday(input.weekday)) {
        return {false, 0, 0, 0, 0, "星期必须是 1 到 7"};
    }

    int year = input.year;
    int month = input.month;
    int day = input.day;
    int weekday = input.weekday;
    int remaining = input.offsetDays;

    while (remaining != 0) {
        if (remaining > 0) {
            ++day;
            weekday = weekday == 7 ? 1 : weekday + 1;
            if (day > daysInMonth(year, month)) {
                day = 1;
                ++month;
                if (month > 12) {
                    month = 1;
                    ++year;
                }
            }
            --remaining;
        } else {
            --day;
            weekday = weekday == 1 ? 7 : weekday - 1;
            if (day < 1) {
                --month;
                if (month < 1) {
                    month = 12;
                    --year;
                }
                if (year <= 0) {
                    return {false, 0, 0, 0, 0, "结果年份超出支持范围"};
                }
                day = daysInMonth(year, month);
            }
            ++remaining;
        }
    }

    return {true, year, month, day, weekday, ""};
}
