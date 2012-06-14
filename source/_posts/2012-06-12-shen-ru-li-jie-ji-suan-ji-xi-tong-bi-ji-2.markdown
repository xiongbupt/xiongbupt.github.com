---
layout: post
title: "深入理解计算机系统-笔记 Ch2"
date: 2012-06-12 03:00
comments: true
categories: Notes
tags: [Learning, OS, C, Perl]
---
计算机的表示法是用有限数量的位来完成对一个数字的编码，因此当结果太大时，将会溢出（overflow），整数运算具有结合性但是浮点数的运算是不可结合的。附录中有演示了书中提到的溢出和浮点数结合的c源代码。

gcc编译选项指定c语言的版本：

|c版本      |GCC命令行选项  |
|:---------:|:-------------:|
|GNU89      |无， -std=gnu89
|ANSI, ISO C90| -ansi, -std=c89
|ISO C99    |-std=c99
|GNU 99     |-std=gnu99

<!--more-->

##信息存储


##附录 
c代码
{% include_code overflow溢出代码 lang:c c/overflow.c %}
perl代码
{% include_code perl 10进制转16进制脚本 lang:perl perl/d2h %}
{% include_code perl 16进制转10进制脚本 lang:perl perl/h2d %}
