---
layout: post
title: "linux_awk_study"
category: 
tags: [linux awk]
---
{% include JB/setup %}
##awk
awk以花括号分隔命令，命令以'{}'围起来？

其中print与print $0的作用相同，都是打印整整一行。print $1 $2则是打印改行的第1个和第2个类容。

-F用来标志分隔符是什么，如下面

awk -F ":" '{print $1 $2}' /etc/passwd

意味着以:（冒号）为分隔符，打印/etc/passwd每行的第一个和第二个字符。

在外部脚本中使用FS这个参量来设置分隔符。

BEGIN和END区域

BEGIN区域可以用于设置在awk进行文本处理之前处理，如初始化FS（字段分隔符）变量，打印页眉等。
END区域可以用于设置awk在处理文本完之后进行汇总处理。

###使用正则表达式

awk '/xiong/ {print }' a

打印文件a中含有xiong的一整行，这个可以与正则表达式紧密的结合。如下行，打印含有浮点数的整行。

awk '/\[0-9\]+\\.\[0-9\]\*/ {print}' a

###使用判断符号
awk支持==，>,<,>=,<=,!=同时它还支持~(包含),!~(不包含)。可以使用这些条件符号进行判断，来进行输出处理。如下行：

awk '$1 == "xiong" {print $3}' a

仅仅在a文件的第一个字符为xiong时输出改行的第3个变量。

awk '$5 ~ /root/ {print $3}' a

仅仅在a文件的第5个参数含有root时输出第3个参量。

awk也支持类似于c语言的条件判断处理，如上面的那条语句可以写成下面的判断形式

{
    if( $5 ~ /root/) {
        print $3
    }
}


###awk算术支持
awk支持+,-,*,/,%,^,++,--,+=,-=,*=,/=。
甚至还支持^=,%=

###awk的分隔符
awk的分隔符支持正则表达式，使用FS这个变量表明分隔符为什么。

如下面，表明分隔符为多个tab键

FS="\t+"

###awk符号设置
FS：输入分隔符，在单行的时候和RS可以认为为相同的
RS：记录分隔符
OFS：输出分隔符号，默认为空白
ORS：输出记录分隔符，默认为换行
NF：区域数，当前记录的区域数目。由RS来决定一条记录区域数目有多少。
RS：记录数，在每个记录都是单行时，RS与行数是相等的，但是在多行的记录时，这两个值就不等了。

###awk循环设置
awk拥有while，do...while,for循环，与c语言类似。同时awk也拥有break和continue的语句，可以进行循环的退出。
###awk指针与数组
awk的数组从下标1开始。

如下所示：

for ( x in myarray ) {
	print myarray[x]
}

上述的输出不知道哪个会放在前面，即无法判断是myarray[1]先出现还是myarray[2]先出现，它是无序的。

awk的数组下标可以是字符串，比如

myarr["1"]="abc"
print myarr[1]
print myarr["1"]

这两个的输出结果一致，都是abc。

myarr["hello"] = "abc"

数组也可以这样定义，即数组的下标可以是字符串，不一定得是数字。

使用delete可以删除一个数组中的元素，比如

delete fooarray[1]

将会删除fooarray[1]这个数组元素。

###awk格式化输出
awk含有类似c语言的printf和sprintf

###awk字符串处理
length(mystring) 输出字符串的长度

index(mystring, substring) 输出substring在mystring中出现的位置值，若未找到匹配则返回0

tolower(mystring) 将mystring的字母变成小写

toupper(mystring) 将mystring的字母变为大写

substr(mystring, startpos, maxlen) 输出mystring中的从startpos位置开始的maxlen个字符。注意startpos+maxlen的值应该小于length(mystring)。

mach(mystring,/substring/) 与index类似，但是它可以使用正则表达式，同时它会返回RSTART和RLENGTH这两个值用来表明开始位置以及匹配的长度。若没有匹配的则RSTART为0，RLENGTH的大小为-1.

sub(regexp, replstring, mystring)查找mystring中首先出现的匹配regexp的字符串，并且替换为repstring。

gsub(regexp, replstring, mystring)功能与sub()类似，但是它完成全局的替代，不仅仅替代第一个出现的字符串。

split(mystring,myarray,"splitor")字符的分隔，将mystring中的字符按照"splitor"的要求进行分割，存储到myarray的数组中，这个数组是一个以整形数为下标的数组，split的返回值为最终形成的数组的长度。

在调用length(),sub(),gsub()函数时，可以省略最后的一个参数，awk将会默认使用$0代替。
