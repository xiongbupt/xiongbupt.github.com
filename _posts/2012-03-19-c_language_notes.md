---
layout: post
title: "c_language_notes"
category: 
tags: []
---
{% include JB/setup %}

__attribute__((packed))
    取消编译器的默认优化，按照字节的方式进行对齐

memset(void *ptr, int value, size_t num)
    注意第二个和第三个参数的顺序，首先是设置的值然后才是设置的位数
