# 个人财务管理系统

这是一个基于命令行的个人财务管理程序，使用 C++ 编写。系统支持记录收入与支出、按日期范围查询、分类统计、余额预警以及财务目标追踪等功能。

## 主要功能

- 添加收入记录（工资、经营、投资、利息、零用钱、其他）
- 添加支出记录（住房、饮食、交通、保险、医疗、服饰、教育、娱乐、宠物、旅行、其他）
- 查看所有记录，并支持按金额、类型或日期排序
- 按日期查询、修改或删除记录
- 实时计算余额，超支时自动发出警告
- 设置并跟踪财务目标，达成时提示祝贺
- 数据持久化存储于 `records.txt` 文件
- 输入校验，包括日期合法性检查及禁止输入未来日期

## 编译与运行

1. 使用支持 C++11 或更高标准的编译器编译源代码：
   ```bash
   g++ -std=c++11 *.cpp -o financial_management
   ```

2. 运行可执行文件：
   ```bash
   ./financial_management    # Linux/macOS
   financial_management.exe  # Windows
   ```

## 配置说明

- 所有数据均保存在程序所在目录下的 `records.txt` 文件中，程序启动时自动加载。
- 默认财务目标为 10000 单位，可通过菜单选项 “Set expect target”（设置期望目标）进行修改。
- 日期输入必须合法，且不能为未来日期。

## 文件结构

- `main.cpp`：程序入口
- `record.h` / `record.cpp`：记录基类
- `income_record.h` / `income_record.cpp`：收入记录实现
- `spend_record.h` / `spend_record.cpp`：支出记录实现
- `date.h` / `date.cpp`：日期处理与验证
- `recordmanager.h` / `recordmanager.cpp`：核心管理逻辑
- `menu.h` / `menu.cpp`：用户界面与输入处理
