---
layout: post
title: "Linux定时器"
category: Linux
tags: [Linux, OS]
---
{% codeblock lang:c %}
int mod_timer(struct timer_list *timer，unsigned long expires)
{% endcodeblock %}
该函数负责修改内核定时器timer的超时字段expires。该函数可以修改激活和没有激活的内核定时器的超时时间，并把它们都设置为激活状态；返回值为0表示修改的内核定时器在修改之前处于未激活状态，返回值为1表示修改的内核定时器在修改之前处于已激活状态。
<!--more-->
{% codeblock lang:c %}
del_timer(sturct timer_list *timer)
{% endcodeblock %}
返回值为0表示修删的内核定时器在删除之前处于未激活状态，返回值为1表示删除的内核定时器在删除之前处于已激活状态。
