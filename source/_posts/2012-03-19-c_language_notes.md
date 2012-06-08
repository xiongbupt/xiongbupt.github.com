---
layout: post
title: "c语言笔记"
category: C语言
tags: [C Language]
---

{% codeblock lang:c %}
__attribute__((packed))  
{% endcodeblock %}
取消编译器的默认优化，按照字节的方式进行对齐

{% codeblock lang:c %}
memset(void *ptr, int value, size_t num)
{% endcodeblock %}
注意第二个和第三个参数的顺序，首先是设置的值然后才是设置的位数
