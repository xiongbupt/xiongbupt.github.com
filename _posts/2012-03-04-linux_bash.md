---
layout: post
title: "Learing bash笔记"
category: [Linux]
tags: [Linux, Shell]
---
{% include JB/setup %}
###第一章
cd - ：返回到之前的文件夹。用于工作路径的跳转。  
\ ' "引用键，可以取消特殊字符的含义，各个功能有强弱，其中'为强取消."为若取消，\仅仅取消一个字符的含义。使用上面这三个可以在命令过长时取消回车的含义，一般终端会提示>作为提示符号。  
ctrl+m在终端中相当于回车  
ctrl+d DELETE  
ctrl+j BACKSPACE  
stty --all查看当前终端的所有ctrl配置。  
在shell中，使用help中的通配符时，需要使用`''`将对应的通配符引用起来，如help 're*'; help 're??'等。  
###第二章 Command-Line Editing
改变shell的编辑模式使用set命名  
set -o emacs 或者 set -o vi  
vi模式编辑中的一些基本知识  
####字符移动
vi模式中有两种词的概念，一种是non-blank，这些就是所有的非空字符便是这种概念，另一种是word，这些是仅仅由字母数字以及_组成的，其他的均不算。  
h 左移一个字符  
l 右移一个字符  
w 右移一个词word  
b 左移一个词word  
W 下一个non-blank的开始  
B 前一个non-blank的开始  
e 当前词word的最后  
E 当前词non-blank的最后  
0 行的开始  
^ non-blank的开始  
$ 行的结束  
####插入改变文本
i  
a append  
I beginning  
A end of line  
R  
####删除指令
dh 向后删除一个字符  
dl 向前删除一个字符  
db 向后删除一个词  
dw 向前删除一个词  
dB 向后删除一个非空区域  
dW向前删除一个非空区域  
d$ 删除到行尾  
d0 删除到行首  

D d$  
dd 0d$  
C c$  
cc 0c$  
X dl  
x dh  
####历史中穿梭
k - backward  
j + forward  
G   move to line given by repeat count  
/string search backward  
?string search forward  
n       repeat the same as previous  
N       repeat in opposite direction of previous  
####字符寻找
fx move right   
Fx move left  
tx move right (until, back one space)  
Tx move left (until, forward one space)  
; redo last finding  
, redo last finding in opposite direction  
####文本补全
ESC \  
*  
####混杂命令
~ 翻转大小写  
- 将上一个命令的最后一个参数添加到当前行  
ctrl-l 清空屏幕  
\# 注释符号  
注意上述命令均需在vi的命令模式下输入，不能在输入模式下输入  
#####fc
fc -l列出之前的命令，带编号。  
####bash快捷键
C-A 行开始  
C-E 行结束  
C-F 右移  
C-B 左移  
C-K 整行删除  
C-P 向上翻阅历史命令  
C-N 向下翻阅历史命令  
C-R 搜索历史命令  
####bash自定义中最重要四种特征
特殊文件：.bashrc,.bash_log,.bash_profile  
别名：alias  
变量：var=value(等号两侧不能有空格）  
选项  
