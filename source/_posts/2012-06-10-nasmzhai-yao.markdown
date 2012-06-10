---
layout: post
title: "nasm摘要"
date: 2012-06-10 15:22
comments: true
categories: Notes
tags: [Learning, NASM, 汇编]
---
还是为了看[这本书][l1]，又找了下nasm的学习资料，在网上找到了这个[网址][l2]，应该是nasm的官方参考手册，重点打算看下前面三章，做下笔记。
##介绍
###什么是NASM
NASM是一种面向80x86和x86-64的新型汇编语言，其出现主要是为了可移植性和可修改性。
<!--more-->

##运行NASM
###NASM语法
<kbd>nasm -f <format> <filename> [-o <output>]</kbd>
####<kbd>-o</kbd>选项：指定输出文件名
NASM会根据文件的名字自动来生成输出文件名，对于WIN32和Unix系列输出的文件名的方式不一样，但是都是会将后缀去掉，NASM不关心后缀究竟是什么，只是按照不同的平台输出对应的后缀名。  
如果指定了<kbd>-o</kbd>选项，将会按照<kbd>-o</kbd>的选项的文件名产生文件，如果<kbd>-o</kbd>指定的文件已经存在则会将已存在的文件覆盖除非指定的输出的文件名为汇编源文件，在这种情况下将会输出警告，同时NASM将会生成一个名为<kbd>nasm.out</kbd>的文件。在<kbd>-o</kbd>选项和输出的文件名之间可以有空格也可以没有。
####<kbd>-f</kbd>选项指定输出文件的格式
<kbd>-f</kbd>选项指定输出文件的格式，如果没有指定的话，NASM将会按照其默认格式输出，一般输出的是bin格式。在`-f`和输出格式之间的空格是可选的，比如<kbd>-f elf</kbd>和<kbd>-felf</kbd>都是合法的。
####<kbd>-l</kbd>选项生成文件清单
如果指定-l选项，将会生成一个汇编生成的文件。在该文件，左侧是地址和产生的代码，右侧是实际的汇编代码。
####<kbd>-M</kbd>选项生成Makefile的依赖关系
如果使用该选项，将会在标准输出上生成Makefile的依赖关系。
####<kbd>-MG</kbd>选项生成Makefile的依赖关系
该选项和上面的选项的区别在与如果存在一个不存在的文件的依赖关系，它将会假定产生了该文件，同时将未加文件前缀的名字输出到标准输出上。
####<kbd>-MF</kbd>选项将Makefile的依赖关系输出到文件
这个选项一般和-M或者-MG同时使用，将依赖关系生成一个文件。  
nams -M -MF myfle.dep myfile.asm
####<kbd>-MD</kbd>选项汇编并且生成依赖关系
-MD选项可以作为-M和-MF的联合体。但是与-M或者-MG不同的是，-MD选项不会禁止汇编器的正常操作。比如：  
nasm -f elf -o myfile.o -MD myfile.dep myfile.asm
####<kbd>-MT</kbd>选项：目的文件文件名
功能与-o一样。
####<kbd>-MQ</kbd>选项：指定目的文件文件名
功能与-MT类似，只是其指定了被引用的字符具有特殊含义。
####<kbd>-MP</kbd>选项：省略中间输出
使用该选项将会省略中间的输出。
####<kbd>-F</kbd>选项：选择Debug的格式
####<kbd>-g</kbd>选项：允许调试信息
####<kbd>-x</kbd>选项：选择生成错误报告的格式
####<kbd>-z</kbd>选项：将错误信息输出到文件
####<kbd>-s</kbd>选项：将错误信息输出到标准输出
####<kbd>-i</kbd>选项：在搜索目录中添加搜索路径

###MASM用户指南
下文主要介绍NASM与MASM的区别
####NASM区分大小写
一个最简单的区别就是NASM是区分大小写的。
####NASM对内存的使用需要使用方括号
与MASM相比较来说，NASM的目的是对所有语句，尽可能的将一条语句与对应的机器码对应起来。对内存地址的引用都需要使用中括号。相对于MASM中的间接寻址等方式，NASM中的所有和内存相关的操作均需要添加中括号。因此在NASM中也就没有`offset`这样的关键字，比如在MASM中的`mov ax, table[bx]`在NASM中是非法的，必须转为`mov ax, [table+bx]`。  
####NASM不支持存储变量类型
在MASM中，对变量的说明的同时还指定了变量的类型，但是NASM中仅仅记录了变量的开始位置，不会记录任何有关变量类型的说明。因此在对变量赋值操作时，需要指定赋值的大小，因此NASM不支持例如`LODS, MOVS, STOS, SCAS, CMPS, INS, OUTS`等指令，而仅仅支持`LODSB, MOVSW, SCASD`，这几种支持的操作都明确指定了操作数的大小。
####NASM不使用<kbd>ASSUME</kbd>
作为NASM的一个简化动机，NASM不支持使用<kbd>ASSUME</kbd>，NASM不会跟踪在段寄存器中存放的是什么值，并且不会自动生成段前缀。
####NASM不支持内存模型
NASM不支持16比特的内存模型，程序员自己负责`jmp`等指令是否为近转移或是远转移。同时对于`RET`指令，也是程序员自己负责。NASM将`RET`作为`RETN`的一个可选模式。
####浮点数的区别
NASM使用不同的名字来命名浮点数，在MASM中，对于浮点数将会命名为类似于`ST(0)`或`ST(1)`等类似的方式，可在NASM中，将会命名为`st0`，`st1`等方式。  
####其他区别
由于历史的原因，NASM使用关键字<kbd>TWORD</kbd>而MASM使用的是<kbd>TBYTE</kbd>。  
除了上述区别之外，宏和指令性的工作在MASM和NASM中也是不同的。

##NASM语言
###NASM语言的布局
{% codeblock NASM语言的布局 lang:nasm %}
label:  instruction     operands        ;comment
{% endcodeblock %}
NASM语句中空格是可以任意多的。NASM使用\\来作为一行的换行符指示后面还是当前行的继续。
###伪指令
NASM中支持的伪指令包括<kbd>DB,DW,DD,DQ,DT,DO</kbd>和<kbd>DY；RESB，RESW，RESD，RESQ，REST，RESO和RESY</kbd>；以及<kbd>INCBIN，EQU，TIMES</kbd>
####DB及同类：声明已初始化数据
####RESB及同类：声明未初始化数据
####INCBIN：包含而外的二进制文件
####EQU：定义常量
####TIMES：重复指令或数据
###有效的地址
语法非常简单，就是在有效地址的变量加上中括号即可。
###常量
NASM包括四种类型的常量，分别是数字、字符、字符串和浮点数
###表达式
在NASM中的表达式与C语言中的类似。表达式被当做64位整型数计算然后再被调整到合适的尺寸。NASM在表达式中支持两个特殊的符号，用来计算当前汇编语言的位置，分别是<kbd>$</kbd>和<kbd>$$</kbd>操作符。  
<kbd>$</kbd>操作符用来计算包含该符号的表达式在汇编语言中的起始位置；<kbd>$$</kbd>用来计算当前区域的其实位置。所以可以通过使用<kbd>$-$$</kbd>来计算当前位置与段起始处的距离。
####<kbd>|</kbd>按位或
####<kbd>^</kbd>按位异或
####<kbd>&</kbd>按位与
####<kbd>>></kbd>和<kbd><<</kbd>移位操作符
####<kbd>+</kbd> <kbd>-</kbd>：加减操作符
####<kbd>*</kbd>,<kbd>/</kbd>,<kbd>//</kbd>,<kbd>%</kbd>, <kbd>%%</kbd>：乘法和除法表达式
####一元操作符：<kbd>+</kbd>,<kbd>-</kbd>,<kbd>~</kbd>,<kbd>!</kbd>,<kbd>SEG</kbd>

[l1]:http://book.douban.com/subject/3735649/ "一个操作系统的实现"
[l2]:http://www.nasm.us/doc/nasmdoc0.html "nasm手册"
