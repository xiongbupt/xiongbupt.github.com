---
layout: post
title: "c语言笔记"
category: C语言
tags: [C语言]
---

{% highlight c %}
__attribute__((packed))  
{% endhighlight %}
取消编译器的默认优化，按照字节的方式进行对齐

{% highlight c %}
memset(void *ptr, int value, size_t num)
{% endhighlight %}
注意第二个和第三个参数的顺序，首先是设置的值然后才是设置的位数
