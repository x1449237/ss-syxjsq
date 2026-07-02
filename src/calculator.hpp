#pragma once

#include <string>

enum class NumberMode {
    Integer,
    FloatingPoint
};

struct CalculationResult {
    bool ok{};
    std::string expression;
    std::string value;
    std::string error;
};

bool isSupportedOperator(char op);
CalculationResult calculate(NumberMode mode, const std::string& left, const std::string& right, char op);
