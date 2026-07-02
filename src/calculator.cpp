#include "calculator.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {

bool parseLongLong(const std::string& text, long long& value) {
    std::size_t consumed = 0;
    try {
        value = std::stoll(text, &consumed);
    } catch (const std::exception&) {
        return false;
    }
    return consumed == text.size();
}

bool parseDouble(const std::string& text, double& value) {
    std::size_t consumed = 0;
    try {
        value = std::stod(text, &consumed);
    } catch (const std::exception&) {
        return false;
    }
    return consumed == text.size();
}

std::string formatDouble(double value) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(10) << value;
    std::string text = out.str();

    while (text.size() > 1 && text.back() == '0') {
        text.pop_back();
    }
    if (!text.empty() && text.back() == '.') {
        text.pop_back();
    }
    return text.empty() ? "0" : text;
}

std::string makeExpression(const std::string& left, const std::string& right, char op) {
    return left + " " + op + " " + right;
}

} // namespace

bool isSupportedOperator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/';
}

CalculationResult calculate(NumberMode mode, const std::string& left, const std::string& right, char op) {
    if (!isSupportedOperator(op)) {
        return {false, "", "", "不支持的运算符"};
    }

    if (mode == NumberMode::Integer) {
        long long a = 0;
        long long b = 0;
        if (!parseLongLong(left, a) || !parseLongLong(right, b)) {
            return {false, "", "", "整数格式错误"};
        }
        if (op == '/' && b == 0) {
            return {false, "", "", "除数不能为 0"};
        }

        long long value = 0;
        switch (op) {
            case '+': value = a + b; break;
            case '-': value = a - b; break;
            case '*': value = a * b; break;
            case '/': value = a / b; break;
            default: break;
        }

        return {true, makeExpression(left, right, op), std::to_string(value), ""};
    }

    double a = 0;
    double b = 0;
    if (!parseDouble(left, a) || !parseDouble(right, b)) {
        return {false, "", "", "浮点数格式错误"};
    }
    if (op == '/' && b == 0.0) {
        return {false, "", "", "除数不能为 0"};
    }

    double value = 0;
    switch (op) {
        case '+': value = a + b; break;
        case '-': value = a - b; break;
        case '*': value = a * b; break;
        case '/': value = a / b; break;
        default: break;
    }

    return {true, makeExpression(left, right, op), formatDouble(value), ""};
}
