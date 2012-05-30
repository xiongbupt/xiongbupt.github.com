---
layout: post
title: "linux_timer"
category:
tags: []
---
{% include JB/setup %}
int mod_timer(struct timer_list *timer，unsigned long expires)：该函数负责修改内核定时器timer的超时字段expires。该函数可以修改激活和没有激活的内核定时器的超时时间，并把它们都设置为激活状态；返回值为0表示修改的内核定时器在修改之前处于未激活状态，返回值为1表示修改的内核定时器在修改之前处于已激活状态。
del_timer(sturct timer_list *timer):返回值为0表示修删的内核定时器在删除之前处于未激活状态，返回值为1表示删除的内核定时器在删除之前处于已激活状态。
