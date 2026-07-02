#include "calculator.hpp"
#include "date_calculator.hpp"
#include "history.hpp"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <locale>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {

enum class Command {
    Continue,
    Clear,
    Back
};

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

Command checkCommand(const std::string& input) {
    if (input == "$") {
        return Command::Clear;
    }
    if (input == "#") {
        return Command::Back;
    }
    return Command::Continue;
}

bool readInt(const std::string& input, int& value) {
    std::stringstream ss(input);
    ss >> value;
    return !ss.fail() && ss.eof();
}

void cleanupInput() {
    if (std::cin.fail()) {
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void runCalculator(NumberMode mode, HistoryStore& history) {
    std::cout << "\n----------\n";
    std::cout << "请输入：数字 数字 运算符（$=清屏，#=返回主菜单）\n";

    while (true) {
        std::cout << "> ";

        std::string left;
        std::cin >> left;
        if (!std::cin) {
            cleanupInput();
            continue;
        }

        const Command command = checkCommand(left);
        if (command == Command::Clear) {
            clearScreen();
            continue;
        }
        if (command == Command::Back) {
            return;
        }

        std::string right;
        char op = '\0';
        if (!(std::cin >> right >> op)) {
            std::cout << "输入格式错误，请按：数字 数字 运算符\n";
            cleanupInput();
            continue;
        }

        if (checkCommand(right) != Command::Continue || op == '$' || op == '#') {
            std::cout << "清屏或返回主菜单请单独输入 $ 或 #\n";
            cleanupInput();
            continue;
        }

        const CalculationResult result = calculate(mode, left, right, op);
        if (!result.ok) {
            std::cout << result.error << "\n";
            continue;
        }

        std::cout << "结果：" << result.value << "\n";
        history.add(result.expression, result.value);
        history.save();
    }
}

void runDateCalculator() {
    std::cout << "\n----------\n";
    std::cout << "请输入：年 月 日 星期 增加天数（$=清屏，#=返回主菜单，负数表示减少）\n";

    while (true) {
        std::cout << "> ";

        std::string first;
        std::cin >> first;
        if (!std::cin) {
            cleanupInput();
            continue;
        }

        const Command command = checkCommand(first);
        if (command == Command::Clear) {
            clearScreen();
            continue;
        }
        if (command == Command::Back) {
            return;
        }

        DateInput input{};
        if (!readInt(first, input.year) ||
            !(std::cin >> input.month >> input.day >> input.weekday >> input.offsetDays)) {
            std::cout << "输入格式错误，请按：年 月 日 星期 增加天数\n";
            cleanupInput();
            continue;
        }

        const DateResult result = addDays(input);
        if (!result.ok) {
            std::cout << result.error << "\n";
            continue;
        }

        std::cout << result.year << "年" << result.month << "月" << result.day
                  << "日 星期" << result.weekday << "\n";
    }
}

void showHistory(const HistoryStore& history) {
    const auto& entries = history.entries();
    if (entries.empty()) {
        std::cout << "暂无历史记录。\n";
        return;
    }

    std::cout << "\n---- 历史记录（最新在前）----\n";
    for (std::size_t i = entries.size(); i > 0; --i) {
        const HistoryEntry& entry = entries[i - 1];
        std::cout << "[" << i - 1 << "] " << entry.expression << " = " << entry.result << "\n";
    }
}

void runHistoryMenu(HistoryStore& history) {
    while (true) {
        std::cout << "\n-------- 历史记录（$=清屏，#=返回主菜单）--------\n";
        std::cout << "1. 查看所有记录\n";
        std::cout << "2. 清空所有记录\n";
        std::cout << "3. 返回主菜单\n";
        std::cout << "请选择: ";

        std::string input;
        std::cin >> input;

        const Command command = checkCommand(input);
        if (command == Command::Clear) {
            clearScreen();
            continue;
        }
        if (command == Command::Back) {
            return;
        }

        int choice = 0;
        if (!readInt(input, choice)) {
            std::cout << "输入无效，请输入数字 1/2/3\n";
            continue;
        }

        if (choice == 1) {
            showHistory(history);
        } else if (choice == 2) {
            history.clear();
            history.save();
            std::cout << "历史记录已清空。\n";
        } else if (choice == 3) {
            return;
        } else {
            std::cout << "无效选择，请输入 1/2/3\n";
        }
    }
}

bool confirmExit() {
    while (true) {
        std::cout << "是否确定退出？1.确定 | 2.返回主菜单：";

        std::string input;
        std::cin >> input;

        int choice = 0;
        if (!readInt(input, choice)) {
            std::cout << "输入无效，请输入 1 或 2\n";
            continue;
        }

        if (choice == 1) {
            return true;
        }
        if (choice == 2) {
            return false;
        }
        std::cout << "无效选择，请输入 1 或 2\n";
    }
}

} // namespace

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::locale::global(std::locale(""));
    std::cin.imbue(std::locale());
    std::cout.imbue(std::locale());

    HistoryStore history("history.txt");
    history.load();

    while (true) {
        std::cout << "\n------------------------------------------------------------\n";
        std::cout << "请输入功能：1.整数计算 | 2.浮点计算 | 3.日期推算器 | 4.清屏 | 5.退出 | 6.历史记录：";

        std::string input;
        std::cin >> input;

        int choice = 0;
        if (!readInt(input, choice)) {
            std::cout << "输入无效，请输入菜单编号。\n";
            continue;
        }

        switch (choice) {
            case 1:
                runCalculator(NumberMode::Integer, history);
                break;
            case 2:
                runCalculator(NumberMode::FloatingPoint, history);
                break;
            case 3:
                runDateCalculator();
                break;
            case 4:
                clearScreen();
                break;
            case 5:
                if (confirmExit()) {
                    history.save();
                    std::cout << "退出成功\n";
                    return 0;
                }
                break;
            case 6:
                runHistoryMenu(history);
                break;
            default:
                std::cout << "无效选择，请输入 1 到 6。\n";
                break;
        }
    }
}
