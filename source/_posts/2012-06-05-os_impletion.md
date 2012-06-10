---
layout: post
title: "一个操作系统的实现笔记"
category: Notes
tags: [OS, Learning]
---
下面的主要介绍的是Arch下面，对[Orange'S一个操作系统的实现][lab1]，这本书的笔记。
##Arch下工具安装
文章介绍的汇编器为nasm，在arch下安装相当简单
>pacman -S nasm

<!--more-->
上面这条命令即可完成nasm汇编器的安装。对于虚拟机，使用的是bochs，在Arch下如果使用`pacman`安装的话，没有调试功能，对于后期的调试不方便。但是在Arch的AUR包中，已经有了bochs的调试版本，仅仅需要使用`yaourt -S bochs-with-debugger`即可将具有调试功能的bochs虚拟机安装上。

在完成上述操作后，该书介绍的基本工具便已经完备了，接下来便是对bochs进行配置了。

##bochs配置
bochs的示例配置文件位于`/usr/share/doc/bochs/bochsrc-sample.txt`，将该配置文件拷贝出来，位于自己工作目录下，并重新命名为bochsrc。这样在每次启动bochs时，便没有必要使用`-f`来指定使用的配置文件名。

按照书中的推荐配置，bochsrc-sample.txt文件很大，上面有很多不需要的配置选项，按照书中的指示，将bochsrc文件中配置精简为如下所示：

{% codeblock lang:bash %}
megs:   32
floppya: 1_44=a.img, status=inserted
romimage: file=/usr/share/bochs/BIOS-bochs-latest
vgaromimage: file=/usr/share/bochs/VGABIOS-lgpl-latest
boot: floppy
log: bochsout.txt
mouse: enabled=0
keyboard_mapping: enabled=1, map=/usr/share/bochs/keymaps/x11-pc-us.map
{% endcodeblock %}

##汇编文件编译及制作启动软盘
按照书中第一章节中的介绍，将启动软盘的代码敲入，然后使用nasm编译，使用bximage生成一个虚拟的软盘，接着使用dd工具将对应的编译生成的文件拷贝到相应的软盘工具中。接下来的工作按照书中介绍的内容继续即可。

##附录：汇编代码
{% codeblock lang:nasm %}
    org     07c00h
    mov     ax, cs
    mov     ds, ax
    mov     es, ax
    call    DispStr
    jmp     $       ;jump to this line, be a dead loop
DispStr:
    mov     ax, BootMessage
    mov     bp, ax
    mov     cx, 16      ;the length of string
    mov     ax, 01301h  ;make the font on the screen
    mov     bx, 000ch
    mov     dl, 0
    int     10h
    ret
BootMessage:        db      "Hello, Os world!"
times   510-($-$$)  db  0
dw      0xaa55
{% endcodeblock %}
[lab1]:http://book.douban.com/subject/3735649/ "一个操作系统的实现"
