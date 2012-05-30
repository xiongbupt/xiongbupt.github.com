---
layout: post
title: "linux进程学习"
category: 
tags: []
---
{% include JB/setup %}
##linux进程调度与管理

###linux进程状态

linux进程描述符使用的结构体为task_struct，结构体的定义位于include/linux/sched.h文件中。该结构体很复杂，包含了一个进程应该包含的所有信息。

进程可以处于的状态包括：

TASK_RUNNING:进程当前正在运行或者处于待运行的队列中；

TASK_INTERRUPTIBLE:进程处于休眠队列中，可以被中断唤醒或者被信号唤醒。其中被信号唤醒为伪唤醒，每次进程被唤醒时需要对唤醒的条件进行判断，若不符合条件则继续休眠。

TASK_UNINTERRUPTIBLE:进程同样位于休眠队列中，但是只能够被中断所唤醒，忽略信号。这种情况可以用于在驱动程序中，等待硬件初始化中使用，防止对硬件进行其他操作。

TASK_STOPPED:进程被终止，如被调试器缩终止。

TASK_TRACED:进程被追踪了，用来和TASK_STOPPED所区分。

EXIT_ZOMBIE:子进程终止，但是父进程没有调用wait()系列函数，子进程无法正常退出，处于这种状态。

EXIT_DEAD:在适当的wait()调用之后当程序还没有完全从系统中移除时，防止其他线程再次调用wait()系列函数时处的状态。


