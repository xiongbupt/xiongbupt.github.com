---
layout: post
title: "Linux系统调用分类"
category: Linux
tags: [Linux,OS]
---
##进程管理

进程管理包括创建进程，查询进程信息，修改进程信息等。fork，vfork将一个进程创建为两个进程。clone是fork的增强版，还可以创建线程。

exit结束一个进程并释放其占用的资源。

personlity定义应用程序的执行环境。

ptrace使得能跟踪系统调用，是strace的分支。（strace的使用方法 strace -o a.txt program，将program调用的系统调用输出到文件a.txt中）

nice设置普通进程的优先级，从-20到19之间。数值越低，优先级越高。

##时间操作

adjtimex读取和设置基于时间的内核变量。

gettimeofday和settimeofday分别获取和设置当前系统时间。

time返回自1970年1月1日零时开始经过的时间。stime可以设置这个值，因此也可以修改系统时间。

##信号处理

signal设置信号处理函数。

sigpending检查进程当前是否有待解决的信号被阻塞。

kill用于向一个进程发送任何信号。

##调度

setpriority和getpriority分别设置和获取进程的优先级。

##模块

init_module添加一个新模块

delete_module从内核移除一个模块

##文件系统


##内存管理
##进程间通信和网络功能
##系统信息和设置
##系统安全和能力

