# ss-syxjsq

一个命令行计算器练习项目，支持整数计算、浮点计算、日期推算和本地历史记录。

## 功能

- 整数四则运算
- 浮点四则运算
- 日期增减天数推算
- 最近 100 条计算历史记录
- 功能页内输入 `$` 清屏，输入 `#` 返回主菜单

## 项目结构

```text
.
├── src/
│   ├── calculator.cpp        # 四则运算逻辑
│   ├── calculator.hpp
│   ├── date_calculator.cpp   # 日期推算逻辑
│   ├── date_calculator.hpp
│   ├── history.cpp           # 历史记录读写
│   ├── history.hpp
│   └── main.cpp              # 命令行交互入口
├── .gitignore
└── README.md
```

## 构建

需要支持 C++17 的编译器。

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/*.cpp -o syxjsq
```

Windows PowerShell 下如果使用 MinGW，请确保把所有实现文件一起编译：

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic .\src\main.cpp .\src\calculator.cpp .\src\date_calculator.cpp .\src\history.cpp -o syxjsq.exe
```

## 运行

```bash
./syxjsq
```

Windows PowerShell：

```powershell
.\syxjsq.exe
```

## 输入示例

整数或浮点计算：

```text
10 3 +
10 3 /
```

日期推算：

```text
2026 7 2 4 10
2026 7 2 4 -10
```

含义为：`年 月 日 星期 增加天数`，星期取值为 `1` 到 `7`。

历史记录会保存在运行目录下的 `history.txt`，该文件不会提交到 Git。
