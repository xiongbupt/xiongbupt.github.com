---
layout: post
title: "linux_kernel_notes"
category: 
tags: []
---
{% include JB/setup %}
###linux内核等待队列
wait_queue_head_t
init_waitqueue_head()
DECLARE_WAIT_QUEUE_HEAD
等待队列就是一个进程链表，其中包含了所有等待某个特定事件的进程。
静态初始化一个等待队列头使用下面的宏
DECLARE_WAIT_QUEUE_HEAD(name)

动态初始化一个等待队列
wait_queue_head_t name;
init_waitqueue_head(&name)

add_wait_queue()用来将一个进程添加到等待队列，该函数在获得必要的自旋锁后，使用__add_wait_queue()函数来完成队列添加工作
