---
layout: post
title: "gdb 学习"
category: Notes
tags: [Linux, Learning]
---

##GBD指令
backtrace 在程序出现错误之后，使用它可以看出出错的函数被哪个函数所调用。

查看内存地址存放的值
>x 内存地址(examine)  

查看代码。  
>list  
    如list 1,90用来查看1到90行的代码。

<!--more-->
用来设置断点
>break  

设置到函数的断点,函数所在行也可以设置断点
>break 函数名  

设置条件
>condition  

仅仅在var变量的值为some_value时使用断点，与断点一起使用，可以减少断点的量
>condition 1 var==some_value  



##[摘抄][lab1]
###断点(breakpoint)

break命令（可以简写为b）可以用来在调试的程序中设置断点，该命令有如下四种形式：

使程序恰好在执行给定行之前停止。
>break line-number  

使程序恰好在进入指定的函数之前停止。
>break function-name  

如果condition（条件）是真，程序到达指定行或函数时停止。
>break line-or-function if condition   

在指定例程的入口处设置断点
>break routine-name   

如果该程序是由很多原文件构成的，你可以在各个原文件中设置断点，而不是在当前的原文件中设置断点，其方法如下：
>(gdb) break filename:line-number
>(gdb) break filename:function-name

要想设置一个条件断点，可以利用break if命令，如下所示：
>(gdb) break line-or-function if expr

例：
>(gdb) break 46 if testsize==100

从断点继续运行：countinue 命令


###断点的管理
1. 显示当前gdb的断点信息：
>(gdb) info break  

他会以如下的形式显示所有的断点信息：
    Num Type Disp Enb Address What
    1 breakpoint keep y 0x000028bc in init_random at qsort2.c:155
    2 breakpoint keep y 0x0000291c in init_organ at qsort2.c:168
    (gdb)
2. 删除指定的某个断点：
>(gdb) delete breakpoint 1  

上面的命令将会删除编号为1的断点，如果不带编号参数，将删除所有的断点
>(gdb) delete breakpoint

3. 禁止使用某个断点
下面的命令将禁止断点 1,同时断点信息的 (Enb)域将变为 n
>(gdb) disable breakpoint 1  

4. 允许使用某个断点
命令将允许断点 1,同时断点信息的 (Enb)域将变为 y
>(gdb) enable breakpoint 1

5. 清除原文件中某一代码行上的所有断点
>(gdb)clear number
    注：number 为原文件的某个代码行的行号


###变量的检查和赋值
* whatis:识别数组或变量的类型
* ptype:比whatis的功能更强，他可以提供一个结构的定义
* set variable:将值赋予变量
* print 除了显示一个变量的值外，还可以用来赋值


###单步执行
不进入函数的单步执行
>next

进入函数的单步执行
>step
如果已经进入了某函数，而想退出该函数返回到它的调用函数中，可使用命令finish


####常用的gdb命令
* backtrace 显示程序中的当前位置和表示如何到达当前位置的栈跟踪（同义词：where）
* breakpoint 在程序中设置一个断点
* cd 改变当前工作目录
* clear 删除刚才停止处的断点
* commands 命中断点时，列出将要执行的命令
* continue 从断点开始继续执行
* delete 删除一个断点或监测点；也可与其他命令一起使用
* display 程序停止时显示变量和表达时
* down 下移栈帧，使得另一个函数成为当前函数
* frame 选择下一条continue命令的帧
* info 显示与该程序有关的各种信息
* jump 在源程序中的另一点开始运行
* kill 异常终止在gdb 控制下运行的程序
* list 列出相应于正在执行的程序的原文件内容
* next 执行下一个源程序行，从而执行其整体中的一个函数
* print 显示变量或表达式的值
* pwd 显示当前工作目录
* pype 显示一个数据结构（如一个结构或C++类）的内容
* quit 退出gdb
* reverse-search 在源文件中反向搜索正规表达式
* run 执行该程序
* search 在源文件中搜索正规表达式
* set variable 给变量赋值
* signal 将一个信号发送到正在运行的进程
* step 执行下一个源程序行，必要时进入下一个函数
* undisplay display命令的反命令，不要显示表达式
* until 结束当前循环
* up 上移栈帧，使另一函数成为当前函数
* watch 在程序中设置一个监测点（即数据断点）
* whatis 显示变量或函数类型
[lab1]:http://fanqiang.chinaunix.net/program/other/2006-07-14/4834.shtml
