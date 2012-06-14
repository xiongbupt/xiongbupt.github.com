---
layout: post
title: "UTICODE编码记录"
date: 2012-06-11 11:29
comments: true
categories: Notes
tags: [VIM, Learning, UTF-8]
---
今天查看师兄以前写的笔记，中间看到一个UNICODE和UTF-8编码的内容，于是在网上找了下资料，现在对这点有一点点了解，主要参考了[阮老师的这篇文章][l1]，先记录下笔记吧。  
##UNICODE编码由来
在20世纪60年代，美国指定了ASCII编码体系，将英语字符与二进制位的关系做了统一的规定，这就是ASCII编码，并且一直沿用到今天。ASCII一共规定了128个字符的编码，只占用了一个字节的后7位，最高位始终为0。  

但是不同的国家的字符符号不一样，为了适应这种情况，就出现了UNICODE。  
UNICODE目前可以容纳100多万个符号，每个符号的编码都不一样。  
<!--more-->

##UNICODE的问题
UNCIDOE仅仅是一个符号集，它仅仅规定了符号的二进制代码，并没有规定符号如何存储。这就造成了下面两种结果：  

* 出现了UNICODE的多种存储方式；
* UNICODE在很长时间无法推广，直到互联网出现。

##UTF-8
目前UTF-8（UCS Transformation Format-8-bit）是互联网使用最广的一种编码，在[WIKI][l2]上其说明UTF-8是为了向后兼容ASCII码，同时也是为了避免在UTF-16和UTF-32中出现的复杂的大端序、小端序和字节符号序列，具统计目前有超过一半的Web网页使用的是UTF-8编码格式。IETF工作组也要求所有的网络协议表明字符集所使用的编码并且要求必须支持UTF-8。  

最开始UTF-8的设计图可以在下表中清晰的反应出来：  

|Bits|Last Code Point|Byte 1|Byte 2|Byte 3|Byte 4|Byte 5|Byte 6|
|---:|:----------|:------:|:------:|:------:|:------:|:------:|:------:|
|7   |U+007F     |0xxxxxxx|
|11  |U+07FF     |110xxxxx|10xxxxxx|
|16  |U+FFFF     |1110xxxx|10xxxxxx|10xxxxxx|
|21  |U+1FFFFF   |11110xxx|10xxxxxx|10xxxxxx|10xxxxxx|
|25  |U+3FFFFFF  |111110xx|10xxxxxx|10xxxxxx|10xxxxxx|10xxxxxx|
|31  |U+7FFFFFFF |1111110x|10xxxxxx|10xxxxxx|10xxxxxx|10xxxxxx|10xxxxxx|

最开始UTF-8的设计如上图所示，但是在[RFC 3629][l3]中UTF-8被截短了，目前UTF-8的最大值为U+10FFFF，因此所有的5字节和6字节的编码都被取消掉了。  

UTF-8的编码即是将UNICODE对应的编码值以上表的方式编码出来即可。因此所有的ASCII码都是以一个字节的方式编码，其他的字符集会根据对应的UNICODE的编码值进行编码。比如`美`对应的UNICODE的值为7F8E，在上表中可以查看出其使用3字节编码即可，7F8E的二进制表示为0111 1111 1000 1110因此其UTF-8的编码为E7 BE 8E。就是将UNICODE的二进制值填充到UTF-8中的x上，完成编码。   
注意，UTF-8仅仅是UNICODE的一种编码方式。

##UTF-8的bomb字符
在编辑器打开一个文本文件时，其是怎么判断打开文件的编码格式？下面是个人的理解，编辑器应该会对打开的文件进行编码猜测，但是如果文件没有提供对应的编码标志的话，其就会按照自己的猜测文件编码格式将文本文件打开。如果编辑器猜测的编码与文件的实际编码不一致，就会出现乱码现象。但是如果文本文件提供了自身的编码方式，并且编辑器也可以理解即解释这种编码方式的话，应该就可以将文本文件按照正确的形式显现出来。  

上面的那段主要是为了引出UTF-8的bomb字符。参考[这篇博客][l4]，可以知道UTF-8的bomb为字符：EF BB BF。按照文中的方式，在VIM中使用16进制的方式<kbd>:%!xxd</kbd>，将文本文件打开，可以看出对应文字的UTF-8编码，在自己的环境下，使用的是UTF-8的编码格式，VIM似乎就已经将该bomb值去掉了。但是通过设置<kbd>:set bomb</kbd>可以将bomb保留，通过<kbd>:set nobomb</kbd>可以将文件的bomb去除。  

在这种情形下想到以前从Linux系统向Windows系统下拷贝文本文件时，有时候会出现乱码现象，猜想会不会是由于VIM将文件的bomb去除了，而Windows使用的编码默认不是UTF-8编码，其编辑器猜测编码的格式猜测错了，导致乱码，于是在Linux系统下拷贝了两个简单的带有汉字的文件到Windows系统下，这两个文件分别使用<kbd>:set bomb</kbd>和<kbd>:set nobomb</kbd>的方式将UTF-8的编码信息保留和去除。  

在Windows下使用记事本打开这两个文件时，汉字都可以正常的显示，但是由于Linux和Windows的换行方式不一致，会出现一些黑的方框；在写字板中打开文件时，带有bomb编码信息的文本文件可以正常的显示汉字，但是去除了bomb信息的文本文件出现了乱码。  

上面的现象应该可以说明Windows下面的记事本猜测编码格式正确，但是写字板猜测错误，可写字板对Linux下的换行符可以正常的显示。如果为了在Windows下正确的打开Linux下带有中文字符的文本文件，同时换行符也正常显示的话，可以在保存文件之前输入<kbd>:set bomb</kbd>将文本文件的编码格式保存下。

###附录
VIM中使用16进制的方式打开文件 <kbd>:%!xxd</kbd>     
VIM中在打开16进制的方式中编辑完文件之后保存 <kbd>:%!xxd -r</kbd>    
VIM保存UTF-8文件的bomb信息 <kbd>:set bomb</kbd>     
VIM中去除文件的bomb信息 <kbd>:set nobomb</kbd>      
UTF－8：一个汉字＝3个字节

[l1]:http://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html
[l2]:http://en.wikipedia.org/wiki/UTF-8  "WIKI UTF-8"
[l3]:http://tools.ietf.org/html/rfc3629 "rfc3629"
[l4]:http://www.i-alive.com/post/8/

