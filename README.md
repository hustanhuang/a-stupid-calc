# a-stupid-calc

A Simple Calculator. (rewritten version of the task-calc)

## task-calc

repository for lab task 0x01

---

| Subject        | 【重要】【Lab组实习任务】Task 0x01   |
| :------------- | :--------------------------------- |
| From           | Xu Haoqi                           |
| To             | All members, Freshmembers          |
| Date           | November 2, 2015 at 18:14:44 GMT+8 |

#### Lab Task 0x01

C语言是一门美妙的语言，我们要（努力地）像使用母语一样，流利地使用C语言。

这一周我们来用C写一个命令行计算器吧。为什么是命令行呢？因为如果一个pc端计算器程序带有图形界面，那他一定是在嘲讽用户的智商。:P

来提一下要求吧：
  - C语言
    - 代码风格
  - 命令行
    - 参数传递
    - 交互模式 与 单行命令计算
  - 计算器
    - 支持二进制、八进制、十六进制（不想支持十进制的话随意）
    - 中缀表达式、支持括号优先级

统一使用git进行代码的版本控制

嗯 就这样吧 happy coding :)

## a-stupid-calc

usage: calc [-f input_file] [-o output_file] [-e] [expression] ...
Options and arguments:
-f     : specify the input file
-o     : specify the output file
-e     : enable the Evaluating mode
-h     : print this help message and exit

Expressions output:
    If the input or output is not given by the standard i/o, the expressions
    themselves would also be printed.
    The expressions would also be printed under the Evaluating mode.
